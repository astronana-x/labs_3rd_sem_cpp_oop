#include "ToDoList.h"
using namespace std;

//Лабораторная работа 6
void ToDoList :: validate_time(const char* time) {
    if (strlen(time) != 5 || time[2] != ':')
        throw invalid_argument("Invalid time format (expected hh:mm)");

    if (!isdigit(time[0]) || !isdigit(time[1]) || !isdigit(time[3]) || !isdigit(time[4]))
        throw invalid_argument("Invalid characters in time (expected digits)");

    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
        throw invalid_argument("Invalid time value (out of range 00:00–23:59)");
}

ToDoList :: ToDoList() : String(), start_time(), end_time(), done(false) {}

ToDoList :: ToDoList(const char* task, const char* start, const char* end, bool done) :
    String(task), start_time(start), end_time(end), done(done) {
    validate_time(start);
    validate_time(end);
}

ToDoList::ToDoList(const ToDoList& other)
    : String(other),
      start_time(other.start_time),
      end_time(other.end_time),
      done(other.done) {}

ToDoList& ToDoList::operator=(const ToDoList& other) {
    if (this == &other) return *this;

    String::operator=(other);
    start_time = other.start_time;
    end_time = other.end_time;
    done = other.done;
    return *this;
}

char* ToDoList::to_string() const {
    String res("Task: ");
    res = res + get_string();
    res = res + " | Time: " + start_time + "-" + end_time;
    res = res + " | Status: "; res = res + (done ? "Completed" : "Not completed");
    char* str = new char[res.get_length() + 1];
    strcpy(str, res.get_string());
    return str;
}

/*ostream& operator<<(ostream& os, const ToDoList& obj) {
    os << "Task: " << obj.get_string() << " |Time: " << obj.start_time << "-" << obj.end_time
       << " | Status: " << (obj.done ? "Completed" : "Not completed");
    return os;
}*/