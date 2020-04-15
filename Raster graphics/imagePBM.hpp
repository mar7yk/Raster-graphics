//
//  imagePBM.hpp
//  dev
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef imagePBM_hpp
#define imagePBM_hpp

#include <stdio.h>
#include <fstream>

#include "Image.hpp"

class ImagePBM: public Image {
    MatrixPBM pixels;
    
    friend class FileInterpr;
    
public:
    
    void grayscale() override {
        
    }
    
    void monochrome() override {
        
    }
    void negative() override {
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                pixels[y][x] = !pixels[y][x];
            }
        }
    }
    void rotateLeft() override {
        MatrixPBM temp = pixels;
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
        MatrixPBM temp = pixels;
        size_t w = pixels.getHight();
        size_t h = pixels.getWidth();
        pixels(w, h);
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                pixels[y][x] = temp[w - 1 - x][y];
            }
        }
    }
    void saveAs(const String& name) override {
        f_name = name;
        save();
    }
    
    
    void save() override {
        std::ofstream oimg (f_name.get(), std::ios::binary);
        
//        oimg << "P4" << std::endl;
//        oimg << pixels.getWidth() << " " << pixels.getHight() << std::endl;
//
//        for (size_t y = 0; y < pixels.getWidth(); ++y) {
//            for (size_t x = 0; x < pixels.getHight(); ++x) {
//                unsigned char p = pixels[y][x];
//                oimg.write((char*)&p, sizeof(char));
//                if(p == 1 && pixels[y][x]){
//
//                }
//            }
//        }
        
        oimg << "P4" << std::endl;
        oimg << pixels.getWidth() << " " << pixels.getHight() << std::endl;
        
//        for (size_t y = 0; y < pixels.getHight(); ++y) {
//
//            for (size_t x = 0; x < pixels.getWidth(); ++x) {
//                unsigned char p = pixels[y][x];
////                for (unsigned i = 0; i <= 7; ++i) {
////                    p = pixels[y][x]/(1<<(7 - i));
////                    oimg << p%(2);
////                }
//                oimg.write((char*)&p, sizeof(char));
////                oimg << (unsigned)p;
//            }
//        }
        
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            size_t x = 0;
            while (x < pixels.getWidth()) {
                unsigned byte = 0;
                for (int i = 7; i >= 0; --i) {
                    unsigned p = pixels[y][x] * (1 << (i));
                    byte += p;
                    if (x == pixels.getWidth()) {
                        break;
                    } else {
                        ++x;
                    }
                }
                oimg.write((char*)&byte, sizeof(char));
            }
        }
        
        oimg.close();
    }
};

#endif /* imagePBM_hpp */
