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
    
    /// Изпълнява команда вурху всички снимки в сесията.
    void doInstructions(const Command c);
    /// Изпълнява команда вурху всички първата снимка.
    void doInstructionsForFirst(const Command c);
    
    /// Запазва всички снимки
    void save();
    /// Запазва първата снимка под ново име
    void saveAs(const String& name);
    
    Image*& operator[](const size_t n);
    const Image *const& operator[](const size_t n) const;
    
    ImageContainer(const ImageContainer& other) = delete;
    ImageContainer& operator=(const ImageContainer& other) = delete;
};

#endif /* ImageContainer_hpp */
