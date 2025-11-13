#pragma once
#include "NodeNew/NodeNew.h"
#include <sstream>

using namespace std;

template <typename T>
class StackNew {
public:
    StackNew();
    ~StackNew();

    void push(T* obj);
    void pop();
    T* find_by_index(int index) const;
    char* to_string() const;

    NodeNew<T>* get_top() const;
    size_t get_size() const;

private:
    NodeNew<T>* top;
    size_t size;
};

//для всех типов с to_string()
template <typename T>
char* convert_to_cstr(const T* obj) {
    return obj->to_string();
}

// для int
template <>
char* convert_to_cstr<int>(const int* obj) {
    char* buf = new char[256];
    sprintf(buf, "%d", *obj);
    return buf;
}

// для float
template <>
char* convert_to_cstr<float>(const float* obj) {
    char* buf = new char[256];
    sprintf(buf, "%.2f", *obj);
    return buf;
}

// для double
template <>
char* convert_to_cstr<double>(const double* obj) {
    char* buf = new char[256];
    sprintf(buf, "%.2f", *obj);
    return buf;
}

/*
template <typename T>
char* convert_to_cstr(const T* obj) {
    stringstream ss;
    ss << *obj;
    string s = ss.str();
    char* buf = new char[s.size() + 1];
    strcpy(buf, s.c_str());
    return buf;
}*/

#include "StackNew.hpp"
