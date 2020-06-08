//
//  InstructionList.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "InstructionList.hpp"


InstructionList::InstructionList()
    : h(nullptr), n(nullptr) {
    
}

InstructionList::InstructionList(const InstructionList &other)
    : h(nullptr), n(nullptr) {
    inst *temp = other.h;
    while (temp) {
        push_back(temp->data);
        temp = temp->next;
    }
}

InstructionList::~InstructionList() {
    clear();
}

void InstructionList::clear() {
    while (!empty()) {
        pop_front();
    }
}

Command &InstructionList::front() const {
    return h->data;
}

Command &InstructionList::back() const {
    return n->data;
}

bool InstructionList::empty() const  {
    return !h;
}

void InstructionList::push_back(const Command newInst) {
    inst *temp = n;
    n = new inst;
    n->data = newInst;
    n->next = nullptr;
    if(!h)
        h = n;
    else
        temp->next = n;
}

void InstructionList::pop_front() {
    inst *temp = h->next;
    delete h;
    h = temp;
}


void InstructionList::pop_back() {
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



InstructionList &InstructionList::operator=(const InstructionList &other) {
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












