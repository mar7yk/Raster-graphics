//
//  Session.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "Session.hpp"

size_t Session::nextID = 1;

Session::Session(): ID(nextID) {
    ++nextID;
}

size_t Session::getID() const {
    return ID;
}

Vector<String> Session::getNamesOfImgs() const {
    Vector<String> names;
    names.resize(images.size());
    for (size_t i = 0; i < images.size(); ++i) {
        names[i] = images[i]->getName();
    }
    return names;
}

Vector<String> Session::getNamesOfInstr() const{
    Vector<String> mames;
    InstructionList temp = instructions;
    while (!temp.empty()) {
        Command c = temp.front();
        switch (c) {
            case Command::Grayscale:
                mames.push_back("grayscale");
                break;
            case Command::Monochrome:
                mames.push_back("monochrome");
                break;
            case Command::Negative:
                mames.push_back("negative");
                break;
            case Command::RotateLeft:
                mames.push_back("rotate left");
                break;
            case Command::RotateRight:
                mames.push_back("rotate right");
                break;

            default:
                break;
        }
        temp.pop_front();
    }
    
    return mames;
}

bool Session::add(const String &name) {
    
    ImageType type = ImageFileInterpreter::getType(name);
    
    switch (type) {
        case ImageType::Invalid:
            return false;
        case ImageType::PPM:
            images.add(new ImagePPM(name));
            
            break;
        case ImageType::PGM:
            images.add(new ImagePGM(name));

            break;
        case ImageType::PBM:
            images.add(new ImagePBM(name));
            break;
    }
    return true;
}

void Session::addCollage(const String &img1Name, const String &img2Name, const String &name, const Command type) {
    
    ImageType typeOfImgs = ImageFileInterpreter::getType(img1Name, img2Name);
    
    if (typeOfImgs == ImageType::Invalid) {
        throw std::runtime_error("Can't make a collage with these images!");
    }
    
    Image *img1 = images.getImg(img1Name);
    Image *img2 = images.getImg(img2Name);
    
    using PPM = ImagePPM*;
    using PGM = ImagePGM*;
    using PBM = ImagePBM*;
    
    if (!img1 || !img2) {
        throw std::runtime_error("These images are not in this session!");
    }
    
    switch (typeOfImgs) {
        case ImageType::PPM:
            images.add(new ImagePPM(*PPM(img1), *PPM(img2), name, type));
            break;
        case ImageType::PGM:
            images.add(new ImagePGM(*PGM(img1), *PGM(img2), name, type));
            break;
        case ImageType::PBM:
            images.add(new ImagePBM(*PBM(img1), *PBM(img2), name, type));
            break;
        default:
            break;
    }
}

void Session::addCommand(const Command command) {
    if (command == Command::Invalid) {
        return;
    }
    instructions.push_back(command);
}


void Session::save() {
    while (!instructions.empty()) {
        images.doInstructions(instructions.front());
        instructions.pop_front();
    }
    images.save();
}

void Session::saveAs(const String name) {
    while (!instructions.empty()) {
        images.doInstructionsForFirst(instructions.front());
        instructions.pop_front();
    }
    images.saveAs(name);
}

void Session::undo() {
    if(!instructions.empty()){
        instructions.pop_back();
    }
}
