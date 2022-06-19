/*
** EPITECH PROJECT, 2022
** look_around.c
** File description:
** look_around ai
*/

#include "zappy_ai.h"

int round_map(client_t *client, int pos, bool is_x)
{
    if (is_x) {
        if (pos >= client->size_map.x)
            return pos - client->size_map.x;
        if (pos < 0)
            return pos + client->size_map.x;
        return pos;
    } else {
        if (pos >= client->size_map.y)
            return pos - client->size_map.y;
        if (pos < 0)
            return pos + client->size_map.y;
    }
    return pos;
}

size_t change_pos(client_t *client, size_t v, size_t change_v, bool is_x)
{
    int ret = v + change_v;

    if (is_x) {
        if (ret < 0)
            return (client->size_map.x - 1);
        if (ret >= client->size_map.x)
            return (ret - client->size_map.x);
        return ret;
    }
    if (ret < 0)
        return (client->size_map.y - 1);
    if (ret >= client->size_map.y)
        return (ret - client->size_map.y);
    return ret;
}

void free_map(client_t *client)
{
    size_t max_x = client->size_map.x;
    size_t max_y = client->size_map.y;

    for (size_t y = 0; y < max_y; y++) {
        for (size_t x = 0; x < max_x; x++)
            free(client->map[y][x].inv);
        free(client->map[y]);
    }
    free(client->map);
}

static bool split_create_map(map_t *map, size_t x)
{
    size_t i = 0;

    for (i = 0; i != x; i++) {
        map[i].inv = calloc(1, sizeof(inventory_t));
        memset(map[i].inv, -1, sizeof(inventory_t));
        map[i].player = NULL;
        if (!map[i].inv)
            return false;
    }
    map[i].player = NULL;
    map[i].inv = NULL;
    return true;
}

bool create_map(client_t *client)
{
    int h = 0;
    client->map = malloc(sizeof(map_t *) * (client->size_map.y + 1));

    if (!client->map)
        return false;
    for (h = 0; h != client->size_map.y; h++) {
        client->map[h] = malloc(sizeof(map_t) * (client->size_map.x + 1));
        if (!client->map[h])
            return false;
        if (!split_create_map(client->map[h], client->size_map.x))
            return false;
    }
    client->map[h] = NULL;
    return true;
}
