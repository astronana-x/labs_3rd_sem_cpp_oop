#pragma once
#include <iostream>
#include "Node/Node.h"
#include "String/String.h"

class Stack{
public:
    Stack() : top(nullptr), size(0) {}
    ~Stack();

    void push(String* obj);
    void pop();
    String* find_by_index(int index) const;
    int find_by_obj(String* obj) const;

    Node* get_top() const { return top; }
    size_t get_size() const { return size; }
    char* to_string() const;

private:
    Node* top;
    size_t size;
};
