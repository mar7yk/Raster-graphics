//
//  FileInterpreter.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef FileInterpreter_hpp
#define FileInterpreter_hpp

#include <stdio.h>
#include <fstream>

#include "string.hpp"

#include "ImageType.h"

class FileInterpreter {
    static ImageType strToType(const String& sType);
    
public:
    static ImageType getType(const String& name);
    static ImageType getType(const String& name1, const String& name2);
};

#endif /* FileInterpreter_hpp */
