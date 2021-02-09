#include "../inc/interface.h"

void open_main_page(GtkWidget *widget, gpointer gp_client)
{
    UNUSED(widget);

    GObject *send_b;
    client_t *client = (client_t *)gp_client;
    GtkButton *menu_b;
    GtkMenu *menu;
    GtkWidget *menu_new_chat, *menu_join_chat;

    //GtkListBox *box;

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    //client->m = (gtk_utils_t *)malloc(sizeof(gtk_utils_t));
    //client->m = message_s;

    GtkWidget *send_b_image = gtk_image_new_from_file ("client/resources/send_b_img.png");
    GtkWidget *menu_b_image = gtk_image_new_from_file ("client/resources/menu.png");
    GtkWidget *edit_b_image = gtk_image_new_from_file ("client/resources/edit.png");


    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_get_position (GTK_WINDOW(window), &client->m->root_x, &client->m->root_y);
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_window_move(GTK_WINDOW(window), client->m->root_x, client->m->root_y);
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window);
    //ПЕРЕДЕЛАЙ ОКНА В ОКНА А НЕ ВИДЖЕТЫ
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner"));
    edit_b = GTK_BUTTON(gtk_builder_get_object (builder, "edit_b"));
    gtk_button_set_image (edit_b, edit_b_image);
    gtk_widget_hide(GTK_WIDGET(edit_b));
    menu_b = GTK_BUTTON(gtk_builder_get_object (builder, "main_menu"));
    chat_label  = GTK_LABEL(gtk_builder_get_object(builder, "chat_lbl"));
    gtk_button_set_image (menu_b, menu_b_image);
    menu_new_chat = gtk_menu_item_new_with_label ("Add Chat");
    menu_join_chat = gtk_menu_item_new_with_label ("Join Chat");
    menu = GTK_MENU(gtk_builder_get_object (builder, "menu"));
    chat_lbl = GTK_BUTTON(gtk_builder_get_object (builder, "chat_label"));
    gtk_button_set_label(chat_lbl, "");
    gtk_menu_button_set_popup (GTK_MENU_BUTTON(menu_b), GTK_WIDGET(menu));

    
    gtk_menu_attach (menu, menu_new_chat, 0, 1, 0, 1);
    gtk_menu_attach (menu, menu_join_chat, 0, 1, 1, 2);
    gtk_widget_show_all(GTK_WIDGET(menu));

    send_b = gtk_builder_get_object (builder, "send_buttom");
    gtk_button_set_image (GTK_BUTTON (send_b), send_b_image);

    client->m->box_message = GTK_LIST_BOX(gtk_builder_get_object(builder, "message_list"));
    client->m->box_chat_list = GTK_LIST_BOX(gtk_builder_get_object(builder, "chat_list"));
    //gtk_text_buffer_create_tag(message_s->buffer, "gray_bg", "background","gray", NULL);
    //gtk_text_buffer_insert_with_tags_by_name (message_s->buffer, &message_s->end, "name", -1, "gray_bg", NULL);
    message_entry = GTK_ENTRY(gtk_builder_get_object(builder, "message_entry"));

    //g_signal_connect(send_b, "clicked", G_CALLBACK(show_my_msg), (gpointer)message_s);
    //gtk_binding_entry_add_signall()
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_send), gp_client);
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_clear), NULL);
    gtk_list_box_set_selection_mode(client->m->box_message, GTK_SELECTION_SINGLE);
    gtk_list_box_set_activate_on_single_click (client->m->box_message, FALSE);
    gdk_threads_add_idle(is_edit_delet, (gpointer)client);
    client->m->cancel_b = GTK_WIDGET(gtk_builder_get_object (builder, "cancel_b"));
    client->m->edit_b = GTK_WIDGET(gtk_builder_get_object (builder, "ed_b"));
    client->m->delet_b = GTK_WIDGET(gtk_builder_get_object (builder, "del_b"));
    client->m->b_box = GTK_BUTTON_BOX(gtk_builder_get_object(builder, "ed_del_box"));
    gtk_widget_hide(GTK_WIDGET(client->m->b_box));
    gtk_widget_hide(client->m->cancel_b);
    gtk_widget_hide(client->m->edit_b);
    gtk_widget_hide(client->m->delet_b);
    g_signal_connect(client->m->delet_b, "clicked", G_CALLBACK(message_delet),gp_client);
    g_signal_connect(client->m->edit_b, "clicked", G_CALLBACK(message_edit),gp_client);
    g_signal_connect(client->m->cancel_b, "clicked", G_CALLBACK(cancel_ch),gp_client);


    new_chat_request_s *new_chat_r = (new_chat_request_s *)malloc(sizeof(new_chat_r));
    new_chat_r->client = client;
    ch_b = GTK_BUTTON(gtk_builder_get_object(builder, "confirm"));
    g_signal_connect(ch_b, "clicked", G_CALLBACK(new_chat_request), (gpointer)new_chat_r);
    g_signal_connect(ch_b, "clicked", G_CALLBACK(chatname_clear), NULL);
    g_signal_connect(menu_new_chat, "activate", G_CALLBACK(new_chat), gp_client);
    g_signal_connect(chat_lbl, "clicked", G_CALLBACK(chat_menu), gp_client);
    //g_signal_connect(message_s->view, "move-cursor", G_CALLBACK(del_message), (gpointer)message_s->buffer);

}
