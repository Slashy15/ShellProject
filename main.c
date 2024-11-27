#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

// Fonction pour écrire des messages dans la sortie standard
void write_message(const char *message) {
    write(STDOUT_FILENO, message, strlen(message));
}

int main() {
    // Message d'accueil
    write_message("Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");

    char input[BUFFER_SIZE];

    while (1) {
        // Afficher le prompt
        write_message("enseash % ");

        // Lire l'entrée utilisateur
        ssize_t bytes_read = read(STDIN_FILENO, input, BUFFER_SIZE - 1);
        if (bytes_read <= 0) {
            write_message("Erreur de lecture.\n");
            continue;
        }

        // Ajouter un terminateur de fin de chaîne
        input[bytes_read] = '\0';

        // Retirer le caractère '\n' de l'entrée
        input[strcspn(input, "\n")] = '\0';

        // Vérifier si l'utilisateur veut quitter
        if (strcmp(input, "exit") == 0) {
            write_message("Bye bye!\n");
            break;
        }

        // Afficher un message temporaire pour les commandes non reconnues
        write_message("Commande inconnue : ");
        write_message(input);
        write_message("\n");
    }

    return 0;
}
