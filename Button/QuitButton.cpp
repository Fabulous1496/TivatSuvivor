#include "QuitButton.h"

QuitButton::QuitButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    : Button(rect,path_img_idle,path_img_hovered,path_img_pushed) {}

QuitButton::~QuitButton() {}

void QuitButton::onClick(bool& game_status)
{
    game_status = false;
}