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

#include "string.hpp"
#include "command.h"
#include "sessionContainer.hpp"


/// Служи за комуникация между конзолата и SessionContainer
class StrCommandInterpr {
    SessionContainer sessions;
    
    /// Преобразува string команда в enum command
    command getCommand(const String& sCommad);
    
    /// Преобразъва позитивно число от string в size_t
    size_t stringToNum(const String& sID);
    
    /// Изпълнява зареждане на сесия
    void _load();
    /// Добавя снимка към текущата сесия
    void _add();
    /// Затваря текущата сесия
    void _close();
    /// Запазва всички промени в текущата сесия
    void _save();
    /// Запазва първата снимка в текущата сесия под ново име
    void _saveAs();
    
    void _addInstr(const command instr);
    
    void _undo();
    
    /// Сменя текущата сесия с друга
    void _switch();
    /// Показва информация за текущата сесия
    void _sessionInfo() const;
    
    void _collage(const command type);
    /// Показва списък с наличните команди
    void _help() const;
    
public:
    /// Изпълнява команда по подаден стринг
    bool execut(const String& commad);
};

#endif /* string_Command_Interpreter_hpp */
