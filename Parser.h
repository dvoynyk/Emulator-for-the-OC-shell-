#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

struct ParseResult {
    bool success;
    std::vector<std::string> tokens;
    std::string errorMessage;
};

class Parser {
public:
    static ParseResult parse(const std::string& input);
};

#endif // PARSER_HPP