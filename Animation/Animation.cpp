#include "Animation.h"

Animation::Animation(Atlas* atlas, int interval)
{
    interval_ms = interval;
    anim_atlas = atlas;
}

Animation::Animation(){}

Animation::~Animation(){}

// 使用MSIMG库处理图片实现透明通道混叠
inline void Animation::putImage_alpha(int x, int y, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL),x,y,w,h,
               GetImageHDC(img),0,0,w,h,{AC_SRC_OVER,0,255,AC_SRC_ALPHA});
}

void Animation::play(int x,int y, int delta)
{
    timer += delta;
    if(timer>=interval_ms)
    {
        idx_frame = (idx_frame + 1) % anim_atlas->frame_list.size();
        timer = 0;
    }

    putImage_alpha(x,y,anim_atlas->frame_list[idx_frame]);
}
