#include "binary_utils.h"
#include <bitset>

std::string to_binary_string(const std::string& str) {
    std::string result;
    for (std::string::size_type i = 0; i < str.size(); ++i) {
        result += std::bitset<8>(static_cast<unsigned char>(str[i])).to_string();
        if (i < str.size() - 1) {
            result += " ";
        }
    }
    return result;
}