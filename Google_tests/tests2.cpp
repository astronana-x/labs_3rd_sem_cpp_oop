#include "String/String.h"
#include <gtest/gtest.h>

// Warning: при запуске тестов - убедиться, что они не отключены в CMakeLists.txt!

// оператор сложения строки String со строкой char*
TEST(LAB2, OperatorPlusCharPtr) {
    String s1("Nice time");
    String result = s1 + " for testing";

    EXPECT_STREQ(result.get_string(), "Nice time for testing");
}

// оператор сложения двух объектов класса String
TEST(LAB2, OperatorPlusStringObj) {
    String s1("Nice time");
    String s2(" for testing");
    String result = s1 + s2;

    EXPECT_STREQ(result.get_string(), "Nice time for testing");
}

// String + char* + String
TEST(LAB2, OperatorPlusChain) {
    String s1("Nice");
    String s2(" time");
    String result = s1 + " time" + " for" + String(" testing");

    EXPECT_STREQ(result.get_string(), "Nice time for testing");
}

// оператор вычитания (удаление подстроки) из середины строки
TEST(LAB2, OperatorMinusSubstring) {
    String s1("Nice time for testing");
    String result = s1 - " time";

    EXPECT_STREQ(result.get_string(), "Nice for testing");
}

// удаление подстроки, которая встречается несколько раз (должен удалиться только первый экземпляр)
TEST(LAB2, OperatorMinusMultipleSubstr) {
    String s1("test test test");
    String result = s1 - "test";

    EXPECT_STREQ(result.get_string(), " test test");
}

// удаление несуществующей строки
TEST(LAB2, OperatorMinusNonExistentSubstring) {
    String s1("Nice time for testing");
    String result = s1 - "poop";

    EXPECT_STREQ(result.get_string(), "Nice time for testing");
}

// оператор присваивания между двумя объектами String
TEST(LAB2, OperatorAssignment) {
    String s1("Nice time for testing");
    String s2;
    s2 = s1;

    EXPECT_STREQ(s2.get_string(), "Nice time for testing");
    EXPECT_NE(s1.get_string(), s2.get_string()); // проверяем, что это глубокое копирование (разные указатели)
}

// проверяем присваивание объекта самому себе
TEST(LAB2, OperatorAssignmentSelf) {
    String s1("Nice time for testing");
    s1 = s1;

    EXPECT_STREQ(s1.get_string(), "Nice time for testing");
}

// оператор индексирования для чтения символов в разных позициях
TEST(LAB2, IndexOperatorRead) {
    String s1("Nice time for testing");

    EXPECT_EQ(s1[0], 'N');
    EXPECT_EQ(s1[5], 't');
    EXPECT_EQ(s1[10], 'f');
    EXPECT_EQ(s1[100], String::value_error); // Чтение за пределами строки
    EXPECT_EQ(s1[-1], String::value_error);  // Чтение по отрицательному индексу
}

// оператор индексирования для записи символов в существующие позиции
TEST(LAB2, IndexOperatorWrite) {
    String s1("Nice time for testing");
    s1[0] = 'n';
    s1[5] = 'T';

    EXPECT_STREQ(s1.get_string(), "nice Time for testing");
}

TEST(LAB2, IndexOperatorWriteBeyondLength) {
    String s1("test");
    s1[10] = 'X'; // запись за пределами текущей длины

    // проверяем что массив расширился и символ записался
    EXPECT_EQ(s1[10], 'X');

    // проверяем что оригинальная строка осталась неизменной до нового индекса
    EXPECT_EQ(s1[0], 't');
    EXPECT_EQ(s1[1], 'e');
    EXPECT_EQ(s1[2], 's');
    EXPECT_EQ(s1[3], 't');

    // проверяем что промежуточные символы заполнены нулями или пробелами
    for (int i = 4; i < 10; ++i) {
        EXPECT_TRUE(s1[i] == '\0' || s1[i] == ' ' || s1[i] == String::value_error);
    }
}

// проверяем запись символа сразу после последнего символа строки
TEST(LAB2, IndexOperatorWriteAtEnd) {
    String s1("test");
    size_t old_length = strlen(s1.get_string());
    s1[old_length] = '!'; // Запись сразу после конца строки

    EXPECT_STREQ(s1.get_string(), "test!");
}

// расширение массива при записи за пределами текущего размера
TEST(LAB2, AutoResizeOnIndexWrite) {
    String s1;

    // изначальный размер должен быть start_length
    EXPECT_GE(s1.get_max_length(), String::start_length);

    // записываем за пределами начального размера
    size_t beyond_initial = String::start_length + 5;
    s1[beyond_initial] = 'Z';

    // проверяем что размер увеличился
    EXPECT_GT(s1.get_max_length(), String::start_length);
    EXPECT_EQ(s1[beyond_initial], 'Z');
}

// проверяем что увеличение массива происходит с коэффициентом resize_factor
TEST(LAB2, ResizeFactorRespected) {
    String s1;
    size_t initial_size = s1.get_max_length();

    // записываем за пределами текущего размера
    s1[initial_size * 2] = 'A';
    EXPECT_GE(s1.get_max_length(), initial_size * String::resize_factor);
}

// проверяем что размер массива не превышает установленный лимит max_length_limit
TEST(LAB2, MaxLengthLimit) {
    String s1;

    // пытаемся записать за пределом max_length_limit
    s1[String::max_length_limit + 100] = 'X';

    // не должно превышать лимит
    EXPECT_LE(s1.get_max_length(), String::max_length_limit);
    EXPECT_EQ(s1[String::max_length_limit + 100], String::value_error);
}


// комплексное тестирование
TEST(LAB2, CombinedOperations) {
    String s1("Nice");
    String s2("time");
    String s3("for");
    String s4("testing");

    // Собираем строку из частей
    String result = s1 + " " + s2 + " " + s3 + " " + s4;
    EXPECT_STREQ(result.get_string(), "Nice time for testing");

    result = result - "Nice";
    EXPECT_STREQ(result.get_string(), " time for testing");

    result = String("Great") + result;
    EXPECT_STREQ(result.get_string(), "Great time for testing");

    result[0] = 'g';
    EXPECT_STREQ(result.get_string(), "great time for testing");
}

// операции с пустой строкой
TEST(LAB2, EmptyStringOperations) {
    String empty;
    String s1("test");

    String result1 = empty + s1;
    String result2 = s1 + empty;
    String result3 = empty - "nothing";

    EXPECT_STREQ(result1.get_string(), "test");
    EXPECT_STREQ(result2.get_string(), "test");
    EXPECT_STREQ(result3.get_string(), "");
}

TEST(LAB2, CountWordsAfterOperations) {
    String s1("Nice time for testing");
    String result = s1 + " more words";

    EXPECT_EQ(result.count_words(), 6);

    // доп проверка для уверенности
    EXPECT_STREQ(result.get_string(), "Nice time for testing more words");
}

// проверяем что оригинальная строка не изменяется при операциях с ее копией
TEST(LAB2, OriginalStringUnaffectedByCopyOperations) {
    String original("Nice time for testing");
    String copy = original;

    copy[0] = 'n';
    copy = copy + " modified";

    EXPECT_STREQ(original.get_string(), "Nice time for testing");
    EXPECT_STREQ(copy.get_string(), "nice time for testing modified");
}