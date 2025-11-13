#pragma once
#include "String/String.h"

template <typename T>
class NodeNew {
public:
    explicit NodeNew(T* data, NodeNew<T>* next = nullptr);
    ~NodeNew();

    T* get_data() const;
    NodeNew<T>* get_next() const;
    void set_next(NodeNew<T>* new_next);

    // Запрещаем копирование
    NodeNew(const NodeNew&) = delete;
    NodeNew& operator=(const NodeNew&) = delete;

private:
    T* data;
    NodeNew<T>* next;
};

#include "NodeNew.hpp"