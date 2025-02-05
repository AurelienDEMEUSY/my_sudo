/*
** EPITECH PROJECT, 2024
** B-PSU-100-LYN-1-1-mysudo-charly.rousselet
** File description:
** test.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "sudo.h"



Test(switch_to_root_test, switch_to_root_success) {
    cr_assert_eq(switch_to_root(), SUCCESS, "Le passage au mode root a échoué.");
}

Test(switch_to_id_test, switch_to_valid_user) {
    int test = switch_to_id("root", SEARCH_USER);
    cr_assert_eq(test, 0, "La fonction switch_to_id a échoué pour l'utilisateur 'root'");
}


Test(switch_to_id_test, switch_to_invalid_user) {
    cr_assert_eq(switch_to_id("nonexistentuser", SEARCH_USER), FAILURE, "Le passage à un utilisateur inexistant aurait dû échouer.");
}

Test(switch_to_id_test, switch_to_valid_group) {
    cr_assert_eq(switch_to_id("root", SEARCH_USER), SUCCESS, "Le passage au groupe root a échoué.");
}

Test(switch_to_id_test, switch_to_invalid_group) {
    cr_assert_eq(switch_to_id("nonexistentgroup", SEARCH_GROUP), FAILURE, "Le passage à un groupe inexistant aurait dû échouer.");
}

Test(find_id_in_file_test, valid_user_id) {
    char *uid = find_id_in_file("/etc/passwd", "root");
    cr_assert_not_null(uid, "L'ID de l'utilisateur n'a pas été trouvé.");
    free(uid);
}

Test(find_id_in_file_test, invalid_user_id) {
    char *uid = find_id_in_file("/etc/passwd", "nonexistentuser");
    cr_assert_null(uid, "L'ID de l'utilisateur inexistant n'aurait pas dû être trouvé.");
}

Test(find_id_in_file_test, valid_group_id) {
    char *gid = find_id_in_file("/etc/group", "root");
    cr_assert_not_null(gid, "L'ID du groupe n'a pas été trouvé.");
    free(gid);
}

Test(find_id_in_file_test, invalide_file_name) {
    char *gid = find_id_in_file(NULL, "root");
    cr_assert_null(gid, "L'ID du groupe n'aurait pas dû être trouvé avec un fichier NULL.");
    if (gid)
        free(gid);
}


Test(find_id_in_file_test, invalid_group_id) {
    char *gid = find_id_in_file("/etc/group", "nonexistentgroup");
    cr_assert_null(gid, "L'ID du groupe inexistant n'aurait pas dû être trouvé.");
}

Test(get_id_from_name_test, valid_user_id) {
    uid_t result = get_id_from_name("nobody", SEARCH_USER);
    cr_assert_neq(result, (uid_t)-1, "L'ID de l'utilisateur valide n'a pas été trouvé.");
}

Test(get_id_from_name_test, invalid_user_id) {
    uid_t result = get_id_from_name("nonexistentuser", SEARCH_USER);
    cr_assert_eq(result, (uid_t)-1, "L'ID de l'utilisateur inexistant aurait dû échouer.");
}

Test(get_id_from_name_test, valid_group_id) {
    uid_t result = get_id_from_name("adm", SEARCH_GROUP);
    cr_assert_neq(result, (uid_t)-1, "L'ID du groupe valide n'a pas été trouvé.");
}

Test(get_id_from_name_test, invalid_group_id) {
    uid_t result = get_id_from_name("nonexistentgroup", SEARCH_GROUP);
    cr_assert_eq(result, (uid_t)-1, "L'ID du groupe inexistant aurait dû échouer.");
}


Test(get_id_from_name_test, valid_group_with_search_type) {
    uid_t result = get_id_from_name("swtpm", SEARCH_GROUP);
    cr_assert_neq(result, (uid_t)-1, "L'ID du groupe avec SEARCH_GROUP n'a pas été trouvé.");
}

Test(get_id_from_name_test, invalid_user_with_search_type) {
    uid_t result = get_id_from_name("nonexistentuser", SEARCH_USER);
    cr_assert_eq(result, (uid_t)-1, "L'ID de l'utilisateur inexistant avec SEARCH_USER aurait dû échouer.");
}

Test(get_id_from_name_test, invalid_group_with_search_type) {
    uid_t result = get_id_from_name("nonexistentgroup", SEARCH_GROUP);
    cr_assert_eq(result, (uid_t)-1, "L'ID du groupe inexistant avec SEARCH_GROUP aurait dû échouer.");
}

Test(get_id_from_name_test, valid_user_id_for_search_user) {
    uid_t result = get_id_from_name("root", SEARCH_USER);
    cr_assert_neq(result, (uid_t)-1, "L'ID de l'utilisateur 'root' n'a pas été trouvé.");
}

Test(get_id_from_name_test, valid_group_id_for_search_group) {
    uid_t result = get_id_from_name("root", SEARCH_GROUP);
    cr_assert_neq(result, (uid_t)-1, "L'ID du groupe 'root' n'a pas été trouvé.");
}

Test(get_id_from_name_test, invalid_user_id_for_search_user) {
    uid_t result = get_id_from_name("nonexistentuser", SEARCH_USER);
    cr_assert_eq(result, (uid_t)-1, "L'ID de l'utilisateur inexistant n'a pas échoué.");
}

Test(get_id_from_name_test, invalid_group_id_for_search_group) {
    uid_t result = get_id_from_name("nonexistentgroup", SEARCH_GROUP);
    cr_assert_eq(result, (uid_t)-1, "L'ID du groupe inexistant n'a pas échoué.");
}

Test(h_test, valide) {
    char *argv[] = { "gfnj","-h"};
    int result = flag_h(argv);
    cr_assert_eq(result, 1, "L'option -h aurait dû être reconnue.");
}

Test(h_test, invalide) {
    char *argv[] = { "gfnj","dfvn"};
    int result = flag_h(argv);
    cr_assert_eq(result, 0, "L'option -h aurait dû être reconnue.");
}