#include "impTimer.h"
#include "CommonFunc.h"

ImpTimer::ImpTimer()
{
    start_tick=0;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start()
{
    is_started_=true;
    start_tick=SDL_GetTicks();
}


int ImpTimer::get_tick()
{
    if(is_started_==true)
    {

            return SDL_GetTicks()-start_tick;

    }
    return 0;
}


