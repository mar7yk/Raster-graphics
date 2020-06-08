//
//  InstructionList.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef InstructionList_hpp
#define InstructionList_hpp

#include <stdio.h>

#include "Command.h"

class InstructionList {
    struct inst {
        Command data;
        inst *next;
    };
    
    inst *h;
    inst *n;
    
    void clear();
    
public:
    InstructionList();
    InstructionList(const InstructionList& other);
    ~InstructionList();
    
    Command& front() const;
    Command& back() const;
    bool empty() const;
    
    void push_back(const Command newImg);
    
    void pop_front();
    void pop_back();
    
    InstructionList& operator=(const InstructionList& other);
};

#endif /* InstructionList_hpp */
