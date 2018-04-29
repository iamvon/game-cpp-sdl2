#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "object.h"

class Entity : public Object {
public:
    Entity() {rev=0;}
    int createCycle(int r, int w, int h, int amount, int speed);
    void setCurAnimation(int c) {begin=0;curAnim = c;}
    void updateAnimation();
    void reverse(bool r) {rev=r;}
    void reverse(bool r, int nA) {rev=r; nAb=1; nA=newAnim;}
private:
    struct cycle {
        int row;
        int w;
        int h;
        int amount;
        int speed;
        int tick;
    };
    vector<cycle> animations;
    int curAnim;
    int begin;
    bool rev, nAb;
    int newAnim;
};

#endif //ENTITY_H