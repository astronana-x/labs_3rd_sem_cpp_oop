#include "Index.h"
#include "String/String.h"
#include <cstring>


Index::operator char() const {
    if (!str || index >= str->get_length()) {
        return String::value_error;
    }
    return str->get_arr()[index];
}

char Index::operator=(char right) {
    if (!str || index >= String::max_length_limit) {
        return right;
    }

    if (index >= str->get_max_length()) {
        str->_resize_array(index + 1);
    }

    if (index >= str->get_length()) {
        for (size_t i = str->get_length(); i < index; ++i) {
            str->get_arr()[i] = '\0';
        }
        str->set_length(index + 1);
    }

    // присваиваем символ
    str->get_arr()[index] = right;

    if (str->get_length() < str->get_max_length()) {
        str->get_arr()[str->get_length()] = '\0';
    }

    return right;
}
