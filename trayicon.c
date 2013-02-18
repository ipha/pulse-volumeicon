#include "trayicon.h"
#include "pulseaudio.h"

void trayicon_init(){
	// Set up tray icon
	trayIcon = gtk_status_icon_new_from_icon_name("audio-volume-muted");

	// // Set up tray menu
	// GtkWidget *menu, *menuExit;

	// menu = gtk_menu_new();

	// // Creat menu items with labels and icons
	// menuExit = gtk_image_menu_item_new_with_label("Exit");
	// gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuExit),
	// 	gtk_image_new_from_stock(GTK_STOCK_QUIT, GTK_ICON_SIZE_MENU));

	// // Add items to menu
	// gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuExit);
	// gtk_widget_show_all(menu);

	// // Menu item handlers
	// g_signal_connect(G_OBJECT(menuExit),
	// 	"activate", G_CALLBACK(gtk_main_quit), trayIcon);

	// // Tray action handlers
	// g_signal_connect(G_OBJECT(trayIcon),
	// 	"popup-menu", G_CALLBACK(trayicon_menuPopup), menu);
	g_signal_connect(G_OBJECT(trayIcon),
		"button-release-event", G_CALLBACK(trayicon_click), NULL);
	g_signal_connect(G_OBJECT(trayIcon),
		"scroll-event", G_CALLBACK(trayicon_scroll), NULL);
}

void trayicon_update(int volumeLevel, int volumeMuted){
	printf("volume: %i\n", volumeLevel);
	if(volumeMuted || volumeLevel == 0)
		gtk_status_icon_set_from_icon_name(trayIcon, "audio-volume-muted");
	else if(volumeLevel <= 33)
		gtk_status_icon_set_from_icon_name(trayIcon, "audio-volume-low");
	else if(volumeLevel <= 66)
		gtk_status_icon_set_from_icon_name(trayIcon, "audio-volume-medium");
	else
		gtk_status_icon_set_from_icon_name(trayIcon, "audio-volume-high");
}

//
// GTK Handler functions

// // Show tray menu
// void trayicon_menuPopup(GtkStatusIcon *status_icon, guint button, guint activate_time, gpointer popUpMenu){
// 	gtk_menu_popup(GTK_MENU(popUpMenu), NULL, NULL, gtk_status_icon_position_menu, status_icon, button, activate_time);
// }

// Left/Middle click handler
void trayicon_click(GtkStatusIcon *status_icon, GdkEventButton *event, gpointer user_data){
	if(event->button == 1)
		printf("Left click\n");
	else if(event->button == 2)
		pulseaudio_mute();
}

// Scroll event handler
void trayicon_scroll(GtkStatusIcon *status_icon, GdkEventScroll *event, gpointer user_data){
	if(event->direction == GDK_SCROLL_UP)
		pulseaudio_volume(1);
	else if(event->direction == GDK_SCROLL_DOWN)
		pulseaudio_volume(-1);
}