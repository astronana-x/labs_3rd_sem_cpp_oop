#include "Stack/Stack.h"
#include "String/String.h"
#include "ToDoList/ToDoList.h"
#include "BinaryString/BinaryString.h"
#include <gtest/gtest.h>
#include <cstring>

using namespace std;

// Warning: при запуске тестов - убедиться, что они не отключены в CMakeLists.txt!

//проверка базы
TEST(LAB5, StackBasic) {
    Stack stack;
    EXPECT_EQ(stack.get_size(), 0);
    EXPECT_EQ(stack.get_top(), nullptr);

    String* str1 = new String("Nice time");
    stack.push(str1);
    EXPECT_EQ(stack.get_size(), 1);

    String* str2 = new String("for testing");
    stack.push(str2);
    EXPECT_EQ(stack.get_size(), 2);

    String* f1 = stack.find_by_index(0);
    EXPECT_NE(f1, nullptr);
    EXPECT_STREQ(f1->get_string(), "for testing");

    String* f2 = stack.find_by_index(1);
    EXPECT_NE(f2, nullptr);
    EXPECT_STREQ(f2->get_string(), "Nice time");

    stack.pop();
    EXPECT_EQ(stack.get_size(), 1);

    stack.pop();
    EXPECT_EQ(stack.get_size(), 0);
}

// поиск объектов в стеке
TEST(LAB5, StackSearch) {
    Stack stack;
    
    String* str1 = new String("Nice time");
    String* str2 = new String("for");
    String* str3 = new String("testing");
    
    stack.push(str1);
    stack.push(str2);
    stack.push(str3);
    
    // Поиск по индексу
    String* found_by_index = stack.find_by_index(1);
    EXPECT_NE(found_by_index, nullptr);
    EXPECT_STREQ(found_by_index->get_string(), "for");
    
    // Поиск по объекту
    int index = stack.find_by_obj(str2);
    EXPECT_EQ(index, 1);
    
    // Поиск несуществующего объекта
    String* non_existent = new String("Non existent");
    int not_found_index = stack.find_by_obj(non_existent);
    EXPECT_EQ(not_found_index, -1);
    delete non_existent;
    
    // Поиск за границами
    EXPECT_THROW(stack.find_by_index(5), out_of_range);
}

// тест полиморфизма с разными типами объектов
TEST(LAB5, PolymorphismTest) {
    Stack stack;
    
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

// Проверка работы с пустым стеком
TEST(LAB5, EmptyStack) {
    Stack stack;
    
    EXPECT_EQ(stack.get_size(), 0);
    EXPECT_NO_THROW(stack.pop()); // pop на пустом стеке не должен падать
    
    EXPECT_THROW(stack.find_by_index(0), out_of_range);
    EXPECT_THROW(stack.find_by_index(-1), out_of_range);
    
    // Поиск объекта в пустом стеке
    String* test_obj = new String("test");
    int index = stack.find_by_obj(test_obj);
    EXPECT_EQ(index, -1);
    delete test_obj;
}


// Проверка последовательности LIFO
TEST(LAB5, LIFO) {
    Stack stack;
    String* objects[] = {
        new String("First"),
        new String("Second"),
        new String("Third"),
        new String("Fourth")
    };
    
    for(auto obj : objects) {
        stack.push(obj);
    }

    EXPECT_STREQ(stack.find_by_index(0)->get_string(), "Fourth");
    EXPECT_STREQ(stack.find_by_index(1)->get_string(), "Third");
    EXPECT_STREQ(stack.find_by_index(2)->get_string(), "Second");
    EXPECT_STREQ(stack.find_by_index(3)->get_string(), "First");

    stack.pop();
    EXPECT_STREQ(stack.find_by_index(0)->get_string(), "Third");
}
