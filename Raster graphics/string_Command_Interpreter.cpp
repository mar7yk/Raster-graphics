//
//  string_Command_Interpreter.cpp
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "string_Command_Interpreter.hpp"



bool StrCommandInterpr::execut(const String& newCommand) {
    bool toContinue = true;
    String sCommand = strtok(newCommand, " ");
    command command = getCommand(sCommand);
    
    switch (command) {
        case command::invalid:
            std::cout << "command not found: " << sCommand << std::endl;
            break;
        case command::load:
            _load();
        case command::add:
            _add();
            break;
        case command::close:
            _close();
            break;
        case command::save:
            //TODO: session save
            _save();
            break;
        case command::saveAs:
            //TODO: session saveAs
            _saveAs();
            break;
        case command::help:
            _help();
            break;
        case command::exit:
            std::cout << "Exiting the program...";
            toContinue = false;
        case command::grayscale:
        case command::monochrome:
        case command::negative:
        case command::rotateLeft:
        case command::rotateRight:
            sessions.current().addCommand(command);
            break;
        case command::undo:
            sessions.current().undo();
            break;
        case command::switchSessin:
            _switch();
        case command::sessionInfo:
            _sessionInfo();
            break;
        case command::collageVertical:
            std::cout <<"Coming soon!!!" << std::endl;
            break;
        case command::collageHorizontal:
            std::cout <<"Coming soon!!!" << std::endl;
            break;
    }
    std::cout << std::endl;
    
    return toContinue;
}

void StrCommandInterpr::_load() {
    sessions.makeNew();
    std::cout << "Session with ID: "<< sessions.current().getID() << " started" << std::endl;
}

void StrCommandInterpr::_add() {
    String img = strtok(NULL, " ");
    
    while (img != NULL) {
        sessions.current().add(img);
        std::cout << "Image \""<< img << "\" added" << std::endl;
        img = strtok(NULL, " ");
    }
}

void StrCommandInterpr::_close() {
    size_t id = sessions.current().getID();
    sessions.pop();
    std::cout << "Session with ID: "<< id << " is close" << std::endl;
}


void StrCommandInterpr::_switch() {
    String sID = strtok(NULL, " ");
    size_t id = stringToNum(sID);
    sessions.start(id);
    std::cout <<"You switched to session with ID: " << sessions.current().getID() << "!" << std::endl;
}


void StrCommandInterpr::_saveAs() {
    String name = strtok(NULL, " ");
    sessions.current().saveAs(name);
    std::cout << "Image was saved" << std::endl;
}

void StrCommandInterpr::_save() {
    sessions.current().save();
    std::cout << "All changes was saved" << std::endl;
}

void StrCommandInterpr::_sessionInfo() {
    String imgNames = sessions.current().getNamesOfImgs();
    String instNames = sessions.current().getNamesOfInstr();
    
    std::cout << "Name of images in the session: " << imgNames << std::endl;
    std::cout <<"Pending transformations: " << instNames << std::endl;
}

command StrCommandInterpr::getCommand(const String& sCommad) {
    if (sCommad == "load") return command::load;
    if (sCommad == "close") return command::close;
    if (sCommad == "save") {
        String word = strtok(NULL, " ");
        if (word == "as") return command::saveAs;
        else return command::save;
    }
    if (sCommad == "help") return command::help;
    if (sCommad == "exit") return command::exit;
    if (sCommad == "grayscale") return command::grayscale;
    if (sCommad == "monochrome") return command::monochrome;
    if (sCommad == "negative") return command::negative;
    if (sCommad == "undo") return command::undo;
    if (sCommad == "add") return command::add;
    if (sCommad == "session" && !strcmp(strtok(NULL, " "), "info")) return command::sessionInfo;
    if (sCommad == "switch") return command::switchSessin;
    if (sCommad == "rotate") {
        String direction = strtok(NULL, " ");
        if(direction == "left")  return command::rotateLeft;
        if(direction == "right")  return command::rotateRight;
    }
    if (sCommad == "collage") {
        String direction = strtok(NULL, " ");
        if(direction == "vertical") return command::collageVertical;
        if(direction == "horizontal")  return command::collageHorizontal;
    }
    return command::invalid;
}

void StrCommandInterpr::_help() {
    std::cout << "load <image>:" << std::endl;
    std::cout << "\tstart new session" << std::endl;
    std::cout << std::endl;
    std::cout << "add <image>:" << std::endl;
    std::cout << "\tadd image in sessin" << std::endl;
    std::cout << std::endl;
    std::cout << "close:" << std::endl;
    std::cout << "\tclose current session" << std::endl;
    std::cout << std::endl;
    std::cout << "save:" << std::endl;
    std::cout << "\tsave all changes in current sesino" << std::endl;
    std::cout << std::endl;
    std::cout << "save as <new-name>:" << std::endl;
    std::cout << "\tsave first image in current sesino whith new name" << std::endl;
    std::cout << std::endl;
    std::cout << "exit:" << std::endl;
    std::cout << "\texit of program" << std::endl;
    std::cout << std::endl;
    std::cout << "grayscale:" << std::endl;
    std::cout << "\tmake all images grayscale" << std::endl;
    std::cout << std::endl;
    std::cout << "monochrome:" << std::endl;
    std::cout << "\tmake all images monochrome" << std::endl;
    std::cout << std::endl;
    std::cout << "negative:" << std::endl;
    std::cout << "\tmake all images negative" << std::endl;
    std::cout << std::endl;
    std::cout << "rotate <direction>:" << std::endl;
    std::cout << "<direction> is one of the left and right" << std::endl;
    std::cout << "\trotate 90 degrees in the corresponding direction" << std::endl;
    std::cout << std::endl;
    std::cout << "undo:" << std::endl;
    std::cout << "\tundo last change" << std::endl;
    std::cout << std::endl;
    std::cout << "switch <session-id>:" << std::endl;
    std::cout << "\tswitches to a session with ID <session-id>" << std::endl;
    std::cout << std::endl;
    std::cout << "session info:" << std::endl;
    std::cout << "\tget info for current session" << std::endl;
    std::cout << std::endl;
    std::cout << "collage <direction> <image1> <image2> <outimage>:" << std::endl;
     std::cout << "\t<direction> is one of the horizontal and vertical" << std::endl;
    std::cout << "\tCreates a collage of two images <image1> and <image2> (in the same format and the same dimension) available in the current session. The result is saved to a new image <outimage>, which is added to the current session" << std::endl;
}

size_t StrCommandInterpr::stringToNum(const String &sID) {
    size_t num = 0;
    for (size_t i = 0; i < sID.lenght; ++i) {
        if (sID[i] < '0' || sID[i] > '9') {
            return 0;
        }
        size_t n = sID[i] - '0';
        num = (num*10) + n;
    }
    return num;
}
