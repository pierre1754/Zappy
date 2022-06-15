/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** include
*/

#ifndef ZAPPY_AI_H
    #define ZAPPY_AI_H

    #ifndef _GNU_SOURCE
        #define _GNU_SOURCE
    #endif

    #define SUCCESS (0)
    #define ERROR (1)
    #define EXIT (2)

    #define ERROR_EXIT (84)

    #define UNUSED __attribute__((unused))

    #include <sys/types.h>
    #include <linux/limits.h>
    #include <sys/stat.h>

    #include <errno.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <unistd.h>
    #include <stdbool.h>
    #include <regex.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <uuid/uuid.h>

    #include "list.h"
    #include "nlib.h"

typedef struct arg_s {
    int port;
    char *machine;
} arg_t;

typedef struct pos_s {
    int x;
    int y;
} pos_t;

typedef struct client_s {
    socket_t *socket;
    char *machine;
    bool init;
    bool client_connected;
    char *uuid;
    pos_t size_map;
    fd_set readfds;
    fd_set writefds;
    list_t *command;
    list_t *pending_commands;
} client_t;

int bct(client_t *client, char *str);

typedef struct com_s {
    const char *cmd;
    int (*func_ptr)(client_t *client, char *str);
} com_t;

static const com_t com[] =
{
    {"bct\0", &bct},
    {NULL, NULL}
};

#define R "\033[1;31m"
#define G "\033[1;32m"
#define Y "\033[1;33m"
#define B "\033[1;34m"
#define M "\033[1;35m"
#define C "\033[1;36m"
#define W "\033[1;0m"

bool send_message(list_t *pending, list_t *list, socket_t *socket, char *mess);

int read_stdin(client_t *client);

bool parse_return(client_t *client, char *str);

bool init_client(arg_t *arg);
client_t *create_client(arg_t *arg);
void free_client(client_t *client);

char *create_uuid();

#endif // ZAPPY_AI_H
