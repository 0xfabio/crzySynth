#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "Instrument.h"
#include "Envelope.h"
#include "Time.h"
#include "Noise.h"
#include "Crazy.h"
#include "Lfo.h"

using namespace std;

const int AMPLITUDE = 2800;
const int SAMPLE_RATE = 44100;
float freq = 440.0f;
int timer = 0;
int beats = 16;
int beat = 0;
float bpm = 120.0f;
int deltaTime;
int millis = 0;
int sixtnth = 0;

Crazy crazy;

Instrument kick(30.0f, beats);

Envelope kickVolEnv(&kick.volEnvVal, 0.9999f, 1.0f);
// Envelope kickPitchEnv(&kick.pitchEnvVal, 0.99f, 1.0f);

Instrument snare(300.0f, beats);
Noise snareN(beats);
Envelope snVolEnv(&snare.volEnvVal, 0.999f, 0.99999f);
Envelope snNEnv(&snareN.volEnvVal, 0.999f, 0.999999f);

Noise cHat(beats);
Envelope cHatVolEnv(&cHat.volEnvVal, 0.99f, 0.999f);

Noise oHat(beats);
float oHatVolDec = 0.9999999999f;
Envelope oHatVolEnv(&oHat.volEnvVal, oHatVolDec, 1.0f);
Lfo oHatVolLfo(0.001f, 0.00000f);

int bassKey = 31;
float bassFreq = crazy.midiToFreq(bassKey);
Instrument bass(bassFreq, beats);
float bassVolDecBase = 0.9999f;
Envelope bassVolEnv(&bass.volEnvVal, bassVolDecBase, 0.999999999f);
Lfo bassVolLfo(0.001f, 0.00001f);

int synthKey = 43;
float synthFreq = crazy.midiToFreq(synthKey);
Instrument synth(synthFreq, beats);
float synthVolDecBase = 0.999999999f;
Envelope synthVolEnv(&synth.volEnvVal, synthVolDecBase, 1.0f);
Lfo synthVolLfo(0.002f, 0.000001f);

Instrument arp(synthFreq, beats);
float arpVolDec = 0.999999f;
Envelope arpVolEnv(&arp.volEnvVal, arpVolDec, 1.0f);
Lfo arpVolLfo(0.001f, 0.00000001f);



float frac(float f) {
	return f - (int)f;
}

float randf() {
	return (rand() % 10000) / 5000.f - 1.f;
}

int bpmToDelta(float _bpm) {
	return (int) ((60000 / _bpm) / 4);
}


void nextStep() {
	timer++;
}


double getSample(double time) {
	nextStep();
	double out = kick.getSample(time) + snare.getSample(time) + snareN.getSample() + cHat.getSample() + oHat.getSample() + bass.getSample(time) * 0.7f + synth.getSample(time) * 0.6 + arp.getSample(time) * 0.5f;
	return out;
}

void audio_callback(void *user_data, Uint8 * raw_buffer, int bytes) {
	Sint16 *buffer = (Sint16*)raw_buffer;
	int length = bytes / 2;
	int &sample_nr(*(int*)user_data);

	for (int i = 0; i < length; i++, sample_nr++) {
		double time = (double)sample_nr / (double)SAMPLE_RATE;
		//buffer[i] = (Sint16)(AMPLITUDE * sin(2.0f * M_PI * freq * time));
		kickVolEnv.tick(kick.steps[sixtnth], millis);
		// kickPitchEnv.tick(kick.steps[sixtnth], millis);

		snVolEnv.tick(snare.steps[sixtnth], millis);
		snNEnv.tick(snareN.steps[sixtnth], millis);

		cHatVolEnv.tick(cHat.steps[sixtnth], millis);

		oHatVolLfo.tick();
		oHatVolEnv.valueFactor = oHatVolDec - oHatVolLfo.currentOut;
		oHatVolEnv.tick(oHat.steps[sixtnth], millis);

		bassVolLfo.tick();
		bassVolEnv.valueFactor = bassVolDecBase - synthVolLfo.currentOut;
		bassVolEnv.tick(bass.steps[sixtnth], millis);


		synthVolLfo.tick();
		synthVolEnv.valueFactor = synthVolDecBase - synthVolLfo.max + synthVolLfo.currentOut;
		synthVolEnv.tick(synth.steps[sixtnth], millis);

		arpVolLfo.tick();
		arpVolEnv.valueFactor = arpVolDec - arpVolLfo.max + arpVolLfo.currentOut;
		arpVolEnv.tick(1, millis);

		buffer[i] = (Sint16)(AMPLITUDE * getSample(time));
	}
}

