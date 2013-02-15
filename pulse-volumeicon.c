#include <gtk/gtk.h>

//
// Fuction prototypes
void updateIcon(GtkStatusIcon *status_icon);

//
// Handler prototypes
void trayMenuPopup(GtkStatusIcon *status_icon, guint button, guint activate_time, gpointer popUpMenu);
void trayMenuPreferences(GtkMenuItem *menuitem, gpointer data);
void trayMenuExit(GtkMenuItem *menuitem, gpointer data);

void trayClickHandler(GtkStatusIcon *status_icon, GdkEventButton *event, gpointer user_data);
void trayScrollHandler(GtkStatusIcon *status_icon, GdkEventScroll *event, gpointer user_data);

int main(int argc, char *argv[]){

	//
	// Start GTK
	gtk_init (&argc, &argv);

	// Set up tray icon
	GtkStatusIcon *trayIcon = gtk_status_icon_new_from_icon_name("audio-volume-muted");

	// Set up tray menu
	GtkWidget *menu, *menuPreferences, *menuExit;

	menu = gtk_menu_new();

	// Creat menu items with labels and icons
	menuPreferences = gtk_image_menu_item_new_with_label("Preferences");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuPreferences),
		gtk_image_new_from_stock(GTK_STOCK_PREFERENCES, GTK_ICON_SIZE_MENU));

	menuExit = gtk_image_menu_item_new_with_label("Exit");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuExit),
		gtk_image_new_from_stock(GTK_STOCK_QUIT, GTK_ICON_SIZE_MENU));

	// Add items to menu
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuPreferences);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuExit);
	gtk_widget_show_all(menu);

	// Menu item handlers
	g_signal_connect(G_OBJECT(menuPreferences),
		"activate", G_CALLBACK(trayMenuPreferences), NULL);
	g_signal_connect(G_OBJECT(menuExit),
		"activate", G_CALLBACK(trayMenuExit), NULL);

	// Tray action handlers
	g_signal_connect(G_OBJECT(trayIcon),
		"popup-menu", G_CALLBACK(trayMenuPopup), menu);
	g_signal_connect(G_OBJECT(trayIcon),
		"button-release-event", G_CALLBACK(trayClickHandler), NULL);
	g_signal_connect(G_OBJECT(trayIcon),
		"scroll-event", G_CALLBACK(trayScrollHandler), NULL);

	//
	// GTK main loop
	gtk_main ();
	return 0;
}

//
// Handler functions

// Show tray menu
void trayMenuPopup(GtkStatusIcon *status_icon, guint button, guint activate_time, gpointer popUpMenu){
	gtk_menu_popup(GTK_MENU(popUpMenu), NULL, NULL, gtk_status_icon_position_menu, status_icon, button, activate_time);
}

// Menu item: Preferences
void trayMenuPreferences(GtkMenuItem *menuitem, gpointer data){
	//TODO: Show preferences window
	printf("Ima showin the preferences!\n");
}
// Menu item: Exit
void trayMenuExit(GtkMenuItem *menuitem, gpointer data){
	gtk_main_quit();
}

// Left/Middle click handler
void trayClickHandler(GtkStatusIcon *status_icon, GdkEventButton *event, gpointer user_data){
	if(event->button == 1)
		printf("Left click\n");
	else if(event->button == 2)
		printf("Middle click\n");
	else
		printf("Unknown button");
}

// Scroll event handler
void trayScrollHandler(GtkStatusIcon *status_icon, GdkEventScroll *event, gpointer user_data){
	if(event->direction == GDK_SCROLL_UP)
		printf("Scroll up\n");
	else if(event->direction == GDK_SCROLL_DOWN)
		printf("Scroll down\n");
	else
		printf("Unknown scroll direction");
}