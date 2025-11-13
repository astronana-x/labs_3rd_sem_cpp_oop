#include "StackNew/StackNew.h"
#include "String/String.h"
#include <gtest/gtest.h>
#include "ToDoList/ToDoList.h"
#include "BinaryString/BinaryString.h"

// Warning: при запуске тестов - убедиться, что они не отключены в CMakeLists.txt!

//int
TEST(LAB7, StackNewInt) {
    StackNew<int> stack;

    // push
    int* a = new int(10);
    int* b = new int(20);
    stack.push(a);
    stack.push(b);
    EXPECT_EQ(stack.get_size(), 2);

    // find_by_index
    EXPECT_EQ(*stack.find_by_index(0), 20);
    EXPECT_EQ(*stack.find_by_index(1), 10);

    // to_string
    char* str = stack.to_string();
    //cout << str << endl;
    EXPECT_STRNE(str, "");
    delete[] str;

    // pop
    stack.pop();
    EXPECT_EQ(stack.get_size(), 1);
    EXPECT_EQ(*stack.find_by_index(0), 10);

    stack.pop();
    EXPECT_EQ(stack.get_size(), 0);
}

//float
TEST(LAB7, StackNewFloat) {
    StackNew<float> stack;

    float* a = new float(4.95f);
    float* b = new float(5.33f);
    stack.push(a);
    stack.push(b);
    EXPECT_EQ(stack.get_size(), 2);

    EXPECT_FLOAT_EQ(*stack.find_by_index(0), 5.33f);
    EXPECT_FLOAT_EQ(*stack.find_by_index(1), 4.95f);

    char* str = stack.to_string();
    //cout << str << endl;
    EXPECT_STRNE(str, "");
    delete[] str;

    stack.pop();
    stack.pop();
    EXPECT_EQ(stack.get_size(), 0);
}

//String
TEST(LAB7, StackNewString) {
    StackNew<String> stack;

    String* s1 = new String("First");
    String* s2 = new String("Second");
    stack.push(s1);
    stack.push(s2);
    EXPECT_EQ(stack.get_size(), 2);

    EXPECT_STREQ(stack.find_by_index(0)->get_string(), "Second");
    EXPECT_STREQ(stack.find_by_index(1)->get_string(), "First");

    char* str = stack.to_string();
    //cout << str << endl;
    EXPECT_STRNE(str, "");
    EXPECT_STRNE(strstr(str, "First"), nullptr);
    EXPECT_STRNE(strstr(str, "Second"), nullptr);
    delete[] str;

    stack.pop();
    stack.pop();
    EXPECT_EQ(stack.get_size(), 0);
}

// тест полиморфизма с разными типами объектов
TEST(LAB7, PolymorphismTest) {
    StackNew<String> stack;

    // Создаем объекты разных типов, но храним как String*
    String* simple_str = new String("Simple string");
    String* todo = new ToDoList("Meeting", "10:00", "11:00", false);
    String* binary = new BinaryString("Test");

    stack.push(simple_str);
    stack.push(todo);
    stack.push(binary);

    EXPECT_EQ(stack.get_size(), 3);

    // Проверяем, что to_string() работает полиморно
    String* obj1 = stack.find_by_index(0);
    String* obj2 = stack.find_by_index(1);
    String* obj3 = stack.find_by_index(2);

    // Проверяем что объекты на месте
    ASSERT_NE(obj1, nullptr);
    ASSERT_NE(obj2, nullptr);
    ASSERT_NE(obj3, nullptr);

    char* str1 = obj1->to_string();
    char* str2 = obj2->to_string();
    char* str3 = obj3->to_string();

    EXPECT_NE(str1, nullptr);
    EXPECT_NE(str2, nullptr);
    EXPECT_NE(str3, nullptr);

    // Проверяем, что строки не пустые
    EXPECT_STRNE(str1, "");
    EXPECT_STRNE(str2, "");
    EXPECT_STRNE(str3, "");

    // ToDoList должен содержать информацию о задаче
    EXPECT_STRNE(strstr(str2, "Task:"), nullptr);
    EXPECT_STRNE(strstr(str2, "Time:"), nullptr);

    delete[] str1;
    delete[] str2;
    delete[] str3;
}