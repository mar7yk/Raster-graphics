//
//  instructionsContainer.cpp
//  dev
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "instructionsContainer.hpp"


InstrContainer::InstrContainer(): h(nullptr), n(nullptr) {
    
}

void InstrContainer::push(const command newInst) {
    inst *temp = n;
    n = new inst;
    n->data = newInst;
    n->next = nullptr;
    if(!h)
        h = n;
    else
        temp->next = n;
}

void InstrContainer::pop() {
    inst *temp = h->next;
    delete h;
    h = temp;
}

command &InstrContainer::front() const {
    return h->data;
}

void InstrContainer::undo() {
    if(h == n){
        pop();
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

bool InstrContainer::empty() const  {
    return !h;
}

InstrContainer::~InstrContainer() {
    clear();
}

InstrContainer &InstrContainer::operator=(const InstrContainer &other) {
    if (this != &other) {
        clear();
//        h = n = nullptr;
        inst *temp = other.h;
        while (temp) {
            push(temp->data);
            temp = temp->next;
        }
    }
    
    return *this;
}

void InstrContainer::clear() {
    while (!empty()) {
        pop();
    }
}

InstrContainer::InstrContainer(const InstrContainer &other) {
    h = n = nullptr;
    inst *temp = other.h;
    while (temp) {
        push(temp->data);
        temp = temp->next;
    }
}







