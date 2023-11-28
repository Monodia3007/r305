//
// Created by Lilith Camplin on 28/11/2023.
//

#ifndef SHELL_H
#define SHELL_H

// Affiche un prompt à l'utilisateur
void affiche_prompt();

// Execute les commandes données par le tableau commandes dont la taille est nb.
// Si arriere_plan vaut 1, les commandes doivent être lancées en arrière plan
void execute_ligne_commande(char*** commandes, int nb, int arriere_plan);

// Lance le shell
void run_shell();

#endif //SHELL_H
