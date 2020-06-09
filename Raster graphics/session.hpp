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

#include "FileInterpreter.hpp"

class Session {
    static size_t nextID;
    
    const size_t ID;
    ImageContainer images;
    InstructionList instructions;
    
public:
    Session();
    
    size_t getID() const;
    Vector<String> getNamesOfImgs() const;
    Vector<String> getNamesOfInstr() const;
    
    bool add(const String& name);
    void addCollage(const String& img1Name, const String& img2Name, const String& name, const Command type);
    void addCommand(const Command command);
    
    void save();
    void saveAs(const String name);
    
    void undo();
};

#endif /* Session_hpp */
