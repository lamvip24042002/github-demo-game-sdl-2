
#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "impTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "GameText.h"
#include "PlayerPower.h"
#include "Geometric.h"
#include "BulletObject.h"


BaseOject g_background;
TTF_Font* font_time=NULL;
TTF_Font* g_font_MENU=NULL;

bool InitData()
{
   bool success=true;
   int ret = SDL_Init(SDL_INIT_VIDEO);
   if(ret<0)
   {
    return false;
   }else
   {
       SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

       g_window = SDL_CreateWindow("My First Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
       if(g_window==NULL){
        return false;
       }
       else{
        g_screen= SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen==NULL){
            return false;
        }
        else
        {
             SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_CORLOR,RENDER_DRAW_CORLOR,RENDER_DRAW_CORLOR,RENDER_DRAW_CORLOR);
             int imgFlag=IMG_INIT_PNG;
             if(!(IMG_Init(imgFlag)&&imgFlag)){
                return false;
             }
        }
       }
       if(TTF_Init()==-1)
       {
           success=false;
       }
       font_time=TTF_OpenFont("font//dlxfont_.ttf",15);
       if(font_time==NULL)
       {
           success=false;
       }
       g_font_MENU = TTF_OpenFont("font//dlxfont_.ttf",60);
        if (g_font_MENU == NULL)
        {
            success=false;
        }
       if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1) success=false;
       g_sound_bk = Mix_LoadWAV("music//bk.wav");
       g_sound_exp = Mix_LoadWAV("music//exp.wav");
       g_sound_bullet= Mix_LoadWAV("music//bullet.wav");
       g_sound_comeback = Mix_LoadWAV("music//cb.wav");
       g_sound_play = Mix_LoadWAV("music//play.wav");
       g_sound_coin = Mix_LoadWAV("music//coin.wav");
       if(g_sound_bk== NULL|| g_sound_bullet==NULL||g_sound_comeback==NULL||g_sound_exp==NULL||g_sound_play==NULL||g_sound_coin==NULL) success=false;
   }
   return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//bk.png",g_screen);
    if(ret==false)
    {
        return false;
    }
    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen=NULL;

    SDL_DestroyWindow(g_window);
    g_window=NULL;

    IMG_Quit();
    SDL_Quit();
}
std::vector<TheatsObject*> Theats_List()
{
    std::vector<TheatsObject*> list_theats;


    TheatsObject* theats_move = new TheatsObject[4];

    for(int i=0;i<4;i++)
    {
        TheatsObject* p_theat = (theats_move+i);
        if(p_theat!=NULL)
        {
            p_theat->LoadImg("img//tl.png",g_screen);
            p_theat->SetClip();
            p_theat->SetTypeMove(TheatsObject::Move_In_Space);
            p_theat->set_x_pos(500+600*i);
            p_theat->set_y_pos(200);
            p_theat->set_input_left(1);

            int pos1=p_theat->get_x_pos()-60;
            int pos2=p_theat->get_x_pos()+60;

            p_theat->SetAnimationPos(pos1,pos2);


            list_theats.push_back(p_theat);
        }
    }


    TheatsObject* theats_obj = new TheatsObject[4];

    for(int i=0;i<4;i++)
    {
        TheatsObject* p_theat = (theats_obj+i);
        if(p_theat!=NULL)
        {
            p_theat->LoadImg("img//threat.png",g_screen);
            p_theat->SetClip();
            p_theat->SetTypeMove(TheatsObject::Static_Threat);
            p_theat->set_x_pos(1000+1100*i);
            p_theat->set_y_pos(250);

            BulletOpject* p_bullet = new BulletOpject();
            p_theat->InitBullet(p_bullet,g_screen);

            list_theats.push_back(p_theat);
        }
    }
    return list_theats;
}

int main(int argc,char* argv[]){

    ImpTimer fps_time;


    if(InitData()==false){
        return -1;
    }
    if(LoadBackground()==false){
        return -1;
    }
    bool is_quit=false;
    Mix_PlayChannel(-1,g_sound_bk,0);

    int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU, "Play Game", "Exit", "img//menu.png");
    if (ret_menu == 1)
        is_quit = true;

