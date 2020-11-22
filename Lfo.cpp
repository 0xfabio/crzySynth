#include "Lfo.h"

Lfo::Lfo(float _max, float _factor) {
    max = _max;
    factor = _factor;
}
/* int max;
float factor;
float current = 0.5f 
float currentOut*/

void Lfo::tick() {
    current += factor;
    if (current > 0.99999f || current < 0.000001f) factor *= (-1);
    currentOut = max * current;
}