#ifndef GAME_MAP_H_INCLUDED
#define GAME_MAP_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"

#define Max_Tiles 20

class TileMat: public BaseOject
{
public:

    TileMat(){;}
    ~TileMat(){;}
};

class GameMap
{
public:
    GameMap(){;}
    ~GameMap(){;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);

    Map GetMap() const {return game_map_;}
    void SetMap(Map& map_data) {game_map_=map_data;};
private:
    Map game_map_;
    TileMat tile_mat[Max_Tiles];

};

#endif // GAME_MAP_H_INCLUDED
