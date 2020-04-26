//
//  imagePPM.cpp
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "imagePPM.hpp"


//ImagePPM::ImagePPM(const String &name): Image(name) {
//    std::ifstream img(name.get() , std::ios::binary);
//    
//    String sType;
//    img >> sType;
//    
//    size_t width, hight;
//    img >> width >> hight;
//    pixels(width, hight);
//    img >> maxValForCalor;
//    
//    if (sType == "P3"){
//        for (size_t y = 0; y < pixels.getHight(); ++y) {
//            for (size_t x = 0; x < pixels.getWidth(); ++x) {
//                unsigned char& r = pixels[y][x].r;
//                unsigned char& g = pixels[y][x].g;
//                unsigned char& b = pixels[y][x].b;
//                img >> r >> g >> b;
//            }
//        }
//        
//    } else if (sType == "P6"){
//        char buff;
//        img.read((char*)&buff, sizeof(char));
//        for (size_t y = 0; y < pixels.getHight(); ++y) {
//            for (size_t x = 0; x < pixels.getWidth(); ++x) {
//                unsigned char& r = pixels[y][x].r;
//                unsigned char& g = pixels[y][x].g;
//                unsigned char& b = pixels[y][x].b;
//                img.read((char*)&r, sizeof(char));
//                img.read((char*)&g, sizeof(char));
//                img.read((char*)&b, sizeof(char));
//            }
//        }
//    }
//    img.close();
//}
