#pragma once

#include <glib.h>         // for gchar
#include <gtk/gtk.h>      // for GtkWidget, GtkWindow, GtkBuilder



//TODO: add our own color palette, a ColorPalette class that creates the palette and handles the color selection


class ColorPalette {
public:
    ColorPalette();
    ~ColorPalette();

    // void buildPalette(GtkWidget* toolbar);
    GdkRGBA getColorFromPicker();

private:
    GdkRGBA* default_palette;
    GdkRGBA recent_colors[6];
};