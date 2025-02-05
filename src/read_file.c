/*
** EPITECH PROJECT, 2024
** B-PSU-100-LYN-1-1-mysudo-charly.rousselet
** File description:
** first_file.c
*/

#include "sudo.h"

/**
 * @brief
 * find the hashed user password in the shadow file
 * @param username the username of the personne
 * @return char* the hashed value of the real password of the user
 */
char *get_user_hash(const char *username)
{
    FILE *file = fopen("/etc/shadow", "r");
    char *line = NULL;
    size_t len = 0;
    char *stored_hash = NULL;
    char *user;

    if (!file)
        return NULL;
    while (getline(&line, &len, file) != -1) {
        user = strtok(line, ":");
        if (strcmp(user, username) == 0) {
            stored_hash = strdup(strtok(NULL, ":"));
            break;
        }
    }
    free(line);
    fclose(file);
    if (!stored_hash)
        return NULL;
    return stored_hash;
}

/**
 * @brief
 * check the authentification password using the hashed
 * user password and crypt.h
 * @param username the username of the personne
 * @return int SUCCESS or FAILUR
 */
int authenticate(const char *username)
{
    char *password = getpass("[my_sudo] password for user: ");
    char *stored_hash = get_user_hash(username);
    char *hash = crypt(password, stored_hash);
    int result = 84;

    if (!stored_hash)
        return 84;
    if (hash && strcmp(hash, stored_hash) == 0)
        result = 0;
    free(stored_hash);
    return result;
}

/**
 * @brief
 * verify if there is a bad flag in the argv line
 * @param argv the input line
 * @return int succes or failur
 */
int flag_verificator(char **argv)
{
    if (argv[1][0] == '-' && (strcmp(argv[1], "-E") != 0 &&
    strcmp(argv[1], "-u") != 0 && strcmp(argv[1], "-g") != 0
    && strcmp(argv[1], "-s") != 0))
        return FAILURE;
    if (argv[1][0] == '-' && (strcmp(argv[1], "-u") == 0 ||
    strcmp(argv[1], "-g") == 0) && !argv[2])
        return FAILURE;
    return SUCCESS;
}

/**
 * @brief
 * Validate the command-line arguments and username.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @param username The username extracted from the environment.
 * @return int SUCCESS or FAILURE.
 */
int validate_arguments(int argc, char **argv, const char *username)
{
    if (argc < 2)
        return FAILURE;
    if (!username)
        return FAILURE;
    if (flag_h(argv))
        exit(0);
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '\0') {
            perror("invalid arguments");
            return FAILURE;
        }
    }
    if (argc > 2 && flag_verificator(argv) == SUCCESS && !argv[2])
        return FAILURE;
    if (argc > 1 && flag_verificator(argv) != SUCCESS)
        return FAILURE;
    return SUCCESS;
}
