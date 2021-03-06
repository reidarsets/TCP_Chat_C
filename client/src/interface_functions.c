#include "../inc/interface.h"

void init_interface(int *argc, char ***argv, gpointer p_client) {
    //GObject *connect_b;
    GtkWidget *widget =  NULL;
    client_t *client = (client_t *)p_client;
    static gtk_utils_t m;
    gtk_utils_t *message_s = (gtk_utils_t *)malloc(sizeof(gtk_utils_t *));
    message_s = &m;
    client->m = (gtk_utils_t *)malloc(sizeof(gtk_utils_t *));
    client->m = message_s;
    client->m->root_x = 0;
    client->m->root_y = 0;
    gtk_init(argc, argv);
    open_login_page(widget, p_client);
}

/*void init_connect_page(GObject **p_connect_b, GtkBuilder **p_builder, gpointer gp_client) {
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    window = GTK_WIDGET(gtk_builder_get_object(*p_builder, "connect_window"));
    gtk_builder_connect_signals(*p_builder, NULL);
    *p_connect_b = gtk_builder_get_object (*p_builder, "connect_b");
    gtk_widget_show(window);
    ipv_entry = GTK_ENTRY(gtk_builder_get_object(builder, "ipv_field"));
    port_entry = GTK_ENTRY(gtk_builder_get_object(builder, "port_field"));
    g_signal_connect(*p_connect_b, "clicked", G_CALLBACK(open_login_page), gp_client);
	g_signal_connect(*p_connect_b, "clicked", G_CALLBACK(th_connect_to_server), gp_client);
    g_object_unref(*p_builder);
}*/

void open_signup_page(GtkWidget *widget, gpointer gp_client)
{
    GObject *login_p;
    GObject *signup_b;
    UNUSED(widget);
    GtkImage *logo;
    client_t *client = (client_t *)gp_client;

    gtk_window_get_position (GTK_WINDOW(window), &client->m->root_x, &client->m->root_y);
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "client/resources/messanger.glade", NULL);
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "signup_window"));
    gtk_window_set_title (GTK_WINDOW(window), "PLACE");
    logo = GTK_IMAGE(gtk_builder_get_object(builder, "logo_1"));
    gtk_image_set_from_file(logo, "client/resources/logo_1.png");
    gtk_window_move(GTK_WINDOW(window), client->m->root_x, client->m->root_y);
    gtk_builder_connect_signals(builder, NULL);
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner_s"));
    diff_p = GTK_LABEL(gtk_builder_get_object(builder, "diff_pass"));
    username_e = GTK_LABEL(gtk_builder_get_object(builder, "username_ex"));
    gtk_widget_hide(GTK_WIDGET(diff_p));
    gtk_widget_hide(GTK_WIDGET(username_e));
    login_p = gtk_builder_get_object (builder, "login_p");
    signup_b = gtk_builder_get_object (builder, "signup_b");
    g_signal_connect(login_p, "clicked", G_CALLBACK(open_login_page), gp_client);
    g_signal_connect(signup_b, "clicked", G_CALLBACK(func_register), gp_client);
    gtk_widget_show(window);
}

void open_login_page(GtkWidget *widget, gpointer gp_client)
{
	UNUSED(widget);
    GObject *signup_p;
    GObject *login_b;
    GObject *login;
    GtkEntry *password;
    GtkImage *logo;
    //client_t *client = (client_t *)gp_client;

    //gtk_window_get_position (GTK_WINDOW(window), &client->m->root_x, &client->m->root_y);
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "client/resources/messanger.glade", NULL);
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    gtk_window_set_title (GTK_WINDOW(window), "PLACE");
    logo = GTK_IMAGE(gtk_builder_get_object(builder, "logo_2"));
    gtk_image_set_from_file(logo, "client/resources/logo_2.png");
    //gtk_window_move(GTK_WINDOW(window), client->m->root_x, client->m->root_y);
    gtk_builder_connect_signals(builder, NULL);
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner_l"));
    signup_p = gtk_builder_get_object (builder, "signup_p");
    login_b = gtk_builder_get_object (builder, "login_b");
    g_signal_connect(signup_p, "clicked", G_CALLBACK(open_signup_page), gp_client);
    g_signal_connect(login_b, "clicked", G_CALLBACK(func_login), gp_client);
    incorrect_l = GTK_LABEL(gtk_builder_get_object(builder, "incorrect_l"));
    incorrect_p = GTK_LABEL(gtk_builder_get_object(builder, "incorrect_p"));
    gtk_widget_hide(GTK_WIDGET(incorrect_l));
    gtk_widget_hide(GTK_WIDGET(incorrect_p));
    login = gtk_builder_get_object(builder, "login");
    password = GTK_ENTRY(gtk_builder_get_object(builder, "password"));
    gtk_entry_set_visibility (password, FALSE);
    gtk_entry_set_icon_from_icon_name(password, GTK_ENTRY_ICON_SECONDARY,"view-reveal-symbolic");
    gtk_widget_show(window);
}

