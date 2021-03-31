#include "GameText.h"

GameText::GameText()
{
    text_color.r=255;
    text_color.g=255;
    text_color.b=255;
    texture=NULL;
}
GameText::~GameText()
{

}

bool GameText::LoadFromRenderText(TTF_Font* font,SDL_Renderer* screen)
{
    SDL_Surface* Text_Surface=TTF_RenderText_Solid(font,str_val.c_str(),text_color);
    if(Text_Surface!=NULL)
    {
        texture = SDL_CreateTextureFromSurface(screen,Text_Surface);
        width_=Text_Surface->w;
        height_=Text_Surface->h;

        SDL_FreeSurface(Text_Surface);
    }
    return texture!=NULL;
}

void GameText::Free()
{
    if(texture!=NULL)
    {
        SDL_DestroyTexture(texture);
        texture=NULL;
    }
}
void GameText::set_color(Uint8 red,Uint8 green, Uint8 blue)
{
    text_color.r=red;
    text_color.g=green;
    text_color.b=blue;

}
void GameText::set_color(int type)
{
    if(type==Red_Text)
    {
        SDL_Color color = {255 , 0 , 0 };
        text_color=color;
    }else if(type==White_Text)
    {
        SDL_Color color = {255 , 255 , 255 };
        text_color=color;
    }else if(type==Black_Text)
    {
        SDL_Color color = {0 , 0 , 0 };
        text_color=color;
    }
}

void GameText::RenderText(SDL_Renderer* screen,int xp,int yp,SDL_Rect* clip,double angle,SDL_Point* center,SDL_RendererFlip flip)
{
    SDL_Rect renderQuad ={xp,yp,width_,height_};
    if(clip!=NULL)
    {
        renderQuad.w=clip->w;
        renderQuad.h=clip->h;
    }
    SDL_RenderCopyEx(screen,texture,clip,&renderQuad,angle,center,flip);
}
