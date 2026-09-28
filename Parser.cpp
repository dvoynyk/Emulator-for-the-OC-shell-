#include "Parser.h"

ParseResult Parser::parse(const std::string& input) {
    ParseResult result;
    result.success = true;

    std::string currentToken;
    char activeQuote = 0;

    for (size_t i = 0; i < input.length(); ++i) {
        char ch = input[i];

        if (activeQuote != 0) {
            if (ch == activeQuote) {
                activeQuote = 0;
            } else {
                currentToken += ch;
            }
        } else {
            if (ch == '\'' || ch == '"') {
                activeQuote = ch;
            } else if (std::isspace(static_cast<unsigned char>(ch))) {
                if (!currentToken.empty()) {
                    result.tokens.push_back(currentToken);
                    currentToken.clear();
                }
            } else {
                currentToken += ch;
            }
        }
    }

    if (activeQuote != 0) {
        result.success = false;
        result.errorMessage = "Ошибка синтаксиса: незакрытая кавычка (" + std::string(1, activeQuote) + ")";
        return result;
    }

    if (!currentToken.empty()) {
        result.tokens.push_back(currentToken);
    }

    return result;
}