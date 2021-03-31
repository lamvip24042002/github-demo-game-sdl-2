
#include "MainObject.h"


MainObject::MainObject()
{
    frame_=0;
    x_val=0;
    y_val=0;
    x_pos=0;
    y_pos=0;
    width_frame=0;
    height_frame=0;
    status_=-1;
    input_type_.left_=0;
    input_type_.right_=0;
    input_type_.jump_=0;
    on_ground_=false;
    map_x_=0;
    map_y_=0;
    come_back_time=0;
    coin_count =0;
}
MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret=BaseOject::LoadImg(path,screen);

    if(ret==true)
    {
        width_frame=rect_.w/8;
        height_frame=rect_.h;
    }
    return ret;
}

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x=rect_.x;
    rect.y=rect_.y;
    rect.h=height_frame;
    rect.w=width_frame;
    return rect;
}

void MainObject::SetClip()
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

void MainObject::Show(SDL_Renderer* des)
{
    if(on_ground_==true)
    {
        if(status_==WalkLeft)
      {
        LoadImg("img//pl.png",des);
      }
      else if(status_==WalkRight)
      {
        LoadImg("img//pr.png",des);
      }

    }

    if(input_type_.left_==1||input_type_.right_==1)
    {
        frame_++;
    }
    else
    {
        frame_=0;
    }
    if(frame_>=8)
    {
        frame_=0;
    }
    rect_.x=x_pos-map_x_;
    rect_.y=y_pos-map_y_;

    SDL_Rect* current_clip= &frame_clip[frame_];
    SDL_Rect renderQuad={rect_.x,rect_.y,width_frame,height_frame};

    SDL_RenderCopy(des,p_object_,current_clip,&renderQuad);
}

void MainObject::HandelInputActision(SDL_Event events,SDL_Renderer* screen,Mix_Chunk* bullet_sound)
{

    if(events.type==SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
          case SDLK_RIGHT:
            {
                status_=WalkRight;
                input_type_.right_=1;
                input_type_.left_=0;
                UpdateImgPlayer(screen);
            }break;
          case SDLK_LEFT:
            {
               status_=WalkLeft;
               input_type_.left_=1;
               input_type_.right_=0;
               UpdateImgPlayer(screen);
            }break;
        }
    }
    else if(events.type==SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
          case SDLK_RIGHT:
            {
                input_type_.right_=0;
            }break;
          case SDLK_LEFT:
            {
               input_type_.left_=0;
            }break;
        }
    }

    if(events.type== SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button==SDL_BUTTON_RIGHT)
        {
            input_type_.jump_=1;
        }
        if(events.button.button==SDL_BUTTON_LEFT)
        {
           BulletOpject* p_bullet= new BulletOpject();
           p_bullet->set_bullet_type(BulletOpject::RocketBullet);
           p_bullet->LoadImgBullet(screen);



            if(status_==WalkLeft)
            {
                p_bullet->set_bullet_dir(BulletOpject::Dir_Left);
                p_bullet->SetRect(this->rect_.x,rect_.y+height_frame*0.3);

            }
            else if(status_==WalkRight)
            {
                p_bullet->set_bullet_dir(BulletOpject::Dir_Right);
                p_bullet->SetRect(this->rect_.x+width_frame-20,rect_.y+height_frame*0.3);

            }
            Mix_PlayChannel(-1,bullet_sound,0);
            p_bullet->set_x_val(20);
            p_bullet->set_is_move(true);

            p_bullet_list.push_back(p_bullet);
        }
    }
}

