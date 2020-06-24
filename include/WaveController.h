#ifndef WAVECONTROLLER_H
#define WAVECONTROLLER_H


class WaveController
{
    public:
        WaveController();
        virtual ~WaveController();
        bool update();
        float wave_progress();

    protected:
        int wavethreshold;
        int wavetime;
    private:
};

#endif // WAVECONTROLLER_H
