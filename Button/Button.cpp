#include "Button.h"

Button::Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
{
    region = rect;
    loadimage(&img_idle,path_img_idle);
    loadimage(&img_hovered,path_img_hovered);
    loadimage(&img_pushed,path_img_pushed);
}

Button::~Button() {}

void Button::drawButton()
{
    switch (status)
    {
        case Status::Idle:
            putimage(region.left,region.top,&img_idle);
            break;
        case Status::Hovered:
            putimage(region.left,region.top,&img_hovered);
            break;
        case Status::Pushed:
            putimage(region.left,region.top,&img_pushed);
            break;
    }
}

void Button::readOperations(const ExMessage &msg,bool& game_status)
{
    switch (msg.message)
    {
        case WM_MOUSEMOVE:
            if(status == Status::Idle && checkMouse(msg.x,msg.y))
                status = Status::Hovered;
            else if (status == Status::Hovered && !checkMouse(msg.x,msg.y))
                status = Status::Idle;
            break;
        case WM_LBUTTONDOWN:
            if (checkMouse(msg.x,msg.y))
                status = Status::Pushed;
            break;
        case WM_LBUTTONUP:
            if (status == Status::Pushed)
                onClick(game_status);
            break;
        default:
            break;
    }

}

bool Button::checkMouse(int x, int y)
{
    return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
}