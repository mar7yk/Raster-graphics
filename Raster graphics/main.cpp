//
//  main.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include <iostream>

#include "string_Command_Interpreter.hpp"

int main() {
    //com
    StrCommandInterpr interpr;
    String command;

    do {
        std::cout << "> ";
        getline(std::cin, command, 1000);

    } while (interpr.execut(command));
        
    
    
    return 0;
}
