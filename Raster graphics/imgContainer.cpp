//
//  imgContainer.cpp
//  Raster graphics
//
//  Created by Marty Kostov on 24.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#include "imgContainer.hpp"


void ImageContainer::resize(const size_t newCapacity) {
    delete [] images;
    capacity = newCapacity;
    images = new Image*[capacity];
}

ImageContainer::ImageContainer(): size(0), capacity(8) {
    images = new Image*[capacity];
}

ImageContainer::~ImageContainer() {
    for (size_t i = 0; i < size; ++i) {
        delete images[i];
    }
    delete [] images;
}

void ImageContainer::add(Image*const img) {
    if(size == capacity) {
        resize(2*size);
    }
    images[size] = img;
    ++size;
}

void ImageContainer::add(const ImagePPM& img) {
    if(size == capacity) {
        resize(2*size);
    }
    images[size] = new ImagePPM(img);
    ++size;
}

void ImageContainer::add(const ImagePGM& img) {
    if(size == capacity) {
        resize(2*size);
    }
    images[size] = new ImagePGM(img);
    ++size;
}

void ImageContainer::add(const ImagePBM& img) {
    if(size == capacity) {
        resize(2*size);
    }
    images[size] = new ImagePBM(img);
    ++size;
}

Image *ImageContainer::getImg(const String &name) const {
    Image *img = nullptr;
    for (size_t i = 0; i < size; ++i) {
        if (images[i]->getName() == name) {
            return images[i];
        }
    }
    return img;
};

Image*& ImageContainer::operator[](const size_t n){
    return images[n];
}

size_t ImageContainer::getSize(){
    return size;
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

void ImageContainer::doInst(const command c) {
    switch (c) {
        case command::grayscale:
            for (size_t i = 0; i < size; ++i)
                images[i]->grayscale();
            break;
        case command::monochrome:
            for (size_t i = 0; i < size; ++i)
                images[i]->monochrome();
            break;
        case command::negative:
            for (size_t i = 0; i < size; ++i)
                images[i]->negative();
            break;
        case command::rotateLeft:
            for (size_t i = 0; i < size; ++i)
                images[i]->rotateLeft();
            break;
        case command::rotateRight:
            for (size_t i = 0; i < size; ++i)
                images[i]->rotateRight();
            break;
            
        default:
            break;
    }
}

void ImageContainer::saveAs(const String& name) {
    images[0]->saveAs(name);
}


void ImageContainer::save() {
    for (size_t i = 0; i < size; ++i) {
        images[i]->save();
    }
}



