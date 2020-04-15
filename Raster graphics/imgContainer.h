//
//  imgContainer.h
//  dev
//
//  Created by Marty Kostov on 11.04.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef imgContainer_h
#define imgContainer_h

#include <stdio.h>

#include "imagePPM.hpp"
#include "imagePGM.hpp"
#include "imagePBM.hpp"

#include "command.h"

template<typename imgType>
class ImgContainer {
    size_t size;
    size_t capacity;
    imgType *images;
    
    void resize(const size_t newCapacity) {
        delete [] images;
        capacity = newCapacity;
        images = new(std::nothrow) imgType[capacity];
    }
    
public:
    ImgContainer(): size(0), capacity(8) {
        images = new(std::nothrow) imgType[capacity];
    }
    ~ImgContainer() {
        delete [] images;
    }
    void add(const imgType& img) {
        if(size == capacity) {
            resize(2*size);
        }
        images[size] = img;
        ++size;
    }
    
    imgType& operator[](const size_t n){
        return images[n];
    }
    
//    ImgContainer& operator=(const ImgContainer& other){
//        if(this != &other){
//            size = other.size;
//            capacity = other.capacity;
//            delete [] images;
//            images = new(std::nothrow) imgType[capacity];
//            for (size_t i = 0; i < size; ++i)
//                images[i] = other.images[i];
//        }
//        return *this;
//    }
};


class ImageContainer {
    size_t size;
    size_t capacity;
    Image **images;
    
    void resize(const size_t newCapacity) {
        delete [] images;
        capacity = newCapacity;
        images = new(std::nothrow) Image*[capacity];
    }
    
public:
    ImageContainer(): size(0), capacity(8) {
        images = new(std::nothrow) Image*[capacity];
    }
    ImageContainer(const ImageContainer& other) = delete;
    ImageContainer& operator=(const ImageContainer& other) = delete;
    ~ImageContainer() {
        //TODO: TO ASK WHY NOT
//        for (size_t i = 0; i < size; ++i) {
//            delete images[i];
//        }
        delete [] images;
    }
    
    void add(const ImagePPM& img) {
        if(size == capacity) {
            resize(2*size);
        }
        images[size] = new ImagePPM(img);
        ++size;
    }
    
    void add(const ImagePGM& img) {
        if(size == capacity) {
            resize(2*size);
        }
        images[size] = new ImagePGM(img);
        ++size;
    }
    
    void add(const ImagePBM& img) {
        if(size == capacity) {
            resize(2*size);
        }
        images[size] = new ImagePBM(img);
        ++size;
    }
    Image*& operator[](const size_t n){
        return images[n];
    }
    
    size_t getSize(){
        return size;
    }
    
    void doInstForFirst(const command c) {
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
    
    void doInst(const command c) {
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
    
    void saveAs(const String& name) {
        images[0]->saveAs(name);
    }
    
    
    void save() {
        for (size_t i = 0; i < size; ++i) {
            images[i]->save();
        }
    }
};

#endif /* imgContainer_h */
