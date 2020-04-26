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

#include "string.hpp"
#include "imgType.h"

class FileInterpr {
    static imgType strToType(const String& sType);
    
public:
    static imgType getType(const String& name);
    static imgType getType(const String& name1, const String& name2);
};

#endif /* file_Interpreter_hpp */
