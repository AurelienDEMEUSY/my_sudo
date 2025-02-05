/*
** EPITECH PROJECT, 2024
** B-PSU-100-LYN-1-1-mysudo-charly.rousselet
** File description:
** flag_e_maj.c
*/

#include "sudo.h"

extern char **environ;

/**
 * @brief
 * free everything from new_env
 * @param new_env
 * @param i
 */
void handle_env_copy_error(char **new_env, int i)
{
    perror("Failed to copy environment variable");
    for (int j = 0; j < i; j++) {
        free(new_env[j]);
    }
    free(new_env);
}

/**
 * @brief
 * return the malloked new env to the right size
 * @param env_size the size of the env
 * @return char** the malloked env
 */
char **save_env(int *env_size)
{
    int count = 0;
    char **new_env;

    while (environ[count])
        count++;
    new_env = malloc((count + 1) * sizeof(char *));
    if (!new_env) {
        perror("Failed to allocate memory for environment");
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        new_env[i] = strdup(environ[i]);
        if (!new_env[i]) {
            handle_env_copy_error(new_env, i);
            return NULL;
        }
    }
    new_env[count] = NULL;
    *env_size = count;
    return new_env;
}

/**
 * @brief
 * preserve the env
 * @param command the stdin line starting at the second element
 * @return int succes or failur
 */
int flag_e_maj(char **command)
{
    int env_size;
    char **new_env = NULL;

    new_env = save_env(&env_size);
    if (new_env == NULL) {
        perror("Error saving environment");
        return 1;
    }
    if (execve(command[0], command, new_env) == -1) {
        perror("Failed to execute command");
        for (int i = 0; i < env_size; i++) {
            free(new_env[i]);
        }
        free(new_env);
        return FAILURE;
    }
    for (int i = 0; i < env_size; i++)
        free(new_env[i]);
    free(new_env);
    return SUCCESS;
}
