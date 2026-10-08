#include "Executor.h"
#include "VFSManager.h"
#include <memory>

ExecutionResult Executor::execute(const std::vector<std::string>& tokens, std::shared_ptr<VFSManager> vfs) {
    ExecutionResult result;
    result.shouldExit = false;
    result.isError = false;

    if (tokens.empty()) {
        result.output = "";
        return result;
    }

    const std::string& command = tokens[0];

    if (command == "exit") {
        result.shouldExit = true;
        result.output = "Завершение работы эмулятора...";
        return result;
    }

    if (command == "ls") {
        if (!vfs) {
            // Без VFS - заглушка
            result.output = "[Заглушка команды ls]\nПереданные аргументы (" +
                            std::to_string(tokens.size() - 1) + "): ";

            for (size_t i = 1; i < tokens.size(); ++i) {
                result.output += "[" + tokens[i] + "] ";
            }
        } else {
            // С VFS - реальная реализация
            std::string path = tokens.size() > 1 ? tokens[1] : "";
            VFSResult vfsResult = vfs->listDirectory(path);

            if (!vfsResult.success) {
                result.isError = true;
                result.output = vfsResult.message;
            } else {
                result.output = "Содержимое директории";
                if (!path.empty()) {
                    result.output += " (" + path + ")";
                } else {
                    result.output += " (" + vfs->getCurrentPath() + ")";
                }
                result.output += ":\n";

                for (const auto& item : vfsResult.items) {
                    if (item->isDirectory) {
                        result.output += "  [DIR]  " + item->name + "\n";
                    } else {
                        result.output += "  [FILE] " + item->name +
                                         " (" + std::to_string(item->content.size()) + " bytes)\n";
                    }
                }

                if (vfsResult.items.empty()) {
                    result.output += "  (директория пуста)\n";
                }
            }
        }
        return result;
    }

    if (command == "cd") {
        if (!vfs) {
            // Без VFS - заглушка
            result.output = "[Заглушка команды cd]\nTarget directory: ";
            if (tokens.size() > 1) {
                result.output += tokens[1];
            } else {
                result.output += "<не указана, переход в домашнюю директорию>";
            }
        } else {
            // С VFS - реальная реализация
            if (tokens.size() < 2) {
                result.output = "Текущая директория: " + vfs->getCurrentPath();
            } else {
                if (vfs->changeDirectory(tokens[1])) {
                    result.output = "Переход в директорию: " + tokens[1];
                } else {
                    result.isError = true;
                    result.output = vfs->getError();
                }
            }
        }
        return result;
    }

    if (command == "pwd") {
        if (!vfs) {
            result.output = "[Заглушка команды pwd]";
        } else {
            result.output = "Текущий путь: " + vfs->getCurrentPath();
        }
        return result;
    }

    if (command == "cat") {
        if (!vfs) {
            result.isError = true;
            result.output = "Ошибка: команда cat требует загруженный VFS";
        } else {
            if (tokens.size() < 2) {
                result.isError = true;
                result.output = "Ошибка: укажите имя файла";
            } else {
                VFSResult vfsResult = vfs->getFileContent(tokens[1]);

                if (!vfsResult.success) {
                    result.isError = true;
                    result.output = vfsResult.message;
                } else {
                    // Преобразуем содержимое в строку
                    result.output = "Содержимое файла '" + tokens[1] + "':\n";
                    result.output += std::string(vfsResult.data.begin(), vfsResult.data.end());
                }
            }
        }
        return result;
    }

    result.isError = true;
    result.output = "Ошибка: неизвестная команда \"" + command + "\"";
    return result;
}