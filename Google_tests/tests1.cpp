#include "String/String.h"
#include <gtest/gtest.h>

// Warning: при запуске тестов - убедиться, что они не отключены в CMakeLists.txt!

TEST(LAB1, DefaultConstructor) {
    String s;
    EXPECT_STREQ(s.get_string(), "");
    EXPECT_EQ(s.count_words(), 0);
}

// Конструктор с параметром
TEST(LAB1, ParamConstructor) {
    String s("Nice time for testing");
    EXPECT_STREQ(s.get_string(), "Nice time for testing");
    EXPECT_EQ(s.count_words(), 4);
    EXPECT_TRUE(s.count_words() > 0);
}

// Конструктор копирования
TEST(LAB1, CopyConstructor) {
    String s1("Nice time for testing");
    String s2(s1);
    EXPECT_STREQ(s2.get_string(), "Nice time for testing");
    EXPECT_TRUE(strcmp(s1.get_string(), s2.get_string()) == 0);
}

// Метод set_string
TEST(LAB1, SetString) {
    String s;
    s.set_string("Nice time for testing");
    EXPECT_STREQ(s.get_string(), "Nice time for testing");
    EXPECT_EQ(s.count_words(), 4);
}

// Метод find_substring
TEST(LAB1, FindSubstring) {
    String s("Nice time for testing");
    EXPECT_EQ(s.find_substring("Nice"), 0);
    EXPECT_EQ(s.find_substring("time"), 5);
    EXPECT_EQ(s.find_substring("testing"), 14);
    EXPECT_EQ(s.find_substring("tremolo"), -1);
}

// Метод count_words
TEST(LAB1, CountWords) {
    String s1("Nice time for testing");
    EXPECT_EQ(s1.count_words(), 4);

    //пробелы в начале и в концк
    String s2("  Nice time for testing ");
    EXPECT_EQ(s2.count_words(), 4);

    //несколько пробелов между словами
    String s3("Nice   time  for  testing");
    EXPECT_EQ(s3.count_words(), 4);

    //пустая строка
    String s4("");
    EXPECT_EQ(s4.count_words(), 0);

    //одно слово в строке
    String s5("Nice");
    EXPECT_EQ(s5.count_words(), 1);

    //с табуляцией и пробелами
    String s6("Nice\ttime for\ttesting");
    EXPECT_EQ(s6.count_words(), 4);
}

// Метод to_string
TEST(LAB1, ToString) {
    String s("Nice time for testing");
    char* copy = s.to_string();
    EXPECT_STREQ(copy, "Nice time for testing");
    EXPECT_TRUE(strlen(copy) == 21); // длина совпадает
    delete[] copy;
}

// Счётчик объектов
TEST(LAB1, ObjectCount) {
    int start_count = String::get_obj_count();
    {
        String s1("object");
        String s2("subject");
        EXPECT_EQ(String::get_obj_count(), start_count + 2);
        EXPECT_TRUE(String::get_obj_count() > start_count);
    }
    EXPECT_EQ(String::get_obj_count(), start_count);
}

