#ifndef IMPTIMER_H_INCLUDED
#define IMPTIMER_H_INCLUDED


class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    int get_tick();


private:
    int start_tick;

    bool is_started_;

};
#endif // IMPTIMER_H_INCLUDED
