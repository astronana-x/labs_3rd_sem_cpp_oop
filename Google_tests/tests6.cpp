#include "Stack/Stack.h"
#include "String/String.h"
#include "ToDoList/ToDoList.h"
#include "gtest/gtest.h"
#include <stdexcept>
using namespace std;

// Warning: при запуске тестов - убедиться, что они не отключены в CMakeLists.txt!

TEST(LAB6, StackIndexException) {
    Stack stack;

    stack.push(new String("First"));
    stack.push(new String("Second"));

    EXPECT_EQ(stack.get_size(), 2);

    EXPECT_NO_THROW({
        String* obj1 = stack.find_by_index(0);
        EXPECT_NE(obj1, nullptr);
        EXPECT_STREQ(obj1->get_string(), "Second");
    });

    EXPECT_THROW(stack.find_by_index(5), out_of_range);
    EXPECT_THROW(stack.find_by_index(-1), out_of_range);
    EXPECT_THROW(stack.find_by_index(2), out_of_range);

    try {
        stack.find_by_index(10);
    }
    catch (const exception& ex) {
        EXPECT_STREQ(ex.what(), "index out of range");
    }
}

TEST(LAB6, TimeExpectation) {
    try {
        ToDoList task("Go to the cinema","9:00","10:00",true);
    }
    catch (const exception& ex) {
        EXPECT_STREQ(ex.what(), "Invalid time format (expected hh:mm)");
    }

    try {
        ToDoList task("Go to the cinema","89:00","10:00",true);
    }
    catch (const exception& ex) {
        EXPECT_STREQ(ex.what(), "Invalid time value (out of range 00:00–23:59)");
    }

    try {
        ToDoList task("Go to the cinema","hh:mm","10:00",true);
    }
    catch (const exception& ex) {
        EXPECT_STREQ(ex.what(), "Invalid characters in time (expected digits)");
    }
    catch (...) {
        FAIL() << "Caught completely unknown exception type in catch-all block";
    }
}