int main (int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_AUDIO) != 0) SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
	
	cout << bassFreq << endl;
	int sample_nr = 0;
	deltaTime = bpmToDelta(bpm);
	cout << deltaTime << endl;

	Timer t = Timer();

	kick.initSteps();
	int kickSteps[] = {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0};
	kick.setSteps(kickSteps);

	snare.initSteps();
	snareN.initSteps();
	int snSteps[] = {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0};
	snare.setSteps(snSteps);
	snareN.setSteps(snSteps);

	cHat.initSteps();
	int cHatSteps[] = {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0};
	cHat.setSteps(cHatSteps);

	oHat.initSteps();
	int oHatSteps[] = {0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0};
	oHat.setSteps(oHatSteps);

	bass.initSteps();
	int bassSteps[beats];
	for (int i = 0; i < beats; i++) {
		bassSteps[i] = (crazy.randFloat() > 0.5 ? 1 : 0);
	}
	bass.setSteps(bassSteps);

	synth.initSteps();
	int synthSteps[beats];
	for (int i = 0; i < beats; i++) {
		synthSteps[i] = (crazy.randFloat() <= 0.6 ? 1 : 0);
	}
	synth.setSteps(synthSteps);

	arp.initSteps();
	int arpSteps[beats];
	for (int i = 0; i < beats; i++) {
		arpSteps[i] = 1;
	}
	arp.setSteps(arpSteps);
	int arpPitchSteps[beats];
	for (int i = 0; i < beats; i++) {
		int in = i % 6;
		int out = (in == 0 ? 0 : in + 1);
		arpPitchSteps[i] = crazy.midiToFreq(synthKey + crazy.scales[8] [out]);
		cout << arpPitchSteps[i] << endl;
	}
	

	
	//kickPitchEnv.startVal = 1.0f;
	SDL_AudioSpec want;
	want.freq = SAMPLE_RATE;
	want.format = AUDIO_S16SYS;
	want.channels = 2;
	want.samples = 2048;
	want.callback = audio_callback;
	want.userdata = &sample_nr;


	SDL_AudioSpec have;
	if (SDL_OpenAudio(&want, &have) != 0) SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());
	if (want.format != have.format) SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to get the desired AudioSpec");

	SDL_PauseAudio(0);

	t.setInterval([&] () {
		millis++;
		if (millis == deltaTime) {
			millis = 0;
			sixtnth++;
			if (sixtnth == 16) {
				sixtnth = 0;
			}
			kick.step(sixtnth);
			kickVolEnv.restart();
			// kickPitchEnv.restart();

			snare.step(sixtnth);
			snareN.step(sixtnth);
			snVolEnv.restart();
			snNEnv.restart();

			cHat.step(sixtnth);
			cHatVolEnv.restart();

			oHat.step(sixtnth);
			oHatVolEnv.restart();

			bass.step(sixtnth);
			bassVolEnv.restart();
			// bass.freq = crazy.randNoteFreq(8, bassKey, 1);

			synth.step(sixtnth);
			synthVolEnv.restart();
			synth.freq = crazy.randNoteFreq(8, synthKey, 1);

			arp.step(sixtnth);
			arpVolEnv.restart();
			arp.freq = arpPitchSteps[sixtnth];

			//cout << "Current Beat: " << sixtnth << endl;
		}

	}, 1);

	char * in;
	
	while (in != "q") {
		cin >> in;
		SDL_Delay(10);
	}

	SDL_CloseAudio();

	return 0;
}
