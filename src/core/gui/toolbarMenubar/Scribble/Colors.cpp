#include "Colors.h"
#include <string>

std::string defaults_colors[40] = { "#000", "#fff", "#f00", "#0f0", "#00f", "#0ff", "#f0f", "#ff0", 
                                    "#000", "#fff", "#f00", "#0f0", "#00f", "#0ff", "#f0f", "#ff0", 
                                    "#000", "#fff", "#f00", "#0f0", "#00f", "#0ff", "#f0f", "#ff0", 
                                    "#000", "#fff", "#f00", "#0f0", "#00f", "#0ff", "#f0f", "#ff0", 
                                    "#000", "#fff", "#f00", "#0f0", "#00f", "#0ff", "#f0f", "#ff0", };

ColorPalette::ColorPalette() {
    // Create the color palette array
    default_palette = new GdkRGBA[40];
    for (int i = 0; i < 40; i++) {
        gdk_rgba_parse(&default_palette[i], defaults_colors[i].c_str());
    }
}

ColorPalette::~ColorPalette() {}

GdkRGBA ColorPalette::getColorFromPicker() {
    GtkWidget* color_chooser = gtk_color_chooser_dialog_new("Choose color", NULL);
    gtk_color_chooser_set_use_alpha(GTK_COLOR_CHOOSER(color_chooser), FALSE);
    gtk_color_chooser_add_palette(GTK_COLOR_CHOOSER(color_chooser), GTK_ORIENTATION_HORIZONTAL, 8, 40, nullptr); // Reset the color palette
    gtk_color_chooser_add_palette(GTK_COLOR_CHOOSER(color_chooser), GTK_ORIENTATION_HORIZONTAL, 8, 40, default_palette); // Add our own

    GdkRGBA color; gdk_rgba_parse(&color, "#000");
    if(gtk_dialog_run(GTK_DIALOG(color_chooser)) == GTK_RESPONSE_OK) {
        gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(color_chooser), &color);
        g_message("Color selected: %f, %f, %f, %f", color.red, color.green, color.blue, color.alpha);
    }

    gtk_widget_destroy(color_chooser);
    return color;
}
