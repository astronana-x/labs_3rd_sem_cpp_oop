#include "String/String.h"
#include "gtest/gtest.h"
#include <filesystem>
//#include <sstream> //не очень то и хотелось
#include <cstdio> //remove()
using namespace std;

// Warning: при запуске тестов - убедиться, что они не отключены в CMakeLists.txt!

//оператор вывода
TEST(LAB3, OstreamOperator) {
    String s("Nice time for testing");
    ostringstream oss;
    oss << s;
    EXPECT_TRUE(strcmp(oss.str().c_str(), "Nice time for testing") == 0);
}

//оператор ввода, считываем каждое слово
TEST(LAB3, IstreamEachWord) {
    String a, b, c, d;
    istringstream iss("Nice\ntime\nfor\ntesting");
    iss >> a >> b  >> c >> d;
    EXPECT_STREQ(a.get_string(), "Nice");
    EXPECT_STREQ(b.get_string(), "time");
    EXPECT_STREQ(c.get_string(), "for");
    EXPECT_STREQ(d.get_string(), "testing");
}

//оператор ввода, объект - строка
TEST(LAB3, IstreamWholeLine) {
    String a;
    istringstream iss("Nice time for testing");
    iss >> a;
    EXPECT_STREQ(a.get_string(), "Nice time for testing");
}

//бинарник - запись и чтение обычной строки
TEST(LAB3, BinWriteAndRead) {
    String saved("Nice time for testing");

    //записываем в бинарный файл:
    ofstream out_file("test1.bin", ios::binary);
    bin_out(out_file, saved);
    out_file.close();

    //читаем из бинарного файла
    String loaded;
    ifstream in_file("test1.bin", ios::binary);
    bin_in(in_file, loaded);
    in_file.close();

    EXPECT_STREQ(saved.get_string(), loaded.get_string());
    EXPECT_EQ(saved.get_length(), loaded.get_length());

    //remove("test1.bin");
    cout << "Working directory: " << filesystem::current_path() << endl;
}

//работа с пустой строкой
TEST(LAB3, WriteAndReadEmptyString) {
    String saved("");

    ofstream out_file("test.bin", ios::binary);
    bin_out(out_file, saved);
    out_file.close();

    String loaded;
    ifstream in_file("test.bin", ios::binary);
    bin_in(in_file, loaded);
    in_file.close();

    EXPECT_STREQ(saved.get_string(), loaded.get_string());
    EXPECT_EQ(saved.get_length(), loaded.get_length());
    EXPECT_EQ(0, loaded.get_length());

    remove("test.bin");
}

//отработка спец символов
TEST(LAB3, WriteAndReadSpecialCharacters) {
    String saved("Nice\ntime\tfor\x01\x02testing");

    ofstream out_file("test.bin", ios::binary);
    bin_out(out_file, saved);
    out_file.close();

    String loaded;
    ifstream in_file("test.bin", ios::binary);
    bin_in(in_file, loaded);
    in_file.close();

    EXPECT_STREQ(saved.get_string(), loaded.get_string());
    EXPECT_EQ(saved.get_length(), loaded.get_length());

    remove("test.bin");
}


//запись и чтение нескольких объектов подряд
TEST(LAB3, ManyOperations) {
    String str1("Nice");
    String str2("time");
    String str3("for testing");

    //записываем несколько строк в один файл
    ofstream out_file("test.bin", ios::binary);
    bin_out(out_file, str1);
    bin_out(out_file, str2);
    bin_out(out_file, str3);
    out_file.close();

    //читаем в том же порядке
    String loaded1, loaded2, loaded3;
    ifstream in_file("test.bin", ios::binary);
    bin_in(in_file, loaded1);
    bin_in(in_file, loaded2);
    bin_in(in_file, loaded3);
    in_file.close();

    EXPECT_STREQ(str1.get_string(), loaded1.get_string());
    EXPECT_STREQ(str2.get_string(), loaded2.get_string());
    EXPECT_STREQ(str3.get_string(), loaded3.get_string());

    remove("test.bin");
}

//попытка чтения из несуществующего файла
TEST(LAB3, FileNotFound) {
    String loaded;
    ifstream in_file("poop.bin", ios::binary);

    bin_in(in_file, loaded);

    EXPECT_TRUE(in_file.fail());
    //объект должен остаться в исходном состоянии или пустым
}

// проверяем запись массива объектов String в текстовый файл
TEST(LAB3, WriteArrToTextFile) {
    cout << "Working directory: " << filesystem::current_path() << endl;

    const int object_count = 4;
    String objects[object_count] = {
        String("No one knows what it's like"),
        String("To be the bad man"),
        String("To be the sad man"),
        String("Behind blue eyes")
    };

    ofstream text_file("limp_bizkit.txt");
    ASSERT_TRUE(text_file.is_open());

    text_file << object_count << endl;

    for (int i = 0; i < object_count; i++) {
        text_file << objects[i] << endl;
    }
    text_file.close();

    // проверяем, что файл создан и имеет правильный размер
    ifstream check_file("limp_bizkit.txt");
    ASSERT_TRUE(check_file.is_open());

    string line;
    int line_count = 0;
    while (getline(check_file, line)) {
        line_count++;
    }
    check_file.close();

    EXPECT_EQ(object_count + 1, line_count);

    ifstream created_file("limp_bizkit.txt");
    int read_count;
    created_file >> read_count;
    created_file.ignore();

    EXPECT_EQ(object_count, read_count);

    string read_lines[object_count];
    for (int i = 0; i < object_count; i++) {
        getline(created_file, read_lines[i]);
        EXPECT_STREQ(objects[i].get_string(), read_lines[i].c_str());
    }
    created_file.close();

    //remove("limp_bizkit.txt");
}

//проверяем чтение массива объектов String из текстового файла
TEST(LAB3, ReadArrFromTextFile) {
    ofstream create_file("limp_bizkit2.txt");
    ASSERT_TRUE(create_file.is_open());

    create_file << "4" << endl;
    create_file << "No one knows what it's like" << endl;
    create_file << "To be the bad man" << endl;
    create_file << "To be the sad man" << endl;
    create_file << "Behind blue eyes" << endl;
    create_file.close();

    ifstream in_file("limp_bizkit2.txt");
    ASSERT_TRUE(in_file.is_open());

    int object_count;
    in_file >> object_count;
    in_file.ignore();

    EXPECT_EQ(4, object_count);

    String* loaded_objects = new String[object_count];

    // читаем каждый объект через перегруженный >>
    for (int i = 0; i < object_count; i++) {
        in_file >> loaded_objects[i];
    }
    in_file.close();

    // проверяем корректность загруженных данных
    EXPECT_STREQ("No one knows what it's like", loaded_objects[0].get_string());
    EXPECT_STREQ("To be the bad man", loaded_objects[1].get_string());
    EXPECT_STREQ("To be the sad man", loaded_objects[2].get_string());
    EXPECT_STREQ("Behind blue eyes", loaded_objects[3].get_string());

    // проверяем длины строк
    EXPECT_EQ(strlen("No one knows what it's like"), loaded_objects[0].get_length());
    EXPECT_EQ(strlen("To be the bad man"), loaded_objects[1].get_length());
    EXPECT_EQ(strlen("To be the sad man"), loaded_objects[2].get_length());
    EXPECT_EQ(strlen("Behind blue eyes"), loaded_objects[3].get_length());

    delete[] loaded_objects;
    remove("limp_bizkit2.txt");
}
