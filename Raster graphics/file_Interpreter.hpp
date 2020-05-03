//
//  file_Interpreter.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef file_Interpreter_hpp
#define file_Interpreter_hpp

#include <stdio.h>
#include <fstream>

#include "string.hpp"
#include "imgType.h"

class FileInterpr {
    static ImgType strToType(const String& sType);
    
public:
    static ImgType getType(const String& name);
    static ImgType getType(const String& name1, const String& name2);
};

#endif /* file_Interpreter_hpp */
