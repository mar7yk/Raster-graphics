//
//  imagePGM.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "imagePGM.hpp"

ImagePGM::ImagePGM(const String& name): Image(name) {
    std::ifstream img(name.get() , std::ios::binary);
    
    String sType;
    img >> sType;
    
    size_t width, hight;
    img >> width >> hight;
    pixels(width, hight);
    img >> maxValForCalor;
    
    if (sType == "P2"){
        for (size_t y = 0; y < pixels.hight(); ++y) {
            for (size_t x = 0; x < pixels.width(); ++x) {
                img >> pixels[y][x];
            }
        }
        
    } else if (sType == "P5"){
        char buff;
        img.read((char*)&buff, sizeof(char));
        for (size_t y = 0; y < pixels.hight(); ++y) {
            for (size_t x = 0; x < pixels.width(); ++x) {
                img.read((char*)&pixels[y][x], sizeof(char));
            }
        }
    }
    img.close();
}

ImagePGM::ImagePGM(const ImagePGM img1, const ImagePGM img2, const String& name, const command type) : Image(name) {
    
    maxValForCalor = img1.maxValForCalor;
    
    if (type == command::CollageVertical) {
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
        
        
    } else if (type == command::CollageHorizontal) {
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

void ImagePGM::grayscale() {
    
}

void ImagePGM::monochrome() {
    for (size_t y = 0; y < pixels.hight(); ++y) {
        for (size_t x = 0; x < pixels.width(); ++x) {
            unsigned char& p = pixels[y][x];
            p > maxValForCalor / 3 ? p = 255 : p = 0;
        }
    }
    maxValForCalor = 255;
}
void ImagePGM::negative() {
    for (size_t y = 0; y < pixels.hight(); ++y) {
        for (size_t x = 0; x < pixels.width(); ++x) {
            pixels[y][x] = maxValForCalor - pixels[y][x];
        }
    }
}

void ImagePGM::rotateLeft() {
    MatrixPGM temp = pixels;
    size_t w = pixels.hight();
    size_t h = pixels.width();
    pixels(w, h);
    for (size_t y = 0; y < pixels.hight(); ++y) {
        for (size_t x = 0; x < pixels.width(); ++x) {
            pixels[y][x] = temp[x][h - 1 - y];
        }
    }
}

void ImagePGM::rotateRight() {
    MatrixPGM temp = pixels;
    size_t w = pixels.hight();
    size_t h = pixels.width();
    pixels(w, h);
    for (size_t y = 0; y < pixels.hight(); ++y) {
        for (size_t x = 0; x < pixels.width(); ++x) {
            pixels[y][x] = temp[w - 1 - x][y];
        }
    }
}

void ImagePGM::save() {
    std::ofstream oimg(f_name.get(), std::ios::binary);
    
    oimg << "P5" << std::endl;
    oimg << pixels.width() << " " << pixels.hight() << std::endl;
    oimg << maxValForCalor << std::endl;
    
    for (size_t y = 0; y < pixels.hight(); ++y) {
        for (size_t x = 0; x < pixels.width(); ++x) {
            oimg.write((char*)&pixels[y][x], sizeof(char));
        }
    }
    oimg.close();
}

void ImagePGM::saveAs(const String& name) {
    f_name = name;
    save();
}
