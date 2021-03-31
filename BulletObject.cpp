#include "BulletObject.h"

BulletOpject::BulletOpject()
{
    is_move=false;
    x_val=0;
    y_val=0;
    height_frame=0;
    width_frame=0;
    x_pos=0;
    y_pos=0;
    bullet_type=NomalBullet;
}

BulletOpject::~BulletOpject()
{

}

void BulletOpject::HandleMove(Map& map_data,const int& x_border,const int & y_border)
{
    if(bullet_dir==Dir_Right)
    {
        rect_.x+=x_val;
        x_pos=map_data.start_x+rect_.x;
        y_pos=map_data.start_y+rect_.y;
        if(rect_.x>x_border)
     {
        is_move=false;
     }
    }else if(bullet_dir==Dir_Left)
    {
        rect_.x-=x_val;
        x_pos=map_data.start_x+rect_.x;
        y_pos=map_data.start_y+rect_.y;
        if(rect_.x<0)
     {
        is_move=false;
     }
    }
   CheckToMap(map_data);

}

void BulletOpject::CheckToMap(Map& map_data)
{
    int x1=0;
    int x2=0;
    int y1=0;
    int y2=0;

    //Kiểm tra chiều ngang
    int heigh_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

    x1=(x_pos + x_val)/TILE_SIZE;
    x2=(x_pos+x_val+width_frame-1)/TILE_SIZE;

    y1=(y_pos)/TILE_SIZE;
    y2=(y_pos+heigh_min-1)/TILE_SIZE;

    /*
    x1,y1*********x2,y1
        *        *
        *        *
        *        *
        *        *
    x1,y2*********x2,y2

    */

    if(x1>=0&&x2 < Max_map_x&&y1>=0&&y2<Max_map_y)
    {
        if(x_val>0)//di chuyển sang phải
        {
            int val1 = map_data.Tile[y1][x2];
            int val2 = map_data.Tile[y2][x2];
                if(val1!=Blank_Tile || val2!=Blank_Tile)//kiểm tra va chạm
              {
                is_move=false;

              }

        }
        else if(x_val<0)//di chuyển sang trái
        {
            int val1 = map_data.Tile[y1][x1];
            int val2 = map_data.Tile[y2][x1];
                 if(val1!=Blank_Tile || val2!=Blank_Tile)
              {
                is_move=false;

              }
        }
    }


}


bool BulletOpject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret=false;
    if(bullet_type==RocketBullet)
    {
        ret=LoadImg("img//rb.png",des);
    }else if(bullet_type==NomalBullet)
    {
        ret=LoadImg("img//nb.png",des);
    }

    height_frame=rect_.h;
    width_frame=rect_.w;

    return ret;
}
