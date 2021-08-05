//includes the c libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_audio.h>
//debugging & error checking libraries
#include <SDL2/SDL_error.h>
#include <stdio.h>

//default resolution
int width = 640;
int height = 480;

//Initializes SDL 
int main(int argc, char* args[]) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    //Defines the basic needs of the game
    SDL_Window *window;
    SDL_Renderer *renderer;

    //Creates a window to display
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_OPENGL);
    if (window == NULL) 
    {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //Render it
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        printf("Could not render the window: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // load support for the JPG and PNG image formats
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags)
    {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }
  
    //SDL surface
    SDL_Surface* surface = IMG_Load("src/images/480p.jpg");
    if(!surface)
    {
        printf("Error creating surface!\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    //load image into gpu
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(!texture)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
    //render the picture
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    //keeps window open
    SDL_Delay(5000);
    
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
