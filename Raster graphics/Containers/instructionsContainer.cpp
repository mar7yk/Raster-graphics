//
//  instructionsContainer.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "instructionsContainer.hpp"


InstrContainer::InstrContainer()
    : h(nullptr), n(nullptr) {
    
}

InstrContainer::InstrContainer(const InstrContainer &other)
    : h(nullptr), n(nullptr) {
    inst *temp = other.h;
    while (temp) {
        push_back(temp->data);
        temp = temp->next;
    }
}

InstrContainer::~InstrContainer() {
    clear();
}

void InstrContainer::clear() {
    while (!empty()) {
        pop_front();
    }
}

command &InstrContainer::front() const {
    return h->data;
}

bool InstrContainer::empty() const  {
    return !h;
}

void InstrContainer::push_back(const command newInst) {
    inst *temp = n;
    n = new inst;
    n->data = newInst;
    n->next = nullptr;
    if(!h)
        h = n;
    else
        temp->next = n;
}

void InstrContainer::pop_front() {
    inst *temp = h->next;
    delete h;
    h = temp;
}


void InstrContainer::pop_back() {
    if(h == n){
        pop_front();
        return;
    }
    inst *temp = h;
    while (temp->next != n) {
        temp = temp->next;
    }
    delete n;
    n = temp;
    n->next = nullptr;
}



InstrContainer &InstrContainer::operator=(const InstrContainer &other) {
    if (this != &other) {
        clear();
//        h = n = nullptr;
        inst *temp = other.h;
        while (temp) {
            push_back(temp->data);
            temp = temp->next;
        }
    }
    
    return *this;
}









