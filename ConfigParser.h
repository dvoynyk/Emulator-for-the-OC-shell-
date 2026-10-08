#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include <memory>

class VFSManager;

struct AppConfig
{
    std::string pathVFS;
    std::string pathStartScript;
    bool hasVFS = false;
    bool hasScript = false;
    std::shared_ptr<VFSManager> vfsManager;
};

class ConfigParser
{
public:
    ConfigParser();

    AppConfig parse(int argc, char* argv[]);
    void printConfig(const AppConfig& config) const;
};

#endif // CONFIGPARSER_H