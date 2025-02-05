# 💻 MY_SUDO 🐚

## Description 📝

MySudo est une implémentation personnalisée de la commande sudo, permettant d'exécuter des commandes avec des privilèges élevés. Ce projet a été réalisé dans le cadre de l'EPITECH en 2024.

## Features list 📋

- Authentification utilisateur via /etc/shadow

- Vérification des arguments et des flags

- Gestion des privilèges utilisateur et groupe

- Exécution de commandes avec préservation de l'environnement

## Compilation 🛠️

Pour compiler le projet, utilisez la commande :

```sh
make
```

Cela générera l'exécutable my_sudo.

Utilisation

Exécutez my_sudo suivi d'une commande :

./my_sudo [options] [commande]

you must use

```sh
sudo chown root my_sudo
```
and

```sh
sudo chmod u+s my_sudo
```
or

```sh
sudo ./my_sudo
```

## Options disponibles :

- -h : Affiche l'aide

- -E : Conserve l'environnement de l'utilisateur courant

- -u <utilisateur> : Exécute la commande en tant qu'un autre utilisateur

- -g <groupe> : Exécute la commande avec un groupe différent

- -s : Ouvre un shell en tant qu'administrateur

## Exemples :

Exécuter une commande avec privilèges root :

```sh
./my_sudo ls /root
```

Changer d'utilisateur :

```sh
./my_sudo -u bob whoami
```

Lancer un shell root :

```sh
./my_sudo -s
```

Explication des fichiers principaux

main.c : Point d'entrée du programme, gère l'authentification et l'exécution des commandes

authentication.c : Gestion des mots de passe et vérification de l'authentification

flags.c : Gestion des options passées en ligne de commande

switch_user.c : Gestion des changements d'utilisateur et de groupe

get_id.c : Récupération des IDs utilisateur et groupe

Sécurité

Ce projet manipule des informations sensibles telles que les mots de passe hashés. Il est donc essentiel de l'exécuter avec précaution et de s'assurer que seul root a les permissions nécessaires.

Auteurs

Charly Rousselet - EPITECH 2024
Aurelien Demeusy - EPITECH 2024
