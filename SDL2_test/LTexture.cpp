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
/*
 *Constructor 1
 */
LTexture::LTexture(SDL_Renderer* ren) {
    SDL_Texture *mTexture = NULL;
    int mWidth = 0;
    int mHeight = 0;
    SDL_Renderer *mRen = ren;
}

/*
 *Constructor 2
 */

LTexture::LTexture(const LTexture& orig) {
}

/*
 *Destructor
 */

LTexture::~LTexture() {
    free();
}

/*LTexture::free()
 * Function to destroy the real SDL_Texture, so the memory is clean.
 */
void LTexture::free() {
 SDL_DestroyTexture(mTexture);   
}

/*LTexture::loadFromFile(std::string &path)
 * Destroys mTexture, if LTexture already has a mTexture, to load new one.
 * Uses errorLoggerSDL, if there goes something wrong while loading the texture.
 * Retruns true if the loading was successful and false if it failed. It also fills
 * in the correct values for mHeight and mWidth.
 */

bool LTexture::loadFromFile(std::string &path) {
    free();
    bool success = false;
    
    
    mTexture = IMG_LoadTexture(mRen, path.c_str());
    if(mTexture == NULL) {
        errorLoggerSDL(std::cout, "LoadPNGTexture");
        success = false;
    } else {
        success = true;
    }
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
    return success;
    
}

/*LTexture::getHeight()
 *Simple getter to return mHeight.
 */

int LTexture::getHeight() {
    return mHeight;
}

/*LTexture::getWidth()
 *Simple Getter to return mWidth.
 */

int LTexture::getWidth() {
    return mWidth;
}

void LTexture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    
    if(clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(mRen, mTexture, clip, &renderQuad);
}

