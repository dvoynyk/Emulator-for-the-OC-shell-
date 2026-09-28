#include "Executor.h"

ExecutionResult Executor::execute(const std::vector<std::string>& tokens) {
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
        result.output = "[Заглушка команды ls]\nПереданные аргументы (" +
                        std::to_string(tokens.size() - 1) + "): ";

        for (size_t i = 1; i < tokens.size(); ++i) {
            result.output += "[" + tokens[i] + "] ";
        }
        return result;
    }

    if (command == "cd") {
        result.output = "[Заглушка команды cd]\nTarget directory: ";
        if (tokens.size() > 1) {
            result.output += tokens[1];
        } else {
            result.output += "<не указана, переход в домашнюю директорию>";
        }
        return result;
    }

    result.isError = true;
    result.output = "Ошибка: неизвестная команда \"" + command + "\"";
    return result;
}