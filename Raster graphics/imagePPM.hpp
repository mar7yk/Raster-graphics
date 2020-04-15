//
//  imagePPM.hpp
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef imagePPM_hpp
#define imagePPM_hpp

#include <stdio.h>
#include <fstream>

#include "Image.h"

class ImagePPM: public Image {
    unsigned maxValForCalor;
    MatrixPPM pixels;
    
    friend class FileInterpr;
    
public:
    ImagePPM() {
        
    }
    ImagePPM(const String& name): Image(name) {
        std::ifstream img(name.get() , std::ios::binary);
        
        String sType;
        img >> sType;
        
        size_t width, hight;
        img >> width >> hight;
        pixels(width, hight);
        img >> maxValForCalor;
        
        if (sType == "P3"){
            for (size_t y = 0; y < pixels.getHight(); ++y) {
                for (size_t x = 0; x < pixels.getWidth(); ++x) {
                    unsigned char& r = pixels[y][x].r;
                    unsigned char& g = pixels[y][x].g;
                    unsigned char& b = pixels[y][x].b;
                    img >> r >> g >> b;
                }
            }
            
        } else if (sType == "P6"){
            char buff;
            img.read((char*)&buff, sizeof(char));
            for (size_t y = 0; y < pixels.getHight(); ++y) {
                for (size_t x = 0; x < pixels.getWidth(); ++x) {
                    unsigned char& r = pixels[y][x].r;
                    unsigned char& g = pixels[y][x].g;
                    unsigned char& b = pixels[y][x].b;
                    img.read((char*)&r, sizeof(char));
                    img.read((char*)&g, sizeof(char));
                    img.read((char*)&b, sizeof(char));
                }
            }
        }
        img.close();
    }
    
    void grayscale() override {
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                unsigned char& r = pixels[y][x].r;
                unsigned char& g = pixels[y][x].g;
                unsigned char& b = pixels[y][x].b;
                r = g = b = (r + g + b)/3;
            }
        }
    }
    
    void monochrome() override {
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                unsigned char& r = pixels[y][x].r;
                unsigned char& g = pixels[y][x].g;
                unsigned char& b = pixels[y][x].b;
                r = g = b = ((r + g + b)/3 > maxValForCalor / 3);
            }
        }
        maxValForCalor = 1;
    }
    void negative() override {
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                pixels[y][x].r = maxValForCalor - pixels[y][x].r;
                pixels[y][x].g = maxValForCalor - pixels[y][x].g;
                pixels[y][x].b = maxValForCalor - pixels[y][x].b;
            }
        }
    }
    void rotateLeft() override {
        MatrixPPM temp = pixels;
        size_t w = pixels.getHight();
        size_t h = pixels.getWidth();
        pixels(w, h);
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                pixels[y][x] = temp[x][h - 1 - y];
            }
        }
    }
    void rotateRight() override {
        MatrixPPM temp = pixels;
        size_t w = pixels.getHight();
        size_t h = pixels.getWidth();
        pixels(w, h);
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                pixels[y][x] = temp[w - 1 - x][y];
            }
        }
    }
    void saveAs(const String& name) override{
        f_name =  name;
        //TODO: Name change?
        save();
    }
    
    void save() override {
        std::ofstream oimg (f_name.get(), std::ios::binary);
        
        oimg << "P6" << std::endl;
        oimg << pixels.getWidth() << " " << pixels.getHight() << std::endl;
        oimg << maxValForCalor << std::endl;
        
        for (size_t y = 0; y < pixels.getWidth(); ++y) {
            for (size_t x = 0; x < pixels.getHight(); ++x) {
                unsigned char& r = pixels[y][x].r;
                unsigned char& g = pixels[y][x].g;
                unsigned char& b = pixels[y][x].b;
                oimg.write((char*)&r, sizeof(char));
                oimg.write((char*)&g, sizeof(char));
                oimg.write((char*)&b, sizeof(char));
            }
        }
        oimg.close();
    }
};
#endif /* imagePPM_hpp */
