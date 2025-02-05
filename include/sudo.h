/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday09-aurelien.demeusy
** File description:
** include
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <crypt.h>
#include <sys/types.h>
#include "sudo_struct.h"
#ifndef MY__SUDO_H
    #define MY__SUDO_H
    /**
     * @brief used for returning 0
     */
    #define SUCCESS 0
    /**
     * @brief used for returning 84
     */
    #define FAILURE 84
    /**
     * @brief used to read the /etc/group file
     */
    #define GROUP "/etc/group"
    /**
     * @brief used to read the /etc/passwd file
     */
    #define PASSWD "/etc/passwd"
/**
 * @brief
 * find the hashed user password in the shadow file
 * @param username the username of the personne
 * @return char* the hashed value of the real password of the user
 */
char *get_user_hash(const char *username);
/**
 * @brief
 * check the authentification password using the hashed
 * user password and crypt.h
 * @param username the username of the personne
 * @return int SUCCESS or FAILUR
 */
int authenticate(const char *username);
/**
 * @brief
 * Get the GID of a group by its name from /etc/group.
 * @param group_name The name of the group
 * @return gid_t The GID of the group, or -1 on failure
 */
uid_t get_id_from_name(const char *name_to_find, search_type_t type);
/**
 * @brief
 * Switch to root privileges by changing GID and UID to 0.
 * @return int SUCCESS or FAILURE
 */
int switch_to_root(void);
/**
 * @brief
 * Switch to a specific group by name or GID.
 * @param name_or_id The group or user name or GID as a string
 * @param type define if you want the group or user
 * @return int SUCCESS or FAILURE
 */
int switch_to_id(const char *name_or_id, search_type_t type);
/**
 * @brief
 * swith to the right user or group
 * @param command Array of command arguments
 * @param i the indentation of the array
 * @param type define if you want the group or user
 * @return int SUCCESS or FAILURE
 */
int flag_u_and_g(char **command, int *i, search_type_t type);
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
char *find_id_in_file(const char *file_path, const char *name_to_find);
/**
 * @brief
 * preserve the env
 * @param command the stdin line starting at the second element
 * @return int succes or failur
 */
int flag_e_maj(char **command);
/**
 * @brief
 * the documentation of how to use the my_sudo commande
 * @param argv
 * @return int
 */
int flag_h(char **argv);
/**
 * @brief
 * verify if there is a bad flag in the argv line
 * @param argv the input line
 * @return int succes or failur
 */
int flag_verificator(char **argv);
/**
 * @brief
 * Validate the command-line arguments and username.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @param username The username extracted from the environment.
 * @return int SUCCESS or FAILURE.
 */
int validate_arguments(int argc, char **argv, const char *username);
/**
 * @brief
 * free everything from new_env
 * @param new_env
 * @param i
 */
void handle_env_copy_error(char **new_env, int i);
/**
 * @brief
 * return the malloked new env to the right size
 * @param env_size the size of the env
 * @return char** the malloked env
 */
char **save_env(int *env_size);
/**
 * @brief
 * preserve the env
 * @param command the stdin line starting at the second element
 * @return int succes or failur
 */
int flag_e_maj(char **command);
#endif
