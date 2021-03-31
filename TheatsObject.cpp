#include "ThreatsObject.h"


TheatsObject::TheatsObject()
{
    frame_=0;
    x_val=0.0;
    y_val=0.0;
    x_pos=0.0;
    y_pos=0.0;
    width_frame=0;
    height_frame=0;
    on_ground_=false;
    come_back_time=0;
    animation_a_=0;
    animation_b_=0;
    input_type.left_=0;
    type_move=Static_Threat;
}

TheatsObject::~TheatsObject()
{

}

bool TheatsObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret=BaseOject::LoadImg(path,screen);

    if(ret==true)
    {
        width_frame=rect_.w/Theats_Flame_Num;
        height_frame=rect_.h;
    }
    return ret;
}

SDL_Rect TheatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x=rect_.x;
    rect.y=rect_.y;
    rect.h=height_frame;
    rect.w=width_frame;
    return rect;
}
void TheatsObject::SetClip()
{
    if(width_frame>0&&height_frame>0)
    {
        for(int i=0;i<8;i++)
        {
            frame_clip[i].x=i*width_frame;
            frame_clip[i].y=0;
            frame_clip[i].w=width_frame;
            frame_clip[i].h=height_frame;
        }
    }
}

void TheatsObject::show(SDL_Renderer* des)
{
    if(come_back_time==0)
    {
        rect_.x=x_pos-map_x;
        rect_.y=y_pos-map_y;
        frame_++;
        if(frame_>=8) frame_=0;

        SDL_Rect* current_clip= &frame_clip[frame_];
        SDL_Rect renderQuad={rect_.x,rect_.y,width_frame,height_frame};

        SDL_RenderCopy(des,p_object_,current_clip,&renderQuad);
    }
}

void TheatsObject::DoTheats(Map& map_data)
{
    if(come_back_time==0)
    {
        x_val=0;
        y_val+= Theats_Gravity_Speed;

        if(y_val>=MAX_FALL_SPEED)
        {
            y_val=MAX_FALL_SPEED;
        }
        if(input_type.left_==1)
        {
            x_val-=Theats_Speed;
        }
        else if(input_type.right_==1)
        {
            x_val+=Theats_Speed;
        }
        CheckToMap(map_data);
    }
    else if(come_back_time>0)
    {
        come_back_time--;
        if(come_back_time==0)
        {
            InitTheats();
        }
    }
}

void TheatsObject::InitTheats()
{
     x_val=0;
            y_val=0;
            if(x_pos>256)
            {
                x_pos-=256;
                animation_a_-=256;
                animation_b_-=256;
            }else x_pos=0;
            y_pos=0;
            input_type.left_=1;
}

void TheatsObject::CheckToMap(Map& map_data)
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
                if((val1!=Blank_Tile && val1!= Coin_tile )|| (val2!=Blank_Tile&& val2!=Coin_tile))//kiểm tra va chạm
              {
                x_pos=x2*TILE_SIZE;
                x_pos-=width_frame+1;
                x_val=0;
              }


        }
        else if(x_val<0)//di chuyển sang trái
        {
            int val1 = map_data.Tile[y1][x1];
            int val2 = map_data.Tile[y2][x1];

                 if((val1!=Blank_Tile && val1!= Coin_tile )|| (val2!=Blank_Tile&& val2!=Coin_tile))
              {
                x_pos=(x1+1)*TILE_SIZE;
                x_val=0;
              }

        }
    }

    //kiểm tra chiều dọc
    int width_min= width_frame < TILE_SIZE ? width_frame : TILE_SIZE;

    x1=(x_pos)/TILE_SIZE;
    x2=(x_pos+width_min-1)/TILE_SIZE;

    y1=(y_pos+y_val-1)/TILE_SIZE;
    y2=(y_pos+y_val+height_frame-1)/TILE_SIZE;

    if(x1>=0&&x2 < Max_map_x&&y1>=0&&y2<Max_map_y)
    {
        if(y_val>0)//rơi tự do
        {
            int val1 = map_data.Tile[y2][x1];
            int val2 = map_data.Tile[y2][x2];

                if((val1!=Blank_Tile && val1!= Coin_tile )||( val2!=Blank_Tile&& val2!=Coin_tile))
               {
                y_pos=y2*TILE_SIZE;
                y_pos-=(height_frame+1);
                y_val=0;
                on_ground_=true;
               }

            }
    }

    x_pos +=x_val;
    y_pos +=y_val;
    if(x_pos<0)
    {
        x_pos=0;
    }else if(x_pos+width_frame>=map_data.Max_x_)
    {
        x_pos=map_data.Max_x_-width_frame-1;
    }
    if(y_pos>map_data.Max_y_)
    {
        come_back_time=1;
    }
}

void TheatsObject::ImpMoveType(SDL_Renderer* screen)
{
    if(type_move==Static_Threat)
    {
        ;
    }
    else
    {
        if(on_ground_==true)
        {
            if(x_pos>animation_b_)
            {
                input_type.left_=1;
                input_type.right_=0;
                LoadImg("img//tl.png",screen);
            }
            else if(x_pos<animation_a_)
            {
                input_type.left_=0;
                input_type.right_=1;
                LoadImg("img//tr.png",screen);
            }
        }
        else
        {
            if(input_type.left_==1)
            {
                LoadImg("img//tl.png",screen);
            }
        }
    }
}

void TheatsObject::InitBullet(BulletOpject* p_bullet,SDL_Renderer* screen)
{
    if(p_bullet!=NULL)
    {

        p_bullet->set_bullet_type(BulletOpject::NomalBullet);
        bool ret=p_bullet->LoadImgBullet(screen);
        if(ret==true)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletOpject::Dir_Left);
            p_bullet->SetRect(x_pos+20,y_pos+10);
            p_bullet->set_x_val(15);
        }

       bullet_list.push_back(p_bullet);

    }

}

void TheatsObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit,Map& map_data)
{
    for(int i=0;i<bullet_list.size();i++)
    {
        BulletOpject* p_bullet=bullet_list.at(i);
        if(p_bullet!=NULL)
        {
            if(p_bullet->get_is_move())
            {
                int bullet_distance = rect_.x+width_frame-p_bullet->GetRect().x;
                if(bullet_distance<300&&bullet_distance>0)
                {
                    p_bullet->HandleMove(map_data,x_limit,y_limit);
                    p_bullet->Render(screen);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }

            }
            else
            {
                p_bullet->SetRect(rect_.x+5,rect_.y+10);
                p_bullet->set_is_move(true);

            }
        }
    }
}


