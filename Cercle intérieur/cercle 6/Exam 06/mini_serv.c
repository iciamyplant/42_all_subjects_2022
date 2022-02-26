#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 65535

typedef struct s_message {
	char* content;
	int sender;
	size_t length;
	size_t offset;
	struct s_message* next;
} message;

typedef struct s_client {
	int id;
	int fd;
	char* buffer;
	message* queue;
	struct s_client* next;
} client;

typedef struct s_state {
	int total;
	int sockfd;
	client* clients;
} state;

// Split buf by line and returns the first line or until it's end.
int extract_message(const char* buffer, char** stk) {
	int i = 0;
	char* cpy = NULL;

	while (buffer[i]) {
		if (buffer[i] == '\n') {
			if (!(cpy = calloc(i + 2, sizeof(char))))
				return -1;
			memcpy(cpy, buffer, i + 1);
			cpy[i + 1] = 0;
			*stk = cpy;
			return 1;
		}
		i++;
	}
	return 0;
}

// Join to non-null strings in a newly allocated string.
char* str_join(char* str1, char* str2) {
	char* merged = NULL;
	size_t len1 = 0;
	if (str1)
		len1 = strlen(str1);
	size_t len2 = strlen(str2);

	if (!(merged = calloc(len1 + len2 + 1, sizeof(char))))
		return NULL;
	if (str1)
		memcpy(merged, str1, len1);
	memcpy(merged + len1, str2, len2);
	merged[len1 + len2] = 0;
	if (str1)
		free(str1);

	return merged;
}

int broadcast(state* server, int sender, char* content, size_t length) {
	printf("%s", content);
	client* curr = server->clients;
	while (curr) {
		if (curr->id != sender) {
			message* msg = NULL;
			if (!(msg = (message*)malloc(sizeof(message))))
				return 1;
			if (!(msg->content = (char*)malloc(length + 1))) {
				free(msg);
				return 1;
			}
			strcpy(msg->content, content);
			msg->content[length] = 0;
			msg->length = length;
			msg->next = NULL;
			msg->offset = 0;
			msg->sender = sender;
			if (!curr->queue)
				curr->queue = msg;
			else {
				message* curr_msg = curr->queue;
				while (curr_msg->next)
					curr_msg = curr_msg->next;
				curr_msg->next = msg;
			}
		}
		curr = curr->next;
	}
	return 0;
}

client* clean_client(client* clt) {
	client* next_client = clt->next;
	message* curr_msg = clt->queue;
	while (curr_msg) {
		message* next_msg = curr_msg->next;
		free(curr_msg->content);
		curr_msg->content = NULL;
		curr_msg->next = NULL;
		free(curr_msg);
		curr_msg = next_msg;
	}
	clt->queue = NULL;
	if (clt->buffer)
		free(clt->buffer);
	clt->buffer = NULL;
	clt->next = NULL;
	close(clt->fd);
	clt->fd = 0;
	free(clt);
	return next_client;
}

int clean_exit(state* server, int return_code) {
	if (server) {
		client* clt = server->clients;
		while (clt)
			clt = clean_client(clt);
		server->clients = NULL;
		if (server->sockfd > 0)
			close(server->sockfd);
	}
	return return_code;
}

int exit_fatal(state* server) {
	write(STDERR_FILENO, "Fatal error\n", 12);
	return clean_exit(server, 1);
}

