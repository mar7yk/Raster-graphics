//
//  main.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include <iostream>

#include "string.hpp"
#include "string_Command_Interpreter.hpp"

int main() {
    const Matrix<int> a(3, 5);
    
    std::cout << a[0][0];
    
//    StrCommandInterpr interpr;
//    String command;
//
//    do {
//        std::cout << "> ";
//        getline(std::cin, command, 1000);
//
//    } while (interpr.execut(command));
//
//    return 0;
}
