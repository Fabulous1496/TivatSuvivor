#ifndef SURVIVAL_BUTTON_H
#define SURVIVAL_BUTTON_H
#include <graphics.h>

class Button
{
public:
    Button(RECT rect,LPCTSTR path_img_idle,LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
    ~Button();
    void drawButton();
    void readOperations(const ExMessage &msg,bool& game_status);

protected:
    virtual void onClick(bool& game_status) = 0;

private:
    RECT region;
    IMAGE img_idle;
    IMAGE img_hovered;
    IMAGE img_pushed;
    enum Status{Idle,Hovered,Pushed};
    Status status = Status::Idle;
    bool checkMouse(int x,int y);
};


#endif
