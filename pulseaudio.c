#include "pulseaudio.h"
#include "trayicon.h"
#include "volnotify.h"

// TODO: All of this
 
void pulseaudio_init(){
	printf("Pulseaudio init\n");
	volumeLevel = 20;
	volumeMuted = 0;
	pulseaudio_volume(0);
}

// void pulseaudio_event(){
// 	// TODO: set as callback for external volme changes
// 	trayicon_update(volumeLevel, volumeMuted);
// }

//
// Hack to make this work while I figure out pulseaudio's API

void pulseaudio_mute(){
	printf("Mute toggled\n");
	volumeMuted ^= 1;
	if(volumeMuted)
		system("pactl set-sink-mute 0 1");
	else
		system("pactl set-sink-mute 0 0");
	volnotify_show(volumeLevel, volumeMuted);
	trayicon_update(volumeLevel, volumeMuted);
}

void pulseaudio_volume(int ammount){
	char buffer[30];

	printf("Volume change\n");

	volumeLevel += ammount;
	if(volumeLevel < 0)
		volumeLevel = 0;
	else if(volumeLevel > 100)
		volumeLevel = 100;

	snprintf(buffer, sizeof(buffer), "pactl set-sink-volume 0 %i%%", volumeLevel);
	system(buffer);
	volnotify_show(volumeLevel, volumeMuted);
	trayicon_update(volumeLevel, volumeMuted);

}
