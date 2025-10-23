#include "Stack.h"

Stack::~Stack() {
    while (top) {
        Node* temp = top;
        top = top->get_next();
        delete temp->get_data();
        delete temp;
    }
}

void Stack::push(String* obj)
{
    try
    {
        Node* newNode = new Node(obj, top);
        top = newNode;
        size++;
    }
    catch (bad_alloc& e)
    {
        cout << "Error in push(): " << e.what() << endl;
    }
}

void Stack::pop() {
    if (!top) return;
    Node* tmp = top;
    top = top->get_next();
    delete tmp->get_data();
    delete tmp;
    size--;
}

//Лаб.6 Исключение - Индекс за пределами диапазона
String* Stack::find_by_index(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("index out of range");
    }
    Node* current = top;
    for (int i = 0; i < index; i++) {
        current = current->get_next();
    }
    return current->get_data();
}

int Stack::find_by_obj(String* obj) const {
    if (!obj) return -1;

    Node* current = top;
    int index = 0;

    while (current) {
        const char* str1 = current->get_data()->get_string();
        const char* str2 = obj->get_string();

        if (strcmp(str1, str2) == 0) {
            return index;
        }

        current = current->get_next();
        index++;
    }

    return -1;
}

char* Stack::to_string() const {
    if (!top) {
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }

    String result;
    Node* current = top;

    while (current) {
        result = result + current->get_data()->to_string();
        if (current->get_next()) {
            result = result + "\n";
        }
        current = current->get_next();
    }

    return result.to_string();
}