#include "ScribbleToolbar.h"

#include <unordered_map>

std::unordered_map<std::string, std::string> icons = {
        {"Pen", "xopp-tool-pencil"}, {"Eraser", "xopp-tool-eraser"}, {"Highlighter", "xopp-tool-highlighter"}};


static void on_tool_left_clicked(GtkWidget* widget, gpointer _data)
{
    ScribbleTool* tool = (ScribbleTool*)_data;

    tool->getToolbar()->create_tool_popover(tool);
}

static void on_tool_right_clicked(GtkWidget* widget, GdkEventButton* event, gpointer _data)
{
    if (event->button != 3)
        return;
    g_message("Right mouse button clicked");
    ScribbleTool* tool = (ScribbleTool*)_data;
    GdkRGBA color = tool->getToolbar()->colorPalette.getColorFromPicker();
    tool->setColor(color);

}



void ScribbleToolbar::addToolButton(GtkWidget* toolbar, const gchar* iconName, const gchar* tooltip, ScribbleTool* tool) {
    GtkToolItem* item = gtk_tool_button_new(NULL, tooltip);
    tool->toolItem = item;
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(item), iconName);
    g_object_ref(item);
    gtk_widget_set_tooltip_text(GTK_WIDGET(item), tooltip);

    g_signal_connect(item, "button-press-event", G_CALLBACK(&on_tool_right_clicked), (gpointer)tool);
    g_signal_connect(item, "clicked", G_CALLBACK(&on_tool_left_clicked), (gpointer)tool);

    gtk_widget_show_all(GTK_WIDGET(item));
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), GTK_TOOL_ITEM(item), -1);
}

ScribbleToolbar::ScribbleToolbar() {
    tools[0] = new ScribbleTool(this, "Pen");
    tools[1] = new ScribbleTool(this, "Pen");
    tools[2] = new ScribbleTool(this, "Pen");
    tools[3] = new ScribbleTool(this, "Eraser");
    tools[4] = new ScribbleTool(this, "Highlighter");
}

ScribbleToolbar::~ScribbleToolbar() {}

void ScribbleToolbar::buildToolbar(GtkWidget* toolbar) {
    for(ScribbleTool* tool : tools) {
        if(tool == nullptr)
            break;
        addToolButton(toolbar, icons[tool->name].c_str(), tool->name.c_str(), tool);
    }

    gtk_widget_show(toolbar);
}

void ScribbleToolbar::create_tool_popover(ScribbleTool* tool) {
    GtkWidget* popover = gtk_popover_new(GTK_WIDGET(tool->toolItem));
    gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_LEFT);

    tool->drawOptions(popover);

    gtk_widget_show_all(popover);
}