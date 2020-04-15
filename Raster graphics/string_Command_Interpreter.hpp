//
//  string_Command_Interpreter.hpp
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef string_Command_Interpreter
#define string_Command_Interpreter

#include <stdio.h>
#include <iostream>
#include <string>

#include "string.hpp"
#include "command.h"

#include "sessionContainer.hpp"

class StrCommandInterpr {
    SessionContainer sessions;
    
    command getCommand(const String& sCommad);
    
    size_t stringToNum(const String& sID);
    
    void _load();
    void _add();
    void _close();
    void _switch();//...
    void _help();
    void _saveAs();
    void _save();
    
public:
    bool execut(const String& commad);
};

#endif /* string_Command_Interpreter_hpp */
