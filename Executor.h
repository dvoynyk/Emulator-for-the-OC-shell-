#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <string>
#include <vector>
#include <memory>

class VFSManager;

struct ExecutionResult {
    bool shouldExit;
    std::string output;
    bool isError;
};

class Executor {
public:
    static ExecutionResult execute(const std::vector<std::string>& tokens, std::shared_ptr<VFSManager> vfs = nullptr);
};

#endif // EXECUTOR_H