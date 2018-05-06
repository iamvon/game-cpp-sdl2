// #include "message.h"

// void Message::drawMsg(const char* msg, int x, int y, int r, int g, int b) {
//  SDL_Surface* surf;
//  SDL_Texture* tex;
//  SDL_Color color;
//  color.r=r;
//  color.g=g;
//  color.b=b;
//  color.a=255;
//  SDL_Rect rect;
//  surf = TTF_RenderText_Solid(font, msg, color);
//  tex = SDL_CreateTextureFromSurface(ren, surf);
//  rect.x=x;
//  rect.y=y;
//  rect.w=surf->w;
//  rect.h=surf->h;
//  SDL_FreeSurface(surf);
//  SDL_RenderCopy(ren, tex, NULL, &rect);
//  SDL_DestroyTexture(tex);
// }

// void Message::drawMsgLarge(const char* msg, int x, int y, int r, int g, int b) {
//  SDL_Surface* surf;
//  SDL_Texture* tex;
//  SDL_Color color;
//  color.r=r;
//  color.g=g;
//  color.b=b;
//  color.a=255;
//  SDL_Rect rect;
//  surf = TTF_RenderText_Solid(fontLarge, msg, color);
//  tex = SDL_CreateTextureFromSurface(ren, surf);
//  rect.x=x;
//  rect.y=y;
//  rect.w=surf->w;
//  rect.h=surf->h;
//  SDL_FreeSurface(surf);
//  SDL_RenderCopy(ren, tex, NULL, &rect);
//  SDL_DestroyTexture(tex);
// }
