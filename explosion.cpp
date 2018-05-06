#include "explosion.h"

void Explosion::setExplosion(Entity explosion, SDL_Renderer* ren) {
   explosion.setImage("assets/explosion1.png",ren);
   explosion_1 = explosion.createCycle(1, 400, 400, 8, 14);
   explosion.setCurAnimation(explosion_1);
}

void Explosion::showExplosion(Entity explosion, double x, double y) {
   explosion.setDest(x, y, 180, 180);
   draw(explosion);
   explosion.updateAnimation();
}

void Explosion::draw(Entity obj) {
 SDL_Rect dest = obj.getDest();
 SDL_Rect src = obj.getSource();
 SDL_RenderCopyEx(ren, obj.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}