#ifndef SCRIPTEXECUTOR_H
#define SCRIPTEXECUTOR_H

#include <string>
#include <vector>

class ScriptExecutor
{
public:
    ScriptExecutor();

    bool loadScript(const std::string& filepath);
    bool executeScript();
    std::string getError() const;

private:
    std::vector<std::string> scriptLines;
    std::string errorMessage;

    bool isComment(const std::string& line) const;
    bool isEmpty(const std::string& line) const;
    std::string trim(const std::string& str) const;
};

#endif // SCRIPTEXECUTOR_H