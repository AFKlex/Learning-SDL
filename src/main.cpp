#include<SDL2/SDL.h>
#include <stdio.h>

// Define Screen 
const int SCREEN_WIDTH =640; 
const int SCREEN_HEIGHT = 480;

bool initalize_Game(SDL_Window *window, SDL_Surface *screenSurface ){
     
     bool success = true; 
     //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false; 
    } else {
        // Create Window 
        window = SDL_CreateWindow("Mein Erstes SDL Program", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false; 
        }else{
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );
        }
    }

    return success;
}

bool destroy_Game(SDL_Window* window){
    bool success = true;
    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
    return success; 
}

bool load_content(){
    bool success = true;

    return success;
}

int main( int argc, char* args[] )
{
    //The window we'll be rendering to
    SDL_Window* window = nullptr;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = nullptr;

   initalize_Game(window,screenSurface);


   //Hack to get window to stay up
   SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
   destroy_Game(window); 
    
    return 0;
}

