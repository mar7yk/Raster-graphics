//
//  Console_RG_Engine.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef Console_RG_Engine_hpp
#define Console_RG_Engine_hpp

#include <stdio.h>
#include <iostream>

#include "string.hpp"

#include "SessionList.hpp"

#include "Command.h"


/// Служи за комуникация между конзолата и SessionContainer
class Console_RG_Engine {
    SessionList sessions;
    
    /// Преобразува string команда в enum command
    Command getCommand(const String& sCommad);
    
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
    
    void _addInstr(const Command instr);
    
    void _undo();
    
    /// Сменя текущата сесия с друга
    void _switch();
    /// Показва информация за текущата сесия
    void _sessionInfo() const;
    
    void _collage(const Command type);
    /// Показва списък с наличните команди
    void _help() const;
    
public:
    /// Изпълнява команда по подаден стринг
    bool execut(const String& commad);
    
    void run();
};

#endif /* Console_RG_Engine_hpp */
