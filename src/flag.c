/*
** EPITECH PROJECT, 2024
** B-PSU-100-LYN-1-1-mysudo-charly.rousselet
** File description:
** flag.c
*/

#include "sudo.h"

/**
 * @brief
 * swith to the right user or group
 * @param command Array of command arguments
 * @param i the indentation of the array
 * @param type define if you want the group or user
 * @return int SUCCESS or FAILURE
 */
int flag_u_and_g(char **command, int *i, search_type_t type)
{
    const char *id_type = (type == SEARCH_GROUP) ? "GID" : "UID";

    if (!command[*i + 1]) {
        fprintf(stderr, "Missing %s after -%c\n", id_type,
        (type == SEARCH_GROUP) ? 'g' : 'u');
        return FAILURE;
    }
    if (switch_to_id(command[*i + 1], type) != SUCCESS)
        return FAILURE;
    for (int j = *i; command[j] != NULL; j++)
        command[j] = command[j + 2];
    (*i)--;
    return SUCCESS;
}
