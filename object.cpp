#include "object.h"

void Object::setDest(double x, double y, double w, double h) {
  dest.x=x;
  dest.y=y;
  dest.w=w;
  dest.h=h;
}
void Object::setSource(double x, double y, double w, double h) {
  src.x=x;
  src.y=y;
  src.w=w;
  src.h=h;
}
void Object::setImage(string filename, SDL_Renderer* ren) {
  SDL_Surface* surf = IMG_Load(filename.c_str());
  tex = SDL_CreateTextureFromSurface(ren, surf);
  // SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE);
}
