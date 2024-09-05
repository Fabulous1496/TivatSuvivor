#ifndef SURVIVAL_STARTBUTTON_H
#define SURVIVAL_STARTBUTTON_H
#include "Button.h"

class StartButton : public Button
{
public:
    StartButton(RECT rect,LPCTSTR path_img_idle,LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
    ~StartButton();

protected:
    void onClick(bool& game_status);

};


#endif
