//
//  file_Interpreter.cpp
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "file_Interpreter.hpp"


imgType FileInterpr::getType(const String& name) {
    std::ifstream img(name.get() , std::ios::binary);
    if (img.is_open()) {
        String sType;
        img >> sType;
        
        imgType type = strToType(sType);
        
        img.close();

        return type;
    }
    return imgType::invalid;
}

imgType FileInterpr::getType(const String &name1, const String &name2) {
    std::ifstream img1(name1.get() , std::ios::binary);
    std::ifstream img2(name2.get() , std::ios::binary);
    
    String sType1;
    img1 >> sType1;
    imgType type1 = strToType(sType1);
    if (type1 == imgType::invalid) {
        return type1;
    }
    String sType2;
    img2 >> sType2;
    imgType type2 = strToType(sType2);
    if (type2 == imgType::invalid) {
        return type2;
    }
    if (type1 != type2) {
        return imgType::invalid;
    }
    size_t width1, hight1;
    img1 >> width1 >> hight1;
    
    size_t width2, hight2;
    img2 >> width2 >> hight2;
    
    if (width1 != width2 || hight1 != hight2) {
        return imgType::invalid;
    }
    
    if (type1 != imgType::PBM) {
        unsigned maxValForCalor1;
        img1 >> maxValForCalor1;
        unsigned maxValForCalor2;
        img2 >> maxValForCalor2;
        
        if (maxValForCalor1 != maxValForCalor2) {
            return imgType::invalid;
        }
    }
    
    return type1;
}

imgType FileInterpr::strToType(const String &sType) { 
    if(sType == "P3" || sType == "P6") return imgType::PPM;
    if(sType == "P2" || sType == "P5") return imgType::PGM;
    if(sType == "P1" || sType == "P4") return imgType::PBM;
    return imgType::invalid;
}


