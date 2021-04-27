#ifndef THREATSOBJECT_H_INCLUDED
#define THREATSOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "CommonFunc.h"
#include "BulletObject.h"

#define MAX_FALL_SPEED 10
#define Theats_Flame_Num 8
#define Theats_Gravity_Speed 0.8
#define Theats_Speed 3
class TheatsObject : public BaseOject
{
public:
    TheatsObject();
    ~TheatsObject();

    enum TypeThreat
    {
        Static_Threat=0,
        Move_In_Space=1,
    };
    void set_x_val(const float& xVal) {x_val=xVal;}
    void set_y_val(const float& yVal) {y_val=yVal;}
    void set_x_pos(const float& xPos) {x_pos=xPos;}
    void set_y_pos(const float& yPos) {y_pos=yPos;}
    float get_x_pos() const{return x_pos;}
    float get_y_pos() const{return y_pos;}
    void SetMapXY(const int& mp_x,const int& mp_y) {map_x=mp_x;map_y=mp_y;}

    void SetClip();
    bool LoadImg(std::string path,SDL_Renderer* screen);
    void show(SDL_Renderer* des);
    int get_width_frame()const {return width_frame;}
    int get_height_frame() const {return height_frame;}
    void DoTheats(Map& map_data);
    void CheckToMap(Map& map_data);
    void InitTheats();
    void SetTypeMove(const int& typeMove) {type_move=typeMove;}
    int GetTypeMove() const {return type_move;}
    SDL_Rect GetRectFrame();
    void SetAnimationPos(const int& pos_a,const int& pos_b) {animation_a_=pos_a;animation_b_=pos_b;}
    void set_input_left(const int& ipLeft) {input_type.left_=ipLeft;}
    void ImpMoveType(SDL_Renderer* screen);

    std::vector<BulletOpject*> get_bullet_list() const {return bullet_list;}
    void set_bullet_list(const std::vector<BulletOpject*>& bullet_list_) {bullet_list=bullet_list_;}

    void InitBullet(BulletOpject* p_bullet,SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit,Map& map_data);

    void RemoveBullet(const int& id);

private:
    int width_frame;
    int height_frame;
    int frame_;

    SDL_Rect frame_clip[Theats_Flame_Num];
    bool on_ground_;
    float x_pos;
    float y_pos;
    float x_val;
    float y_val;

    int come_back_time;
    int map_x;
    int map_y;

    int type_move;
    int animation_a_;
    int animation_b_;
    Input input_type;

    std::vector<BulletOpject*> bullet_list;

};

#endif // THREATSOBJECT_H_INCLUDED
