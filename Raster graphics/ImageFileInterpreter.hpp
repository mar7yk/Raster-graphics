//
//  ImageFileInterpreter.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef ImageFileInterpreter_hpp
#define ImageFileInterpreter_hpp

#include <stdio.h>
#include <fstream>

#include "string.hpp"

#include "ImageType.h"

class ImageFileInterpreter {
    static ImageType strToType(const String& sType);
    
public:
    /// Проверява типа на снимката.
    ///
    /// @param name име на снимка
    /// @return тип на снимка
    static ImageType getType(const String& name);
    
    /// Проверява типа на две снимки.
    ///
    /// @param name1 име на първата снимка
    /// @param name2 име на втората снимка
    /// @return тип на двете снимки, ако не са еднакви Invalid
    static ImageType getType(const String& name1, const String& name2);
};

#endif /* ImageFileInterpreter_hpp */
