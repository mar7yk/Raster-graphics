//
//  string.cpp
//
//  Created by Marty Kostov on 5.03.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "string.hpp"


String::String() {
    lenght = 0;
    string = new char[1];
    strcpy(string, "");
}

String::String(const char *str) {
    setVal(str);
}

String::String(const String &other) {
    copyFrom(other);
}

String::String(String &&other) {
    lenght = other.lenght;
    string = other.string;
    
    other.lenght = 0;
    other.string = nullptr;
}

void String::copyFrom(const String &other) {
    lenght = other.lenght;
    string = new char[lenght + 1];
    strcpy(string, other.string);
}

String &String::operator=(const char *str) {
    delete [] string;
    setVal(str);
    return *this;
}

void String::setVal(const char *str) {
    if(str != NULL){
        lenght = strlen(str);
        string = new char[lenght + 1];
        strcpy(string, str);
    } else {
        lenght = 0;
        string = new char[1];
        strcpy(string, "");
    }
}

String::~String() {
    delete [] string;
}

String &String::operator=(const String &other) {
    if(this != &other){
        delete [] string;
        copyFrom(other);
    }
    return *this;
}




String String::operator+(const String &other) {
    String result;
    result.lenght = lenght + other.lenght;
    delete [] result.string;
    result.string = new char[result.lenght + 1];
    strcpy(result.string, string);
    strcat(result.string, other.string);
    
    return result;
}

String &String::operator+=(const String &other) {
    lenght = lenght + other.lenght;
    char* buff = new char[lenght + 1];
    strcpy(buff, string);
    strcat(buff, other.string);
    delete [] string;
    string = buff;
    return *this;
}

String String::operator+(const char other) {
    String result;
    result.lenght = lenght + 1;
    delete [] result.string;
    result.string = new char[result.lenght + 1];
    strcpy(result.string, string);
    result.string[lenght] = other;
    result.string[result.lenght] = '\0';
    return result;
}

String &String::operator+=(const char other) {
    lenght = lenght + 1;
    char* buff = new char[lenght + 1];
    strcpy(buff, string);
    buff[lenght - 1] = other;
    buff[lenght] = '\0';
    delete [] string;
    string = buff;
    return *this;
}

bool String::operator<(const String &other) const{
    return strcmp(string, other.string) < 0 ? true: false;
}

bool String::operator>(const String &other) const{
    return strcmp(string, other.string) > 0 ? true: false;
}


bool String::operator==(const String &other) const {
    return !strcmp(string, other.string);
}


char *String::get() const {
    return string;
}

void String::changeSize(String &word, size_t x) {
    word.lenght = x;
    char* buff = new char[word.lenght + 1];
    strcpy(buff, word.string);
    delete [] word.string;
    word.string = buff;
}

bool String::operator!=(const String &other) const {
    return strcmp(string, other.string);
}

Vector<String> String::split(const String flag) const{

    Vector<String> tokens;

    String token = strtok(string, flag.string);

    while (token != NULL)
    {
        tokens.push_back(token);
        token = strtok(NULL, flag.string);
    }

    return tokens;
}

const char String::operator[](const size_t i) const {
    return string[i];
}

char String::operator[](const size_t i) {
    return string[i];
}

std::istream& String::getfromStream(std::istream& input, String& word, size_t startFrom){
    long i;
    for (i = startFrom; i < word.lenght + 1; ++i) {
        input.read((char*)&word.string[i], sizeof(char));
        
        if(isspace(word.string[i]) || word.string[i] == '\0'){
            if (i == 0) {
                i = -1;
                continue;
            }
            word.string[i] = '\0';
            changeSize(word, i);
            return input;
        }
    }

    changeSize(word, i*2);
    return getfromStream(input, word, i);
}

std::istream& String::getfromStreamTo(std::istream& input, String& word, size_t startFrom, char to){
    size_t i;
    for (i = startFrom; i < word.lenght + 1; ++i) {
        input.read((char*)&word.string[i], sizeof(char));
        
        if(word.string[i] == to || word.string[i] == '\0'){
            word.string[i] = '\0';
            changeSize(word, i);
            return input;
        }
    }

    changeSize(word, i*2);
    return getfromStreamTo(input, word, i, to);
}


std::istream& operator>>(std::istream& input, String& word) {
    if(word.lenght < 10){
        word.lenght = 10;
        delete [] word.string;
        word.string = new char[word.lenght + 1];
    }
    return String::getfromStream(input, word, 0);
}


std::istream& getline(std::istream& input, String& word) {
    if(word.lenght < 10){
        word.lenght = 10;
        delete [] word.string;
        word.string = new char[word.lenght + 1];
    }
    
    return String::getfromStreamTo(input, word, 0, '\n');
}

std::istream& getline(std::istream& input, String& word, unsigned maxLenght) {
    char buff[maxLenght + 1];
    input.getline(buff, maxLenght);
    word = buff;
    return input;
}

std::ostream& operator<<(std::ostream& output, const String& word) {
    output << word.string;
    return output;
}

String strtok(const String& str, const String& sep){
    if (str == NULL) {
        return strtok(NULL, sep.string);
    }
    return strtok(str.string, sep.string);
}

Vector<String> split(const String& str, const String& delimiter) {
    
    Vector<String> tokens;
    
    String token = strtok(str.string, delimiter.string);
    
    while (token != NULL)
    {
        tokens.push_back(token);
        token = strtok(NULL, delimiter.string);
    }
    
    return tokens;
}

int stoi(const String& str) {
    
    int num = std::stoi(str.string);
    
    return num;
}

unsigned long long stoull(const String& str) {
    
    unsigned long long num = std::stoull(str.string);
    
    return num;
}

String to_string(int num) {
    String str;
    unsigned i = 0;
    
    
    if (num < 0) {
        num *= -1;
        str += '-';
        ++i;
    }
    
    Vector<char> chars;
    
    while (num) {
        int n = num % 10;
        chars.push_back(n + '0');
        num /= 10;
    }
    
    for (long j = chars.size() - 1; j >= 0; --j) {
        str += chars[j];
        ++i;
    }
    
    return str;
}

