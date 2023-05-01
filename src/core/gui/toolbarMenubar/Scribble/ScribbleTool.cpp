#include "ScribbleTool.h"
#include <stdlib.h>
#include "ScribbleToolbar.h"

ScribbleTool::ScribbleTool() {
    name = "";
    toolbar = nullptr;
}

ScribbleTool::ScribbleTool(ScribbleToolbar* toolbar, std::string toolName) {
    this->toolbar = toolbar;
    this->name = toolName;
}


ScribbleToolbar* ScribbleTool::getToolbar() { return toolbar; }

void ScribbleTool::setColor(GdkRGBA color) { this->color = color; g_message("Color selected: %f, %f, %f, %f", color.red, color.green, color.blue, color.alpha); }


static void update_input_on_slider_changed(GtkScale* scale, gpointer data) {
    GtkEntry* entry = GTK_ENTRY(data);

    int value = (int)gtk_range_get_value(GTK_RANGE(scale));
    gtk_entry_set_text(entry, std::to_string(value).c_str());
}

static void update_slider_on_input_changed(GtkEntry* entry, gpointer data) {
    GtkScale* size_slider = GTK_SCALE(data);

    const char* input_str = gtk_entry_get_text(entry);
    int input = atoi(input_str);
    if(input <= 0)
        return;
    
    gtk_range_set_value(GTK_RANGE(size_slider), input);
}

void ScribbleTool::drawOptions(GtkWidget* popover) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //!===== Header
    GtkWidget* header_toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(box), header_toolbar);

    GtkWidget* header_icon = gtk_image_new_from_icon_name("edit-paste", GTK_ICON_SIZE_LARGE_TOOLBAR);
    gtk_box_pack_start(GTK_BOX(header_toolbar), header_icon, FALSE, FALSE, 0);
    GtkWidget* header_label = gtk_label_new("header");
    gtk_box_pack_start(GTK_BOX(header_toolbar), header_label, FALSE, FALSE, 5);
    GtkWidget* header_separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(header_toolbar), header_separator, TRUE, TRUE, 0);
    GtkWidget* header_close_button = gtk_button_new_from_icon_name("window-close", GTK_ICON_SIZE_BUTTON);
    g_signal_connect_swapped(header_close_button, "clicked", G_CALLBACK(gtk_widget_destroy), popover);
    gtk_box_pack_start(GTK_BOX(header_toolbar), header_close_button, FALSE, FALSE, 0);

    //!===== Color picker
    GtkWidget* color_picker = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(box), color_picker);

    GtkWidget* color_label = gtk_label_new("Color");
    gtk_box_pack_start(GTK_BOX(color_picker), color_label, FALSE, FALSE, 5);
    //TODO: add the 5 recent colors and the color picker button
    // GtkWidget* color_widget = create_color_picker();
    // gtk_box_pack_start(GTK_BOX(color_picker), color_widget, FALSE, FALSE, 5);

    //!===== Size picker
    GtkWidget* size_controls = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(box), size_controls);

    GtkWidget* size_label = gtk_label_new("Size");
    gtk_box_pack_start(GTK_BOX(size_controls), size_label, FALSE, FALSE, 5);
    GtkWidget* size_slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 96, 1);
    gtk_box_pack_start(GTK_BOX(size_controls), size_slider, TRUE, TRUE, 5);
    gtk_widget_set_size_request(size_slider, 200, -1);
    gtk_scale_set_draw_value(GTK_SCALE(size_slider), FALSE);
    GtkWidget* size_input = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(size_controls), size_input, FALSE, FALSE, 5);
    gtk_entry_set_width_chars(GTK_ENTRY(size_input), 2);
    g_signal_connect(size_input, "changed", G_CALLBACK(update_slider_on_input_changed),  (gpointer)size_slider);
    g_signal_connect(size_slider, "value-changed", G_CALLBACK(update_input_on_slider_changed),  (gpointer)size_input);


    gtk_container_add(GTK_CONTAINER(popover), box);
}

