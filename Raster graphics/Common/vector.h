//
//  vector.h
//  FMIBOOK
//
//  Created by Marty Kostov on 24.05.20.
//  Copyright © 2020 Marty Kostov. All rights reserved.
//

#ifndef vector_h
#define vector_h

template <typename T>
class Vector {
    T* arr;
    size_t f_size;
    size_t f_capacity;
    
    
    
    void copy(const Vector& other){
        f_size = other.f_size;
        f_capacity = other.f_capacity;
        arr = new T[f_capacity];
        for (size_t i = 0; i < f_size; ++i) {
            arr[i] = other.arr[i];
        }
    }
    
    void del() {
        delete [] arr;
    }
    
public:
    Vector() : f_size(0), f_capacity(8) {
        arr = new T[f_capacity];
    }

    Vector(size_t size) : f_size(size), f_capacity(size*2) {
        arr = new T[f_capacity];
    }

    Vector(const Vector& other) {
        copy(other);
    }
    
    Vector(Vector&& other) {
        f_size = other.f_size;
        f_capacity = other.f_capacity;
        arr = other.arr;
        
        other.f_size = 0;
        other.f_capacity = 0;
        other.arr = nullptr;
    }

    ~Vector() {
        del();
    }
    
    Vector& operator=(const Vector<T>& other) {
        if (this != &other) {
            del();
            copy(other);
        }
        return *this;
    }
    
    size_t size() const {
        return f_size;
    }
    
    size_t capacity() const {
        return f_capacity;
    }
    
    void reserve(size_t newCapacity) {
        if (newCapacity > f_capacity) {
            f_capacity = newCapacity;
            T* buff = new T[f_capacity];
            for (size_t i = 0; i < f_size; ++i) {
                buff[i] = arr[i];
            }
            
            delete [] arr;
            arr = buff;
        }
    }
    
    void resize(size_t newSise) {
        if (f_capacity < newSise)
            reserve(newSise * 2);
        
        f_size = newSise;
    }
    
    void push_back(T el) {
        if (f_capacity == f_size)
            reserve(f_size * 2);
        
        arr[f_size] = el;
        
        ++f_size;
    }
    
    bool empty() {
        return !f_size;
    }
    
    T& front() const {
        return arr[0];
    }
    
    T& back() const {
        return arr[f_size - 1];
    }
    
    T* begin() const {
        return &arr[0];
    }
    
    T* end() {
        return &arr[f_size - 1];
    }
    
    void pop_back() {
        if (!empty()) {
            --f_size;
        }
    }
    
    void clear() {
        f_size = 0;
    }
    
    const T& operator[](size_t i) const {
        return arr[i];
    }
    
    T& operator[](size_t i) {
        return arr[i];
    }
};

#endif /* vector_h */
