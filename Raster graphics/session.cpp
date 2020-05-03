//
//  session.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "session.hpp"

size_t Session::nextID = 1;

Session::Session(): ID(nextID){
    ++nextID;
}

size_t Session::getID() const {
    return ID;
}

String Session::getNamesOfImgs() const {
    String mames;
    for (size_t i = 0; i < comtainer.size(); ++i) {
        mames = mames + comtainer[i]->getName() + " ";
    }
    return mames;
}

String Session::getNamesOfInstr() const{
    String mames;
    InstrContainer temp = instructions;
    while (!temp.empty()) {
        command c = temp.front();
        temp.pop_front();
        switch (c) {
            case command::Grayscale:
                mames = mames + "grayscale";
                break;
            case command::Monochrome:
                mames = mames + "monochrome";
                break;
            case command::Negative:
                mames = mames + "negative";
                break;
            case command::RotateLeft:
                mames = mames + "rotate left";
                break;
            case command::RotateRight:
                mames = mames + "rotate right";
                break;

            default:
                break;
        }
        if(!temp.empty()) {
            mames = mames + ", ";
        }
    }
    
    
    return mames;
}

bool Session::add(const String &name) {
    
    imgType type = FileInterpr::getType(name);
    
    switch (type) {
        case imgType::Invalid:
            return false;
        case imgType::PPM:
            
            comtainer.add(new ImagePPM(name));
            break;
        case imgType::PGM:
            comtainer.add(new ImagePGM(name));

            break;
        case imgType::PBM:
            comtainer.add(new ImagePBM(name));
            break;
    }
    return true;
}

bool Session::addCollage(const String &img1Name, const String &img2Name, const String &name, const command type) {
    
    imgType typeOfImgs = FileInterpr::getType(img1Name, img2Name);
    
    if (typeOfImgs == imgType::Invalid) {
        return false;
    }
    
    Image *img1 = comtainer.getImg(img1Name);
    Image *img2 = comtainer.getImg(img2Name);
    
    using PPM = ImagePPM*;
    using PGM = ImagePGM*;
    using PBM = ImagePBM*;
    
    if (img1 && img2) {
        switch (typeOfImgs) {
            case imgType::PPM:
                comtainer.add(new ImagePPM(*PPM(img1), *PPM(img2), name, type));
                break;
            case imgType::PGM:
                comtainer.add(new ImagePGM(*PGM(img1), *PGM(img2), name, type));
                break;
            case imgType::PBM:
                comtainer.add(new ImagePBM(*PBM(img1), *PBM(img2), name, type));
                break;
            default:
                return false;
        }
        return true;
    }
    return false;
}

bool Session::addCommand(const command command) {
    if (command == command::Invalid) {
        return false;
    }
    instructions.push_back(command);
    return true;
}


bool Session::save() {
    if(!comtainer.size())
        return false;
    while (!instructions.empty()) {
        comtainer.doInst(instructions.front());
        instructions.pop_front();
    }
    comtainer.save();
    
    return true;
}

bool Session::saveAs(const String name) {
    if(!comtainer.size())
        return false;
    
    while (!instructions.empty()) {
        comtainer.doInstForFirst(instructions.front());
        instructions.pop_front();
    }
    comtainer.saveAs(name);
    return true;
}

bool Session::undo() {
    if(!instructions.empty()){
        instructions.pop_back();
        return true;
    }
    return false;
}
