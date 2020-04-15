//
//  command.h
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef command_h
#define command_h

enum class command {
    invalid = -1,
    load = 0,
    add,
    close,
    save,
    saveAs,
    help,
    exit,
    grayscale,
    monochrome,
    negative,
    rotateLeft,
    rotateRight,
    undo,
    switchSessin,
    sessionInfo,
    collageHorizontal,
    collageVertical
};

#endif /* command_h */
