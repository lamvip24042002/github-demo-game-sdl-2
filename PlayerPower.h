#ifndef PLAYERPOWER_H_INCLUDED
#define PLAYERPOWER_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"

class PlayerPower : public BaseOject
{
public:
    PlayerPower();
    ~PlayerPower();

    void Set_num(const int& num) {number_=num;}
    int get_num() const {return number_;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    int get_pos_list_size() const {return pos_list.size();}

    void Initcrease();
    void Decrease();
private:
    int number_;
    std::vector<int> pos_list;
};

#endif // PLAYERPOWER_H_INCLUDED
