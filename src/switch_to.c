/*
** EPITECH PROJECT, 2024
** B-PSU-100-LYN-1-1-mysudo-charly.rousselet
** File description:
** switch_to.c
*/

#include "sudo.h"

/**
 * @brief
 * Switch to root privileges by changing GID and UID to 0.
 * @return int SUCCESS or FAILURE
 */
int switch_to_root(void)
{
    if (setgid(0) != 0 || setuid(0) != 0) {
        perror("Failed to switch to root");
        return FAILURE;
    }
    return SUCCESS;
}

/**
 * @brief
 * Switch to a specific group by name or GID.
 * @param name_or_id The group or user name or GID as a string
 * @param type define if you want the group or user
 * @return int SUCCESS or FAILURE
 */
int switch_to_id(const char *name_or_id, search_type_t type)
{
    char *endptr;
    uid_t target_id;

    target_id = (uid_t)strtoul(name_or_id, &endptr, 10);
    if (*endptr != '\0') {
        target_id = get_id_from_name(name_or_id, type);
        if (target_id == (uid_t)-1) {
            fprintf(stderr, "Error: Invalid %s name '%s'.\n",
                    (type == SEARCH_GROUP) ? "group" : "user", name_or_id);
            return FAILURE;
        }
    }
    if ((type == SEARCH_GROUP && setegid(target_id) != 0) ||
        (type == SEARCH_USER && seteuid(target_id) != 0)) {
        perror("Failed to change effective ID");
        return FAILURE;
    }
    return SUCCESS;
}
