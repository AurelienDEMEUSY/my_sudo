/*
** EPITECH PROJECT, 2024
** B-PSU-100-LYN-1-1-mysudo-charly.rousselet
** File description:
** flag_h.c
*/

#include <unistd.h>
#include <string.h>

/**
 * @brief
 * the documentation of how to use the my_sudo commande
 * @param argv
 * @return int
 */
int flag_h(char **argv)
{
    if (strcmp(argv[1], "-h") == 0) {
        write(1, "usage: ./my_sudo -h\n", 21);
        write(1, "usage: ./my_sudo [-ugEs] [command [args ...]]", 45);
        return 1;
    }
    return 0;
}
