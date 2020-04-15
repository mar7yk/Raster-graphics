//
//  sessionContainer.hpp
//  dev
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
    SessionContainer(const SessionContainer&) = delete;
    SessionContainer& operator=(const SessionContainer &) = delete;
    ~SessionContainer();
    
    void makeNew();
    void pop();
    Session& current() const;
    bool start(const size_t ID);
    bool empty() const;
};

#endif /* sessionContainer_hpp */
