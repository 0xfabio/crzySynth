#include "Instrument.h"
#include <math.h>
#include <iostream>
using namespace std;

Instrument::Instrument(float _baseFreq, int _stepLength) {
	baseFreq = _baseFreq;
	freq = baseFreq;
	stepLength = _stepLength;
	steps.reserve(stepLength);
	initSteps();

}
Instrument::~Instrument() {
	cout << "Instrument Deleted" << endl;
}


void Instrument::initSteps() {
	for (int i = 0; i < stepLength; i++) {
		steps[i] = 0;
	}
}

void Instrument::setSteps(int* _steps) {
	for (int i = 0; i < stepLength; i++) {
		steps[i] = _steps[i];
	}
}

void Instrument::step(int _currentBeat) {
	currentVol = (steps[_currentBeat] ? 1.0f : 0.0000001f);
	// cout << pitchEnvVal << "   " << freq << endl;
}

double Instrument::getSample(double _time) {
	double newFreq = freq * pitchEnvVal;
	double sample = sin(2.0f * M_PI * newFreq * _time) * currentVol * volEnvVal;
	return sample;
}



