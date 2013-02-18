#include <pulse/pulseaudio.h>

void pulseaudio_init();

// void pulseaudio_event();

void pulseaudio_mute();
void pulseaudio_volume(int ammount);

int volumeLevel;
int volumeMuted;
