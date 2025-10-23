#pragma once
#include "String/String.h"

class String; // вперед объявляем String, чтобы можно было использовать указатель

class Index {

public:
    Index() : str(nullptr), index(0) {}
    Index(String* s, size_t indx) : str(s), index(indx) {}

    // присваивание символа
    char operator=(char right);

    // чтение символа
    operator char() const;

private:

    String* str;
    size_t index;
};
