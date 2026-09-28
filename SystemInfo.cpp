#include "SystemInfo.h"
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

std::string SystemInfo::getUsername() {
    const char* user = std::getenv("USER");
    if (!user) user = std::getenv("USERNAME");
    if (user) return std::string(user);
    return "user";
}

std::string SystemInfo::getHostname() {
    const char* host = std::getenv("HOSTNAME");
    if (!host) host = std::getenv("COMPUTERNAME");
    if (host) return std::string(host);

#ifdef _WIN32
    char buffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(buffer);
    if (GetComputerNameA(buffer, &size)) return std::string(buffer);
#else
    char buffer[HOST_NAME_MAX];
    if (gethostname(buffer, sizeof(buffer)) == 0) return std::string(buffer);
#endif

    return "localhost";
}

std::string SystemInfo::getWindowTitle() {
    return "Эмулятор - [" + getUsername() + "@" + getHostname() + "]";
}