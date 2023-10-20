#include<SDL2/SDL.h>
#include <stdio.h>
#include<string>
#include<iostream>
#include<SDL2/SDL_image.h>



// Define Screen 
const int SCREEN_WIDTH =640;
const int SCREEN_HEIGHT =480;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_P,
    KEY_PRESS_SURFACE_TOTAL
};
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

bool init(SDL_Window *&ptrWindow, SDL_Surface *&prtScreen, SDL_Renderer *&ptrRenderer){

     bool success = true; 
     //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0){
        printf( "SDL or SDL_image could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false; 
    } else {

        // Create Window
        ptrWindow = SDL_CreateWindow("Mein Erstes SDL Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                     SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (ptrWindow == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
            } else {
                //Get window surface
                prtScreen = SDL_GetWindowSurface(ptrWindow);

                ptrRenderer = SDL_CreateRenderer(ptrWindow, -1, SDL_RENDERER_ACCELERATED);
                if (ptrRenderer == nullptr) {
                    std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;

                }else{
                    SDL_SetRenderDrawColor(ptrRenderer, 0xFF,0xFF,0xFF,0xFF);
                }
            }
        }
    return success;
}

void close(SDL_Window *&ptrWindow){
    //Destroy window
    SDL_DestroyWindow( ptrWindow );

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface(const std::string& path){

    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if(surface == nullptr){
        std::cout << "Error Loading Surface on" << path <<"." << SDL_GetError()<< std::endl;
    }
    return  surface;
}



SDL_Texture *loadTexture(const std::string &path, SDL_Renderer *&ptrRenderer){
    SDL_Texture* newTexture = nullptr;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        std::cout << "Unable to Load Image: " << IMG_GetError() << std::endl;
    }else{
        newTexture = SDL_CreateTextureFromSurface(ptrRenderer,loadedSurface);
    }
    if(newTexture == nullptr){
        std::cout << "Unable to Load Texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(loadedSurface);

    return  newTexture;

}

void loadMedia(SDL_Texture *&ptrTexture, SDL_Renderer *& ptrRenderer){
    /*
    std::string assetPath = "../assets/";

    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( assetPath+"press.bmp" );
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( assetPath+"up.bmp" );
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( assetPath+"down.bmp" );
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( assetPath+"left.bmp" );
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( assetPath+"right.bmp" );
    */
    // Load JPG
    ptrTexture = loadTexture("../assets/blackhole.jpg", ptrRenderer);

}


int main( int argc, char* args[] )
{

    //The window we'll be rendering to
    SDL_Window *window = nullptr;

    //The surface contained by the window
    SDL_Surface *screenSurface = nullptr;
    SDL_Renderer * renderer = nullptr;
    SDL_Texture* texture = nullptr;



    if(!init(window,screenSurface, renderer)){
        printf("Failed to init Game \n");
    }

    loadMedia(texture,renderer);
    //SDL_Surface *currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];


    bool quit =false; 
    
    //Event handler
    SDL_Event e;

    while(!quit){
    //User requests quit
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            /* else if (e.type == SDL_KEYDOWN) {
                //Select surfaces based on key press
                switch (e.key.keysym.sym) {

                    case SDLK_UP:
                        currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                        break;

                    case SDLK_DOWN:
                        currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                        break;

                    case SDLK_LEFT:
                        currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                        break;

                    case SDLK_RIGHT:
                        currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;

                    case SDLK_p:
                        currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_P];
                        break;

                    default:
                        currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }
            }*/
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        /*
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(currentSurface, nullptr, screenSurface, nullptr);
        SDL_UpdateWindowSurface(window);
        */
        SDL_Delay(10);
    }

    printf("Clear Stuff");
    close(window);
    
    return 0;
}

