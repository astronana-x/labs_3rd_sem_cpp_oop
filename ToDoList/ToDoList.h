#include "String/String.h"
#include <cctype>
#pragma once

class ToDoList : public String {
public:
    ToDoList();
    ToDoList(const char* task, const char* start, const char* end, bool completed = false);
    ToDoList(const ToDoList& other);

    ToDoList& operator=(const ToDoList& other);
    char* to_string() const override;

    //friend ostream& operator<<(ostream& os, const ToDoList& obj);

    void mark_done() { done = true; }
    void mark_undone() { done = false; }
    bool is_done() const { return done; }


private:
    static void validate_time(const char* time);
    String start_time;
    String end_time;
    bool done;
};