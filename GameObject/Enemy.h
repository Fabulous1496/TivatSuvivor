#ifndef SURVIVAL_ENEMY_H
#define SURVIVAL_ENEMY_H
#include <graphics.h>
#include <cmath>
#include "../Animation/Animation.h"
#include "Player.h"
#include "bullet.h"


class Enemy
{
public:
    Enemy(Atlas* enemy_left, Atlas* enemy_right);
    ~Enemy();
    void born();
    bool bulletCollision(const bullet &bullet);
    bool playerCollision(const Player &player);
    void move(const Player& player);
    void drawEnemy(int delta);
    void hurt();
    bool checkAilve();

private:
    int HP;
    const int SPEED = 2;
    const int WIDTH = 80;
    const int Height = 80;
    const int SHADOW_WIDTH = 48;
    IMAGE shadow;
    Animation* anim_left;
    Animation* anim_right;
    POINT enemy_pos = {0,0};
    bool facing_left = false;
    // 随机出生
    enum BRON_PLACE{UP,DOWN,LEFT,RIGHT};
    BRON_PLACE direction;
};


#endif
