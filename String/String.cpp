#include "String.h"

//определение статической константы:
const size_t String::start_length = 10;
const size_t String::resize_factor = 2;
const size_t String::max_length_limit = 1000;
const char String::value_error = '\0';

int String :: count = 0;

//конструктор по умолчанию:
String :: String() {
    this->max_length = 10;
    this->length = 0;
    this->arr = new char[max_length];
    this->arr[0] = '\0'; 
    count++; 
}

//конструктор с параметром:
String :: String(const char* str){
    this->length = strlen(str);
    this->max_length = length + 1; 
    this->arr = new char[max_length];
    strcpy(arr, str);
    count++;
}

//конструктор копирования:
String :: String(const String& other){
    this->length = other.length;
    this->max_length = other.max_length;
    this->arr = new char[max_length];
    strcpy(arr, other.arr);
    count++;
}

//деструктор:
String :: ~String(){
    delete[] arr;
    count--;
}

//сеттер
void String :: set_string(const char* str){
    length = strlen(str);
    max_length = length + 1;
    delete[] arr;
    arr = new char[max_length];
    strcpy(arr, str);
}

//геттер
const char* String :: get_string() const{
    return arr;
}

//метод нахождения подстроки в строке:
int String::find_substring(const char* substr){
    char* pos = strstr(arr, substr);
    if (pos) return static_cast<int>(pos - arr); // явное приведение
    return -1;
}


//метод подсчёта количества слов в строке:
int String::count_words() const {
    if (length == 0) return 0;

    int count = 0;
    bool in_word = false;

    for (size_t i = 0; i < length; i++) {
        if (arr[i] != ' ' && arr[i] != '\t' && !in_word) {
            in_word = true;
            count++;
        }
        else if (arr[i] == ' ' || arr[i] == '\t') {
            in_word = false;
        }
    }
    return count;
}


//метод для получения количества объектов в классе:
int String :: get_obj_count(){
        return count;
    }

//метод для возвращения копии строки:
char* String::to_string() const {
    char* res = new char[length + 1]; 
    strcpy(res, arr);                 
    return res;                       
}

// перегрузка + со стркоой типа *char
String String::operator+(const char* s) const {
    size_t new_len = length + strlen(s);
    char* new_arr = new char[new_len + 1];
    strcpy(new_arr, arr);
    strcat(new_arr, s);
    String res(new_arr);
    delete[] new_arr;
    return res;
}

//сложение двух объектов класса
String String::operator+(const String& obj) const {
    return *this + obj.get_string();
}

//операция вычитания как удаление подстроки
String String::operator-(const char* substr) const {
    String res(*this);
    int pos = res.find_substring(substr);
    if (pos != -1) {
        size_t sub_len = strlen(substr);

        // сдвигаем оставшуюся часть строки, начинаем с позиции удаления и сдвигаем всё что после подстроки
        for (size_t i = pos; i < res.length - sub_len; i++) {
            res.arr[i] = res.arr[i + sub_len];
        }
        res.length -= sub_len;
        res.arr[res.length] = '\0';
    }
    return res;
}

// присваивание
String& String::operator=(const String& other) {
    if (this == &other) return *this;
    delete[] arr;
    length = other.length;
    max_length = other.max_length;
    arr = new char[max_length];
    strcpy(arr, other.arr);
    return *this;
}

// индексирование через дружественный класс для записи
Index String::operator[](size_t indx) {
    return Index(this, indx);
}

//индексирование для чтения
char String::operator[](size_t indx) const {
    if (indx < 0 || static_cast<size_t>(indx) >= length) {
        return value_error;
    }
    return arr[indx];
}


//метод для увеличения размера массива
void String::_resize_array(size_t required_size) { //required_size = требуемый размер
    if (required_size <= max_length) return;

    // вычисляем новый размер
    size_t new_size = max_length;
    while (new_size < required_size) {
        new_size *= resize_factor;
        if (new_size > max_length_limit) {
            new_size = max_length_limit;
            break;
        }
    }

    char* new_arr = new char[new_size];
    memset(new_arr, 0, new_size);

    // копируем данные из старого массива
    if (arr) {
        strcpy(new_arr, arr);
        delete[] arr;
    }
    arr = new_arr;
    max_length = new_size;
}


//Лабораторная работа 3

//перегрузка оператора вывода
ostream& operator<<(ostream& os, const String& obj) {
    if (obj.arr) os << obj.arr;
    return os;
}

istream& operator>>(istream& is, String& obj) {
    char buffer[256];
    if (!is.getline(buffer, 256)) return is;
    obj.set_string(buffer);
    return is;
}

ofstream& bin_out(ofstream& os, const String& s) {
    size_t len = s.length;
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(s.arr, len);
    return os;
}

ifstream& bin_in(ifstream& is, String& s){
    size_t len;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    s._resize_array(len + 1); // +1 на всякий случай
    is.read(s.arr, len);
    s.arr[len] = '\0';
    s.length = len;
    return is;
}