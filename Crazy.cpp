#include "Crazy.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

float Crazy::midiToFreq(int _noteNr){
    float a = 440.0f; //frequency of A (coomon value is 440Hz)
    return (a / 32.0f) * pow(2.0f, ((_noteNr - 9.0f) / 12.0f));

}
float Crazy::randFloat() {
    float out = (float) rand() / (RAND_MAX);
    if (out < 0) out *= (-1);
    return out;
}
int Crazy::randNote(int _range) {
    return (int)randFloat() * _range;
}
int Crazy::randNoteKey(int _scale, int _key, int _range) {
    int note = (int)(randFloat() * 7);
    // cout << "Note :  "<< note << endl;
    int range = (int)(randFloat() * _range);
    int scale = scales[_scale] [note];
    // cout << "Scale nr  " << scale << endl;
    int out = (int)(range * 12 + _key + scale);
    // cout << "rand Note:  " << out << endl;
    return out;
}
float Crazy::randNoteFreq(int _scale, int _key, int _range) {
    int key = randNoteKey(_scale, _key, _range);
    // cout << "randkey:  " << key << endl;
    float t = midiToFreq(key);
    return t;
}