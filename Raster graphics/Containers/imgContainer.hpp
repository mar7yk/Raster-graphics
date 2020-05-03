//
//  imgContainer.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 24.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef imgContainer_hpp
#define imgContainer_hpp

#include <stdio.h>

#include "imagePPM.hpp"
#include "imagePGM.hpp"
#include "imagePBM.hpp"

#include "command.h"

class ImageContainer {
    size_t f_size;
    size_t f_capacity;
    Image ** images;
    
    void resize(const size_t newCapacity);
    
public:
    ImageContainer();
    ~ImageContainer();
    
    Image* getImg(const String& name) const;
    size_t size() const;
    
    void add(Image*const img);
    
    void doInst(const Command c);
    void doInstForFirst(const Command c);
    
    void save();
    void saveAs(const String& name);
    
    Image*& operator[](const size_t n) const;
    
    ImageContainer(const ImageContainer& other) = delete;
    ImageContainer& operator=(const ImageContainer& other) = delete;
};

#endif /* imgContainer_hpp */
