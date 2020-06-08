//
//  ImagePPM.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 10.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef ImagePPM_hpp
#define ImagePPM_hpp

#include <stdio.h>
#include <fstream>

#include "Image.h"

#include "Matrix.h"
#include "pixel_RGB.h"

using MatrixPPM = Matrix<pixel_RGB>;

class ImagePPM: public Image {
    unsigned maxValForCalor;
    MatrixPPM pixels;
    
public:
    ImagePPM(const String& name);
    ImagePPM(const ImagePPM img1, const ImagePPM img2, const String& name, const Command type);
    
    void grayscale() override;
    void monochrome() override;
    void negative() override;
    void rotateLeft() override;
    void rotateRight() override;
    
    void save() override;
    void saveAs(const String& name) override;
};
#endif /* ImagePPM_hpp */
