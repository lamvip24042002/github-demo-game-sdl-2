#ifndef GAMETEXT_H_INCLUDED
#define GAMETEXT_H_INCLUDED

#include "CommonFunc.h"

class GameText
{
public:
    GameText();
    ~GameText();

    enum TexTColor
    {
        Red_Text = 0,
        White_Text = 1,
        Black_Text = 2,
    };

    bool LoadFromFile(std::string path);
    bool LoadFromRenderText(TTF_Font* font,SDL_Renderer* screen);
    void Free();
    void set_color(Uint8 red,Uint8 green, Uint8 blue);
    void set_color(int type);

    void RenderText(SDL_Renderer* screen,int xp,int yp,SDL_Rect* clip=NULL,double angle=0.0,SDL_Point* center=NULL,SDL_RendererFlip flip=SDL_FLIP_NONE);
    int GetWidth() const {return width_;}
    int GetHeight() const {return height_;}

    void SetText(const std::string& text) {str_val=text;}
    std::string GetText() const {return str_val;}
private:
    std::string str_val;
    SDL_Color text_color;
    SDL_Texture* texture;
    int width_;
    int height_;

};

#endif // GAMETEXT_H_INCLUDED
