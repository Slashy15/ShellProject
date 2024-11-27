#include "shell.h"
#include "utils.h"

int main() {
    // Message d'accueil
    write_message("Bienvenue dans le Shell ENSEI.\nPour quitter, tapez 'exit'.\n");

    // Boucle principale
    shell_loop();

    write_message("Bye bye!\n");
    return 0;
}