void MainObject::RemoveBullet(const int& id)
{
    int size_ = p_bullet_list.size();
    if(size_>0&&id<size_)
    {
        BulletOpject* p_bullet = p_bullet_list.at(id);
        p_bullet_list.erase(p_bullet_list.begin()+id);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet=NULL;
        }
    }
}
void MainObject::HandelBullet(SDL_Renderer* des,Map& map_data)
{
    for(int i=0;i<p_bullet_list.size();i++)
    {
        BulletOpject* p_bullet=p_bullet_list.at(i);
        if(p_bullet!=NULL)
        {
            if(p_bullet->get_is_move()==true)
            {
                p_bullet->HandleMove(map_data,SCREEN_WIDTH,SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list.erase(p_bullet_list.begin()+i);
                if(p_bullet!=NULL)
                {
                    delete p_bullet;
                    p_bullet=NULL;
                }
            }
        }
    }
}

void MainObject::DoPlayer(Map& map_data,PlayerPower* p_pow,SDL_Renderer* screen,Mix_Chunk* cb_sound)
{
    if(come_back_time==0)
  {
    x_val=0;
    y_val+=GRAVITY_SPEED;

    if(y_val>=MAX_FALL_SPEED)
    {
        y_val=MAX_FALL_SPEED;
    }
    if(input_type_.left_==1)
    {
        x_val-=PLAYER_SPEED;
    }else if(input_type_.right_==1)
    {
        x_val+=PLAYER_SPEED;
    }
    if(input_type_.jump_==1)
    {
      if(on_ground_==true)
      {
          y_val= - PLAYER_JUMP_VAL;
          on_ground_=false;
      }
      input_type_.jump_=0;
    }
    CheckToMap(map_data, p_pow,screen);
    CenterEntityOnMap(map_data);
   }
    else
    {
      come_back_time--;
      if(come_back_time==0)
      {
          Mix_PlayChannel(-1,cb_sound,0);
          x_pos-=4*TILE_SIZE;
          y_pos=0;
          x_val=0;
          y_val=0;
      }
    }
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x=x_pos-(SCREEN_WIDTH/2);
    if(map_data.start_x<0)
    {
        map_data.start_x=0;
    }
    else if(map_data.start_x+SCREEN_WIDTH>=map_data.Max_x_)
    {
        map_data.start_x=map_data.Max_x_-SCREEN_WIDTH;
    }


    map_data.start_y = y_pos - (SCREEN_HEIGHT/2);
    if(map_data.start_y<0)
    {
        map_data.start_y=0;
    }
    else if(map_data.start_y+SCREEN_HEIGHT>=map_data.Max_y_)
    {
        map_data.start_y=map_data.Max_y_-SCREEN_HEIGHT;
    }
}


void MainObject::CheckToMap(Map& map_data,PlayerPower* p_pow,SDL_Renderer* screen)
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
            if( val1 == Coin_tile || val2 == Coin_tile)
            {
                map_data.Tile[y1][x2]=0;
                map_data.Tile[y2][x2]=0;
                IncreaseCoin();
            }
            else
            {
                if(val1!=Blank_Tile || val2!=Blank_Tile)//kiểm tra va chạm
              {
                x_pos=x2*TILE_SIZE;
                x_pos-=width_frame+1;
                x_val=0;
              }
            }

        }
        else if(x_val<0)//di chuyển sang trái
        {
            int val1 = map_data.Tile[y1][x1];
            int val2 = map_data.Tile[y2][x1];
            if( val1 == Coin_tile || val2 == Coin_tile)
            {
                map_data.Tile[y1][x1]=0;
                map_data.Tile[y2][x1]=0;
                IncreaseCoin();
            }
            else
            {
                 if(val1!=Blank_Tile||val2!=Blank_Tile)
              {
                x_pos=(x1+1)*TILE_SIZE;
                x_val=0;
              }
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
            if( val1 == Coin_tile || val2 == Coin_tile)
            {
                map_data.Tile[y2][x1]=0;
                map_data.Tile[y2][x2]=0;
                IncreaseCoin();
            }
            else
            {
                if(val1!=Blank_Tile||val2!=Blank_Tile)
               {
                y_pos=y2*TILE_SIZE;
                y_pos-=(height_frame+1);
                y_val=0;
                on_ground_=true;
               }
            }

            }
    }
    else if(y_val<0)//nhảy
    {
        on_ground_=false;
        int val1 = map_data.Tile[y1][x1];
        int val2 = map_data.Tile[y1][x2];
        if( val1 == Coin_tile || val2 == Coin_tile)
        {
                map_data.Tile[y1][x1]=0;
                map_data.Tile[y1][x2]=0;
                IncreaseCoin();
        }
        else
        {
            if(val1!=Blank_Tile||val2!=Blank_Tile)
          {
            y_pos=(y1+1)*TILE_SIZE;
            y_val=0;
          }
        }

    }
    if(p_pow->get_pos_list_size()<3)
    {
        if(coin_count>=10)
    {
        coin_count-=10;
        p_pow->Initcrease();
        p_pow->Render(screen);
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
        p_pow->Decrease();
        p_pow->Render(screen);
    }
}

void MainObject::IncreaseCoin()
{
    coin_count++;
}

void MainObject::UpdateImgPlayer(SDL_Renderer* des)
{
   if(on_ground_==true)
   {
       if(status_==WalkLeft)
       {
           LoadImg("img//pl.png",des);
       }else
       {
           LoadImg("img//pr.png",des);
       }
   }else
   {
       if(status_==WalkLeft)
       {
           LoadImg("img//jl.png",des);
       }else
       {
           LoadImg("img//jr.png",des);
       }
   }
}

