#include<SDL2/SDL.h>
#include <stdio.h>
#include<SDL2/SDL_image.h>


// Define Screen 
const int SCREEN_WIDTH =1000; 
const int SCREEN_HEIGHT =1000;

bool initalize_Game(SDL_Window *window, SDL_Surface *screenSurface ){
     
     bool success = true; 
     //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 || IMG_Init(IMG_INIT_JPG) == 0)
    {
        printf( "SDL or SDL_image could not initialize! SDL_Error: %s\n", SDL_GetError() );
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
            //SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            //SDL_UpdateWindowSurface( window );
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

bool load_media(SDL_Surface** media_pointer){
    bool success = true; 

    *media_pointer = SDL_LoadBMP( "/home/afklex/OneDrive/04_Programmieren/C++/Learning SDL/assets/dots.bmp" );
    if(*media_pointer == nullptr ){
        printf( "Unable to load image %s! SDL Error: %s\n", "/home/afklex/OneDrive/04_Programmieren/C++/Learning SDL/assets/dots.bmp", SDL_GetError() );
        success = false; 
    }

    return success;

}

int main( int argc, char* args[] )
{
    //The window we'll be rendering to
    SDL_Window* window = nullptr;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = nullptr;

    SDL_Surface* image = nullptr; 

    if(!initalize_Game(window,screenSurface)){
        printf("Failed to initalize! Game \n");
    }
    else{    
        if(!load_media(&image)){
            printf("Failed to Load image \n");
    }else{
        printf("Loaded Image \n"); 
        SDL_BlitSurface(image, nullptr, screenSurface, nullptr); 
        SDL_UpdateWindowSurface(window);
        SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }  

    }

    }

    

    /*
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

    */
   printf("Clear Stuff");
    SDL_FreeSurface(image); 
    image = nullptr; 
    destroy_Game(window); 
    
    return 0;
}

