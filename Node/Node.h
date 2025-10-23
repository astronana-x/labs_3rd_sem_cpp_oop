#pragma once
#include "String/String.h"

class Node {
public:
    explicit Node(String* obj, Node* next_node=nullptr);
    ~Node();

    String* get_data() const;
    Node* get_next() const;
    void set_next(Node* new_node);

    //запертим копирование, чтобы избежать двойного удаления
    Node(const Node& other) = delete;
    Node& operator=(const Node& other) = delete;


private:
    String* data;
    Node* next;
};
