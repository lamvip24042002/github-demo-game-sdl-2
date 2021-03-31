#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED


#include "CommonFunc.h"
#include "BaseObject.h"


class BulletOpject : public BaseOject
{
public:
    BulletOpject();
    ~BulletOpject();

    enum BulletDir
    {
        Dir_Right=20,
        Dir_Left=21,

    };
    enum BulletType
    {
        NomalBullet=30,
        RocketBullet=31,

    };
    void set_x_val(const int& xVal) {x_val=xVal;}
    void set_y_val(const int& yVal) {y_val=yVal;}
    int get_x_val() const {return x_val;}
    int get_y_val() const {return y_val;}

    void set_is_move(const bool isMove) {is_move=isMove;}
    bool get_is_move() const {return is_move;}

    void set_bullet_dir(const unsigned int& bullet_dir_) {bullet_dir=bullet_dir_;}
    unsigned int get_bullet_dir() const {return bullet_dir;}

    void set_bullet_type(const unsigned int& bullet_type_) {bullet_type=bullet_type_;}
    unsigned int get_bullet_type() const {return bullet_type;}

    void HandleMove(Map& map_data,const int& x_border,const int & y_border);
    bool LoadImgBullet(SDL_Renderer* des);


    void CheckToMap(Map& map_data);

private:
    int x_val;
    int y_val;

    int height_frame;
    int width_frame;

    int x_pos;
    int y_pos;

    unsigned int bullet_dir;
    unsigned int bullet_type;
    bool is_move;
};



#endif // BULLETOBJECT_H_INCLUDED
