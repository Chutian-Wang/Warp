#include "warp_types.h"

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
public:
    textureSize_t   size;
    color_t*        buffer;
    bool            loaded;

    Texture(textureSize_t size);
    Texture(const char* filename);
    Texture(const Texture& other);
    ~Texture();

    int     load(const char* filename);
    int     save(const char* filename);
    void    free();

};

#endif