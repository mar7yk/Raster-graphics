//
//  string.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 5.03.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "string.hpp"

String::String(const char *str) {
    setVal(str);
}

String &String::operator=(const char *str) {
    delete [] string;
    setVal(str);
    return *this;
}

void String::setVal(const char *str) {
    if(str != NULL){
        lenght = strlen(str);
        string = new(std::nothrow) char[lenght + 1];
        if(!string){
            std::cout << "str";
        }
        strcpy(string, str);
    } else {
        lenght = 0;
        string = new(std::nothrow) char[1];
        if(!string){
            std::cout << "str";
        }
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


String::String(const String &other) {
    copyFrom(other);
}

void String::copyFrom(const String &other) {
    lenght = other.lenght;
    string = new(std::nothrow) char[lenght + 1];
    if(!string){
        std::cout << "str";
    }
    strcpy(string, other.string);
}

String String::operator+(const String &other) {
    String result;
    result.lenght = lenght + other.lenght;
    delete [] result.string;
    result.string = new(std::nothrow) char[result.lenght + 1];
    if(!result.string){
        std::cout << "str";
    }
    strcpy(result.string, string);
    strcat(result.string, other.string);
    
    return result;
}


String::String() {
    lenght = 0;
    string = new(std::nothrow) char[1];
    if(!string){
        std::cout << "str";
    }
    strcpy(string, "");
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
    char* buff = new(std::nothrow) char[word.lenght + 1];
    strcpy(buff, word.string);
    delete [] word.string;
    word.string = buff;
}

std::istream& String::getfromStream(std::istream& input, String& word, size_t startFrom){
    size_t i;
    for (i = startFrom; i < word.lenght + 1; ++i) {
        input.read((char*)&word.string[i], sizeof(char));
        
        if(isspace(word.string[i]) || word.string[i] == '\0'){
            word.string[i] = '\0';
            changeSize(word, i);
            return input;
        }
    }

    changeSize(word, i*2);
    return getfromStream(input, word, i);
}

bool String::operator!=(const String &other) const {
    return strcmp(string, other.string);
}

String *String::split(const String flag) const{
    size_t size = 0;
    size_t capacity = 4;
    String * tokens = new(std::nothrow) String[capacity];
    
    String token = strtok(string, flag.string);
    
    while (token != NULL)
    {
        tokens[size] = token;
        size++;
        if (size == capacity) {
            capacity *= 2;
            String * buff = new(std::nothrow) String[capacity];
            delete [] tokens;
            tokens = buff;
        }
        token = strtok(NULL, flag.string);
    }
    capacity = size;
    String * buff = new(std::nothrow) String[capacity];
    delete [] tokens;
    tokens = buff;
    return tokens;
}

char String::operator[](const size_t i) const {
    return string[i];
}



std::istream& operator>>(std::istream& input, String& word) {
    if(word.lenght < 10){
        word.lenght = 10;
        delete [] word.string;
        word.string = new(std::nothrow) char[word.lenght + 1];
    }
    
    return String::getfromStream(input, word, 0);
}

std::istream& getline(std::istream& input, String& word) {
    char buff[1000];
    input.getline(buff, 999);
    word = buff;
    return input;
}

std::istream& getline(std::istream& input, String& word, unsigned maxLenght) {
    char buff[maxLenght + 1];
    input.getline(buff, maxLenght);
    word = buff;
    return input;
}

std::ostream& operator<<(std::ostream& output, String& word) {
    output << word.string;
    return output;
}
