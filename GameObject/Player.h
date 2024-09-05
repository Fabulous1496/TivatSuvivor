#ifndef SURVIVAL_PLAYER_H
#define SURVIVAL_PLAYER_H
#include "../Animation/Animation.h"
#include <graphics.h>
#include <cmath>

class Player
{
public:
    Player(Atlas* player_left, Atlas* player_right);
    ~Player();
    void readOperations(const ExMessage& msg);
    void move();
    void drawPlayer(int delta);
    POINT getPos() const;
    int getBulletNum() const;
private:
    int PLAYER_SPEED = 4;
    int BULLET_NUM;
    Animation* anim_left;
    Animation* anim_right;
    IMAGE shadow;
    POINT player_pos{0,0};
    bool facing_left = false;
    bool moving_up = false;
    bool moving_down = false;
    bool moving_left = false;
    bool moving_right = false;
};


#endif
