#ifndef EXPLOSIONOBJECT_H_INCLUDED
#define EXPLOSIONOBJECT_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"

#define Num_Frame_EXP 8

class ExplosionObject : public BaseOject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void SetClip();
    void set_frame(const int& fr){frame_=fr;}
    virtual bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width() const {return frame_width;}
    int get_frame_height() const {return frame_height;}

private:
    SDL_Rect frame_clip[Num_Frame_EXP];
    unsigned int frame_;
    int frame_width;
    int frame_height;

};


#endif // EXPLOSIONOBJECT_H_INCLUDED
