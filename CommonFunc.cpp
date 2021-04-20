#include "CommonFunc.h"
int SDLCommonFunc::ShowMenu(SDL_Renderer* g_screen, TTF_Font* font, const std::string& menu1, const std::string& menu2,const std::string& img_name)
{
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 2;
    char* labels[kMenuNum];

    labels[0] = new char [size1 + 1];
    labels[1] = new char[size2 + 1];

    strcpy_s(labels[0], size1+1, ch1);
    strcpy_s(labels[1], size2+1, ch2);

    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 };
    SDL_Color color[2] = { { 255, 255, 255 },{ 255, 0, 0 } };

    GameText text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].set_color(color[0].r, color[0].g, color[0].b);

    text_object[0].LoadFromRenderText(font, g_screen);

    text_object[1].SetText(labels[1]);
    text_object[1].set_color(color[0].r, color[0].g, color[0].b);
    text_object[1].LoadFromRenderText(font, g_screen);


    SDL_Rect pos[kMenuNum];
    pos[0].x = SCREEN_WIDTH*0.4 - 100;
    pos[0].y = SCREEN_HEIGHT*0.5 - 40;
    pos[1].x = SCREEN_WIDTH*0.4 - 100;
    pos[1].y = SCREEN_HEIGHT*0.5 + 40;

    BaseOject gBackground;
    bool ret = gBackground.LoadImg(img_file, g_screen);

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[0].Free();
                gBackground.Free();
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].set_color(color[1].r, color[1].g, color[1].b);
                            text_object[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].set_color(color[0].r, color[0].g, color[0].b);
                            text_object[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        gBackground.Free();
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    gBackground.Free();
                    return 1;
                }
            }
        }

        gBackground.Render(g_screen, NULL);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].GetWidth();
            pos[i].h = text_object[i].GetHeight();
        }


        SDL_RenderPresent(g_screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
}
bool SDLCommonFunc::CheckCollistion(const SDL_Rect& obj1,const SDL_Rect& obj2)
{
  int x1_1 = obj1.x;
  int x2_1 = obj1.x + obj1.w;
  int y1_1 = obj1.y;
  int y2_1 = obj1.y + obj1.h;

   /* x1,y1............x2,y1
      .                    .
      .                    .
      .                    .
      .                    .
      x1,y2............x2,y2*/
  int x1_2 = obj2.x;
  int x2_2 = obj2.x + obj2.w;
  int y1_2 = obj2.y;
  int y2_2 = obj2.y + obj2.h;

  // TH1 obj1 > obj2
  if (x1_1 > x1_2 && x1_1 < x2_2)
  {
    if (y1_1 > y1_2 && y1_1 < y2_2)
    {
      return true;
    }
    else if(y2_1 > y1_2 && y2_1 < y2_2)
    {
      return true;
    }
  }

  if (x2_1 > x1_2 && x2_1 < x2_2)
  {
    if (y2_1 > y2_2 && y2_1 < y1_2)
    {
      return true;
    }
    else if(y2_1 > y1_2 && y2_1< y2_2)
    {
      return true;
    }
  }


  // TH2: obj1 <  obj2
  if (x1_2 > x1_1 && x1_2 < x2_1)
  {
    if (y1_2 > y1_1 && y1_2 < y2_1)
    {
      return true;
    }
    else if(y2_2 > y1_1 && y2_2 < y2_1)
    {
      return true;
    }
  }

  if (x2_2 > x1_1 && x2_2 < x2_1)
  {
    if (y2_2 > y2_1 && y2_2 < y1_1)
    {
      return true;
    }
    else if(y2_2 > y1_1 && y2_2 < y2_1)
    {
      return true;
    }
  }

   // TH3: obj1 = obj2
  if (y1_1 == y1_2 && x2_1 == x2_2 && y2_1 == y2_2 && x1_1 == x1_2)
  {
    return true;
  }

  return false;
}
