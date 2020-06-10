//
//  ImagePGM.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef ImagePGM_hpp
#define ImagePGM_hpp

#include <stdio.h>
#include <fstream>

#include "Image.h"

#include "Matrix.h"

using MatrixPGM = Matrix<unsigned char>;

class ImagePGM: public Image {
    unsigned maxValForCalor;
    MatrixPGM pixels;
    
    void load(const String& name) override;
    
public:
    ImagePGM(const String& name);
    
    /// Създава колаж от две снимки
    ///
    /// @param img1 първа снима
    /// @param img2 втора снимка
    /// @param name име на колажа
    /// @param type тип на колажа (CollageHorizontal или CollageVertical)
    ImagePGM(const ImagePGM& img1, const ImagePGM& img2, const String& name, const Command type);
    
    void grayscale() override;
    void monochrome() override;
    void negative() override;
    void rotateLeft() override;
    void rotateRight() override;
    
    void save() override;
    void saveAs(const String& name) override;
};

#endif /* ImagePGM_hpp */
