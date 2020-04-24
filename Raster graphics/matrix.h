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
class PixelMatrix {
    size_t width, hight;
    pixel** elements;
    
    void del() {
        delete [] *elements;
        delete [] elements;
    }
    
    void set() {
        if(hight == 0 || width == 0){
            elements = new pixel*;
            *elements = new pixel;
            return;
        }
        elements = new pixel*[hight];
        *elements = new pixel[width*hight];
        for (size_t i = 1; i < hight; ++i)
            elements[i] = elements[i-1] + width;
    }
    
    void init(const PixelMatrix& other) {
        for (size_t y = 0; y < hight; ++y) {
            for (size_t x = 0; x < width; ++x) {
                elements[y][x] = other.elements[y][x];
            }
        }
    }
public:
    PixelMatrix(): width(0), hight(0) {
        set();
    }
    
    PixelMatrix(size_t x, size_t y): width(x), hight(y) {
        set();
    }
    
    PixelMatrix(const PixelMatrix& other): width(other.width), hight(other.hight) {
        set();
        init(other);
    }
    
    ~PixelMatrix(){
        del();
    }
    
    PixelMatrix& operator = (const PixelMatrix& other) {
        if(this != &other) {
            del();
            width = other.width;
            hight = other.hight;
            set();
            init(other);
        }
        return *this;
    }
    
    pixel*& operator[](const size_t y) const{
        return elements[y];
    }
    
    PixelMatrix& operator()(size_t x, size_t y){
        width = x;
        hight = y;
        del();
        set();
        return *this;
    }
    
    size_t getWidth() const{
        return width;
    }
    
    size_t getHight() const{
        return hight;
    }
};


using MatrixPPM = PixelMatrix<pixel_RGB>;
using MatrixPGM = PixelMatrix<unsigned char>;
using MatrixPBM = PixelMatrix<bool>;

#endif /* matrix_h */
