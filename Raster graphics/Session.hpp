//
//  Session.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef Session_hpp
#define Session_hpp

#include <stdio.h>

#include "vector.h"

#include "ImageContainer.hpp"
#include "InstructionList.hpp"

#include "Command.h"
#include "ImageType.h"

#include "ImageFileInterpreter.hpp"

class Session {
    static size_t nextID;
    
    const size_t ID;
    ImageContainer images;
    InstructionList instructions;
    
public:
    Session();
    
    size_t getID() const;
    
    Vector<String> getNamesOfImgs() const;
    
    /// @return Вектор от имената на неизпълнените инструкции
    Vector<String> getNamesOfInstr() const;
    
    
    /// Добавя снимка в сесията
    ///
    /// @param name име на снимка
    /// @return добавена ли е сниката
    bool add(const String& name);
    
    /// Добавя колаж към синките в сесията
    ///
    /// @param img1Name - име на пурвата снимка
    /// @param img2Name - име на втората снимка
    /// @param name          - име на колажа
    /// @param type          - тип на колажа (CollageHorizontal или CollageVertical)
    void addCollage(const String& img1Name, const String& img2Name,
                    const String& name, const Command type);
    
    /// Добавя комнда към списъка с комнди на сесията
    void addCommand(const Command command);
    
    
    /// Запазва всички снимки
    ///
    /// Изпълнява командите от списъка с комнди вурху всички снимки в сесията и след това ги запазва.
    /// След изпулнението на всяка команда тя се изтрива от списъка.
    void save();
    
    /// Запазва първата снимка в сесията под ново име
    ///
    /// Изпълнява командите от списъка с комнди вурху снимката.
    /// След изпулнението на всяка команда тя се изтрива от списъка.
    void saveAs(const String name);
    
    
    /// Истрива поскедната команда от списъка с команди
    void undo();
};

#endif /* Session_hpp */
