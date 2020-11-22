#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include <vector>

class Instrument {
private:
	float baseFreq;
	int stepLength;


public:
	Instrument(float _baseFreq, int _stepLength);
	~Instrument();
	std::vector<int> steps;
	float currentVol;
	float freq;

	void initSteps();
	void setSteps(int* _steps);
	void step(int _currentBeat);
	double getSample(double _time);

	float volEnvVal = 1.0f;
	float pitchEnvVal = 1.0f;

};



#endif
