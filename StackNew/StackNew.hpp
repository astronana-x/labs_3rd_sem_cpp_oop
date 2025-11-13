#pragma once
#include "StackNew.h"
#include <stdexcept>
#include <iostream>
#include <cstring>

template <typename T>
StackNew<T>::StackNew() : top(nullptr), size(0) {}

template <typename T>
StackNew<T>::~StackNew() {
    while (top) {
        NodeNew<T>* tmp = top;
        top = top->get_next();
        delete tmp->get_data();
        delete tmp;
    }
}

template <typename T>
void StackNew<T>::push(T* obj) {
    NodeNew<T>* node = new NodeNew<T>(obj, top);
    top = node;
    size++;
}

template <typename T>
void StackNew<T>::pop() {
    if (!top) return;
    NodeNew<T>* tmp = top;
    top = top->get_next();
    delete tmp->get_data();
    delete tmp;
    size--;
}

template <typename T>
T* StackNew<T>::find_by_index(int index) const {
    if (index < 0 || index >= size) throw out_of_range("index out of range");
    NodeNew<T>* current = top;
    for (int i = 0; i < index; ++i) {
        current = current->get_next();
    }
    return current->get_data();
}

template <typename T>
NodeNew<T>* StackNew<T>::get_top() const { return top; }

template <typename T>
size_t StackNew<T>::get_size() const { return size; }

template <typename T>
char* StackNew<T>::to_string() const {
    if (!top) {
        return new char[1]{'\0'};
    }

    String result;
    NodeNew<T>* current = top;

    while (current) {
        if (current != top)
            result = result + "\n";

        T* data = current->get_data();
        if (data) {
            char* str_data = convert_to_cstr<T>(data);
            result = result + str_data;
            delete[] str_data;
        } else {
            result = result + "[null]";
        }

        current = current->get_next();
    }

    return result.to_string();
}
