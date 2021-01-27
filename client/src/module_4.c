#include "../inc/header.h"

void *process_cmd(void *arg) {
	struct process_cmd_info_s *Info = (struct process_cmd_info_s *)arg;
	while(1) {
		if (Info->client->exit == 1) {
			break;
		}
		if (*Info->cmd_q_front != NULL)
		{
			command fst_cmd = take_fst_cmd_in_q(Info->cmd_q_front);
			move_cmd_q(Info->cmd_q_front);
			for (int j = 0; j < AMOUNT_OF_CMD; j++) {
				analyse_cmd(fst_cmd, Info->arr_cmd_func[j]);
			}
			if (strcmp(fst_cmd.command, Info->arr_cmd_func[10].name) == 0) {
				//gtk_text_buffer_insert_interactive(Info->client->m->buffer, &Info->client->m->iter, param_2(fst_cmd.params), -1, TRUE );
				//gtk_text_buffer_insert_interactive(Info->client->m->buffer, &Info->client->m->iter, "\n", -1, TRUE );
			}
		}
	}
	int ret_val = 1;
	printf("5. Process command thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}

void analyse_cmd(command fst_cmd, cmd_func function) {
	if (strcmp(fst_cmd.command, function.name) == 0) {
		printf("--- %s ---\n", function.name);
		function.func(fst_cmd.params);
	}
}
