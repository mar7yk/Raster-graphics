//
//  ImageFileInterpreter.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "ImageFileInterpreter.hpp"


ImageType ImageFileInterpreter::getType(const String& name) {
    std::ifstream img(name.get() , std::ios::binary);
    if (img.is_open()) {
        String sType;
        img >> sType;
        
        ImageType type = strToType(sType);
        
        img.close();

        return type;
    }
    return ImageType::Invalid;
}

ImageType ImageFileInterpreter::getType(const String &name1, const String &name2) {
    std::ifstream img1(name1.get() , std::ios::binary);
    std::ifstream img2(name2.get() , std::ios::binary);
    
    String sType1;
    img1 >> sType1;
    ImageType type1 = strToType(sType1);
    if (type1 == ImageType::Invalid) {
        return type1;
    }
    String sType2;
    img2 >> sType2;
    ImageType type2 = strToType(sType2);
    if (type2 == ImageType::Invalid) {
        return type2;
    }
    if (type1 != type2) {
        return ImageType::Invalid;
    }
    size_t width1, hight1;
    img1 >> width1 >> hight1;
    
    size_t width2, hight2;
    img2 >> width2 >> hight2;
    
    if (width1 != width2 || hight1 != hight2) {
        return ImageType::Invalid;
    }
    
    if (type1 != ImageType::PBM) {
        unsigned maxValForColor1;
        img1 >> maxValForColor1;
        unsigned maxValForColor2;
        img2 >> maxValForColor2;
        
        if (maxValForColor1 != maxValForColor2) {
            return ImageType::Invalid;
        }
    }
    
    return type1;
}

ImageType ImageFileInterpreter::strToType(const String &sType) {
    if(sType == "P3" || sType == "P6") return ImageType::PPM;
    if(sType == "P2" || sType == "P5") return ImageType::PGM;
    if(sType == "P1" || sType == "P4") return ImageType::PBM;
    return ImageType::Invalid;
}


