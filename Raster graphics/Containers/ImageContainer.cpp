//
//  ImageContainer.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 24.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "ImageContainer.hpp"


ImageContainer::~ImageContainer() {
    for (size_t i = 0; i < images.size(); ++i) {
        delete images[i];
    }
}

Image *ImageContainer::getImg(const String &name) const {
    Image *img = nullptr;
    for (size_t i = 0; i < images.size(); ++i) {
        if (images[i]->getName() == name) {
            return images[i];
        }
    }
    return img;
}

size_t ImageContainer::size() const{
    return images.size();
}


void ImageContainer::add(Image*const img) {
    images.push_back(img);
}

void ImageContainer::doInstructions(const Command c) {
    switch (c) {
        case Command::Grayscale:
            for (size_t i = 0; i < images.size(); ++i)
                images[i]->grayscale();
            break;
        case Command::Monochrome:
            for (size_t i = 0; i < images.size(); ++i)
                images[i]->monochrome();
            break;
        case Command::Negative:
            for (size_t i = 0; i < images.size(); ++i)
                images[i]->negative();
            break;
        case Command::RotateLeft:
            for (size_t i = 0; i < images.size(); ++i)
                images[i]->rotateLeft();
            break;
        case Command::RotateRight:
            for (size_t i = 0; i < images.size(); ++i)
                images[i]->rotateRight();
            break;
            
        default:
            break;
    }
}

void ImageContainer::doInstructionsForFirst(const Command c) {
    switch (c) {
        case Command::Grayscale:
            images[0]->grayscale();
            break;
        case Command::Monochrome:
            images[0]->monochrome();
            break;
        case Command::Negative:
            images[0]->negative();
            break;
        case Command::RotateLeft:
            images[0]->rotateLeft();
            break;
        case Command::RotateRight:
            images[0]->rotateRight();
            break;
            
        default:
            break;
    }
}

void ImageContainer::save() {
    for (size_t i = 0; i < images.size(); ++i) {
        images[i]->save();
    }
}

void ImageContainer::saveAs(const String& name) {
    images[0]->saveAs(name);
}

Image* &ImageContainer::operator[](const size_t n) {
    return images[n];
}

const Image *const ImageContainer::operator[](const size_t n) const {
    return images[n];
}
