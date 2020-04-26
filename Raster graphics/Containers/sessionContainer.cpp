//
//  sessionContainer.cpp
//  dev
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "sessionContainer.hpp"


SessionContainer::SessionContainer()
    : h(nullptr), c(nullptr), n(nullptr) {
    
}

SessionContainer::~SessionContainer() {
    while (!empty()) {
        Element *temp = h->next;
        delete h;
        h = temp;
    }
}

Session &SessionContainer::current() const {
    return c->data;
}

bool SessionContainer::empty() const {
    return !h;
}

void SessionContainer::makeNew() {
    Element *temp = n;
    n = new Element;
    n->next = nullptr;
    c = n;
    if(!h)
        h = n;
    else
        temp->next = n;
}

bool SessionContainer::start(const size_t ID) {
    Element *temp = h;
    while (temp && temp->data.getID() != ID) {
        temp = temp->next;
    }
    if(temp){
        c = temp;
    }
    return temp;
}

void SessionContainer::pop() {
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








