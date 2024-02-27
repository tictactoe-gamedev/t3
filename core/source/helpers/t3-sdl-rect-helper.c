#include "t3-helpers.h"

SDL_Rect T3_Helper_SDL_Rect_Init(int x, int y, int w, int h){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}
