#include "Noise.h"
#include <iostream>
#include <cstdlib>
using namespace std;


Noise::Noise(int _stepLength) {
    stepLength = _stepLength;
    steps.reserve(stepLength);
    initSteps();
}
Noise::~Noise() {

}

void Noise::initSteps() {
    for (int i = 0; i < stepLength; i++) {
        steps[i] = 0;
    }
}

void Noise::setSteps(int* _steps) {
    for (int i = 0; i < stepLength; i++) {
        steps[i] = _steps[i];
    }
}

void Noise::step(int _currentBeat) {
    currentVol = (steps[_currentBeat] ? 1.0f : 0.000000001f);
}


float Noise::randf() {
	return (rand() % 10000) / 5000.f - 1.f;
}

double Noise::getSample() {
    double sample = randf() * currentVol * volEnvVal;
    return sample;
}