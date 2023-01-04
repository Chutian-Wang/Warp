#include "texture.h"
#include <fstream>

Texture::Texture(textureSize_t size) {
    this->size = size;
    buffer = new color_t[size.width * size.height];
    loaded = true;
}

Texture::Texture(const char* filename) {
    this->loaded = false;
    this->buffer = nullptr;
    this->load(filename);
}

Texture::~Texture() {
    delete[] buffer;
}

Texture::Texture(const Texture& other) {
    this->size = other.size;
    this->loaded = other.loaded;
    this->buffer = new color_t [size.width * size.height];
    for (size_t i = 0; i < size.height * size.width; ++i) {
        this->buffer[i] = other.buffer[i];
    }
}

/**
 * Writes texture.size and content of buffer to a binary
 * file given by filename. The filename is a relative path.
 * If the file cannot be opened, the returned error code is -1.
 */
int Texture::save(const char* filename) {
    std::fstream fs;
    fs.open(filename, std::fstream::out | std::fstream::binary);
    // Error state -1: cannot open file.
    if (!fs) return -1;
    fs.write((char*)(&size), sizeof(textureSize_t));
    fs.write((char*)buffer, sizeof(color_t) * size.width * size.height);
    fs.close();
    // Return 0 upon success.
    return 0;
}

/**
 * Reads texture.size and content of buffer from the given file.
 * If a texture is already loaded, it is overwritten and the function
 * returns success status 1. If the file cannot be opened, the function
 * returns error status -1. If the file content cannot be recognized,
 * the function returns error status -2. Either error case preserves the
 * buffer content.
 */
int Texture::load(const char* filename) {
    int ret = 0;
    if (loaded == true) {
        // Success state 1: overwrite texture.
        // The buffer will be freed if a overwrite operation is possible.
        ret = 1;
    }
    std::fstream fs;
    fs.open(filename, std::fstream::in | std::fstream::binary);
    // Error state -1: cannot open file.
    if (!fs) return -1;

    // Get length of file:
    fs.seekg (0, fs.end);
    int length = fs.tellg();
    fs.seekg (0, fs.beg);

    fs.read((char*)(&size), sizeof(textureSize_t));
    if (length != sizeof(textureSize_t) + 
        sizeof(color_t) * size.width * size.height) {
        // An overwrite operation is not possible.
        // Error state -2: file contents are corrupted.
        fs.close();
        return -2;
    }
    if (ret == 1) delete[] buffer;
    buffer = new color_t[size.width * size.height];
    fs.read((char*)buffer, sizeof(color_t) * size.width * size.height);
    loaded = true;
    fs.close();
    return ret;
}

void Texture::free() {
    delete[] buffer;
    loaded = false;
    buffer = nullptr;
}