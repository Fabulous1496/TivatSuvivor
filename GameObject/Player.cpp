#include "Player.h"

Player::Player(Atlas* player_left, Atlas* player_right)
{
    player_pos.x=500;
    player_pos.y=500;
    BULLET_NUM = 3;
    loadimage(&shadow,_T("img/shadow_player.png"));
    anim_left = new Animation(player_left,45);
    anim_right= new Animation(player_right,45);
}

Player::~Player()
{
    delete anim_left;
    delete anim_right;
}

void Player::readOperations(const ExMessage& msg)
{
    // 读取键盘输入
    if(msg.message == WM_KEYDOWN)
    {
        switch (msg.vkcode)
        {
            case 0x57:
                moving_up = true;
                break;
            case 0x53:
                moving_down = true;
                break;
            case 0x41:
                moving_left = true;
                break;
            case 0x44:
                moving_right = true;
                break;
            case 0x5A:
                PLAYER_SPEED *= 2;
                break;
            case 0x4A:
                BULLET_NUM += 1;
                break;
        }
    }

    else if(msg.message == WM_KEYUP)
    {
        switch (msg.vkcode)
        {
            case 0x57:
                moving_up = false;
                break;
            case 0x53:
                moving_down = false;
                break;
            case 0x41:
                moving_left = false;
                break;
            case 0x44:
                moving_right = false;
                break;
        }
    }
}

void Player::move()
{
    int dir_x = moving_right - moving_left;
    int dir_y = moving_down - moving_up;
    double len_dir = sqrt(dir_x*dir_x + dir_y*dir_y);
    if(len_dir != 0)
    {
        double normalized_x = dir_x / len_dir;
        double normalized_y = dir_y / len_dir;
        player_pos.x += (int)(PLAYER_SPEED * normalized_x);
        player_pos.y += (int)(PLAYER_SPEED * normalized_y);
    }

    // 边界判断
    if(player_pos.x < 0) player_pos.x = 0;
    if(player_pos.y < 0) player_pos.y = 0;
    if(player_pos.x + 80 > 1280) player_pos.x = 1200;
    if(player_pos.y + 80 > 720) player_pos.y = 640;
}

void Player::drawPlayer(int delta)
{
    int dir_x = moving_right - moving_left;
    int pos_shadow_x = player_pos.x+24;
    int pos_shadow_y = player_pos.y+72;
    Animation::putImage_alpha(pos_shadow_x,pos_shadow_y,&shadow);

    if(dir_x < 0)
    {
        facing_left = true;
    }
    else if(dir_x > 0)
    {
        facing_left = false;
    }

    if(facing_left)
    {
        anim_left->play(player_pos.x,player_pos.y,delta);
    }
    else
    {
        anim_right->play(player_pos.x,player_pos.y,delta);
    }
}

POINT Player::getPos() const
{
    return this->player_pos;
}

int Player::getBulletNum() const
{
    return BULLET_NUM;
}