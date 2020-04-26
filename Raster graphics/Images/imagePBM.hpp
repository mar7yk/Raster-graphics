//
//  imagePBM.hpp
//  Raster graphics
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef imagePBM_hpp
#define imagePBM_hpp

#include <stdio.h>
#include <fstream>

#include "Image.h"

using MatrixPBM = Matrix<bool>;

class ImagePBM: public Image {
    MatrixPBM pixels;
    
public:
    ImagePBM(const String& name);
    
    
    ImagePBM(const ImagePBM img1, const ImagePBM img2, const String& name, const command type);
    
    void grayscale() override;
    
    void monochrome() override;
    
    void negative() override;
    
    void rotateLeft() override;
    
    void rotateRight() override;
    
    void saveAs(const String& name) override;
    
    
    void save() override;
};

#endif /* imagePBM_hpp */
