/*
** EPITECH PROJECT, 2024
** B-PSU-100-LYN-1-1-mysudo-charly.rousselet
** File description:
** main.c
*/

#include "sudo.h"

/**
 * @brief
 * Launch an interactive shell.
 * @return int SUCCESS or FAILURE
 */
int launch_shell(void)
{
    char *shell = "/bin/bash";
    char *args[] = { shell, NULL };

    if (geteuid() != 0) {
        fprintf(stderr, "Ce programme doit être exécuté en tant que root.\n");
        return FAILURE;
    }
    execve(shell, args, NULL);
    perror("Error while launching the shell");
    return FAILURE;
}

/**
 * @brief
 * Chooses and executes the flag function.
 * @param flag a letter like s, g, u, or E
 * @param command the stdin line starting at the second element
 * @param index index of the array
 * @return int SUCCESS or FAILURE
 */
int handle_specific_flag(char flag, char **command, int *index)
{
    switch (flag) {
        case 's':
            return launch_shell();
        case 'g':
            return flag_u_and_g(command, index, SEARCH_GROUP);
        case 'u':
            return flag_u_and_g(command, index, SEARCH_USER);
        case 'E':
            return flag_e_maj(command);
        default:
            return FAILURE;
    }
}

/**
 * @brief
 * Processes flags in the command line arguments.
 * @param command the stdin line starting at the second element
 * @param index index of the array
 * @return int SUCCESS if all flags are processed correctly, FAILURE otherwise
 */
int process_flag(char **command, int *index)
{
    char *flags = command[*index] + 1;
    int result = SUCCESS;

    for (int i = 0; flags[i] != '\0'; i++) {
        if (handle_specific_flag(flags[i], command, index) != SUCCESS) {
            result = FAILURE;
        }
    }
    return result;
}

/**
 * @brief
 * Check if the argument is a flag and process it.
 * @param command Array of command arguments
 * @param i Current index in the command array
 * @param flag_detected Pointer to flag detection variable
 * @param result Pointer to the execution result
 * @return int 1 if flag processing failed, 0 otherwise
 */
static int tiret_check(char **command, int i, int *flag_detected)
{
    if (command[i][0] == '-') {
        *flag_detected = 1;
        if (process_flag(command, &i) != SUCCESS) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief
 * Execute a command or handle multiple flags like -s, -g, -E, -u.
 * @param command Array of command arguments
 * @return int SUCCESS or FAILURE
 */
int execute_command(char **command)
{
    int flag_detected = 0;
    int result = SUCCESS;

    if (!command || !command[0])
        return FAILURE;
    for (int i = 0; command[i] != NULL; i++) {
        if (tiret_check(command, i, &flag_detected)) {
            result = FAILURE;
        }
    }
    if (!flag_detected || command[0]) {
        execvp(command[0], command);
        perror("Command execution failed");
        return FAILURE;
    }
    return result;
}

/**
 * @brief
 * Handles user authentication with a maximum of 3 attempts.
 * @param username The username to authenticate
 * @return int SUCCESS or FAILURE
 */
static int authenticate_user(const char *username)
{
    int attempts = 0;

    while (authenticate(username) != SUCCESS) {
        attempts++;
        if (attempts == 3) {
            fprintf(stderr, "Authentication failed after 3 attempts\n");
            return FAILURE;
        }
    }
    printf("Number of failed attempts before success: %d\n", attempts);
    return SUCCESS;
}

/**
 * @brief
 * Main function: manages authentication, privilege escalation,
 * and command execution.
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @return int SUCCESS or FAILURE
 */
int main(int argc, char **argv)
{
    const char *username = getenv("USER");
    int validation_result = validate_arguments(argc, argv, username);

    if (validation_result != SUCCESS)
        return validation_result;
    if (geteuid() != 0) {
        if (authenticate_user(username) != SUCCESS) {
            return FAILURE;
        }
    }
    if (switch_to_root() != SUCCESS)
        return FAILURE;
    return execute_command(&argv[1]);
}
