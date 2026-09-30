#include "ConfigParser.h"
#include <iostream>
#include <fstream>

ConfigParser::ConfigParser()
{
}

AppConfig ConfigParser::parse(int argc, char* argv[])
{
    AppConfig config;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--vfs" || arg == "-v")
        {
            if (i + 1 < argc)
            {
                config.pathVFS = argv[i + 1];
                config.hasVFS = true;
                i++;
            }
            else
            {
                std::cerr << "Ошибка: после флага --vfs должен быть путь" << std::endl;
            }
        }
        else if (arg == "--script" || arg == "-s")
        {
            if (i + 1 < argc)
            {
                config.pathStartScript = argv[i + 1];
                config.hasScript = true;
                i++;
            }
            else
            {
                std::cerr << "Ошибка: после флага --script должен быть путь" << std::endl;
            }
        }
        else if (arg == "--help" || arg == "-h")
        {
            std::cout << "Использование: shell-emulator [опции]\n\n"
                      << "Опции:\n"
                      << "  --vfs <путь>, -v <путь>        Путь к файлу VFS\n"
                      << "  --script <путь>, -s <путь>     Путь к стартовому скрипту\n"
                      << "  --help, -h                      Показать эту справку\n";
        }
    }

    return config;
}

void ConfigParser::printConfig(const AppConfig& config) const
{
    std::cout << "\n=== Конфигурация эмулятора ===" << std::endl;
    std::cout << "VFS: " << (config.hasVFS ? config.pathVFS : "не указан") << std::endl;
    std::cout << "Стартовый скрипт: " << (config.hasScript ? config.pathStartScript : "не указан") << std::endl;
    std::cout << "==============================\n" << std::endl;
}