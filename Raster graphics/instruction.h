//
//  instruction.h
//  dev
//
//  Created by Marty Kostov on 12.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef instructions_h
#define instructions_h

enum class instruction {
    invalid = -1,
    grayscale = 0,
    monochrome,
    negative,
    rotateLeft,
    rotateRight,
};

#endif /* instruction_h */
