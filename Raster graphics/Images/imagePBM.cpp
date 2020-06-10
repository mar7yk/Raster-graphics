//
//  ImagePBM.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "ImagePBM.hpp"


ImagePBM::ImagePBM(const String& name): Image(name) {
    load(name);
}


void ImagePBM::load(const String &name) {
    std::ifstream img(name.get() , std::ios::binary);
    
    String sType;
    img >> sType;
    
    size_t width, hight;
    img >> width >> hight;
    pixels(width, hight);
    
    if (sType == "P1") {
        for (size_t y = 0; y < pixels.height(); ++y) {
            for (size_t x = 0; x < pixels.width(); ++x) {
                img >> pixels[y][x];
            }
        }
        
    } else if (sType == "P4") {
        char buff;
        img.read((char*)&buff, sizeof(char));
        for (size_t y = 0; y < pixels.height(); ++y) {
            size_t x = 0;
            while (x < pixels.width()) {
                unsigned byte;
                img.read((char*)&byte, sizeof(char));
                for (int i = 7; i >= 0; --i) {
                    unsigned char p = byte/(1<<(i));
                    pixels[y][x] = p%2;
                    if (x == pixels.width()) {
                        break;
                    } else {
                        ++x;
                    }
                }
            }
        }
    }
}

ImagePBM::ImagePBM(const ImagePBM& img1, const ImagePBM& img2, const String& name, const Command type) : Image(name) {
    
    if (type == Command::CollageVertical) {
        size_t width = img1.pixels.width();
        size_t halfHighrt = img1.pixels.height();
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
        
        
    } else if (type == Command::CollageHorizontal) {
        size_t halfWidth = img1.pixels.width();
        size_t width = halfWidth * 2;
        size_t hight = img1.pixels.height();
        
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

void ImagePBM::grayscale() {
    
}

void ImagePBM::monochrome() {
    
}

void ImagePBM::negative() {
    for (size_t y = 0; y < pixels.height(); ++y) {
        for (size_t x = 0; x < pixels.width(); ++x) {
            pixels[y][x] = !pixels[y][x];
        }
    }
}

void ImagePBM::rotateLeft() {
    MatrixPBM temp = pixels;
    size_t w = pixels.height();
    size_t h = pixels.width();
    pixels(w, h);
    for (size_t y = 0; y < pixels.height(); ++y) {
        for (size_t x = 0; x < pixels.width(); ++x) {
            pixels[y][x] = temp[x][h - 1 - y];
        }
    }
}

void ImagePBM::rotateRight() {
    MatrixPBM temp = pixels;
    size_t w = pixels.height();
    size_t h = pixels.width();
    pixels(w, h);
    for (size_t y = 0; y < pixels.height(); ++y) {
        for (size_t x = 0; x < pixels.width(); ++x) {
            pixels[y][x] = temp[w - 1 - x][y];
        }
    }
}

void ImagePBM::save() {
    std::ofstream oimg (f_name.get(), std::ios::binary);
    
    oimg << "P4" << std::endl;
    oimg << pixels.width() << " " << pixels.height() << std::endl;
    
    for (size_t y = 0; y < pixels.height(); ++y) {
        size_t x = 0;
        while (x < pixels.width()) {
            unsigned byte = 0;
            for (int i = 7; i >= 0; --i) {
                unsigned p = pixels[y][x] * (1 << (i));
                byte += p;
                if (x == pixels.width()) {
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

void ImagePBM::saveAs(const String& name) {
    f_name = name;
    save();
}

