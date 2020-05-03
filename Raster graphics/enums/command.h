//
//  command.h
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef command_h
#define command_h

enum class command {
    Invalid = -1,
    Load = 0,
    Add,
    Close,
    Save,
    SaveAs,
    Help,
    Exit,
    Grayscale,
    Monochrome,
    Negative,
    RotateLeft,
    RotateRight,
    Undo,
    SwitchSession,
    SessionInfo,
    CollageHorizontal,
    CollageVertical
};

#endif /* command_h */
