#include "Base64Decoder.h"

const std::string Base64Decoder::base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int Base64Decoder::charToValue(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

std::vector<unsigned char> Base64Decoder::decode(const std::string& encoded) {
    std::vector<unsigned char> decoded;

    std::vector<int> values;
    for (unsigned char c : encoded) {
        if (c == '=') break;
        int value = charToValue(c);
        if (value != -1) {
            values.push_back(value);
        }
    }

    for (size_t i = 0; i < values.size(); i += 4) {
        int b1 = values[i];
        int b2 = (i + 1 < values.size()) ? values[i + 1] : 0;
        int b3 = (i + 2 < values.size()) ? values[i + 2] : 0;
        int b4 = (i + 3 < values.size()) ? values[i + 3] : 0;

        decoded.push_back((b1 << 2) | (b2 >> 4));

        if (i + 2 < values.size()) {
            decoded.push_back((b2 << 4) | (b3 >> 2));
        }

        if (i + 3 < values.size()) {
            decoded.push_back((b3 << 6) | b4);
        }
    }

    return decoded;
}