//
//  imagePPM.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef imagePPM_hpp
#define imagePPM_hpp

#include <stdio.h>
#include <fstream>

#include "Image.h"
#include "pixel_RGB.h"

using MatrixPPM = Matrix<pixel_RGB>;

class ImagePPM: public Image {
    unsigned maxValForCalor;
    MatrixPPM pixels;
    
    friend class FileInterpr;
    
public:
    ImagePPM(const String& name): Image(name) {
        std::ifstream img(name.get() , std::ios::binary);
        
        String sType;
        img >> sType;
        
        size_t width, hight;
        img >> width >> hight;
        pixels(width, hight);
        img >> maxValForCalor;
        
        if (sType == "P3"){
            for (size_t y = 0; y < pixels.hight(); ++y) {
                for (size_t x = 0; x < pixels.width(); ++x) {
                    unsigned char& r = pixels[y][x].r;
                    unsigned char& g = pixels[y][x].g;
                    unsigned char& b = pixels[y][x].b;
                    img >> r >> g >> b;
                }
            }
            
        } else if (sType == "P6"){
            char buff;
            img.read((char*)&buff, sizeof(char));
            for (size_t y = 0; y < pixels.hight(); ++y) {
                for (size_t x = 0; x < pixels.width(); ++x) {
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
    
    ImagePPM(const ImagePPM img1, const ImagePPM img2, const String& name, const command type) : Image(name) {
        
        maxValForCalor = img1.maxValForCalor;
        
        if (type == command::collageVertical) {
            size_t width = img1.pixels.width();
            size_t halfHighrt = img1.pixels.hight();
            size_t hight = halfHighrt * 2;
            
            pixels(width, hight);
            for (size_t y = 0; y < halfHighrt; ++y) {
                for (size_t x = 0; x < width; ++x) {
                    pixels[y][x] = img1.pixels[y][x];
                }
            }

            for (size_t y = halfHighrt; y < hight; ++y) {
                for (size_t x = 0; x < width; ++x) {
                    pixels[y][x] = img2.pixels[y - halfHighrt][x];
                }
            }


        } else if (type == command::collageHorizontal) {
            size_t halfWidth = img1.pixels.width();
            size_t width = halfWidth * 2;
            size_t hight = img1.pixels.hight();
            pixels(width, hight);

            for (size_t y = 0; y < hight; ++y) {
                for (size_t x = 0; x < halfWidth; ++x) {
                    pixels[y][x] = img1.pixels[y][x];
                }
            }

            for (size_t y = 0; y < hight; ++y) {
                for (size_t x = halfWidth; x < width; ++x) {
                    pixels[y][x] = img2.pixels[y][x - halfWidth];
                }
            }
        }
    }
    
    void grayscale() override {
        for (size_t y = 0; y < pixels.hight(); ++y) {
            for (size_t x = 0; x < pixels.width(); ++x) {
                unsigned char& r = pixels[y][x].r;
                unsigned char& g = pixels[y][x].g;
                unsigned char& b = pixels[y][x].b;
                r = g = b = (r + g + b)/3;
            }
        }
    }
    
    void monochrome() override {
        for (size_t y = 0; y < pixels.hight(); ++y) {
            for (size_t x = 0; x < pixels.width(); ++x) {
                unsigned char& r = pixels[y][x].r;
                unsigned char& g = pixels[y][x].g;
                unsigned char& b = pixels[y][x].b;
                r = g = b = ((r + g + b)/3 > maxValForCalor / 3);
            }
        }
        maxValForCalor = 1;
    }
    void negative() override {
        for (size_t y = 0; y < pixels.hight(); ++y) {
            for (size_t x = 0; x < pixels.width(); ++x) {
                pixels[y][x].r = maxValForCalor - pixels[y][x].r;
                pixels[y][x].g = maxValForCalor - pixels[y][x].g;
                pixels[y][x].b = maxValForCalor - pixels[y][x].b;
            }
        }
    }
    void rotateLeft() override {
        MatrixPPM temp = pixels;
        size_t w = pixels.hight();
        size_t h = pixels.width();
        pixels(w, h);
        for (size_t y = 0; y < pixels.hight(); ++y) {
            for (size_t x = 0; x < pixels.width(); ++x) {
                pixels[y][x] = temp[x][h - 1 - y];
            }
        }
    }
    void rotateRight() override {
        MatrixPPM temp = pixels;
        size_t w = pixels.hight();
        size_t h = pixels.width();
        pixels(w, h);
        for (size_t y = 0; y < pixels.hight(); ++y) {
            for (size_t x = 0; x < pixels.width(); ++x) {
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
        oimg << pixels.width() << " " << pixels.hight() << std::endl;
        oimg << maxValForCalor << std::endl;
        
        for (size_t y = 0; y < pixels.hight(); ++y) {
            for (size_t x = 0; x < pixels.width(); ++x) {
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
