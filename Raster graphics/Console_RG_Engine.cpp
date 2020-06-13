//
//  Console_RG_Engine.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "Console_RG_Engine.hpp"


bool Console_RG_Engine::execut(const String& newCommand) {
    bool toContinue = true;
    String sCommand = strtok(newCommand, " ");
    Command command = getCommand(sCommand);
    
    try {
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
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
   
    std::cout << std::endl;
    
    return toContinue;
}

void Console_RG_Engine::_load() {
    sessions.makeNew();
    Session& cSession = sessions.current();
    std::cout << "Session with ID: "<< cSession.getID() << " started" << std::endl;
}

void Console_RG_Engine::_add() {
    String img = strtok(NULL, " ");
    Session& cSession = sessions.current();
    while (img != NULL) {
        if(cSession.add(img)) {
            std::cout << "Image \""<< img << "\" added" << std::endl;
        }
        img = strtok(NULL, " ");
    }
}

void Console_RG_Engine::_close() {
    Session& cSession = sessions.current();
    size_t id = cSession.getID();
    sessions.pop_current();
    std::cout << "Session with ID: "<< id << " is close" << std::endl;
}

void Console_RG_Engine::_save() {
    Session& cSession = sessions.current();
    cSession.save();
    std::cout << "All changes was saved" << std::endl;
}

void Console_RG_Engine::_addInstr(const Command instr) {
    Session& cSession = sessions.current();
    cSession.addCommand(instr);
}

void Console_RG_Engine::_undo() {
    Session& cSession = sessions.current();
    cSession.undo();
}

void Console_RG_Engine::_saveAs() {
    String name = strtok(NULL, " ");
    
    Session& cSession = sessions.current();
    cSession.saveAs(name);
    std::cout << "Image was saved" << std::endl;
}

void Console_RG_Engine::_switch() {
    String sID = strtok(NULL, " ");
    size_t id = stoull(sID);
    sessions.start(id);
    Session& cSession = sessions.current();
    std::cout <<"You switched to session with ID: " << cSession.getID() << "!" << std::endl;
}

void Console_RG_Engine::_sessionInfo() const {
    Session& cSession = sessions.current();
    Vector<String> imgNames = cSession.getNamesOfImgs();
    Vector<String> instNames = cSession.getNamesOfInstr();
    
    std::cout << "Name of images in the session: ";
    for (size_t i = 0; i < imgNames.size(); ++i) {
        std::cout << imgNames[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Pending transformations: ";
    for (size_t i = 0; i < instNames.size(); ++i) {
        std::cout << instNames[i];
        if (i + 1 < instNames.size()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}


void Console_RG_Engine::_collage(const Command type) {
    String img1 = strtok(NULL, " ");
    String img2 = strtok(NULL, " ");
    String newImg = strtok(NULL, " ");
    
    Session& cSession = sessions.current();
    cSession.addCollage(img1, img2, newImg, type);
    std::cout << "New collage \""<< newImg << "\" created" << std::endl;
}

void Console_RG_Engine::_help() const {
    std::cout << "load <image>:" << std::endl;
    std::cout << "\tstart new session" << std::endl;
    std::cout << std::endl;
    std::cout << "add <image>:" << std::endl;
    std::cout << "\tadd image to session" << std::endl;
    std::cout << std::endl;
    std::cout << "close:" << std::endl;
    std::cout << "\tclose current session" << std::endl;
    std::cout << std::endl;
    std::cout << "save:" << std::endl;
    std::cout << "\tsave all changes to the images in the current session" << std::endl;
    std::cout << std::endl;
    std::cout << "save as <new-name>:" << std::endl;
    std::cout << "\tsave all changes to the first image in the current session" << std::endl;
    std::cout << std::endl;
    std::cout << "exit:" << std::endl;
    std::cout << "\texit the program" << std::endl;
    std::cout << std::endl;
    std::cout << "grayscale:" << std::endl;
    std::cout << "\tmake an image grayscale" << std::endl;
    std::cout << std::endl;
    std::cout << "monochrome:" << std::endl;
    std::cout << "\tmake an image monochrome" << std::endl;
    std::cout << std::endl;
    std::cout << "negative:" << std::endl;
    std::cout << "\tmake an image negative" << std::endl;
    std::cout << std::endl;
    std::cout << "rotate <direction>:" << std::endl;
    std::cout << "\t<direction> is one of the left and right" << std::endl;
    std::cout << "\trotate an image 90 degrees in the corresponding direction" << std::endl;
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
    std::cout << "\tCreates a collage of two images <image1> and <image2> (in the same format and the same dimension) available in the current session. The result is saved to a new image <outimage>, which is added to the current session." << std::endl;
}

Command Console_RG_Engine::getCommand(const String& sCommad) const {
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

void Console_RG_Engine::run() { 
    String command;

    do {
        std::cout << "> ";
        getline(std::cin, command, 1000);

    } while (execut(command));
}



