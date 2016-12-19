#ifndef TIMER_H
#define TIMER_H


class timer
{
    public:
        timer();
        virtual ~timer();
        int GetTime();
        void StartTimer();
        int GetRemaining();
        void Setperiod(int val) { period = val; }
    protected:
    private:
        int StartTime;
        int period;
};

#endif // TIMER_H
