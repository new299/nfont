#include <string.h>
#include <SDL/SDL.h>
#include <iostream>

using namespace std;
#include "nfont.h"

int main(int argc, char **argv) {

  SDL_Surface *screen;
 
  if(SDL_Init(SDL_INIT_VIDEO)<0) {
    cout << "Failed SDL_Init " << SDL_GetError() << endl;
    return 1;
  }
 
  screen=SDL_SetVideoMode(800,600,32,SDL_ANYFORMAT);
  if(screen==NULL) {
    cout << "Failed SDL_SetVideoMode: " << SDL_GetError() << endl;
    SDL_Quit();
    return 1;
  }
 
  for(;;) {
    SDL_Flip(screen);
    SDL_LockSurface(screen);

    string hello = "Hello World!";
    uint32_t highlight = rand()%2;
    if(highlight == 1) highlight=-1;
    draw_text(screen,rand()%500,rand()%500,hello.c_str(),highlight);

    SDL_UnlockSurface(screen);
  }
  SDL_Quit();
 
  return 0;

}
