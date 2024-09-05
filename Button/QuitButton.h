#ifndef SURVIVAL_QUITBUTTON_H
#define SURVIVAL_QUITBUTTON_H
#include "Button.h"

class QuitButton : public Button
{
public:
    QuitButton(RECT rect,LPCTSTR path_img_idle,LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
    ~QuitButton();
protected:
    void onClick(bool& game_status);
};


#endif
