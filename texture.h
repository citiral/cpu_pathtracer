#pragma once

#include <cstdlib>

template <class T>
class Texture {
public:
    Texture(int width, int height): width(width), height(height) {
        buffer = new T[width * height];
        for (size_t i = 0 ; i < width * height ; i++)
            buffer[i] = T();
    }

    ~Texture() {
        delete buffer;
    }

    void set_pixel(int x, int y, T& val) {
        buffer[(x + y * width)] = val;
    }

    void set_pixel(int x, int y, T&& val) {
        buffer[x + y * width] = val;
    }

    void add_pixel(int x, int y, T& val) {
        buffer[x + y * width] += val;
    }

    void add_pixel(int x, int y, T&& val) {
        buffer[x + y * width] += val;
    }

    T& get_pixel(int x, int y) {
        return buffer[x + y * width];
    }
    
    T* buffer;
    int width;
    int height;
};
