#include "ScriptExecutor.h"
#include "Parser.h"
#include "Executor.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

ScriptExecutor::ScriptExecutor()
{
    scriptLines.clear();
    errorMessage = "";
}

bool ScriptExecutor::loadScript(const std::string& filepath)
{
    scriptLines.clear();
    errorMessage = "";

    std::ifstream file(filepath);

    if (!file.is_open())
    {
        errorMessage = "Ошибка: не удалось открыть файл скрипта: " + filepath;
        std::cerr << errorMessage << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        scriptLines.push_back(line);
    }

    file.close();

    if (scriptLines.empty())
    {
        errorMessage = "Предупреждение: скрипт пуст или не содержит команд";
        return true;
    }

    return true;
}

bool ScriptExecutor::executeScript()
{
    if (scriptLines.empty())
    {
        errorMessage = "Ошибка: скрипт не загружен";
        std::cerr << errorMessage << std::endl;
        return false;
    }

    bool hasError = false;

    std::cout << "\n[СКРИПТ] Начало выполнения\n" << std::endl;

    for (size_t i = 0; i < scriptLines.size(); ++i)
    {
        std::string line = scriptLines[i];

        line = trim(line);

        if (isEmpty(line))
        {
            continue;
        }

        if (isComment(line))
        {
            continue;
        }

        std::cout << "user@host:~$ " << line << std::endl;

        ParseResult parseResult = Parser::parse(line);

        if (!parseResult.success)
        {
            std::cerr << parseResult.errorMessage << std::endl;
            hasError = true;
            std::cout << std::endl;
            continue;
        }

        ExecutionResult execResult = Executor::execute(parseResult.tokens);

        if (!execResult.output.empty())
        {
            if (execResult.isError)
            {
                std::cerr << execResult.output << std::endl;
                hasError = true;
            }
            else
            {
                std::cout << execResult.output << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << std::endl;
    }

    std::cout << "[СКРИПТ] Завершено\n" << std::endl;

    return !hasError;
}

bool ScriptExecutor::isComment(const std::string& line) const
{
    if (line.empty())
    {
        return false;
    }

    return line[0] == '#';
}

bool ScriptExecutor::isEmpty(const std::string& line) const
{
    if (line.empty())
    {
        return true;
    }

    for (char c : line)
    {
        if (!std::isspace(c))
        {
            return false;
        }
    }

    return true;
}

std::string ScriptExecutor::trim(const std::string& str) const
{
    size_t start = str.find_first_not_of(" \t\n\r");

    if (start == std::string::npos)
    {
        return "";
    }

    size_t end = str.find_last_not_of(" \t\n\r");

    return str.substr(start, end - start + 1);
}

std::string ScriptExecutor::getError() const
{
    return errorMessage;
}