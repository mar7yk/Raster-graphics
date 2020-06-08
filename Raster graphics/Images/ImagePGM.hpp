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
    
public:
    ImagePGM(const String& name);
    ImagePGM(const ImagePGM img1, const ImagePGM img2, const String& name, const Command type);
    
    void grayscale() override;
    void monochrome() override;
    void negative() override;
    void rotateLeft() override;
    void rotateRight() override;
    
    void save() override;
    void saveAs(const String& name) override;
};

#endif /* ImagePGM_hpp */
