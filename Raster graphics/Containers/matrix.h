//
//  Matrix.h
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

#include <stdio.h>

template<typename Element>
class Matrix {
    size_t f_width;
    size_t f_height;
    Element** elements;
    
    void del() {
        delete [] *elements;
        delete [] elements;
    }
    
    void init() {
        if(f_height == 0 || f_width == 0){
            elements = new Element*[1];
            *elements = new Element[1];
            return;
        }
        elements = new Element*[f_height];
        *elements = new Element[f_width * f_height];
        for (size_t i = 1; i < f_height; ++i)
            elements[i] = elements[i-1] + f_width;
    }
    
    void copyFrom(const Matrix& other) {
        for (size_t y = 0; y < f_height; ++y) {
            for (size_t x = 0; x < f_width; ++x) {
                elements[y][x] = other.elements[y][x];
            }
        }
    }
    
public:
    Matrix(): f_width(0), f_height(0) {
        init();
    }
    
    Matrix(size_t x, size_t y): f_width(x), f_height(y) {
        init();
    }
    
    Matrix(const Matrix& other) : f_width(other.f_width), f_height(other.f_height) {
        init();
        copyFrom(other);
    }
    
    ~Matrix(){
        del();
    }
    
    size_t width() const{
        return f_width;
    }
    
    size_t height() const{
        return f_height;
    }
    
    
    Matrix& operator=(const Matrix& other) {
        if(this != &other) {
            del();
            f_width = other.width;
            f_height = other.hight;
            init();
            copyFrom(other);
        }
        return *this;
    }
    
    /// Задава нови параметри на матрицата
    ///
    /// @attention елементите в матрицата се изтриват
    Matrix& operator()(size_t width, size_t hight){
        del();
        f_width = width;
        f_height = hight;
        init();
        return *this;
    }
    
    Element* &operator[](const size_t y) {
        return elements[y];
    }
    
    const Element *const &operator[](const size_t y) const {
        const Element *const *const &Matrix = elements;
        return Matrix[y];
    }
};

#endif /* Matrix_h */
