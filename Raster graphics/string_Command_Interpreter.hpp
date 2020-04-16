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


/// Служи за комъникация между комзолата и SessionContainer
class StrCommandInterpr {
    SessionContainer sessions;
    
    /// Преонразъва string команда в command
    /// @param sCommad референцуя на string
    /// @return comand
    command getCommand(const String& sCommad);
    
    /// Преонразъва позитивно число от string в size_t
    /// @param sID референцуя на string
    /// @return size_t
    size_t stringToNum(const String& sID);
    
    /// Изпълнява зареждане на сесия
    void _load();
    /// Добавя снимка към текущата сесия
    void _add();
    /// Затваря текущата сесия
    void _close();
    /// Сменя текущата сесия с друга
    void _switch();
    /// Изпринтва списук с наличните команди
    void _help();
    /// Запазва първата снимка в текущата сесия под ново име
    void _saveAs();
    /// Запазва всицики промени в текущата сесия
    void _save();
    /// Показва информазия за текущата сесия
    void _sessionInfo();
    
public:
    /// Извулнява команда по зададен стринг
    /// @param commad референцуя на string
    bool execut(const String& commad);
};

#endif /* string_Command_Interpreter_hpp */
