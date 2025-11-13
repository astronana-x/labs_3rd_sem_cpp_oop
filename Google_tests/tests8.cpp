#include <gtest/gtest.h>
#include <deque>
#include <iomanip>
#include <map>
#include <algorithm>
#include <chrono>
#include "String/String.h"
#include <filesystem>

// Warning: при запуске тестов - убедиться, что они не отключены в CMakeLists.txt!

using namespace std;
using namespace chrono;

const vector<int> size_of_range = {1000, 5000, 10000, 25000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000};

void write_to_csv(const string& container, int N,
                  double add_t, double find_t,
                  double sort_t, double del_t) {
    bool file_exists = filesystem::exists("results.csv");
    ofstream file("results.csv", ios::app);

    if (!file_exists) {
        file << "Container,Size,Add,Find,Sort,Delete\n";
    }

    file << "\"" << container << "\","
     << N << ","
     << fixed << setprecision(9)
     << add_t << "," << find_t << "," << sort_t << "," << del_t << "\n";
}

TEST(LAB8, DequeChar) {
    for (int N : size_of_range) {
        cout << "Deque char, N = "<< N << endl;
        deque<char> dq;

        auto start1 = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) dq.push_back('a' + (i % 26));
        auto end1 = high_resolution_clock::now();
        double time_taken1 = duration_cast<nanoseconds>(end1 - start1).count();
        time_taken1 *= 1e-9;
        cout<<"Add: "<<time_taken1<<endl;

        auto start3 = high_resolution_clock::now();
        sort(dq.begin(), dq.end());
        auto end3 = high_resolution_clock::now();
        double time_taken3 = duration_cast<nanoseconds>(end3 - start3).count();
        time_taken3 *= 1e-9;
        cout<<"Sort: "<<time_taken3<<endl;

        char z = 'z';
        auto start4 = high_resolution_clock::now();
        auto found_it = find(dq.begin(), dq.end(), z);
        auto end4 = high_resolution_clock::now();
        double time_taken4 = duration_cast<nanoseconds>(end4 - start4).count();
        time_taken4 *= 1e-9;
        cout<<"Find: "<<time_taken4<<endl;

        auto start2 = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) dq.pop_front();
        auto end2 = high_resolution_clock::now();
        double time_taken2 = duration_cast<nanoseconds>(end2 - start2).count();
        time_taken2 *= 1e-9;
        cout<<"Delete: "<<time_taken2<<endl;

        write_to_csv("Deque<char>", N, time_taken1, time_taken4, time_taken3, time_taken2);
    }
}

TEST(LAB8, DequeString) {
    for (int N : size_of_range) {
        cout << "Deque String, N = "<< N << endl;
        deque<String> dq;

        auto start1 = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            string temp = "str";
            temp += to_string(i % 100);
            dq.push_back(String(temp.c_str()));
        }
        auto end1 = high_resolution_clock::now();
        double time_taken1 = duration_cast<nanoseconds>(end1 - start1).count();
        time_taken1 *= 1e-9;
        cout<<"Add: "<<time_taken1<<endl;

        auto start3 = high_resolution_clock::now();
        sort(dq.begin(), dq.end());
        auto end3 = high_resolution_clock::now();
        double time_taken3 = duration_cast<nanoseconds>(end3 - start3).count();
        time_taken3 *= 1e-9;
        cout<<"Sort: "<<time_taken3<<endl;

        String z("str60");
        auto start4 = high_resolution_clock::now();
        auto found_it = find(dq.begin(), dq.end(), z);
        auto end4 = high_resolution_clock::now();
        double time_taken4 = duration_cast<nanoseconds>(end4 - start4).count();
        time_taken4 *= 1e-9;
        cout<<"Find: "<<time_taken4<<endl;

        auto start2 = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) dq.pop_front();
        auto end2 = high_resolution_clock::now();
        double time_taken2 = duration_cast<nanoseconds>(end2 - start2).count();
        time_taken2 *= 1e-9;
        cout<<"Delete: "<<time_taken2<<endl;

        write_to_csv("Deque<String>", N, time_taken1, time_taken4, time_taken3, time_taken2);
    }
}

TEST(LAB8, MultimapCharString) {
    for (int N : size_of_range) {
        cout << "Multimap Char-String, N = "<< N<< endl;
        multimap<char, String> arsenal;

        auto start1 = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            char key = 'a' + (i % 26);
            string temp = "str";
            temp += to_string(i % 100);
            arsenal.insert(make_pair(key, String(temp.c_str())));
        }
        auto end1 = high_resolution_clock::now();
        double time_taken1 = duration_cast<nanoseconds>(end1 - start1).count();
        time_taken1 *= 1e-9;
        cout<<"Add: "<<time_taken1<<endl;

        auto start8 = high_resolution_clock::now();
        auto find_it = arsenal.find('v');
        auto end8 = high_resolution_clock::now();
        double time_taken8 = duration_cast<nanoseconds>(end8 - start8).count();
        time_taken8 *= 1e-9;
        cout<<"Find: "<<time_taken8<<endl;

        auto start6 = high_resolution_clock::now();
        arsenal.clear();
        auto end6 = high_resolution_clock::now();
        double time_taken6 = duration_cast<nanoseconds>(end6 - start6).count();
        time_taken6 *= 1e-9;
        cout<<"Delete: "<<time_taken6<<endl;

        write_to_csv("Multimap<char,String>", N, time_taken1, time_taken8, 0.0, time_taken6);
    }
}

TEST(LAB8, UnorderedMultimapCharString) {
    for (int N : size_of_range) {
        cout << "UnorderedMultimap Char-String, N = "<< N<< endl;
        unordered_multimap<char, String> arsenal;

        auto start1 = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            char key = 'a' + (i % 26);
            string temp = "str";
            temp += to_string(i % 100);
            arsenal.insert(make_pair(key, String(temp.c_str())));
        }
        auto end1 = high_resolution_clock::now();
        double time_taken1 = duration_cast<nanoseconds>(end1 - start1).count();
        time_taken1 *= 1e-9;
        cout<<"Add: "<<time_taken1<<endl;


        auto start8 = high_resolution_clock::now();
        auto find_it = arsenal.find('v');
        auto end8 = high_resolution_clock::now();
        double time_taken8 = duration_cast<nanoseconds>(end8 - start8).count();
        time_taken8 *= 1e-9;
        cout<<"Find: "<<time_taken8<<endl;

        auto start6 = high_resolution_clock::now();
        arsenal.clear();
        auto end6 = high_resolution_clock::now();
        double time_taken6 = duration_cast<nanoseconds>(end6 - start6).count();
        time_taken6 *= 1e-9;
        cout<<"Delete: "<<time_taken6<<endl;

        write_to_csv("UnorderedMultimap<char,String>", N, time_taken1, time_taken8, 0.0, time_taken6);
    }
}

