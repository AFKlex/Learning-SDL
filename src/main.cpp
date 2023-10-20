#include<SDL2/SDL.h>
#include <stdio.h>



// Define Screen 
const int SCREEN_WIDTH =680;
const int SCREEN_HEIGHT =400;

bool init(SDL_Window *&ptrWindow, SDL_Surface *&prtScreen){

     bool success = true; 
     //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf( "SDL or SDL_image could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false; 
    } else {
        // Create Window 
        ptrWindow = SDL_CreateWindow("Mein Erstes SDL Program", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( ptrWindow == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false; 
        }else{
            //Get window surface
            prtScreen = SDL_GetWindowSurface( ptrWindow );

            //Fill the surface white
            //SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            //SDL_UpdateWindowSurface( window );
        }
    }

    return success;
}

void close(SDL_Window *&ptrWindow, SDL_Surface *&ptrImage){
    //Destroy window
    SDL_DestroyWindow( ptrWindow );

    SDL_FreeSurface(ptrImage);
    ptrWindow = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

bool load_media(SDL_Surface *&ptrImage){
    bool success = true;

    ptrImage = SDL_LoadBMP( "/home/afklex/OneDrive/04_Programmieren/C++/Learning SDL/assets/dots.bmp" );
    if(ptrImage == nullptr ){
        printf( "Unable to load image %s! SDL Error: %s\n", "/home/afklex/OneDrive/04_Programmieren/C++/Learning SDL/assets/dots.bmp", SDL_GetError() );
        success = false; 
    }

    return success;

}

int main( int argc, char* args[] )
{

    //The window we'll be rendering to
    SDL_Window *window = nullptr;

    //The surface contained by the window
    SDL_Surface *screenSurface = nullptr;

    SDL_Surface *image = nullptr;

    if(!init(window,screenSurface)){
        printf("Failed to init Game \n");
    }
    else{    
        if(!load_media(image)){
            printf("Failed to Load image \n");
    }else{
        printf("Loaded Image \n"); 
        SDL_BlitSurface(image, nullptr, screenSurface, nullptr); 
        SDL_UpdateWindowSurface(window);
    }

    }

    bool quit =false; 
    
    //Event handler
    SDL_Event e;

    while(!quit){
    //User requests quit
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            if( e.type == SDL_QUIT ){
                quit = true;
                }
            }
            SDL_Delay(10);   
    }

    printf("Clear Stuff");
    close(window,image);
    
    return 0;
}

