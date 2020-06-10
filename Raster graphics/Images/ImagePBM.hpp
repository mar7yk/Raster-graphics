//
//  ImagePBM.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef ImagePBM_hpp
#define ImagePBM_hpp

#include <stdio.h>
#include <fstream>

#include "Image.h"

#include "Matrix.h"

using MatrixPBM = Matrix<bool>;

class ImagePBM: public Image {
    MatrixPBM pixels;
    
    void load(const String& name) override;
    
public:
    ImagePBM(const String& name);
    
    
    /// Създава колаж от две снимки
    ///
    /// @param img1 първа снима
    /// @param img2 втора снимка
    /// @param name име на колажа
    /// @param type тип на колажа (CollageHorizontal или CollageVertical)
    ImagePBM(const ImagePBM& img1, const ImagePBM& img2, const String& name, const Command type);
    
    void grayscale() override;
    void monochrome() override;
    void negative() override;
    void rotateLeft() override;
    void rotateRight() override;
    
    void save() override;
    void saveAs(const String& name) override;
};

#endif /* ImagePBM_hpp */
