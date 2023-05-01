#pragma once

#include <string>

#include <glib.h>         // for gchar
#include <gtk/gtk.h>      // for GtkWidget, GtkWindow, GtkBuilder


class ScribbleToolbar;

class ScribbleTool {
public:
    ScribbleTool();
    ScribbleTool(ScribbleToolbar* toolbar, std::string toolName);

    ScribbleToolbar* getToolbar();
    void setColor(GdkRGBA color);

    //TODO: Make virtual later ?
    void drawOptions(GtkWidget* popover);


    std::string name;
    GtkToolItem* toolItem;
private:
    ScribbleToolbar* toolbar;

    GdkRGBA color;
};