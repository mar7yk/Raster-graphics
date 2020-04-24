//
//  imagePGM.hpp
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef imagePGM_hpp
#define imagePGM_hpp

#include <stdio.h>
#include <fstream>

#include "Image.h"

class ImagePGM: public Image {
    unsigned maxValForCalor;
    MatrixPGM pixels;
    
    friend class FileInterpr;
    
public:
    ImagePGM(const String& name): Image(name) {
        std::ifstream img(name.get() , std::ios::binary);
        
        String sType;
        img >> sType;
        
        size_t width, hight;
        img >> width >> hight;
        pixels(width, hight);
        img >> maxValForCalor;
        
        if (sType == "P2"){
            for (size_t y = 0; y < pixels.getHight(); ++y) {
                for (size_t x = 0; x < pixels.getWidth(); ++x) {
                    img >> pixels[y][x];
                }
            }
            
        } else if (sType == "P5"){
            char buff;
            img.read((char*)&buff, sizeof(char));
            for (size_t y = 0; y < pixels.getHight(); ++y) {
                for (size_t x = 0; x < pixels.getWidth(); ++x) {
                    img.read((char*)&pixels[y][x], sizeof(char));
                }
            }
        }
        img.close();
    }
    
    ImagePGM(const Image *img11, const Image *img22, const String& name, const command type) : Image(name) {
        ImagePGM* img1 =(ImagePGM*)(img11);
        ImagePGM* img2 =(ImagePGM*)(img22);
        
        maxValForCalor = img1->maxValForCalor;
        
        if (type == command::collageVertical) {
            size_t width = img1->pixels.getWidth();
            size_t halfHighrt = img1->pixels.getHight();
            size_t hight = halfHighrt * 2;
            
            pixels(width, hight);
            for (size_t y = 0; y < halfHighrt; ++y) {
                for (size_t x = 0; x < width; ++x) {
                    pixels[y][x] = img1->pixels[y][x];
                }
            }

            for (size_t y = halfHighrt; y < hight; ++y) {
                for (size_t x = 0; x < width; ++x) {
                    pixels[y][x] = img2->pixels[y - halfHighrt][x];
                }
            }


        } else if (type == command::collageHorizontal) {
            size_t halfWidth = img1->pixels.getWidth();
            size_t width = halfWidth * 2;
            size_t hight = img1->pixels.getHight();
            pixels(width, hight);

            for (size_t y = 0; y < hight; ++y) {
                for (size_t x = 0; x < halfWidth; ++x) {
                    pixels[y][x] = img1->pixels[y][x];
                }
            }

            for (size_t y = 0; y < hight; ++y) {
                for (size_t x = halfWidth; x < width; ++x) {
                    pixels[y][x] = img2->pixels[y][x - halfWidth];
                }
            }
        }
    }
    
    void grayscale() override {
        
    }
    
    void monochrome() override {
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                unsigned char& p = pixels[y][x];
                p > maxValForCalor / 3 ? p = 255 : p = 0;
//p = 15 * (unsigned char)(p > maxValForCalor / 2);
            }
        }
        maxValForCalor = 255;
    }
    void negative() override {
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                pixels[y][x] = maxValForCalor - pixels[y][x];
            }
        }
    }
    void rotateLeft() override {
        MatrixPGM temp = pixels;
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
        MatrixPGM temp = pixels;
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
        f_name = name;
        save();
    }
    
    
    void save() override {
        std::ofstream oimg(f_name.get(), std::ios::binary);
        
        oimg << "P5" << std::endl;
        oimg << pixels.getWidth() << " " << pixels.getHight() << std::endl;
        oimg << maxValForCalor << std::endl;
        
        for (size_t y = 0; y < pixels.getHight(); ++y) {
            for (size_t x = 0; x < pixels.getWidth(); ++x) {
                oimg.write((char*)&pixels[y][x], sizeof(char));
            }
        }
        oimg.close();
    }
};

#endif /* imagePGM_hpp */
