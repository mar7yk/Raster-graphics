//
//  SessionList.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef SessionList_hpp
#define SessionList_hpp

#include <stdio.h>

#include "Session.hpp"

class SessionList {
    struct Element {
        Session data;
        Element *next;
    };
    
    Element *h;
    Element *c;
    Element *n;
    
public:
    SessionList();
    ~SessionList();
    
    /// @return текуща сесия
    Session& current() const;
    
    bool empty() const;
    
    
    /// Създава нова сесия и я добавя към списъка
    void makeNew();
    
    
    /// Отбелязва сесия с дадено ID като текуща
    void start(const size_t ID);
    
    
    /// Премахва текущата сесия от списъка
    void pop_current();
    
    SessionList(const SessionList&) = delete;
    SessionList& operator=(const SessionList &) = delete;
};

#endif /* SessionList_hpp */
