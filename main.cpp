#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

const int AMPLITUDE = 2800;
const int SAMPLE_RATE = 44100;
float freq = 440.0f;
int timer = 0;
int timeLength = 1600000;
int beats = 16;
int ticksPerBeat = timeLength / beats;
int beat = 0;

float frac(float f) {
	return f - (int)f;
}

float randf() {
	return (rand() % 10000) / 5000.f - 1.f;
}

void nextBeat() {
	beat++;
	if (beat == beats - 1) {
		beat = 0;
	}
	freq = (float) (100.0f * frac(beat * 1.0452435864432f) / 2) + 20.0f;
}

void nextStep() {
	timer++;
	
	if (timer >= ticksPerBeat) {
		timer = 0;
		nextBeat();
	}	
}

double getSample(double time) {
	nextStep();
	double val = sin(2.0f * M_PI * freq * time);
	return val;
}

void audio_callback(void *user_data, Uint8 * raw_buffer, int bytes) {
	Sint16 *buffer = (Sint16*)raw_buffer;
	int length = bytes / 2;
	int &sample_nr(*(int*)user_data);

	for (int i = 0; i < length; i++, sample_nr++) {
		double time = (double)sample_nr / (double)SAMPLE_RATE;
		//buffer[i] = (Sint16)(AMPLITUDE * sin(2.0f * M_PI * freq * time));
		buffer[i] = (Sint16)(AMPLITUDE * getSample(time));
	}
}

int main (int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_AUDIO) != 0) SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
	
	int sample_nr = 0;
	
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
	char * in;
	
	while (in != "q") {
		cin >> in;
		SDL_Delay(100);
	}

	SDL_CloseAudio();

	return 0;
}
