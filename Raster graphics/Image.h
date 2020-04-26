//
//  Image.h
//  dev
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <stdio.h>

#include "string.hpp"
#include "matrix.h"
#include "command.h"


class Image {
protected:
    String f_name;
public:
    Image(const String& name): f_name(name) {
        
    }
    
    Image(const Image* img1, const Image* img2, const String& name, const command type): f_name(name) {
        
    }
    
    virtual ~Image(){
        
    }
    
    virtual String getName() {
        return f_name;
    }
    
    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;
    virtual void rotateLeft() = 0;
    virtual void rotateRight() = 0;
    
    virtual void save() = 0;
    virtual void saveAs(const String& name) = 0;
};

#endif /* Image_hpp */
