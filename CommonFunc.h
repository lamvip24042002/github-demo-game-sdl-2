#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include<string>
#include <vector>
#include<windows.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

static SDL_Window* g_window=NULL;
static SDL_Renderer* g_screen=NULL;
static SDL_Event g_event;

static Mix_Chunk* g_sound_bullet;
static Mix_Chunk* g_sound_exp;
static Mix_Chunk* g_sound_bk;
static Mix_Chunk* g_sound_comeback;
static Mix_Chunk* g_sound_play;

const int FRAME_PER_SECOND = 30;
const int SCREEN_WIDTH=1280;
const int SCREEN_HEIGHT=640;
const int SCREEN_BPP = 32;

const int CORLOR_KEY_R=167;
const int CORLOR_KEY_B=180;
const int CORLOR_KEY_G=175;
const int RENDER_DRAW_CORLOR=0Xff;

#define Coin_tile 4
#define Blank_Tile 0
#define TILE_SIZE 64
#define Max_map_x 70
#define Max_map_y 10

typedef struct Input
{
    int left_;
    int right_;
    int jump_;
};
typedef struct Map
{
    int start_x;
    int start_y;

    int Max_x_;
    int Max_y_;

    int Tile[Max_map_y][Max_map_x];
    char* file_name_;
};
 namespace SDLCommonFunc
 {
     bool CheckCollistion(const SDL_Rect& obj1,const SDL_Rect& obj2);
 }



#endif // COMMONFUNC_H_INCLUDED
