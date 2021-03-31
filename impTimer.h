#ifndef IMPTIMER_H_INCLUDED
#define IMPTIMER_H_INCLUDED


class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void pause();
    void unpause();
    void stop();

    int get_tick();

    bool is_paused();
    bool is_started();

private:
    int start_tick;
    int paused_tick;

    bool is_paused_;
    bool is_started_;
};
#endif // IMPTIMER_H_INCLUDED
