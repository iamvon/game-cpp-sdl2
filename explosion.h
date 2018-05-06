#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "entity.h"

class Explosion : public Entity {
public:
    Explosion() {}
    void setExplosion(Entity explosion, SDL_Renderer* ren);
    void showExplosion(Entity explosion, double x, double y);
    void draw(Entity obj);
private:
    Entity explosion;
    int explosion_1;
    SDL_Renderer* ren;
    double x, y;
};

#endif //EXPLOSION_H