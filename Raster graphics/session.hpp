//
//  session.hpp
//  dev
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef session_hpp
#define session_hpp

#include <stdio.h>

#include "instructionsContainer.hpp"
#include "imgContainer.h"
#include "file_Interpreter.hpp"

#include "command.h"

class Session {
    const size_t ID;
    InstrContainer instructions;
    ImageContainer comtainer;
//    ImgContainer<ImagePPM> PPM_Comtainer;
//    ImgContainer<ImagePGM> PGM_Comtainer;
//    ImgContainer<ImagePBM> PBM_Comtainer;
    
    static size_t nextID;
    
public:
    Session(): ID(nextID){
        ++nextID;
    }
    
    size_t getID(){
        return ID;
    }
    
    bool addCommand(const command command);
    
    bool saveAs(const String name);
    
    bool save();
    
    bool add(const String& name);
    
    bool undo();
    
    String getNamesOfImgs();
    
    String getNamesOfInstr();
};

#endif /* session_hpp */
