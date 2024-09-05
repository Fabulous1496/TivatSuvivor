#include <graphics.h>
#include <string>
#include "GameObject/Enemy.h"
#include "GameObject/bullet.h"
#include <cmath>
#include "GameObject/Player.h"
#include "Animation/Atlas.h"
#include "Button/Button.h"
#include "Button/StartButton.h"
#include "Button/QuitButton.h"

Atlas* player_left = new Atlas(_T("img/player_left_%d.png"),6);
Atlas* player_right = new Atlas(_T("img/player_right_%d.png"),6);
Atlas* enemy_left = new Atlas(_T("img/enemy_left_%d.png"),6);
Atlas* enemy_right = new Atlas(_T("img/enemy_right_%d.png"),6);

Player* Paimon = new Player(player_left,player_right);

bool game_started = false;
bool isRunning = true;

void generateEnemy(std::vector<Enemy*>& enemy_list)
{
    const int INTERVAL = 100;
    static int counter = 0;
    if((++counter) % INTERVAL == 0 && enemy_list.size() <=10 )
        enemy_list.push_back(new Enemy(enemy_left,enemy_right));
}

void generateBullet(std::vector<bullet>& bullet_list,const Player& player)
{
    // 径向速度和切向速度
    const double RADIAL_SPEED = 0.0045;
    const double TANGENT_SPEED = 0.0055;
    double radian_interval = 2 * 3.14159 / bullet_list.size();
    POINT player_pos = player.getPos();
    double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
    for(int i = 0; i < bullet_list.size(); i++)
    {
        double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;
        bullet_list[i].position.x = player_pos.x + 40 + (int)(radius * sin(radian));
        bullet_list[i].position.y = player_pos.y + 40 + (int)(radius * cos(radian));
    }
}

void drawScore(int score)
{
    static TCHAR text[64];
    _stprintf_s(text,_T("Your score is : %d"),score);
    setbkmode(TRANSPARENT);
    settextcolor(RGB(255,85,185));
    outtextxy(10,10,text);
}

int main()
{
    initgraph(1280,720);
    mciSendString(_T("open mus/bgm.mp3 alias bgm"),NULL,0,NULL);
    mciSendString(_T("open mus/iKUN.mp3 alias hit"),NULL,0,NULL);

    int score = 0;
    ExMessage msg;
    std::vector<Enemy*> enemy_list;
    IMAGE background;
    IMAGE menu;
    RECT region_start_button, region_quit_button;

    region_start_button.left = (1280-192)/2;
    region_start_button.right = region_start_button.left+192;
    region_start_button.top = 430;
    region_start_button.bottom = 430+75;

    region_quit_button.left = (1280-192)/2;
    region_quit_button.right = region_quit_button.left + 192;
    region_quit_button.top = 550;
    region_quit_button.bottom = region_quit_button.top + 75;

    StartButton startButton = StartButton(region_start_button,_T("img/ui_start_idle.png"),_T("img/ui_start_hovered.png"),_T("img/ui_start_pushed.png"));
    QuitButton quitButton = QuitButton(region_quit_button,_T("img/ui_quit_idle.png"),_T("img/ui_quit_hovered.png"),_T("img/ui_quit_pushed.png"));

    loadimage(&background,_T("img/background.png"));
    loadimage(&menu,_T("img/menu.png"));

    BeginBatchDraw();
    while(isRunning)
    {
        DWORD start_time = GetTickCount();
        std::vector<bullet> bullet_list(Paimon->getBulletNum());

        while(peekmessage(&msg))
        {
            if (game_started)
                Paimon->readOperations(msg);
            else
            {
                startButton.readOperations(msg,game_started);
                quitButton.readOperations(msg,isRunning);
            }
        }

        if(game_started)
        {
            generateEnemy(enemy_list);
            generateBullet(bullet_list, *Paimon);

            // 移动
            Paimon->move();
            for (auto enemy: enemy_list) {
                enemy->move(*Paimon);
            }

            // 碰撞逻辑
            for (auto enemy: enemy_list) {
                if (enemy->playerCollision(*Paimon)) {
                    static TCHAR text[128];
                    MessageBox(GetHWnd(), _T("You Lose!"), _T("Game Over!"), MB_OK);
                    isRunning = false;
                    break;
                }
            }

            for (auto enemy: enemy_list) {
                for (auto bullet: bullet_list) {
                    if (enemy->bulletCollision(bullet)) {
                        mciSendString(_T("play hit from 0"), NULL, 0, NULL);
                        enemy->hurt();
                        score++;
                    }
                }
            }

            for (int i = 0; i < enemy_list.size(); i++) {
                Enemy *enemy = enemy_list[i];
                if (!enemy->checkAilve()) {
                    std::swap(enemy_list[i], enemy_list.back());
                    enemy_list.pop_back();
                    delete enemy;
                }
            }
        }

        // 绘图
        cleardevice();

        if(game_started)
        {
            putimage(0, 0, &background);
            Paimon->drawPlayer(1000 / 144);
            for (auto enemy: enemy_list) {
                enemy->drawEnemy(1000 / 144);
            }
            for (auto bullet: bullet_list) {
                bullet.drawBullet();
            }
            drawScore(score);
        }
        else
        {
            putimage(0,0,&menu);
            startButton.drawButton();
            quitButton.drawButton();
        }

        DWORD end_time = GetTickCount();
        DWORD delta_time = end_time - start_time;
        // 控制帧率为144Hz
        if (delta_time < 1000 / 144) {
            Sleep(1000 / 144 - delta_time);
        }

        FlushBatchDraw();

    }
    EndBatchDraw();
    return 0;
}
