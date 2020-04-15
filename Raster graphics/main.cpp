//
//  main.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include <iostream>

#include "string_Command_Interpreter.hpp"

class A{
protected:
public:
    
    virtual int getX() = 0;
//    virtual int setX(const int x) = 0;
};

class B: public A {
    int x;
public:
    B(): A(){
        
    }
    B(const int x): x(x) {

    }
    int getX() override{
        return x;
    }
};

class C: public A {
    double x;
public:
    C(): A(){
        
    }
    C(const double x): x(x) {
        
    }
    int getX() override{
        return (int)x;
    }
};

class D: public A {
    char x;
public:
    D(): A(){

    }
    D(const char x): x(x) {

    }
    int getX() override{
        return (int)x;
    }
};
//
//class LinkedList {
//    struct el {
//        A *data;
//        el * next;
//    };
//    el *h;
//    el *n;
//
//};

class Arr {
    size_t size;
    size_t capacity;
    A** as;
public:
    Arr(): size(0), capacity(8) {
        as = new A*[capacity];
    }
    void add(const B e) {
        as[size] = new B(e);
        ++size;
    }
    void add(const C e) {
        as[size] = new C(e);
        ++size;
    }
    void add(const D e) {
        as[size] = new D(e);
        ++size;
    }
    A*& operator[](const size_t i) {
//        int b = as[0]->getX();
//        int c = as[1]->getX();
//        int d = as[2]->getX();
        return as[i];
    }
};

//class ImageContainer {
//    size_t size;
//    size_t capacity;
//    Image **images;
//
//    void resize(const size_t newCapacity) {
//        delete [] images;
//        capacity = newCapacity;
//        images = new(std::nothrow) Image*[capacity];
//    }
//
//public:
//    void setS(const String& a) {
//        images[0]->func(a);
//    }
//    ImageContainer(): size(0), capacity(8) {
//        images = new(std::nothrow) Image*[capacity];
//    }
//    ImageContainer(const ImageContainer& other) = delete;
//    ImageContainer& operator=(const ImageContainer& other) = delete;
//    ~ImageContainer() {
//        //TODO: TO ASK WHY NOT
////        for (size_t i = 0; i < size; ++i) {
////            delete images[i];
////        }
//        delete [] images;
//    }
//
//    void add(const ImagePPM& img) {
//        if(size == capacity) {
//            resize(2*size);
//        }
//        images[size] = new ImagePPM(img);
//        Image *a = new ImagePPM;
//        *a = *images[size];
//        Image *b = images[size];
//        ++size;
//    }
//
//    void add(const ImagePGM& img) {
//        if(size == capacity) {
//            resize(2*size);
//        }
//        images[size] = new ImagePGM(img);
//        ++size;
//    }
//
//    void add(const ImagePBM& img) {
//        if(size == capacity) {
//            resize(2*size);
//        }
//        images[size] = new ImagePBM(img);
//        ++size;
//    }
//    Image*& operator[](const size_t n){
//        return images[n];
//    }
//};


int main() {
    
//    ImageContainer contaner;
//
//    contaner.add(FileInterpr::ridePPM("P10.ppm"));
//    contaner.add(FileInterpr::ridePGM("P10.pgm"));
//    contaner.add(FileInterpr::ridePBM("P10.pbm"));
//
//    ImagePPM sa;
//    ImagePPM da;
//
//    da = sa;
    
//    B b(3);
//    C c(5.14);
//    A *bb = &b;
//    A *cc = &c;
//
//    A **arr = new A*[2];
//    arr[0] = bb;
//    arr[1] = cc;
//
//
//    std::cout << arr[0]->getX();
//    std::cout << arr[1]->getX();
    
//    Arr arr;
//    B b(4);
//    C c(8.3);
//    D d('0');
//    arr.add(b);
//    arr.add(c);
//    arr.add(d);
//    std::cout << arr[0]->getX();
//    std::cout << arr[1]->getX();
//    std::cout << arr[2]->getX();
    
//
    
    
    StrCommandInterpr interpr;

    String command;
    
//    interpr.execut("load P10.pbm");
//    interpr.execut("grayscale");
////    interpr.execut("negative");
//    interpr.execut("save as P100.pbm");
    

    do {
        std::cout << "> ";
        getline(std::cin, command, 1000);

    } while (interpr.execut(command));
        
    
    
    return 0;
}
