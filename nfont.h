#ifndef NFONT
#define NFONT

#ifdef __cplusplus 
extern "C" {
#endif

#include <SDL/SDL.h>

void draw_text(SDL_Surface *screen,int x,int y,const char *text,int16_t background);

#ifdef __cplusplus 
}
#endif
#endif
