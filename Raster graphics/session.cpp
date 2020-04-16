//
//  session.cpp
//  dev
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "session.hpp"

size_t Session::nextID = 1;




bool Session::addCommand(const command command) {
    if (command == command::invalid) {
        return false;
    }
    instructions.push(command);
    return true;
}

bool Session::add(const String &name) {
    
    imgType type = FileInterpr::readType(name);
    
    switch (type) {
        case imgType::invalid:
            return false;
        case imgType::PPM:
            
            comtainer.add(new ImagePPM(name));
//            PPM_Comtainer.add(FileInterpr::readPPM(name));
            break;
        case imgType::PGM:
            comtainer.add(new ImagePGM(name));
//            PGM_Comtainer.add(FileInterpr::readPGM(name));
            break;
        case imgType::PBM:
            comtainer.add(new ImagePBM(name));
//            PBM_Comtainer.add(FileInterpr::readPBM(name));
            break;
    }
    return true;
}

bool Session::undo() {
    if(!instructions.empty()){
        instructions.undo();
        return true;
    }
    return false;
}

bool Session::saveAs(const String name) {
    if(!comtainer.getSize())
        return false;
    
    while (!instructions.empty()) {
        comtainer.doInstForFirst(instructions.front());
        instructions.pop();
    }
    comtainer.saveAs(name);
    return true;
}

bool Session::save() {
    if(!comtainer.getSize())
        return false;
    while (!instructions.empty()) {
        comtainer.doInst(instructions.front());
        instructions.pop();
    }
    comtainer.save();
    
    return true;
}

String Session::getNamesOfImgs() {
    String mames;
    for (size_t i = 0; i < comtainer.getSize(); ++i) {
        mames = mames + comtainer[i]->getName() + " ";
    }
    return mames;
}

String Session::getNamesOfInstr() {
    String mames;
    InstrContainer temp = instructions;
    while (true) {
        command c = temp.front();
        temp.pop();
        switch (c) {
            case command::grayscale:
                mames = mames + "grayscale";
                break;
            case command::monochrome:
                mames = mames + "monochrome";
                break;
            case command::negative:
                mames = mames + "negative";
                break;
            case command::rotateLeft:
                mames = mames + "rotate left";
                break;
            case command::rotateRight:
                mames = mames + "rotate right";
                break;

            default:
                break;
        }
        if(temp.empty()){
            break;
        } else {
            mames = mames + ", ";
        }
    }
    
    
    return mames;
}






