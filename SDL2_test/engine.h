/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   engine.h
 * Author: philip
 *
 * Created on 23. November 2017, 17:03
 */

#ifndef ENGINE_H
#define ENGINE_H

void errorFile(const std::string &msg);

void cleanup(SDL_Window *window, SDL_Renderer *renderer, std::list<SDL_Texture*>del);

void errorLoggerSDL(std::ostream &os, const std::string &msg);

void useViewport(int x, int y, int w, int h, SDL_Renderer *ren);

SDL_Texture* loadBMP(const std::string &file, SDL_Renderer *renderer);

SDL_Texture* loadPNG(const std::string &file, SDL_Renderer *ren);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

SDL_Window* init();

SDL_Renderer* setUpRenderer(SDL_Window* win);

#endif /* ENGINE_H */

