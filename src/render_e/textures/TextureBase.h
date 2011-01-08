/* 
 * File:   TextureBase.h
 * Author: morten
 *
 * Created on November 12, 2010, 11:50 AM
 */

#ifndef TEXTUREBASE_H
#define	TEXTUREBASE_H

#include <string>

namespace render_e {


enum TextureLoadStatus{
    ERROR,
    ERROR_READING_FILE,
    INVALID_FORMAT,
    OK
};

enum TextureFormat {
    RGB,
    RGBA,
    DEPTH
};

class TextureBase {
public:
    TextureBase(int textureType);
    virtual ~TextureBase();
    
    virtual TextureLoadStatus Load() = 0;
    virtual void Create(int width, int height, TextureFormat textureFormat) = 0;
    void Bind();
    void Unbind();
    void Unload();
    void SetName(std::string name) { this->name = name;}
    std::string GetName() {return name; }
    int GetTextureId() { return textureId; }
    int GetTextureType() { return textureType; }
    int GetWidth(){ return width; }
    int GetHeight(){ return height; }
protected:
    int textureType;
    unsigned int textureId;
    bool mipmapping;
    std::string name;
    int width;
    int height;
private:
    TextureBase(const TextureBase& orig); // disallow copy constructor
    TextureBase& operator = (const TextureBase&); // disallow copy constructor
};

}

#endif	/* TEXTUREBASE_H */

