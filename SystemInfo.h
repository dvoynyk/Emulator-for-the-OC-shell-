#ifndef SYSTEMINFO_HPP
#define SYSTEMINFO_HPP

#include <string>

class SystemInfo {
public:
    static std::string getUsername();
    static std::string getHostname();
    static std::string getWindowTitle();
};

#endif // SYSTEMINFO_HPP