#include "Google_tests/binary_utils/binary_utils.h"
#include "gtest/gtest.h"
#include "ToDoList/ToDoList.h"
#include "String/String.h"
#include "BinaryString/BinaryString.h"
#include <cstdio>
#include <fstream>

using namespace std;

// Warning: при запуске тестов - убедиться, что они не отключены в CMakeLists.txt!


TEST(LAB4, ToBinary) {
    const char* s = "Nice time for testing";
    BinaryString bs(s);

    String binary = bs.to_binary();

    string expected_str = to_binary_string(s);
    if (!expected_str.empty() && expected_str.back() == ' ') {
        expected_str.pop_back();
    }
    String expected(expected_str.c_str());

    EXPECT_STREQ(binary.get_string(), expected.get_string());
    EXPECT_STREQ(bs.get_result().get_string(), expected.get_string());
}

TEST(LAB4, FromBinary) {
    const char* s = "Nice time for testing";
    BinaryString bs(s);

    bs.to_binary();

    String orig = bs.from_binary();

    EXPECT_STREQ(orig.get_string(), s);
    EXPECT_STREQ(bs.get_result().get_string(), s);
}

// проверка создания объекта и работы базовых методов
TEST(LAB4, ConstructorAndGetters) {
    ToDoList task("Complete lab work 4", "10:00", "12:00", false);

    EXPECT_STREQ(task.get_string(), "Complete lab work 4");
    EXPECT_FALSE(task.is_done());
}

// тестируем to_string()
TEST(LAB4, ToString) {
    BinaryString bs("A");

    char* result = bs.to_string();
    EXPECT_STREQ(result, "01000001");
    EXPECT_STREQ(bs.get_result().get_string(), "01000001");

    delete[] result;
}

//проверка работы конструктора копирования
TEST(LAB4, CopyConstructor) {
    ToDoList original("To walk a dog", "21:00", "21:30", true);
    ToDoList copy = original;

    EXPECT_STREQ(copy.get_string(), original.get_string());
    EXPECT_EQ(copy.is_done(), original.is_done());
}

// проверка работы оператора присваивания
TEST(LAB4, AssignmentOperator) {
    ToDoList task1("Yoga", "09:00", "10:00", false);
    ToDoList task2("Pilates", "11:00", "12:00", true);

    task1 = task2;

    EXPECT_STREQ(task1.get_string(), task2.get_string());
    EXPECT_EQ(task1.is_done(), task2.is_done());
}

// проверка методов изменения статуса задачи
TEST(LAB4, MarkMethods) {
    ToDoList task("Read amazing book", "16:00", "19:00", false);

    EXPECT_FALSE(task.is_done());
    task.mark_done();
    EXPECT_TRUE(task.is_done());
    task.mark_undone();
    EXPECT_FALSE(task.is_done());
}

// проверка записи в файл
TEST(LAB4, ToDoListFile) {
    ofstream file("todo_list.txt");
    ASSERT_TRUE(file.is_open()) << "Failed to create file!";

    ToDoList task1("Go to church", "09:00", "10:00", true);
    ToDoList task2("Complete laboratory work 4", "14:00", "16:30", false);

    char* str1 = task1.to_string();
    char* str2 = task2.to_string();

    file << "1. " << str1 << endl;
    file << "2. " << str2 << endl;
    file.close();

    delete[] str1;
    delete[] str2;

    ifstream checkFile("todo_list.txt");
    EXPECT_TRUE(checkFile.good());

    string firstLine;
    getline(checkFile, firstLine);
    EXPECT_FALSE(firstLine.empty());
    checkFile.close();

    //remove("todo_list.txt");
}
