#include "volnotify.h"

void volnotify_init(){
	notify_init("pulse-volumeicon");
	volnotify_volume = notify_notification_new(NULL, NULL, NULL);

	notify_notification_set_timeout(volnotify_volume, NOTIFY_EXPIRES_DEFAULT);
	notify_notification_set_hint_string(volnotify_volume, "synchronous", "volume");
}

void volnotify_show(int volumeLevel, int volumeMuted){
	if(volumeMuted || volumeLevel == 0)
		notify_notification_update(volnotify_volume,
			"pulse-volumeicon", NULL, "audio-volume-muted");
	else if(volumeLevel <= 33)
		notify_notification_update(volnotify_volume,
			"pulse-volumeicon", NULL, "audio-volume-low");
	else if(volumeLevel <= 66)
		notify_notification_update(volnotify_volume,
			"pulse-volumeicon", NULL, "audio-volume-medium");
	else
		notify_notification_update(volnotify_volume,
			"pulse-volumeicon", NULL, "audio-volume-high");

	notify_notification_set_hint_int32(volnotify_volume, "value", volumeLevel);
	notify_notification_show(volnotify_volume, NULL);
}