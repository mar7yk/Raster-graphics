//
//  SessionList.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "SessionList.hpp"


SessionList::SessionList()
    : h(nullptr), c(nullptr), n(nullptr) {
    
}

SessionList::~SessionList() {
    while (!empty()) {
        Element *temp = h->next;
        delete h;
        h = temp;
    }
}

Session &SessionList::current() const {
    if (!c) {
        throw std::runtime_error("There isn't started session");
    }
    return c->data;
}

bool SessionList::empty() const {
    return !h;
}

void SessionList::makeNew() {
    Element *temp = n;
    n = new Element;
    n->next = nullptr;
    c = n;
    if(!h)
        h = n;
    else
        temp->next = n;
}

void SessionList::start(const size_t ID) {
    Element *temp = h;
    while (temp && temp->data.getID() != ID) {
        temp = temp->next;
    }
    if(temp){
        c = temp;
        
    } else {
        throw std::runtime_error("There isn't a session with that id!");
        
    }
}

void SessionList::pop_current() {
    if (h == c) {
        Element *temp = h->next;
        delete h;
        h = temp;
        return;
    }
    Element *temp1 = h;
    while (temp1->next != c) {
        temp1 = temp1->next;
    }
    Element *temp2 = c->next;
    delete c;
    temp1->next = temp2;
    c = nullptr;
}








