#include "../inc/header.h"

// --- LOGIN ---
void func_rpl_login(char *params, void *p) {
    UNUSED(p);
    char *p_rpl = take_param(params, 1);
    if (strcmp(p_rpl, "ERROR") == 0) {
        if (strcmp(take_param(params, 2), "INCORRECT_LOGIN") == 0) {
            sw_login = 1;
        }
        else if (strcmp(take_param(params, 2), "INCORRECT_PASS") == 0) {
            sw_login = 2;
        }
    }
    else if (strcmp(p_rpl, "SUCCESS") == 0) {
        sw_login = 0;
    }
}

// --- REGISTER ---
void func_rpl_register(char *params, void *p) {
    UNUSED(p);
    char *p_rpl = take_param(params, 1);
    if (strcmp(p_rpl, "ERROR") == 0) {
        if (strcmp(take_param(params, 2), "USERNAME_EXIST") == 0) {
            sw_register = 1;
        }
        else if (strcmp(take_param(params, 2), "PASS_NOT_MATCH") == 0) {
            sw_register = 2;
        }
    }
    else if (strcmp(p_rpl, "SUCCESS") == 0) {
        sw_register = 0;
    }
}

// --- SEND ---
void func_rpl_send(char *params, void *p) {
    received_messages *received_mess = (received_messages *)malloc(sizeof(received_messages));
    client_t *client = (client_t *)p;
    received_mess->client = client;
    strcpy(received_mess->is_special, take_param(params, 7));
    strcpy(received_mess->message, take_param(params, 6));
    strcpy(received_mess->time, take_param(params, 5));
    strcpy(received_mess->sender_name, take_param(params, 4));
    received_mess->msg_id = atoi(take_param(params, 2));
    received_mess->chat_id = atoi(take_param(params, 1));

    /*int chat_index = get_index_by_chat_id(&received_mess->client->chat_list_head, received_mess->chat_id);

    char last_msg_time_buf[BUFFER_SZ];
    chat_info_t *chat = get_chat_p_by_chat_id(&received_mess->client->chat_list_head, received_mess->chat_id);

    //time_t time = (time_t)atoi(received_mess->time);
    //time_t time = (time_t)atoi(chat->last_msg_time);
    struct tm *ptm = localtime(&time);
    if (ptm == NULL) {
        puts("The localtime() function failed");
        return;
    }

    snprintf(last_msg_time_buf, BUFFER_SZ, "%s  %02d:%02d", chat->chat_name, ptm->tm_hour, ptm->tm_min);
    gtk_button_set_label(GTK_BUTTON(received_mess->client->m->chat[chat_index]), last_msg_time_buf);*/

    if (received_mess->chat_id == received_mess->client->active_chat_id)
        gdk_threads_add_idle(message_show, (gpointer)received_mess);

    //bzero(last_msg_time_buf, BUFFER_SZ);
}

// --- DELETE_MSG ---
void func_rpl_del_msg(char *params, void *p) {
    client_t *client = (client_t *)p;
    GtkListBox *box = client->m->box_message;
    int msg_id = atoi(take_param(params, 1));
    int index = get_index_by_msg_id(&client->msg_id_q_head, msg_id);

    gtk_list_box_select_row(box, gtk_list_box_get_row_at_index(box, (gint)index));
    gtk_container_remove(GTK_CONTAINER(box), GTK_WIDGET(gtk_list_box_get_selected_row (box)));
    del_elem_msg_id_q(&client->msg_id_q_head, msg_id);
    //printf("## index in rpl_delete: %d\n", index);
}

