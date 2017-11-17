
#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <list>
#include <fstream>
#include <SDL2/SDL_image.h>
#include </home/philip/Schreibtisch/C_und_C++/SDL2_test/stage.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/*void errorFile(string)
 *Posting the errors into a log-file to save them if needed later
 */
void errorFile(const std::string &msg) {
    ofstream errorl("errorlog.txt", ios::app);
    if(!errorl.fail()) {
        
        errorl << msg << std::endl;
        errorl.close();
    }
   
}



/*void cleanup(window, renderer, list<texture>)
 *Cleaning up the SDL window, renderer and textures to not leave a mess after 
 * quitting the program
 */
void cleanup(SDL_Window *window, SDL_Renderer *renderer, std::list<SDL_Texture*>del) {
    if(window != NULL) {
        SDL_DestroyWindow(window);
    }
    if(renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    
        
    for(int i = 1; i <= del.size(); i++) {
        SDL_Texture* destr = del.back();
        del.pop_back();
        SDL_DestroyTexture(destr);
    }
    SDL_Quit();
}



/*void errorLoggerSDL(ostream, string)
 *prints out the occuring SDL-error on commandline and uses errorFile to put
 * the error into the error-log
 */
void errorLoggerSDL(std::ostream &os, const std::string &msg) {
    
    os << msg <<  " error: " << SDL_GetError() << std::endl;
    errorFile(msg+" Error: "+ SDL_GetError());
    
}



/*SDL_Texture* loadBMP(filename, renderer)
 *simple function to load BMPs into a SDL_Texture. It will return the loaded 
 * texture.
 */
SDL_Texture* loadBMP(const std::string &file, SDL_Renderer *renderer) {
    
    SDL_Texture *texture = NULL;
    
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    
    if(loadedImage != NULL) {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        
        if(texture == NULL) {
            errorLoggerSDL(std::cout, "CreateTextureFromSurface");
        }
        
    } else {
        errorLoggerSDL(std::cout, "SDL_LoadBMP");
    }
    return texture;
}



/*SDL_Texture* loadPNG(filename, renderer)
 *simple function to load pngs into a SDL_Texture. It will return the loaded
 * texture.
 */
SDL_Texture* loadPNG(const std::string &file, SDL_Renderer *ren) {
    SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
    if(texture == NULL) {
        errorLoggerSDL(std::cout, "LoadPNGTexture");
        return NULL;
    }
    
    return texture;
}



/*void renderTexture(texture, renderer, x-positions, y-position)
 * short function to render the loaded texture the was given as a 
 * parameter. Maybe I have to app SDL_RenderPresent(renderer) into this.
 * I am not sure how the rendering works.
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
 
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
 
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
    
    
}
/*SDL_Window* init()
 *function to get the initialisation and the process of creation a window out
 * of the main, cause the main is main is too full. If it fail is will return 
 * NULL and if it runs without fail it will return a fullscreen window.
 */
SDL_Window* init() {
    
    SDL_Window *win;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        errorLoggerSDL(std::cout, "SDL_Init, Function init");
        return NULL;
    }
    
    win = SDL_CreateWindow("Game1", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    
    if(win == NULL) {
        errorLoggerSDL(std::cout, "CreateWindow, Function init");
        SDL_Quit();
        return NULL;
    } else {
        return win;
    }   
}


/*SDL_Renderer* setUpRenderer(window)
 *function to get the creation of the renderer and basic setup stuff out of main.
 * If it fails it will return NULL and use the cleanup() to destroy the window
 * and the renderer and also it will use SDL_Quit();
 */
SDL_Renderer* setUpRenderer(SDL_Window* win) {
    
    SDL_Renderer *ren;
    std::list<SDL_Texture*>del;
    
    if(win == NULL) {
        errorFile("Can't create renderer without window, Funcion setUpRenderer()");
        return NULL;
    }
    
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == NULL) {
        errorLoggerSDL(std::cout, "CreateRenderer, Function setUpRenderer");
        cleanup(win, NULL, del);
        return NULL;
    }
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    SDL_RenderClear(ren);
    SDL_RenderPresent(ren);
    return ren;
}


/*int main(argc, argv)
 *Just a usual main-function with way to much code in it. I maybe have to
 * cut it into one or two new functions, cause it looks messy.
 */
int main(int argc, char** argv) {
    
    std::list<SDL_Texture*>deletelist;
    SDL_Window *window;
    SDL_Renderer *renderer;
   
    window = init();
    renderer = setUpRenderer(window);
    
    if(window == NULL || renderer == NULL) {
        return 1;
    }
    
    SDL_Texture *text = loadPNG("Emblem-important.png", renderer);
    deletelist.push_back(text);
    
    renderTexture(text, renderer, 200, 200);
    renderTexture(text, renderer, 300, 300);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    
    cleanup(window, renderer, deletelist);
    errorFile("Keine Fehler");
    return 0;
}

