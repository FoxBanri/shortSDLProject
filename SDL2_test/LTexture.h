/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LTexture.h
 * Author: philip
 *
 * Created on 25. November 2017, 17:05
 */

#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <SDL2/SDL_image.h>
class LTexture {
    
public:
    LTexture();
    LTexture(const LTexture& orig);
    virtual ~LTexture();
    bool loadFromFile(std::string &path, SDL_Renderer* ren);
    void free();
    void render(int x, int y);
    int getWidth();
    int getHeight();
    
private:
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;

};

#endif /* LTEXTURE_H */

