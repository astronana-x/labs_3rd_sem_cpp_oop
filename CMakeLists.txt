cmake_minimum_required(VERSION 3.20)
project(LAB1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основные исходники
set(SRC
        main.cpp

        String/String.cpp
        Index/Index.cpp
        BinaryString/BinaryString.cpp
        ToDoList/ToDoList.cpp

        Node/Node.cpp
        Stack/Stack.cpp

        Google_tests/binary_utils/binary_utils.cpp
        Google_tests/binary_utils/binary_utils.h

        #Google_tests/tests1.cpp
        #Google_tests/tests2.cpp
        #Google_tests/tests3.cpp
        #Google_tests/tests4.cpp
        Google_tests/tests5.cpp
        Google_tests/tests6.cpp


)

# Подключаем GoogleTest (лежит в Google_tests/lib)
add_subdirectory(Google_tests/lib)

# Подключаем include-директории gtest
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# Не помню зачем
include_directories(${CMAKE_SOURCE_DIR})

# Создаём исполняемый файл для основной программы
add_executable(LAB1 ${SRC})

# Линкуем gtest
target_link_libraries(LAB1 gtest gtest_main)