#include "BinaryString.h"
#include <iostream>

//конструктор по умолчанию:
BinaryString::BinaryString(): String(){ }
//конструктор с параметром:
BinaryString::BinaryString(const char* str): String(str){ };
//конструктор копирования:
BinaryString::BinaryString(const String& other): String(other){ };

//представление строки в двоичном формате:
String BinaryString:: to_binary() const{
    const char* s = get_string();
    String res("");
    for (size_t i = 0; i < get_length(); i++) {
        unsigned char s1 = s[i];
        for (int bit = 7; bit >= 0; --bit) {
            res = res + ((s1 & (1 << bit)) ? "1" : "0");
        }
        if (i < get_length() - 1) {
            res = res + " ";
        }
    }
    save_result(res);
    return res;
}

//представление из бинарного формата в строковый:
String BinaryString::from_binary() {
    const char* s = result.get_string();
    String res("");
    unsigned char s1 = 0; //накопитель для 1 байта
    int bit_count = 0;
    for (size_t i = 0; i < result.get_length(); i++) {
        if (s[i] == '0' || s[i] == '1') {
            s1 = (s1 << 1) | (s[i] - '0');
            bit_count++;
            if (bit_count == 8) {
                char ch[2] = {(char)s1, '\0'};
                res = res + ch;
                bit_count = 0;
                s1 = 0;
            }
        }
    }
    save_result(res);
    return res;
}

char* BinaryString::to_string() const {
    to_binary();
    return result.to_string();
}