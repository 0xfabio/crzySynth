#include "Envelope.h"
#include <iostream>
using namespace std;

Envelope::Envelope(float* _value ,float _valueFactor, float _factorFactor) {
	value = _value;
	startVal = *value;
	valueFactor = _valueFactor;
	startValFactor = valueFactor;
	factorFactor = _factorFactor;
	cout << "value addr: " << value << endl;
}

void Envelope::tick(int _currentStep, int _currentMillis) {
	if (_currentStep) {
		valueFactor *= factorFactor;
		*value *= valueFactor;
	}
}

void Envelope::restart() {
	*value = startVal;
	valueFactor = startValFactor;
	//cout << *value << "     " << valueFactor << endl;
}
