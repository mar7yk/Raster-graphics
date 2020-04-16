//
//  instructionsContainer.hpp
//  dev
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef instructionsContainer_hpp
#define instructionsContainer_hpp

#include <stdio.h>

#include "command.h"

class InstrContainer {
    struct inst {
        command data;
        inst *next;
    };
    
    inst *h;
    inst *n;
    
    void clear();
    
public:
    InstrContainer();
    InstrContainer(const InstrContainer& other);
    ~InstrContainer();
    
    InstrContainer& operator=(const InstrContainer& other);
    
    void push(const command newImg);
    void pop();
    command& front() const;
    void undo();
    bool empty() const;
};

#endif /* instructionsContainer_hpp */
