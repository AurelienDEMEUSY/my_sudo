/*
** EPITECH PROJECT, 2024
** B-PSU-100-LYN-1-1-mysudo-charly.rousselet
** File description:
** get_id.c
*/

#include "sudo.h"

/**
 * @brief
 * Searches for the ID of a group or user in a given file.
 * @param file_path The path to the file to search in
 * (e.g., /etc/group or /etc/passwd).
 * @param name_to_find The name of the group or user to search for.
 * @return char* A dynamically allocated string containing
 * the ID if found, or NULL if not found.
 * @note The returned string must be freed by the caller to avoid memory leaks.
 */
char *find_id_in_file(const char *file_path, const char *name_to_find)
{
    FILE *file = fopen(file_path, "r");
    char line[1024];
    char *name;
    char *id_str;

    if (!file)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        name = strtok(line, ":");
        strtok(NULL, ":");
        id_str = strtok(NULL, ":");
        if (name && id_str && strcmp(name, name_to_find) == 0) {
            fclose(file);
            return strdup(id_str);
        }
    }
    fclose(file);
    return NULL;
}

/**
 * @brief
 * Get the GID of a group by its name from /etc/group.
 * @param group_name The name of the group
 * @return gid_t The GID of the group, or -1 on failure
 */
uid_t get_id_from_name(const char *name_to_find, search_type_t type)
{
    const char *file_path = (type == SEARCH_GROUP) ?
    GROUP : PASSWD;
    char *id_str = find_id_in_file(file_path, name_to_find);
    uid_t id;

    if (!id_str)
        return (uid_t)-1;
    id = (uid_t)strtoul(id_str, NULL, 10);
    free(id_str);
    return id;
}
