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
    String names;
    for (size_t i = 0; i < comtainer.size(); ++i) {
        names = names + comtainer[i]->getName() + " ";
    }
    return names;
}

String Session::getNamesOfInstr() const{
    String mames;
    InstrContainer temp = instructions;
    while (!temp.empty()) {
        Command c = temp.front();
        temp.pop_front();
        switch (c) {
            case Command::Grayscale:
                mames = mames + "grayscale";
                break;
            case Command::Monochrome:
                mames = mames + "monochrome";
                break;
            case Command::Negative:
                mames = mames + "negative";
                break;
            case Command::RotateLeft:
                mames = mames + "rotate left";
                break;
            case Command::RotateRight:
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
    
    ImgType type = FileInterpr::getType(name);
    
    switch (type) {
        case ImgType::Invalid:
            return false;
        case ImgType::PPM:
            comtainer.add(new ImagePPM(name));
            
            break;
        case ImgType::PGM:
            comtainer.add(new ImagePGM(name));

            break;
        case ImgType::PBM:
            comtainer.add(new ImagePBM(name));
            break;
    }
    return true;
}

bool Session::addCollage(const String &img1Name, const String &img2Name, const String &name, const Command type) {
    
    ImgType typeOfImgs = FileInterpr::getType(img1Name, img2Name);
    
    if (typeOfImgs == ImgType::Invalid) {
        return false;
    }
    
    Image *img1 = comtainer.getImg(img1Name);
    Image *img2 = comtainer.getImg(img2Name);
    
    using PPM = ImagePPM*;
    using PGM = ImagePGM*;
    using PBM = ImagePBM*;
    
    if (img1 && img2) {
        switch (typeOfImgs) {
            case ImgType::PPM:
                comtainer.add(new ImagePPM(*PPM(img1), *PPM(img2), name, type));
                break;
            case ImgType::PGM:
                comtainer.add(new ImagePGM(*PGM(img1), *PGM(img2), name, type));
                break;
            case ImgType::PBM:
                comtainer.add(new ImagePBM(*PBM(img1), *PBM(img2), name, type));
                break;
            default:
                return false;
        }
        return true;
    }
    return false;
}

bool Session::addCommand(const Command command) {
    if (command == Command::Invalid) {
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
