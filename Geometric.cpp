#include "Geometric.h"

void Geometric::RenderRectangle(GeometricFormat& geo_size,ColorData& color,SDL_Renderer* screen)
{
    SDL_Rect fill_rect={geo_size.left_,geo_size.top_,geo_size.width_,geo_size.height_};
    SDL_SetRenderDrawColor(screen,color.red_,color.green_,color.blue_,0xff);
    SDL_RenderFillRect(screen,&fill_rect);

}

void Geometric::RenderOutLine(GeometricFormat& geo_size,ColorData& color,SDL_Renderer* screen)
{
    SDL_Rect out_rect={geo_size.left_,geo_size.top_,geo_size.width_,geo_size.height_};
    SDL_SetRenderDrawColor(screen,color.red_,color.green_,color.blue_,0xff);
    SDL_RenderFillRect(screen,&out_rect);
}
