#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include "Index/Index.h"

using namespace std;

// Лабораторная работа 2
class Index;

//Лабораторная работа 1
class String{
public:
    String();
    explicit String(const char* str);
    String(const String& other);
    virtual ~String();

    void set_string(const char* str);
    int count_words() const;
    const char* get_string() const;
    int find_substring(const char* substr);
    static int get_obj_count();
    virtual char* to_string() const;

// Лабораторная работа 2
    static const size_t start_length;
    static const size_t resize_factor;
    static const size_t max_length_limit;
    static const char value_error;

    // Перегрузки операторов
    String operator+(const char* s) const;
    String operator+(const String& obj) const;
    String operator-(const char* substr) const;
    String& operator=(const String& other);

    // Индексирование + friend class
    Index operator[](size_t indx);   // для записи
    char operator[](size_t indx) const; // для чтения

    // Методы для доступа к приватным полям из Index
    size_t get_length() const { return length; }
    size_t get_max_length() const { return max_length; }
    char* get_arr() { return arr; }
    void set_length(size_t new_length) { length = new_length; }

//Лабораторная работа 3
    //перегрузка операторов ввода/вывода в т.ч бинарников
    friend ostream& operator<<(ostream& os, const String& obj);
    friend istream& operator>>(istream& is, String& obj);
    friend ofstream& bin_out(ofstream& os, const String& s);
    friend ifstream& bin_in(ifstream& is, String& s);

private:
    char* arr;           // динамический массив
    size_t max_length;   // текущий размер массива
    size_t length;       // фактическая длина строки

    static int count;    // количество объектов

    void _resize_array(size_t new_size); // увеличение размера массива

    friend class Index;
};
