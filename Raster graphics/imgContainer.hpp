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
    size_t size;
    size_t capacity;
    Image ** images;
    
    void resize(const size_t newCapacity);
    
public:
    ImageContainer();
    ImageContainer(const ImageContainer& other) = delete;
    ImageContainer& operator=(const ImageContainer& other) = delete;
    ~ImageContainer();
    
    void add(Image*const img);
    
    void add(const ImagePPM& img);
    
    void add(const ImagePGM& img);
    
    void add(const ImagePBM& img);
    
    Image* getImg(const String& name) const;
    
    Image*& operator[](const size_t n);
    
    size_t getSize();
    
    void doInstForFirst(const command c);
    
    void doInst(const command c);
    
    void saveAs(const String& name);
    
    
    void save();
};

#endif /* imgContainer_hpp */
