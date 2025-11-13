#pragma once
#include "NodeNew.h"

template <typename T>
NodeNew<T>::NodeNew(T* data, NodeNew<T>* next) : data(data), next(next) {}

template <typename T>
NodeNew<T>::~NodeNew() {}

template <typename T>
T* NodeNew<T>::get_data() const { return data; }

template <typename T>
NodeNew<T>* NodeNew<T>::get_next() const { return next; }

template <typename T>
void NodeNew<T>::set_next(NodeNew<T>* new_next) { next = new_next; }
