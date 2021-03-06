#include "../inc/header.h"

	static char inbuf[BUFFER_SZ];
	static size_t inbuf_used = 0;
void input_pump(struct read_msg_info_s *Info) {

	size_t inbuf_remain = sizeof(inbuf) - inbuf_used;
	if (inbuf_remain == 0) {
		fprintf(stderr, "Line exceeded buffer length!\n");
	}
	ssize_t rv = recv(Info->client->sockfd, (void*)&inbuf[inbuf_used], inbuf_remain, MSG_DONTWAIT);
	if (rv == 0) {
		Info->client->is_connected = 0;
		sem_post(sem_reconnect);
		return;
	}
	if (rv < 0 && errno == EAGAIN) {
		/* no data for now, call back when the socket is readable */
		return;
	}
	if (rv < 0) {
		// printf("\r-- Disconnected from server --\n");
		return;
	}
	inbuf_used += rv;
	/* Scan for newlines in the line buffer; we're careful here to deal with embedded \0s
	* an evil server may send, as well as only processing lines that are complete.
	*/
	char *line_start = inbuf;
	char *line_end;
	while ( (line_end = (char*)memchr((void*)line_start, '\n', inbuf_used - (line_start - inbuf))))
	{

		*line_end = 0;
		// printf("  > input: %s\n", line_start);
		to_msg_q(line_start, Info->msg_q_front, Info->lock);
		sem_post(sem_msg_q);
		line_start = line_end + 1;
	}
	/* Shift buffer down so the unprocessed data is at the start */
	inbuf_used -= (line_start - inbuf);
	memmove(inbuf, line_start, inbuf_used);
}

void *read_msg(void *arg) {
	struct read_msg_info_s *Info = (struct read_msg_info_s *)arg;

	if (pthread_mutex_init(&Info->lock, NULL) != 0)
	{
	  // printf("Mutex initialization failed.\n");
	  return NULL;
	}

	while (1) {
		if (Info->client->exit == 1) {
			break;
		}
		if (Info->client->is_connected == 1) {
			input_pump(Info);
		}
		usleep(5000);
	}
	int ret_val = 1;
	// printf("-- Read message thread terminated --\n");
	pthread_mutex_destroy(&Info->lock);
	pthread_exit(&ret_val);
	return NULL;
}

void *make_cmd(void *arg) {
	struct make_cmd_info_s *Info = (struct make_cmd_info_s *)arg;

	if (pthread_mutex_init(&Info->lock, NULL) != 0)
	{
	  // printf("Mutex initialization failed.\n");
	  return NULL;
	}
	while(1) {
		sem_wait(sem_msg_q);
		if (Info->client->exit == 1) {
			break;
		}
		if (*Info->msg_q_front != NULL) {
			char *fst_msg = strdup(take_fst_msg_in_q(Info->msg_q_front));
			move_msg_q(Info->msg_q_front, Info->lock);
			command cmd = msg_to_cmd(fst_msg);
			to_cmd_q(cmd, Info->cmd_q_front, Info->lock);
			sem_post(sem_cmd_q);
			free(fst_msg);
		}
		usleep(5000);
	}
	int ret_val = 1;
	// printf("-- Make command thread terminated --\n");
	pthread_mutex_destroy(&Info->lock);
	pthread_exit(&ret_val);
	return NULL;
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

