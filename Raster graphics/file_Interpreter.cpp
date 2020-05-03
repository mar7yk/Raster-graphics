//
//  file_Interpreter.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "file_Interpreter.hpp"


ImgType FileInterpr::getType(const String& name) {
    std::ifstream img(name.get() , std::ios::binary);
    if (img.is_open()) {
        String sType;
        img >> sType;
        
        ImgType type = strToType(sType);
        
        img.close();

        return type;
    }
    return ImgType::Invalid;
}

ImgType FileInterpr::getType(const String &name1, const String &name2) {
    std::ifstream img1(name1.get() , std::ios::binary);
    std::ifstream img2(name2.get() , std::ios::binary);
    
    String sType1;
    img1 >> sType1;
    ImgType type1 = strToType(sType1);
    if (type1 == ImgType::Invalid) {
        return type1;
    }
    String sType2;
    img2 >> sType2;
    ImgType type2 = strToType(sType2);
    if (type2 == ImgType::Invalid) {
        return type2;
    }
    if (type1 != type2) {
        return ImgType::Invalid;
    }
    size_t width1, hight1;
    img1 >> width1 >> hight1;
    
    size_t width2, hight2;
    img2 >> width2 >> hight2;
    
    if (width1 != width2 || hight1 != hight2) {
        return ImgType::Invalid;
    }
    
    if (type1 != ImgType::PBM) {
        unsigned maxValForCalor1;
        img1 >> maxValForCalor1;
        unsigned maxValForCalor2;
        img2 >> maxValForCalor2;
        
        if (maxValForCalor1 != maxValForCalor2) {
            return ImgType::Invalid;
        }
    }
    
    return type1;
}

ImgType FileInterpr::strToType(const String &sType) {
    if(sType == "P3" || sType == "P6") return ImgType::PPM;
    if(sType == "P2" || sType == "P5") return ImgType::PGM;
    if(sType == "P1" || sType == "P4") return ImgType::PBM;
    return ImgType::Invalid;
}


