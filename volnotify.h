#include <libnotify/notify.h>

void volnotify_init();
void volnotify_show(int volumeLevel, int volumeMuted);

NotifyNotification *volnotify_volume;