#pragma once

#include <string>
#include <array>

#include <glib.h>         // for gchar
#include <gtk/gtk.h>      // for GtkWidget, GtkWindow, GtkBuilder

#include "Colors.h"
#include "ScribbleTool.h"



class ScribbleToolbar {
public:
    ScribbleToolbar();
    ~ScribbleToolbar();

    void buildToolbar(GtkWidget* toolbar);
    void create_tool_popover(ScribbleTool* tool);

    ColorPalette colorPalette;

private:
    void addToolButton(GtkWidget* toolbar, const gchar* iconName, const gchar* tooltip, ScribbleTool* tool);


    std::array<ScribbleTool*, 20> tools = {};
};