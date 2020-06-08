//
//  ImageContainer.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 24.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef ImageContainer_hpp
#define ImageContainer_hpp

#include <stdio.h>

#include "vector.h"

#include "imagePPM.hpp"
#include "imagePGM.hpp"
#include "imagePBM.hpp"

#include "Command.h"

class ImageContainer {
    Vector<Image*> images;
    
public:
    ImageContainer() = default;
    ~ImageContainer();
    
    Image* getImg(const String& name) const;
    size_t size() const;
    
    void add(Image*const img);
    
    void doInst(const Command c);
    void doInstForFirst(const Command c);
    
    void save();
    void saveAs(const String& name);
    
    Image*& operator[](const size_t n);
    const Image *const& operator[](const size_t n) const;
    
    ImageContainer(const ImageContainer& other) = delete;
    ImageContainer& operator=(const ImageContainer& other) = delete;
};

#endif /* ImageContainer_hpp */
