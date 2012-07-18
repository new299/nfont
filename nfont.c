#ifndef NFONT
#define NFONT

#include "nfont.h"
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>

extern uint8_t _binary_font_data_start;
extern uint8_t _binary_font_data_size;

uint32_t get_pixel(char c,int c_x,int c_y) {
  
  int ypos = (c/(128/8)) * 16;
  int xpos = (c%(128/8)) * 8;
  ypos+=1;

  int bitposition = ((ypos*128)+(c_y*128) + (xpos)+c_x) *2;

  int byte_position = bitposition/8;
  int bit_in_byte   = 7-(bitposition%8);

  uint8_t byte = ((uint8_t *) &_binary_font_data_start)[byte_position];
  
  uint32_t value=0;
  if((byte & (1 << bit_in_byte)) > 0) value += 2;
  
  bit_in_byte--;
  if((byte & (1 << bit_in_byte)) > 0) value += 1;
  if(value == 0) {value = 0;   }
  if(value == 1) {value = 85;  }
  if(value == 2) {value = 170; }
  if(value == 3) {value = 255; }

  return (value << 16) | (value << 8) | value;
}

void draw_point(SDL_Surface *screen,int x,int y,int value) {

  int bpp = screen->format->BytesPerPixel;
  Uint8 *p = (Uint8 *) screen->pixels + y * screen->pitch + x * bpp;
  if((x<0)||(y<0)|| (x>=screen->w)||(y>=screen->h)) return;

  *(Uint32 *) p = value;
}

void draw_character(SDL_Surface *screen,int x,int y,char c,uint16_t background) {

  for(size_t c_y=0;c_y<16;c_y++) {
    for(size_t c_x=0;c_x<8;c_x++) {
      int32_t value = get_pixel(c-32,c_x,c_y) - background;
      if(value < 0) value=0;

      if(background == 65535) value = background ^ get_pixel(c-32,c_x,c_y); 

      draw_point(screen,x+c_x,y+c_y,value);
    }
  }
}

void draw_text(SDL_Surface *screen,int x,int y,char *text,int16_t background) {

  int length = strlen(text);
  if(length < 0    ) return;
  if(length > 10000) return;

  int c_x = x;
  int c_y = y;
  for(size_t n=0;n<length;n++) {
    draw_character(screen,c_x,c_y,text[n],background);
    c_x+=8;
  }
}


#endif
