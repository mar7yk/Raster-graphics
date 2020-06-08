//
//  string.hpp
//
//  Created by Marty Kostov on 5.03.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef string_hpp
#define string_hpp

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "vector.h"

class String {
    char* string;
    void setVal(const char* str);
    void copyFrom(const String& other);
    
    static void changeSize(String& word, size_t x);
    
    static std::istream& getfromStream(std::istream& input, String& word, size_t startFrom);
    static std::istream& getfromStreamTo(std::istream& input, String& word, size_t startFrom, char to);
    
    String _to_string(int num, size_t n);
    
public:
    size_t lenght;
    
    String();
    String(const char* str);
    String(const String& other);
    String(String&& other);
    String& operator=(const char* str);
    ~String();
    String& operator=(const String& other);
    String operator+(const String& other);
    String& operator+=(const String& other);
    String operator+(const char other);
    String& operator+=(const char other);
    bool operator<(const String& other) const;
    bool operator>(const String& other) const;
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    const char operator[](const size_t i) const;
    char operator[](const size_t i);
    
    Vector<String> split(const String flag) const;
    
    char* get() const;
    
    friend std::istream& operator>>(std::istream& input, String& word);
    friend std::istream& getline(std::istream& input, String& word);
    friend std::istream& getline(std::istream& input, String& word, unsigned maxLenght);
    friend std::ostream& operator<<(std::ostream& output, const String& word);
    friend String strtok(const String& str, const String& sep);
    friend Vector<String> split(const String& str, const String& delimiter);
    friend int stoi(const String& str);
    friend unsigned long long stoull(const String& str);
};

String strtok(const String& str, const String& sep);
Vector<String> split(const String& str, const String& delimiter);
int stoi(const String& str);
unsigned long long stoull(const String& str);
String to_string(int num);


#endif /* string_hpp */
