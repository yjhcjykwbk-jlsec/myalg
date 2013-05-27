#include "SDL/SDL.h"

const static unsigned width     = 1280;
const static unsigned height    = 720;

void render(SDL_Surface* surface)
{
   SDL_LockSurface(surface);
   auto row = reinterpret_cast<unsigned char*>(surface->pixels);
   for (unsigned y = 0; y < height; ++y)
   {
       auto p = reinterpret_cast<Uint32*>(row);
       for (unsigned x = 0; x < width; ++x)
           *p++ = SDL_MapRGB(surface->format, x % 255, x % 255, x % 255);
       row += surface->pitch;
   }
   SDL_UnlockSurface(surface);
   SDL_UpdateRect(surface, 0, 0, 0, 0);
}

int main(int argc, char *argv[])
{
   SDL_Init(SDL_INIT_VIDEO);
   atexit(SDL_Quit);
   SDL_Surface* screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
   if (!screen)
       return 1;
   render(screen);    
   SDL_Event event;
   while (SDL_WaitEvent(&event))
   {
       switch (event.type)
       {
       case SDL_KEYUP:
           if (event.key.keysym.sym == SDLK_ESCAPE)
               return 0;
           break;
       case SDL_QUIT:
           return 0;
       }
   }
   return 0;
}
