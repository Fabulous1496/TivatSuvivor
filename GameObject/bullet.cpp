#include "bullet.h"

bullet::bullet() {}

bullet::~bullet() {}

void bullet::drawBullet()
{
    setlinecolor(RGB(225,155,50));
    setfillcolor(RGB(200,75,10));
    fillcircle(position.x,position.y,RADIUS);
}