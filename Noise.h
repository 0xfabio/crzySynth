#ifndef NOISE_H
#define NOISE_H

#include <vector>

class Noise {
private:
    float stepLength;

public:
    Noise(int _stepLength);
    ~Noise();
    std::vector<int> steps;
    float currentVol;

    void initSteps();
    void setSteps(int* _steps);
    void step(int _currentBeat);
    float randf();
    double getSample();

    float volEnvVal = 1.0f;

};
#endif