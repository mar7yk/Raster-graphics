//
//  file_Interpreter.hpp
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef file_Interpreter_hpp
#define file_Interpreter_hpp

#include <stdio.h>
#include <fstream>

#include "imagePPM.cpp"
#include "imagePGM.cpp"
#include "imagePBM.cpp"
#include "imgType.h"

class FileInterpr {
    static imgType strToType(const String& sType);
    
public:
    static imgType getType(const String& name);
    static imgType getType(const String& name1, const String& name2);
    
    static ImagePPM readPPM(const String& name);
    static ImagePGM readPGM(const String& name);
    static ImagePBM readPBM(const String& name);
    
    static void writePPM(const ImagePPM& img);
    static void writePPMas(const ImagePPM& img, const String& name);
    static void writePGM(const ImagePGM& img);
    static void writePGMas(const ImagePGM& img, const String& name);
    static void writePBM(const ImagePBM& img);
    static void writePBMas(const ImagePBM& img, const String& name);
};

#endif /* file_Interpreter_hpp */
