#include "BaseObject.h"

BaseOject::BaseOject(){
    p_object_=NULL;
    rect_.h=0;
    rect_.w=0;
    rect_.x=0;
    rect_.y=0;
}

BaseOject::~BaseOject()
{
    Free();
}

bool BaseOject::LoadImg(std:: string path,SDL_Renderer* screen)
{
  Free();
  SDL_Texture* new_texture=NULL;
  SDL_Surface* load_surface= IMG_Load(path.c_str());
  if(load_surface!=NULL)
  {
    SDL_SetColorKey(load_surface,SDL_TRUE,SDL_MapRGB(load_surface->format,CORLOR_KEY_R,CORLOR_KEY_G,CORLOR_KEY_B));
    new_texture=SDL_CreateTextureFromSurface(screen,load_surface);
   if(new_texture!=NULL)
   {
    rect_.h=load_surface->h;
    rect_.w=load_surface->w;
   }


    SDL_FreeSurface(load_surface);
  }
  p_object_=new_texture;
  return p_object_!=NULL;
}

void BaseOject::Render(SDL_Renderer* des,const SDL_Rect* clip  )
{
    SDL_Rect renderquad={rect_.x,rect_.y,rect_.w,rect_.h};

    SDL_RenderCopy(des,p_object_,clip,&renderquad);
}

void BaseOject::Free()
{
    if(p_object_!=NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_=NULL;
        rect_.h=0;
        rect_.w=0;
    }


}
