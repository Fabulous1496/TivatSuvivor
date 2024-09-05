#ifndef SURVIVAL_BULLET_H
#define SURVIVAL_BULLET_H
#include <graphics.h>

class bullet
{
public:
    POINT position = {0,0};
    bullet();
    ~bullet();
    void drawBullet();
private:
    int RADIUS = 10;
};

#endif
