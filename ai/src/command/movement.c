/*
** EPITECH PROJECT, 2022
** movement.c
** File description:
** movement ai
*/

#include "zappy_ai.h"

static void change_dir(client_t *client)
{
    if (client->player->dir == South) {
        client->player->pos.y += 1;
        if (client->player->pos.y >= client->size_map.y)
            client->player->pos.y = 0;
    }
    if (client->player->dir == North) {
        client->player->pos.y -= 1;
        if (client->player->pos.y < 0)
            client->player->pos.y = client->size_map.y - 1;
    }
    if (client->player->dir == East) {
        client->player->pos.x += 1;
        if (client->player->pos.x >= client->size_map.x)
            client->player->pos.x = 0;
    }
    if (client->player->dir == West) {
        client->player->pos.x -= 1;
        if (client->player->pos.x < client->size_map.x)
            client->player->pos.x = client->size_map.x - 1;
    }
}

static void find_right_dir(client_t *client, bool right)
{
    if (client->player->dir == North)
        client->player->dir = (right ? East : West);
    if (client->player->dir == South)
        client->player->dir = (right ? West : East);
    if (client->player->dir == East)
        client->player->dir = (right ? South : North);
    if (client->player->dir == West)
        client->player->dir = (right ? North : South);
}

int forward_movement(client_t *client, char *str)
{
    if (strcmp(str, "ok") == 0) {
        change_dir(client);
        printf("y %d x %d\n", client->player->pos.y, client->player->pos.x);
        printf("%s[COMMAND]%s Forward\n", B, W);
        printf("y %d x %d\n", client->player->pos.y, client->player->pos.x);
        return 0;
    }
    return 1;
}

int right_movement(client_t *client, char *str)
{
    if (strcmp(str, "ok") == 0) {
        printf("y %d x %d\n", client->player->pos.y, client->player->pos.x);
        find_right_dir(client, true);
        printf("y %d x %d\n", client->player->pos.y, client->player->pos.x);
        printf("%s[COMMAND]%s Right\n", B, W);
        return 0;
    }
    return 1;
}

int left_movement(client_t *client, char *str)
{
    if (strcmp(str, "ok") == 0) {
        printf("y %d x %d\n", client->player->pos.y, client->player->pos.x);
        find_right_dir(client, false);
        printf("y %d x %d\n", client->player->pos.y, client->player->pos.x);
        printf("%s[COMMAND]%s Left\n", B, W);
        return 0;
    }
    return 1;
}
