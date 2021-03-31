#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 10
#define PLAYER_JUMP_VAL 17

#include<vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "PlayerPower.h"

class MainObject: public BaseOject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WalkRight=0,
        WalkLeft=1,
    };

    bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputActision(SDL_Event events,SDL_Renderer* screen,Mix_Chunk* bullet_sound);
    void SetClip();

    void DoPlayer(Map& map_data,PlayerPower* p_pow,SDL_Renderer* screen,Mix_Chunk* cb_sound);
    void CheckToMap(Map& map_data,PlayerPower* p_pow,SDL_Renderer* screen);

    void SetMapXY(const int map_x,const int map_y){map_x_=map_x;map_y_=map_y;}
    void CenterEntityOnMap(Map& map_data);
    void UpdateImgPlayer(SDL_Renderer* des);
    SDL_Rect GetRectFrame();
    void set_bullet_list(std::vector<BulletOpject*> bullet_list)
    {
        p_bullet_list=bullet_list;
    }
    std::vector<BulletOpject*> get_bullet_list() const { return p_bullet_list;}


    void HandelBullet(SDL_Renderer* des,Map& map_data);
    void IncreaseCoin();
    void RemoveBullet(const int& id);
    void set_come_back_time (const int & cb_time) {come_back_time=cb_time;}
    int get_coin_count() const{return coin_count;}
private:
    std::vector<BulletOpject*> p_bullet_list;

    // Độ dịch chuyển
    float x_val;
    float y_val;

    //Vị trí ứng với bản đồ
    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[8];
    Input input_type_;
    int frame_;
    int status_;

    bool on_ground_;
    int map_x_;
    int map_y_;

    int come_back_time;
    int coin_count;


};

#endif // MAINOBJECT_H_INCLUDED
