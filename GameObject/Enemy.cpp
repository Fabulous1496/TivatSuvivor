#include "Enemy.h"

Enemy::Enemy(Atlas* enemy_left, Atlas* enemy_right)
{
    HP = 1;
    loadimage(&shadow,_T("img/shadow_enemy.png"));
    anim_left = new Animation(enemy_left,45);
    anim_right = new Animation(enemy_right,45);
    born();
}

Enemy::~Enemy()
{
    delete anim_left;
    delete anim_right;
}

void Enemy::born()
{
    direction = (BRON_PLACE)(rand() % 4);
    switch (direction)
    {
        case BRON_PLACE::UP:
            enemy_pos.x = rand() % 1280;
            enemy_pos.y = -80;
            break;
        case BRON_PLACE::DOWN:
            enemy_pos.x = rand() % 1280;
            enemy_pos.y = 720;
            break;
        case BRON_PLACE::LEFT:
            enemy_pos.x = -80;
            enemy_pos.y = rand() % 720;
            break;
        case BRON_PLACE::RIGHT:
            enemy_pos.x = 1280;
            enemy_pos.y = rand() % 720;
            break;
        default:
            break;
    }
}

bool Enemy::bulletCollision(const bullet &bullet)
{
    bool is_overlap_x = bullet.position.x >= enemy_pos.x && bullet.position.x <= enemy_pos.x +WIDTH;
    bool is_overlap_y = bullet.position.y >= enemy_pos.y && bullet.position.y <= enemy_pos.y +Height;
    return is_overlap_x && is_overlap_y;
}

bool Enemy::playerCollision(const Player &player)
{
    // 敌人碰撞判定点
    POINT check_position = {enemy_pos.x + WIDTH/2,enemy_pos.y + Height/2};
    POINT player_pos = player.getPos();
    bool is_overlap_x = check_position.x >= player_pos.x && check_position.x <= player_pos.x+80;
    bool is_overlap_y = check_position.y >= player_pos.y && check_position.y <= player_pos.y+80;
    return is_overlap_x && is_overlap_y;
}

void Enemy::move(const Player& player)
{
    const POINT& player_pos = player.getPos();
    int dir_x = player_pos.x - enemy_pos.x;
    int dir_y = player_pos.y - enemy_pos.y;
    double len_dir = sqrt(dir_x*dir_x + dir_y*dir_y);
    if(len_dir != 0)
    {
        double normalized_x = dir_x / len_dir;
        double normalized_y = dir_y / len_dir;
        enemy_pos.x += (int)(SPEED * normalized_x);
        enemy_pos.y += (int)(SPEED * normalized_y);
    }

    if(dir_x < 0)
    {
        facing_left = true;
    }
    else if(dir_x > 0)
    {
        facing_left = false;
    }
}

void Enemy::drawEnemy(int delta)
{
    int pos_shadow_x = enemy_pos.x + (WIDTH-SHADOW_WIDTH)/2;
    int pos_shadow_y = enemy_pos.y + Height - 35;
    Animation::putImage_alpha(pos_shadow_x,pos_shadow_y,&shadow);

    if(facing_left)
        anim_left->play(enemy_pos.x,enemy_pos.y,delta);
    else
        anim_right->play(enemy_pos.x,enemy_pos.y,delta);
}

void Enemy::hurt()
{
    HP -= 1;
}

bool Enemy::checkAilve()
{
    return HP > 0;
}