//
//  string_Command_Interpreter.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "string_Command_Interpreter.hpp"


bool StrCommandInterpr::execut(const String& newCommand) {
    bool toContinue = true;
    String sCommand = strtok(newCommand, " ");
    Command command = getCommand(sCommand);
    
    switch (command) {
        case Command::Invalid:
            std::cout << "command not found: " << sCommand << std::endl;
            break;
        case Command::Load:
            _load();
        case Command::Add:
            _add();
            break;
        case Command::Close:
            _close();
            break;
        case Command::Save:
            _save();
            break;
        case Command::SaveAs:
            _saveAs();
            break;
        case Command::Help:
            _help();
            break;
        case Command::Exit:
            std::cout << "Exiting the program..." << std::endl;
            toContinue = false;
            break;
        case Command::Grayscale:
        case Command::Monochrome:
        case Command::Negative:
        case Command::RotateLeft:
        case Command::RotateRight:
            _addInstr(command);
            break;
        case Command::Undo:
            _undo();
            break;
        case Command::SwitchSession:
            _switch();
        case Command::SessionInfo:
            _sessionInfo();
            break;
        case Command::CollageVertical:
        case Command::CollageHorizontal:
            _collage(command);
            break;
    }
    std::cout << std::endl;
    
    return toContinue;
}

void StrCommandInterpr::_load() {
    sessions.makeNew();
    Session& cSession = sessions.current();
    std::cout << "Session with ID: "<< cSession.getID() << " started" << std::endl;
}

void StrCommandInterpr::_add() {
    String img = strtok(NULL, " ");
    Session& cSession = sessions.current();
    while (img != NULL) {
        if(cSession.add(img)) {
            std::cout << "Image \""<< img << "\" added" << std::endl;
        }
        img = strtok(NULL, " ");
    }
}

void StrCommandInterpr::_close() {
    Session& cSession = sessions.current();
    size_t id = cSession.getID();
    sessions.pop();
    std::cout << "Session with ID: "<< id << " is close" << std::endl;
}

void StrCommandInterpr::_save() {
    Session& cSession = sessions.current();
    cSession.save();
    std::cout << "All changes was saved" << std::endl;
}

void StrCommandInterpr::_addInstr(const Command instr) {
    Session& cSession = sessions.current();
    cSession.addCommand(instr);
}

void StrCommandInterpr::_undo() {
    Session& cSession = sessions.current();
    cSession.undo();
}

void StrCommandInterpr::_saveAs() {
    String name = strtok(NULL, " ");
    
    Session& cSession = sessions.current();
    cSession.saveAs(name);
    std::cout << "Image was saved" << std::endl;
}

void StrCommandInterpr::_switch() {
    String sID = strtok(NULL, " ");
    size_t id = stringToNum(sID);
    sessions.start(id);
    Session& cSession = sessions.current();
    std::cout <<"You switched to session with ID: " << cSession.getID() << "!" << std::endl;
}

void StrCommandInterpr::_sessionInfo() const {
    Session& cSession = sessions.current();
    String imgNames = cSession.getNamesOfImgs();
    String instNames = cSession.getNamesOfInstr();
    
    std::cout << "Name of images in the session: " << imgNames << std::endl;
    std::cout <<"Pending transformations: " << instNames << std::endl;
}


void StrCommandInterpr::_collage(const Command type) {
    String img1 = strtok(NULL, " ");
    String img2 = strtok(NULL, " ");
    String newimg = strtok(NULL, " ");
    
    Session& cSession = sessions.current();
    if (cSession.addCollage(img1, img2, newimg, type)) {
        std::cout << "Image \""<< newimg << "\" added" << std::endl;
    }
}

void StrCommandInterpr::_help() const {
    std::cout << "load <image>:" << std::endl;
    std::cout << "\tstart new session" << std::endl;
    std::cout << std::endl;
    std::cout << "add <image>:" << std::endl;
    std::cout << "\tadd image in session" << std::endl;
    std::cout << std::endl;
    std::cout << "close:" << std::endl;
    std::cout << "\tclose current session" << std::endl;
    std::cout << std::endl;
    std::cout << "save:" << std::endl;
    std::cout << "\tsave all changes in current session" << std::endl;
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

Command StrCommandInterpr::getCommand(const String& sCommad) {
    if (sCommad == "load") return Command::Load;
    if (sCommad == "close") return Command::Close;
    if (sCommad == "save") {
        String word = strtok(NULL, " ");
        if (word == "as") return Command::SaveAs;
        else return Command::Save;
    }
    if (sCommad == "help") return Command::Help;
    if (sCommad == "exit") return Command::Exit;
    if (sCommad == "grayscale") return Command::Grayscale;
    if (sCommad == "monochrome") return Command::Monochrome;
    if (sCommad == "negative") return Command::Negative;
    if (sCommad == "undo") return Command::Undo;
    if (sCommad == "add") return Command::Add;
    if (sCommad == "session" && !strcmp(strtok(NULL, " "), "info")) return Command::SessionInfo;
    if (sCommad == "switch") return Command::SwitchSession;
    if (sCommad == "rotate") {
        String direction = strtok(NULL, " ");
        if(direction == "left")  return Command::RotateLeft;
        if(direction == "right")  return Command::RotateRight;
    }
    if (sCommad == "collage") {
        String direction = strtok(NULL, " ");
        if(direction == "vertical") return Command::CollageVertical;
        if(direction == "horizontal")  return Command::CollageHorizontal;
    }
    return Command::Invalid;
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