void is_edit_delet( GtkListBox * box, gpointer m) {
    client_t *client = (client_t *)m;

    if(gtk_list_box_get_selected_row (box)){
        gtk_widget_show(GTK_WIDGET(client->m->b_box));
        gtk_widget_show(client->m->cancel_b);
        gtk_widget_show(client->m->edit_b);
        gtk_widget_show(client->m->delet_b);
        gtk_widget_hide(GTK_WIDGET(add_user));
        gtk_widget_hide(GTK_WIDGET(leave_chat));
    }
    else
    {
        gtk_widget_hide(GTK_WIDGET(client->m->b_box));
        gtk_widget_hide(client->m->cancel_b);
        gtk_widget_hide(client->m->edit_b);
        gtk_widget_hide(client->m->delet_b);
        gtk_widget_show(GTK_WIDGET(add_user));
        gtk_widget_show(GTK_WIDGET(leave_chat));

    }
}

gboolean clean_listbox(gpointer data){
    GtkListBox *box = (GtkListBox *)data;
    if(gtk_list_box_get_row_at_index (box,(gint)0)){
        gtk_container_remove(GTK_CONTAINER(box),
                GTK_WIDGET(gtk_list_box_get_row_at_index (box, (gint)0)));
        return TRUE;
    }
    else{
        return FALSE;
    }
}

void cancel_ch(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    client_t *client = (client_t *)data;
    gtk_list_box_unselect_all(client->m->box_message);
    gtk_entry_set_placeholder_text(GTK_ENTRY(message_entry), "");
    gtk_widget_hide(GTK_WIDGET(edit_b));
}

void new_chat(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    client_t *client = (client_t *)data;
    GtkWidget  *chat_name;
    static int i = 0;
    // printf("index new_chat: %d\n", i);
    i++;
    gtk_window_get_position (GTK_WINDOW(window), &client->m->root_x, &client->m->root_y);
    chat_name_d  = GTK_WIDGET(gtk_builder_get_object(builder, "chat_name"));
    gtk_window_move(GTK_WINDOW(chat_name_d), client->m->root_x, client->m->root_y+398);
    gtk_widget_show(chat_name_d);
    chat_name = GTK_WIDGET(gtk_builder_get_object(builder, "name"));
    chatname_entry = GTK_ENTRY(gtk_builder_get_object(builder, "name"));
}

/*void chat_menu(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    client_t *client = (client_t *)data;

    chat_menu_wind = GTK_WIDGET(gtk_builder_get_object(builder, "chat_dialog"));
    gtk_window_move(GTK_WINDOW(chat_menu_wind), client->m->root_x, client->m->root_y);
    gtk_widget_show(chat_menu_wind);
}*/

gboolean destroy() {
    gtk_main_quit();
    return TRUE;
}

gboolean chat_show(gpointer m) {
    static int last_added_chat_index = -1;
    chat_show_info_s *chat_show_info = (chat_show_info_s *)m;
    char last_msg_time_buf[BUFFER_SZ];
    int new_chat_index = chat_show_info->counter;

    // printf("new_chat_index: %d\nlast_added_chat_index: %d\n", new_chat_index, last_added_chat_index);

    if (new_chat_index > last_added_chat_index) {
        sort_listbox(&chat_show_info->client->chat_list_head, chat_show_info->client);
        last_added_chat_index = new_chat_index;
        bzero(last_msg_time_buf, BUFFER_SZ);
    }

    if (chat_show_info->client->exit == 1)
        return FALSE;
    return FALSE;
}
void add_mem_wind(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    gtk_widget_hide(chat_menu_wind);
    client_t *client = (client_t *)data;
    GtkEntry *entr;
    entr = GTK_ENTRY(gtk_builder_get_object(builder, "search_user"));
    gtk_widget_set_sensitive(GTK_WIDGET(entr), TRUE);
    gtk_window_get_position (GTK_WINDOW(window), &client->m->root_x, &client->m->root_y);
    add_memwind = GTK_WIDGET(gtk_builder_get_object(builder, "add_user_chat"));
    gtk_window_move(GTK_WINDOW(add_memwind), client->m->root_x+600, client->m->root_y+52);
    gtk_widget_show(add_memwind);
}
void clean_adduser() {
    gtk_entry_set_text(GTK_ENTRY(adduser_entry), "");
}
void cancel_n_f() {
    gtk_widget_hide(chat_name_d);
}
void cancel_u_f() {
    gtk_widget_hide(add_memwind);
}






/* 
 * Dorabotat` napil`nikom.
 * 15.02.2021
 * Odarchenko M. S. 
 * Asemiletov A. I.
 * Kuleshova D. A. 
 * Botezat V. K.
 * Ivanov M. M.
 * 
 */


