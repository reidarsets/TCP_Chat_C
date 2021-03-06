#ifndef INTERFACE_H
#define INTERFACE_H

// INCLUDES
    #include <gtk/gtk.h>
    #include <stdlib.h>
    #include <string.h>
    #include "header.h"
//////////////////////////

// DEFINES

//////////////////////////

// STRUCTURES

//////////////////////////

// GLOBAL VARIABLES
    GtkBuilder      *builder;
    GObject *send_b;
    GtkWidget       *window, *chat_name_d, *chat_menu_wind, *add_memwind;
    char username_str [32], passoword_str[32], message_str[2048], username_str_s[32], nick_str_s[32], pass_str_s[32],
                r_pass_str_s[32], chatname_str[32], user_searh_str[32];
    int is_exit;
    GtkEntry *message_entry, *ipv_entry, *port_entry, *chatname_entry, *adduser_entry;
    GtkSpinner *connection_spin;
    //GtkListBox *box_chat_list;
    // GtkWidget *chat[MAX_CHATS];
    GtkButton *ch_b, *chat_lbl, *edit_b,  *add_user, *leave_chat, *add_mem,
                *cancel_u, *cancel_n;
    GtkLabel *chat_label, *incorrect_l, *incorrect_p, *diff_p, *username_e, *no_chat;

//////////////////////////

// FUNCTIONS
    gboolean destroy();
    void init_interface();
    //void init_connect_page();
    void open_signup_page();
    void open_login_page();
    void open_main_page();
    void username_changed();
    void password_changed();
    //void show_my_msg();
    void message_clear();
    void message_send();
    void username_s_changed();
    void nick_s_changed();
    void pass_s_changed();
    void r_pass_s_changed();
    void del_message();
    gboolean message_show();
    gboolean chat_show();
    void is_edit_delet();
    void message_delet();
    void message_edit();
    void cancel_ch();
    gboolean clean_listbox();
    void my_popup_handler();
    void new_chat();
    void chat_menu();
    void chatname_clear();
    void close_ch_dialog();
    void add_mem_wind();
    void user_searh_changed();
    void clean_adduser();
    void cancel_n_f();
    void cancel_d_f();
    void cancel_u_f();
    void some_func();
    //////////////////////////

#endif
