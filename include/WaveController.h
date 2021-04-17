#ifndef WAVECONTROLLER_H
#define WAVECONTROLLER_H


class WaveController
{
    public:
        WaveController();
        virtual ~WaveController();
        bool update();
        float wave_progress();
        int getwavenumber();
        bool next_wave();
    protected:
        int wavenumber;
        int wavethreshold;
        int wavetime;
    private:
};

#endif // WAVECONTROLLER_H
