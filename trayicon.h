#include <gtk/gtk.h>

void trayicon_init();
void trayicon_update(int volumeLevel, int volumeMuted);

// void trayicon_menuPopup(GtkStatusIcon *status_icon,guint button, guint activate_time, gpointer popUpMenu);
void trayicon_click(GtkStatusIcon *status_icon, GdkEventButton *event, gpointer user_data);
void trayicon_scroll(GtkStatusIcon *status_icon, GdkEventScroll *event, gpointer user_data);

GtkStatusIcon *trayIcon;