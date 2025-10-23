#pragma once
#include "String/String.h"


class BinaryString :public String {
public:
    //конструктор по умолчанию:
    BinaryString();
    //конструктор с параметром:
    BinaryString(const char* str);
    //конструктор копирования:
    BinaryString(const String& other);

    //представление строки в двоичном формате:
    String to_binary() const;
    //представление из бинарного формата в строковый:
    String from_binary();

    String get_result() const{return result;}

    char* to_string() const override;

private:
    mutable String result;

    void save_result(const String& res) const {result = res;}
};

