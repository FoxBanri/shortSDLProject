/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LTexture.cpp
 * Author: philip
 * 
 * Created on 25. November 2017, 17:05
 */

#include "LTexture.h"
#include </home/philip/Schreibtisch/C_und_C++/SDL2_test/engine.h>
#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

LTexture::LTexture() {
    SDL_Texture *mTexture = NULL;
    int mWidth = 0;
    int mHeight = 0;
}

LTexture::LTexture(const LTexture& orig) {
}

LTexture::~LTexture() {
    free();
}
void LTexture::free() {
 SDL_DestroyTexture(mTexture);   
}

bool LTexture::loadFromFile(std::string &path, SDL_Renderer* ren) {
    free();
    bool success = false;
    
    
    mTexture = IMG_LoadTexture(ren, path.c_str());
    if(mTexture == NULL) {
        errorLoggerSDL(std::cout, "LoadPNGTexture");
        success = false;
    } else {
        success = true;
    }
    return success;
    
}
