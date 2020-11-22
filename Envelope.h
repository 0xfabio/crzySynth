#ifndef ENVELOPE_H
#define ENVELOPE_H
#include <vector>

class Envelope {
private:
	float startValFactor;
	std::vector<int> steps;
public:
	float* value;
	float valueFactor;
	float factorFactor;
	float startVal = 1.0f;

	Envelope(float* _value, float _valueFactor, float _factorFactor);
	void tick(int _currentStep, int _currentMillis);
	void restart();
};
#endif
