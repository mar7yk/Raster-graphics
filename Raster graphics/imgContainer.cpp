//
//  imgContainer.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 24.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "imgContainer.hpp"




ImageContainer::~ImageContainer() {
    for (size_t i = 0; i < f_size; ++i) {
        delete images[i];
    }
    delete [] images;
}


ImageContainer::ImageContainer(): f_size(0), f_capacity(8) {
    images = new Image*[f_capacity];
}

Image *ImageContainer::getImg(const String &name) const {
    Image *img = nullptr;
    for (size_t i = 0; i < f_size; ++i) {
        if (images[i]->getName() == name) {
            return images[i];
        }
    }
    return img;
}

size_t ImageContainer::size() const{
    return f_size;
}


void ImageContainer::add(Image*const img) {
    if(f_size == f_capacity) {
        resize(2*f_size);
    }
    images[f_size] = img;
    ++f_size;
}

void ImageContainer::resize(const size_t newCapacity) {
    delete [] images;
    f_capacity = newCapacity;
    images = new Image*[f_capacity];
}

void ImageContainer::doInst(const command c) {
    switch (c) {
        case command::grayscale:
            for (size_t i = 0; i < f_size; ++i)
                images[i]->grayscale();
            break;
        case command::monochrome:
            for (size_t i = 0; i < f_size; ++i)
                images[i]->monochrome();
            break;
        case command::negative:
            for (size_t i = 0; i < f_size; ++i)
                images[i]->negative();
            break;
        case command::rotateLeft:
            for (size_t i = 0; i < f_size; ++i)
                images[i]->rotateLeft();
            break;
        case command::rotateRight:
            for (size_t i = 0; i < f_size; ++i)
                images[i]->rotateRight();
            break;
            
        default:
            break;
    }
}

void ImageContainer::doInstForFirst(const command c) {
    switch (c) {
        case command::grayscale:
            images[0]->grayscale();
            break;
        case command::monochrome:
            images[0]->monochrome();
            break;
        case command::negative:
            images[0]->negative();
            break;
        case command::rotateLeft:
            images[0]->rotateLeft();
            break;
        case command::rotateRight:
            images[0]->rotateRight();
            break;
            
        default:
            break;
    }
}

void ImageContainer::save() {
    for (size_t i = 0; i < f_size; ++i) {
        images[i]->save();
    }
}

void ImageContainer::saveAs(const String& name) {
    images[0]->saveAs(name);
}

Image*& ImageContainer::operator[](const size_t n) const {
    return images[n];
}