play_again:
    Mix_FreeChunk(g_sound_bk);
    g_sound_bk=NULL;
    GameMap game_map;
    game_map.LoadMap("map/map.dat");
    game_map.LoadTiles(g_screen);


    MainObject player;
    player.LoadImg("img//pr.png",g_screen);
    player.SetClip();

    PlayerPower player_pow;
    player_pow.Init(g_screen);
    PlayerPower* p_pow = &player_pow;

    std::vector<TheatsObject*> theat_list = Theats_List();

    ExplosionObject exp_threat;
    bool exp_ret=exp_threat.LoadImg("img//exp3.png",g_screen);
    if(!exp_ret) return -1;
    exp_threat.SetClip();


    GameText time_game;
    time_game.set_color(GameText::White_Text);

    GameText mark_game;
    mark_game.set_color(GameText::White_Text);
    Uint32 mark_val =0;

    GameText money_game;
    money_game.set_color(GameText::White_Text);

    Mix_PlayChannel(-1,g_sound_play,0);
    while(!is_quit)
    {
        fps_time.start();
        bool game_over=false;
        while(SDL_PollEvent(&g_event)!=0)
        {
            if(g_event.type==SDL_QUIT)
            {
                is_quit=true;
            }

           player.HandelInputActision(g_event,g_screen,g_sound_bullet);
        }
        SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_CORLOR,RENDER_DRAW_CORLOR,RENDER_DRAW_CORLOR,RENDER_DRAW_CORLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen,NULL);

        Map map_data = game_map.GetMap();

        player.HandelBullet(g_screen,map_data);
        player.SetMapXY(map_data.start_x,map_data.start_y);
        player.DoPlayer(map_data,p_pow,g_screen,g_sound_comeback,g_sound_coin);
        player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        GeometricFormat rectangle_size(0,0,SCREEN_WIDTH,45);
        ColorData color_data(255,255,255);
        Geometric::RenderRectangle(rectangle_size,color_data,g_screen);

        GeometricFormat outLineSize(0,0,SCREEN_WIDTH-1,43);
        ColorData color_data1(128,215,163);
        Geometric::RenderOutLine(outLineSize,color_data1,g_screen);


        player_pow.Show(g_screen);

        for(int i=0;i<theat_list.size();i++)
        {
            TheatsObject* p_theat = theat_list.at(i);
            if(p_theat!=NULL)
            {
                p_theat->SetMapXY(map_data.start_x,map_data.start_y);
                p_theat->ImpMoveType(g_screen);
                p_theat->DoTheats(map_data);
                p_theat->MakeBullet(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT,map_data);
                p_theat->show(g_screen);

                bool col=false;
                std::vector<BulletOpject*> tBullet_list = p_theat->get_bullet_list();
                for(int j=0;j<tBullet_list.size();j++)
                {
                    BulletOpject* bullet_t = tBullet_list.at(j);
                    if(bullet_t!=NULL)
                    {
                        SDL_Rect pRect = player.GetRectFrame();
                        SDL_Rect tBullet = bullet_t->GetRect();
                        col=SDLCommonFunc::CheckCollistion(tBullet,pRect);

                    }
                }
                SDL_Rect tRect=p_theat->GetRectFrame();
                SDL_Rect pRect = player.GetRectFrame();

                bool col1 = SDLCommonFunc::CheckCollistion(tRect,pRect);
                if(col1 || col )
                {

                   if(player_pow.get_num()>0)
                   {
                       player.SetRect(300,0);
                       player.set_come_back_time(1);
                       SDL_Delay(1000);
                       player_pow.Decrease();
                       player_pow.Render(g_screen);
                       continue;
                   }
                   else
                   {
                     game_over=true;
                   }


                }
            }
        }

        int exp_frame_width = exp_threat.get_frame_width();
        int exp_frame_height = exp_threat.get_frame_height();
        std::vector<BulletOpject*> bullet_arr = player.get_bullet_list();
        for(int i=0;i<bullet_arr.size();i++)
        {
            BulletOpject* p_bullet=bullet_arr.at(i);
            if(p_bullet!=NULL)
            {
                for(int j=0;j<theat_list.size();j++)
                {
                    TheatsObject* obj_theat=theat_list.at(j);
                    if(obj_theat!=NULL)
                    {
                        SDL_Rect jRect = obj_theat->GetRectFrame();

                        SDL_Rect iRect=p_bullet->GetRect();

                        bool col = SDLCommonFunc::CheckCollistion(jRect,iRect);

                        if(col==true)
                        {
                            if(obj_theat->GetTypeMove()==TheatsObject::Move_In_Space)
                            {
                                mark_val+=200;
                            }else mark_val+=100;
                            for(int ex=0;ex<Num_Frame_EXP;ex++)
                            {
                                int x_pos = p_bullet->GetRect().x-exp_frame_width*0.5;
                                int y_pos = p_bullet->GetRect().y-exp_frame_height*0.5;

                                exp_threat.set_frame(ex);
                                exp_threat.SetRect(x_pos,y_pos);
                                exp_threat.Show(g_screen);
                            }
                            Mix_PlayChannel(-1,g_sound_exp,0);
                            player.RemoveBullet(i);
                            obj_theat->Free();
                            theat_list.erase(theat_list.begin()+j);
                        }
                    }
                }
            }
        }

        std::string str_time ="Time: ";
        Uint32 time_val=SDL_GetTicks()/1000;
        Uint32 val_time=300-time_val;
        if(val_time<=0)
        {
            game_over=true;
        }
        else
        {
            std::string str_val=std::to_string(val_time);
            str_time+=str_val;
            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time,g_screen);
            time_game.RenderText(g_screen,SCREEN_WIDTH-200,25);
        }

            std::string val_mark_str =std::to_string(mark_val);
            std::string strmark="Mark: ";
            strmark += val_mark_str;
            mark_game.SetText(strmark);
            mark_game.LoadFromRenderText(font_time,g_screen);
            mark_game.RenderText(g_screen,SCREEN_WIDTH*0.5-50,25);

            int coin_count = player.get_coin_count();
            std::string val_coin_str =std::to_string(coin_count);
            std::string strcoin="Coin: ";
            strcoin+=val_coin_str;
            money_game.SetText(strcoin);
            money_game.LoadFromRenderText(font_time,g_screen);
            money_game.RenderText(g_screen,SCREEN_WIDTH*0.5-250,25);


        SDL_RenderPresent(g_screen);
        if(theat_list.size()==0)
        {
            Mix_FreeChunk(g_sound_play);
            g_sound_play=NULL;
            g_sound_bk = Mix_LoadWAV("music//bk.wav");
            Mix_PlayChannel(-1,g_sound_bk,0);
            int ret_win = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU, "Play Again", "Exit","img//win.png");
            if (ret_win == 1)
            {
                is_quit = true;
                continue;
            }
            else
            {
                is_quit = false;
                g_sound_play = Mix_LoadWAV("music//play.wav");
                goto play_again;
            }
        }

        if(game_over)
        {
            Mix_FreeChunk(g_sound_play);
            g_sound_play=NULL;
            g_sound_bk = Mix_LoadWAV("music//bk.wav");
            Mix_PlayChannel(-1,g_sound_bk,0);
            int ret_gover = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU, "Play Again", "Exit","img//gameover.png");
            if (ret_gover == 1)
            {
                is_quit = true;
                continue;
            }
            else
            {
                is_quit = false;
                for(int i=0;i<theat_list.size();i++)
              {
                   TheatsObject* p_theat = theat_list.at(i);
                   if(p_theat!=NULL)
                  {
                      p_theat->Free();
                      p_theat=NULL;
                  }
              }
                theat_list.clear();
                g_sound_play = Mix_LoadWAV("music//play.wav");
                goto play_again;
            }
        }

        int real_imp_time=fps_time.get_tick();
        int time_one_frame=1000/FRAME_PER_SECOND;

        if(real_imp_time<time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time>=0)
            SDL_Delay(delay_time);
        }

    }
    for(int i=0;i<theat_list.size();i++)
    {
            TheatsObject* p_theat = theat_list.at(i);
            if(p_theat!=NULL)
            {
                p_theat->Free();
                p_theat=NULL;
            }
    }
    theat_list.clear();

    close();
    return 0;
}
