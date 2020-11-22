#ifndef LFO_H
#define LFO_H
class Lfo {
private:
public:
    Lfo(float _max, float _factor);
    float max;
    float factor;
    float current = 0.5f;
    float currentOut;

    void tick();
};
#endif