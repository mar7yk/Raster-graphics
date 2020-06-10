//
//  Image.h
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <stdio.h>

#include "string.hpp"

#include "Command.h"


class Image {
protected:
    String f_name;
    
    
    
    /// Десериализира сника по подаден път на сниката
    ///
    /// @param name път на сника, които се задава за име на сниката.
    virtual void load(const String& name) = 0;
    
public:
    Image(const String& name): f_name(name) {
        
    }
    
    virtual ~Image() {}
    
    
    String getName() const {
        return f_name;
    }
    
    
    /// Пави снимката чено-бяла
    virtual void grayscale() = 0;
    /// Пави снимката монохромна
    virtual void monochrome() = 0;
    /// Пави снимката негативна
    virtual void negative() = 0;
    /// Завърта снимката на ляво
    virtual void rotateLeft() = 0;
    /// Завърта снимката на дясно
    virtual void rotateRight() = 0;
    
    /// Сериализира сниката
    virtual void save() = 0;
    /// Сериализира сниката във фаил с име name
    virtual void saveAs(const String& name) = 0;
};

#endif /* Image_hpp */
