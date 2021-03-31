#include "PlayerPower.h"

PlayerPower::PlayerPower()
{
    number_=0;
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int& xPos)
{
    pos_list.push_back(xPos);
}

void PlayerPower::Show(SDL_Renderer* screen)
{
    for(int i=0;i<pos_list.size();i++)
    {
        rect_.x=pos_list.at(i);
        rect_.y=0;
        Render(screen);
    }
}

void PlayerPower::Init(SDL_Renderer* screen)
{
    LoadImg("img//pp.png",screen);
    number_=3;
    if(pos_list.size()>0)
    {
        pos_list.clear();
    }
    AddPos(20);
    AddPos(60);
    AddPos(100);
}

void PlayerPower::Decrease()
{
    number_--;
    pos_list.pop_back();
}

void PlayerPower::Initcrease()
{
    number_++;
    int last_pos = pos_list.back();
    if(pos_list.size()==0)
        AddPos(20);
    last_pos+=40;
    pos_list.push_back(last_pos);
}
