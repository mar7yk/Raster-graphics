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
public:
    /// Десериализира сника по подаден път на сниката
    ///
    /// @param name път на сника, които се задава за име на сниката.
    Image(const String& name): f_name(name) {
        
    }
    
    
    /// Създава колаж от две снимки
    ///
    /// @param img1 първа снима
    /// @param img2 втора снимка
    /// @param name име на колажа
    /// @param type тип на колажа (CollageHorizontal или CollageVertical)
    Image(const Image* img1, const Image* img2, const String& name, const Command type): f_name(name) {
        
    }
    
    virtual ~Image(){}
    
    /// @return име на снимка
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