int main(int argc, char** argv) {
	if (argc != 2) {
		write(STDERR_FILENO, "Wrong number of arguments !\n", 28);
		return 1;
	}

	// Initialize Socket

	state server;
	server.clients = NULL;
	server.total = 0;
	server.sockfd = 0;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		return exit_fatal(&server);
	server.sockfd = sockfd;
	fcntl(server.sockfd, F_SETFL, O_NONBLOCK);

	int port = atoi(argv[1]);
	struct sockaddr_in self;
	socklen_t len = sizeof(self);
	bzero(&self, len);
	self.sin_family = AF_INET;
	self.sin_addr.s_addr = inet_addr("127.0.0.1");
	self.sin_port = htons(port);

	if (bind(server.sockfd, (struct sockaddr*)&self, len) != 0)
		return exit_fatal(&server);

	if (listen(server.sockfd, 10) != 0)
		return exit_fatal(&server);

	printf("Server open on port %d\n", port);

	// Initialize server

	char buffer[BUFFER_SIZE];
	char recv_buffer[BUFFER_SIZE];
	fd_set reads;
	fd_set writes;

	// Main Loop

	while (1) {
		FD_ZERO(&reads);
		FD_ZERO(&writes);
		FD_SET(server.sockfd, &reads);

		// Add current clients to read and write
		int max = server.sockfd;
		client* clt = server.clients;
		while (clt) {
			FD_SET(clt->fd, &reads);
			if (clt->queue)
				FD_SET(clt->fd, &writes);
			if (clt->fd > max)
				max = clt->fd;
			clt = clt->next;
		}

		// Loop trough existing clients
		int activity = select(max + 1, &reads, &writes, NULL, NULL);
		if (activity < 0)
			return exit_fatal(&server);
		else if (activity > 0) {
			// New client on read for the server socket
			if (FD_ISSET(sockfd, &reads)) {
				int new_client = accept(sockfd, NULL, NULL);
				if (new_client) {
					fcntl(new_client, F_SETFL, O_NONBLOCK);
					client* clt = NULL;
					if (!(clt = (client*)malloc(sizeof(client)))) {
						close(new_client);
						return exit_fatal(&server);
					}
					clt->id = server.total++;
					clt->fd = new_client;
					clt->buffer = NULL;
					clt->queue = NULL;
					clt->next = NULL;
					if (!server.clients)
						server.clients = clt;
					else {
						size_t length = sprintf(buffer, "server: client %d just arrived\n", clt->id);
						if (broadcast(&server, clt->id, buffer, length))
							return exit_fatal(&server);
						client* curr = server.clients;
						while (curr->next)
							curr = curr->next;
						curr->next = clt;
					}
				}
			}

			// Handle read and write
			client* previous = NULL;
			client* clt = server.clients;
			client* next = NULL;
			while (clt) {
				next = clt->next;
				if (FD_ISSET(clt->fd, &reads)) {
					ssize_t received = recv(clt->fd, recv_buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
					if (received == 0) {
						size_t length = sprintf(buffer, "server: client %d just left\n", clt->id);
						if (broadcast(&server, clt->id, buffer, length))
							return exit_fatal(&server);
						client* new_next = clean_client(clt);
						if (!previous)
							server.clients = new_next;
						else
							previous->next = new_next;
					}
					else {
						recv_buffer[received] = 0;
						ssize_t offset = 0;
						char* line = NULL;
						while (offset < received) {
							int extracted = extract_message(recv_buffer + offset, &line);
							if (extracted < 0)
								return exit_fatal(&server);
							else if (extracted == 0) {
								clt->buffer = str_join(clt->buffer, recv_buffer);
								offset = received;
							}
							else {
								size_t line_length = strlen(line);
								offset += line_length;
								char* to_send = str_join(clt->buffer, line);
								free(line);
								size_t length = sprintf(buffer, "client %d: ", clt->id);
								if (broadcast(&server, clt->id, buffer, length))
									return exit_fatal(&server);
								if (broadcast(&server, clt->id, to_send, strlen(to_send))) {
									free(to_send);
									return exit_fatal(&server);
								}
								free(to_send);
							}
						}
						previous = clt;
					}
				}
				if (FD_ISSET(clt->fd, &writes) && clt->queue) {
					message* msg = clt->queue;
					ssize_t sent = send(clt->fd, msg->content + msg->offset, msg->length - msg->offset, MSG_DONTWAIT);
					if (sent > 0) {
						if (msg->offset + sent < msg->length)
							msg->offset += sent;
						else {
							message* next_msg = msg->next;
							free(msg->content);
							free(msg);
							clt->queue = next_msg;
						}
					}
					previous = clt;
				}
				clt = next;
			}
		}
	}

	return clean_exit(&server, 0);
}
