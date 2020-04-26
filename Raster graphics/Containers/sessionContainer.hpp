//
//  sessionContainer.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef sessionContainer_hpp
#define sessionContainer_hpp

#include <stdio.h>

#include "session.hpp"

class SessionContainer {
    struct Element {
        Session data;
        Element *next;
    };
    
    Element *h;
    Element *c;
    Element *n;
    
public:
    SessionContainer();
    ~SessionContainer();
    
    Session& current() const;
    bool empty() const;
    
    void makeNew();
    
    bool start(const size_t ID);
    
    void pop();
    
    SessionContainer(const SessionContainer&) = delete;
    SessionContainer& operator=(const SessionContainer &) = delete;
};

#endif /* sessionContainer_hpp */