// --- DELETE_CHAT ---
void func_rpl_del_chat(char *params, void *p) {
    client_t *client = (client_t *)p;
    GtkListBox *box_chat_list = client->m->box_chat_list;
    int chat_id;

    char *p_rpl = take_param(params, 1);
    gtk_button_set_label(chat_lbl, "");
    gtk_widget_set_sensitive (GTK_WIDGET(chat_lbl), FALSE);
    if (strcmp(p_rpl, "NOT_OWNER") == 0) {
        printf("## NOT_OWNER\n");
    }
    else {
        chat_id = atoi(p_rpl);
        int index = get_index_by_chat_id(&client->chat_list_head, chat_id);
        client->active_chat_id = -1;

        gtk_list_box_select_row(box_chat_list, gtk_list_box_get_row_at_index(box_chat_list, (gint)index));
        gtk_container_remove(GTK_CONTAINER(box_chat_list), GTK_WIDGET(gtk_list_box_get_selected_row (box_chat_list)));
        del_elem_chat_list(&client->chat_list_head, chat_id);
        display_chat_list(&client->chat_list_head);

        while (clean_listbox((gpointer)client->m->box_message) == TRUE) {}
        clear_msg_id_q(&client->msg_id_q_head);
        client->m->row_num_list_gtk = -1;
        //printf("## index in rpl_del_chat: %d\n", index);
    }

}

// --- ADD_CHAT ---
void func_rpl_add_chat(char *params, void *p) {
    client_t *client = (client_t *)p;
    int p_chat_id = atoi(take_param(params, 1));
    char *p_chat_name = take_param(params, 2);
    if (p_chat_id == -1) {
        return;
    }

    if (is_chat_exists(&client->chat_list_head, p_chat_id)) {
        return;
    }

    // if chat_name not NULL
    if (p_chat_name != NULL) {
        to_chat_list(p_chat_id, p_chat_name, &client->chat_list_head);
    }

    chat_info_t *current = client->chat_list_head;
    chat_info_t *prev = client->chat_list_head;
    while (current != NULL)
    {
        prev = current;
        current = current->next;
    }

    chat_show_info_s *chat_show_info = (chat_show_info_s *)malloc(sizeof(chat_show_info_s));
    chat_show_info->chat = prev;
    chat_show_info->chat->f_unread_msg_id = atoi(take_param(params, 3));
    chat_show_info->chat->last_msg_time = atoi(take_param(params, 4));
    chat_show_info->client = client;
    chat_show_info->counter = ++client->last_chat_index;
    display_chat_list(&client->chat_list_head);
    //printf("rpl #### counter: %d  client->last_chat_index: %d  chat: %s #####\n",
    //    chat_show_info->counter, client->last_chat_index, chat_show_info->chat->chat_name);

    gdk_threads_add_idle(chat_show, (gpointer)chat_show_info);
}


// --- EDIT ---
void func_rpl_edit(char *params, void *p) {
    client_t *client = (client_t *)p;
    char *chat_id = take_param(params, 1);
    command cmd;
    char buffer[BUFFER_SZ];
    while (clean_listbox((gpointer)client->m->box_message) == TRUE) {}
    clear_msg_id_q(&client->msg_id_q_head);
    client->m->row_num_list_gtk = -1;
    snprintf(buffer, BUFFER_SZ, "<%s>", chat_id);
    cmd.command = "<CHAT_MSG>";
    cmd.params = strdup(buffer);
    send_cmd(cmd, client);

    bzero(buffer, BUFFER_SZ);
}

void init_funcs(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "<LOGIN>", "<REGISTER>", "<SEND>",
                                            "<ADD_CHAT>", "<DELETE_MSG>", "<EDIT_MSG>",
                                            "<DELETE_CHAT>"};

    arr_cmd_func[0].func = &func_rpl_login;
    arr_cmd_func[1].func = &func_rpl_register;
    arr_cmd_func[2].func = &func_rpl_send;
    arr_cmd_func[3].func = &func_rpl_add_chat;
    arr_cmd_func[4].func = &func_rpl_del_msg;
    arr_cmd_func[5].func = &func_rpl_edit;
    arr_cmd_func[6].func = &func_rpl_del_chat;

    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}

void init_switches(void) {
    sw_login = -1;
    sw_register = -1;
}
