#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>

struct AppConfig
{
    std::string pathVFS;
    std::string pathStartScript;
    bool hasVFS = false;
    bool hasScript = false;
};

class ConfigParser
{
public:
    ConfigParser();

    AppConfig parse(int argc, char* argv[]);
    void printConfig(const AppConfig& config) const;
};

#endif // CONFIGPARSER_H