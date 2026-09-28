#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <vector>

struct ExecutionResult {
    bool shouldExit;
    std::string output;
    bool isError;
};

class Executor {
public:
    static ExecutionResult execute(const std::vector<std::string>& tokens);
};

#endif // EXECUTOR_HPP