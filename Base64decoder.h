#ifndef BASE64DECODER_H
#define BASE64DECODER_H

#include <string>
#include <vector>

class Base64Decoder {
public:
    // Декодировать base64 строку в бинарные данные
    static std::vector<unsigned char> decode(const std::string& encoded);

    // Кодировать бинарные данные в base64 строку
    static std::string encode(const std::vector<unsigned char>& data);

private:
    static const std::string base64_chars;
    static int charToValue(char c);
};

#endif // BASE64DECODER_H