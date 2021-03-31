#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
    frame_=0;
    frame_width=0;
    frame_height=0;
}

ExplosionObject::~ExplosionObject()
{

}

bool ExplosionObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret = BaseOject::LoadImg(path,screen);
    if(ret==true)
    {
        frame_width=rect_.w/Num_Frame_EXP;
        frame_height=rect_.h;
    }
    return ret;
}

void ExplosionObject::SetClip()
{
    if(frame_width>0&&frame_height>0)
    {
        for(int i=0;i<Num_Frame_EXP;i++)
        {
            frame_clip[i].x=i*frame_width;
            frame_clip[i].y=0;
            frame_clip[i].w=frame_width;
            frame_clip[i].h=frame_height;
        }
    }
}

void ExplosionObject::Show(SDL_Renderer* des)
{
    SDL_Rect* current_clip= &frame_clip[frame_];
    SDL_Rect renderQuad={rect_.x,rect_.y,frame_width,frame_height};
    if(current_clip!=NULL)
    {
        renderQuad.w=current_clip->w;
        renderQuad.h=current_clip->h;
    }

    SDL_RenderCopy(des,p_object_,current_clip,&renderQuad);
}
