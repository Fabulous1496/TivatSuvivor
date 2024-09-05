#ifndef SURVIVAL_ANIMATION_H
#define SURVIVAL_ANIMATION_H
#include <vector>
#include <graphics.h>
#include <string>
#include "Atlas.h"

class Player;
class Enemy;
class bullet;

class Animation
{
    friend class Player;
    friend class Enemy;
    friend class bullet;
public:
    // 构造函数，包含图片和帧间隔
    Animation(Atlas* atlas,int interval);
    Animation();
    ~Animation();
private:
    int interval_ms = 0;
    int timer = 0;      // 计时器
    int idx_frame = 0;      // 帧索引
    void play(int x,int y, int delta);
    Atlas* anim_atlas;
    static void putImage_alpha(int x, int y, IMAGE* img);
};


#endif //SURVIVAL_ANIMATION_H
