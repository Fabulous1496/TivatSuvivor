#ifndef SURVIVAL_ATLAS_H
#define SURVIVAL_ATLAS_H
#include <vector>
#include <graphics.h>
#include <iostream>

class Atlas
{
public:
    Atlas(LPCTSTR path, int num);
    ~Atlas();
    std::vector<IMAGE*> frame_list;
};


#endif
