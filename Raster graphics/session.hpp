//
//  session.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef session_hpp
#define session_hpp

#include <stdio.h>

#include "imgContainer.hpp"
#include "instructionsContainer.hpp"
#include "command.h"
#include "file_Interpreter.hpp"
#include "imgType.h"

class Session {
    static size_t nextID;
    
    const size_t ID;
    ImageContainer comtainer;
    InstrContainer instructions;
    
public:
    Session();
    
    size_t getID() const;
    String getNamesOfImgs() const;
    String getNamesOfInstr() const;
    
    bool add(const String& name);
    bool addCollage(const String& img1Name, const String& img2Name, const String& name, const Command type);
    bool addCommand(const Command command);
    
    bool save();
    bool saveAs(const String name);
    
    bool undo();
};

#endif /* session_hpp */
