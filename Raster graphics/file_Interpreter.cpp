//
//  file_Interpreter.cpp
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "file_Interpreter.hpp"


//ImagePPM FileInterpr::readPPM(const String& name) {
//    ImagePPM newImg;
//
//    std::ifstream img(name.get() , std::ios::binary);
//
//    newImg.f_name = name;
//
//    String sType;
//    img >> sType;
//
//    size_t width, hight;
//    img >> width >> hight;
//    newImg.pixels(width, hight);
//    img >> newImg.maxValForCalor;
//
//    if (sType == "P3"){
//        for (size_t y = 0; y < newImg.pixels.getHight(); ++y) {
//            for (size_t x = 0; x < newImg.pixels.getWidth(); ++x) {
//                unsigned char& r = newImg.pixels[y][x].r;
//                unsigned char& g = newImg.pixels[y][x].g;
//                unsigned char& b = newImg.pixels[y][x].b;
//                img >> r >> g >> b;
//            }
//        }
//
//    } else if (sType == "P6"){
//        char buff;
//        img.read((char*)&buff, sizeof(char));
//        for (size_t y = 0; y < newImg.pixels.getHight(); ++y) {
//            for (size_t x = 0; x < newImg.pixels.getWidth(); ++x) {
//                unsigned char& r = newImg.pixels[y][x].r;
//                unsigned char& g = newImg.pixels[y][x].g;
//                unsigned char& b = newImg.pixels[y][x].b;
//                img.read((char*)&r, sizeof(char));
//                img.read((char*)&g, sizeof(char));
//                img.read((char*)&b, sizeof(char));
//            }
//        }
//    }
//    img.close();
//
//    return newImg;
//}
//
//ImagePGM FileInterpr::readPGM(const String& name) {
//    ImagePGM newImg;
//
//    std::ifstream img(name.get() , std::ios::binary);
//
//    newImg.f_name = name;
//
//    String sType;
//    img >> sType;
//
//    size_t width, hight;
//    img >> width >> hight;
//    newImg.pixels(width, hight);
//    img >> newImg.maxValForCalor;
//
//    if (sType == "P2"){
//        for (size_t y = 0; y < newImg.pixels.getHight(); ++y) {
//            for (size_t x = 0; x < newImg.pixels.getWidth(); ++x) {
//                img >> newImg.pixels[y][x];
//            }
//        }
//
//    } else if (sType == "P5"){
//        char buff;
//        img.read((char*)&buff, sizeof(char));
//        for (size_t y = 0; y < newImg.pixels.getHight(); ++y) {
//            for (size_t x = 0; x < newImg.pixels.getWidth(); ++x) {
//                img.read((char*)&newImg.pixels[y][x], sizeof(char));
//            }
//        }
//    }
//    img.close();
//
//    return newImg;
//}
//
//ImagePBM FileInterpr::readPBM(const String& name) {
//    ImagePBM newImg;
//
//    std::ifstream img(name.get() , std::ios::binary);
//
//    newImg.f_name = name;
//
//    String sType;
//    img >> sType;
//
//    size_t width, hight;
//    img >> width >> hight;
//    newImg.pixels(width, hight);
//
//    if (sType == "P1"){
//        for (size_t y = 0; y < newImg.pixels.getHight(); ++y) {
//            for (size_t x = 0; x < newImg.pixels.getWidth(); ++x) {
//                img >> newImg.pixels[y][x];
//            }
//        }
//
//    } else if (sType == "P4"){
//        char buff;
//        img.read((char*)&buff, sizeof(char));
//        for (size_t y = 0; y < newImg.pixels.getHight(); ++y) {
//            size_t x = 0;
//            while (x < newImg.pixels.getWidth()) {
//                unsigned byte;
//                img.read((char*)&byte, sizeof(char));
//                for (int i = 7; i >= 0; --i) {
//                    unsigned char p = byte/(1<<(i));
//                    newImg.pixels[y][x] = p%2;
//                    if (x == newImg.pixels.getWidth()) {
//                        break;
//                    } else {
//                        ++x;
//                    }
//                }
//            }
//        }
//    }
//    img.close();
//
//    return newImg;
//}

void FileInterpr::writePPM(const ImagePPM &img) {
    writePPMas(img, img.f_name);
}

void FileInterpr::writePGM(const ImagePGM &img) {
    writePGMas(img, img.f_name);
}

void FileInterpr::writePBM(const ImagePBM &img) {
    writePBMas(img, img.f_name);
}

void FileInterpr::writePPMas(const ImagePPM& img, const String& name) {
    std::ofstream oimg (name.get(), std::ios::binary);
    
    oimg << "P6" << std::endl;
    oimg << img.pixels.getWidth() << " " << img.pixels.getHight() << std::endl;
    oimg << img.maxValForCalor << std::endl;
    
    for (size_t y = 0; y < img.pixels.getWidth(); ++y) {
        for (size_t x = 0; x < img.pixels.getHight(); ++x) {
            unsigned char& r = img.pixels[y][x].r;
            unsigned char& g = img.pixels[y][x].g;
            unsigned char& b = img.pixels[y][x].b;
            oimg.write((char*)&r, sizeof(char));
            oimg.write((char*)&g, sizeof(char));
            oimg.write((char*)&b, sizeof(char));
        }
    }
    oimg.close();
}

void FileInterpr::writePGMas(const ImagePGM& img, const String& name) {
    std::ofstream oimg (name.get(), std::ios::binary);
    
    oimg << "P5" << std::endl;
    oimg << img.pixels.getWidth() << " " << img.pixels.getHight() << std::endl;
    oimg << img.maxValForCalor << std::endl;
    
    for (size_t y = 0; y < img.pixels.getWidth(); ++y) {
        for (size_t x = 0; x < img.pixels.getHight(); ++x) {
            oimg.write((char*)&img.pixels[y][x], sizeof(char));
        }
    }
    oimg.close();
}

void FileInterpr::writePBMas(const ImagePBM& img, const String& name) {
    std::ofstream oimg (name.get(), std::ios::binary);
    
    oimg << "P4" << std::endl;
    oimg << img.pixels.getWidth() << " " << img.pixels.getHight() << std::endl;
    
    for (size_t y = 0; y < img.pixels.getWidth(); ++y) {
        for (size_t x = 0; x < img.pixels.getHight(); ++x) {
            oimg.write((char*)&img.pixels[y][x], sizeof(char));
        }
    }
    oimg.close();
}

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


