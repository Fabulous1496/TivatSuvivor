#include "StartButton.h"

StartButton::StartButton(RECT rect,LPCTSTR path_img_idle,LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    : Button(rect,path_img_idle,path_img_hovered,path_img_pushed) {}

StartButton::~StartButton() {}

void StartButton::onClick(bool& game_status)
{
    game_status = true;
    mciSendString(_T("play bgm repeat from 0"),NULL,0,NULL);
}
