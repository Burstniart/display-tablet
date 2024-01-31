/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Start SDL & create window
bool init();

//Load media
bool loadMedia();

//Free media & shut down SDL
void close();

//the window to render to
SDL_Window* gWindow = NULL;

//surface contained by the window
SDL_Surface* gScreenSurface = NULL;
  
//image to be loaded and shown on the screen
SDL_Surface* gHelloWorld = NULL;

bool init()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
      success = false;
    }
  else
    {
      //Create window
      gWindow = SDL_CreateWindow("SDL Monika Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if(gWindow == NULL)
	{
	  printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
	  success = false;
	}
      else
	{
	  //Gert window surface
	  gScreenSurface = SDL_GetWindowSurface(gWindow);
	}
    }
  //basically: return true
  return success;
}

bool loadMedia()
{
  //loading success flag
  bool success = true;

  //load splash image
  gHelloWorld = SDL_LoadBMP("kobayashi.bmp");
  if(gHelloWorld == NULL)
    {
      printf("Unable to load image %s! SDL Error: %s\n", "kobayashi.bmp", SDL_GetError());
      success = false;
    }
  return success;
}

void close()
{
  //delocate surface
  SDL_FreeSurface( gHelloWorld);
  gHelloWorld = NULL;

  //destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  //quit SDL subsystems
  SDL_Quit();
}

int main( int argc, char* args[] )
{
  //start up SDL and create window
  if( !init() )
  {
    printf("Failed to initialize!\n");
  }
  else
    {
      //load media
      if( !loadMedia() )
	{
	  printf("Failed to load media!\n");
	}
      else
	{
	  //apply image
	  SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL  );

	  //update the surface
	  SDL_UpdateWindowSurface(gWindow);

	  //hide cursor
	  //	  SDL_ShowCursor(SDL_DISABLE);
	  
	  //hack to get window to stay up
	  SDL_Event e;
	  bool quit = false;
	  while( !quit )
	    {while(SDL_PollEvent(&e) != 0)
		{
		  int x,y;
		  Uint32 buttons = SDL_GetGlobalMouseState(&x, &y);
		  printf("%u buttons, x:%d &  y:%d \n", buttons,x,y);
		  if(e.type == SDL_MOUSEMOTION)
		    {
		      printf("We got a motion event.\n");
		      printf("Current mouse position is: (%d, %d) at window %d\n", e.motion.x, e.motion.y, e.motion.windowID);
		    }
		  if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		    printf("button is: %d\n", e.button.state);

		  //grab cursor
		  /*
		  if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
		    SDL_SetWindowMouseGrab(gWindow, SDL_TRUE);
		  else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT)
		    SDL_SetWindowMouseGrab(gWindow, SDL_FALSE);
		  */

		  //Create mouse event
		  
		  if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT)
		    {
		      SDL_Event mEvent;
		      /*testing
		      mEvent.type = mEvent.button.type = SDL_MOUSEBUTTONDOWN;
		      mEvent.button.button = SDL_BUTTON_LEFT;
		      mEvent.button.x = 600;
		      mEvent.button.y = 400;
		      mEvent.button.state = SDL_PRESSED;
		      */

		      mEvent.type =  SDL_WarpMouseGlobal(400, 600);
		      
		      SDL_PushEvent(&mEvent);
		    }
		  
		  if(e.type == SDL_QUIT)
		    quit = true;
		}
	    }
	}
    }

  //free resources and close SDL
  close();

  return 0;

}
