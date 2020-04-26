//
//  matrix.h
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include <stdio.h>
#include "pixel_RGB.h"


template<typename pixel>
class Matrix {
    size_t f_width;
    size_t f_hight;
    pixel** elements;
    
    void del() {
        delete [] *elements;
        delete [] elements;
    }
    
    void set() {
        if(f_hight == 0 || f_width == 0){
            elements = new pixel*;
            *elements = new pixel;
            return;
        }
        elements = new pixel*[f_hight];
        *elements = new pixel[f_width*f_hight];
        for (size_t i = 1; i < f_hight; ++i)
            elements[i] = elements[i-1] + f_width;
    }
    
    void init(const Matrix& other) {
        for (size_t y = 0; y < f_hight; ++y) {
            for (size_t x = 0; x < f_width; ++x) {
                elements[y][x] = other.elements[y][x];
            }
        }
    }
public:
    Matrix(): f_width(0), f_hight(0) {
        set();
    }
    
    Matrix(size_t x, size_t y): f_width(x), f_hight(y) {
        set();
    }
    
    Matrix(const Matrix& other): f_width(other.f_width), f_hight(other.f_hight) {
        set();
        init(other);
    }
    
    ~Matrix(){
        del();
    }
    
    size_t width() const{
        return f_width;
    }
    
    size_t hight() const{
        return f_hight;
    }
    
    
    Matrix& operator=(const Matrix& other) {
        if(this != &other) {
            del();
            f_width = other.width;
            f_hight = other.hight;
            set();
            init(other);
        }
        return *this;
    }
    
    Matrix& operator()(size_t width, size_t hight){
        f_width = width;
        f_hight = hight;
        del();
        set();
        return *this;
    }
    
    pixel*& operator[](const size_t y) const{
        return elements[y];
    }
};


using MatrixPPM = Matrix<pixel_RGB>;
using MatrixPGM = Matrix<unsigned char>;
using MatrixPBM = Matrix<bool>;

#endif /* matrix_h */
