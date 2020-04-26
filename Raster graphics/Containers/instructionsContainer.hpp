//
//  instructionsContainer.hpp
//  Raster graphics
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
    
    command& front() const;
    bool empty() const;
    
    void push_back(const command newImg);
    
    void pop_front();
    void pop_back();
    
    InstrContainer& operator=(const InstrContainer& other);
};

#endif /* instructionsContainer_hpp */
