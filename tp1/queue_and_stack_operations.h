//
// Created by Lilith Camplin on 17/10/2023.
//

#ifndef R305_QUEUE_AND_STACK_OPERATIONS_H
#define R305_QUEUE_AND_STACK_OPERATIONS_H

typedef int element_t;
#define TAILLE_PILE 5

// Une pile de taille fixe
typedef struct
{
    // un tableau d'éléments
    element_t pile[TAILLE_PILE];
    // l'indice du dernier élément empilé
    int sommet;
} pile_fixe_t;

// Le nombre de nouvelles case qui seront ajoutées
// dès que la pile sera pleine
#define PAS_ALLOCATION 5

// Une pile de taille fixe
typedef struct
{
    // un pointeur vers un tableau d'éléments
    element_t *pile;
    // l'indice du dernier élément empilé
    int sommet;
    // la taille du tableau pile
    int taille;
} pile_variable_t;

#define TAILLE_FILE 5

typedef struct
{
    element_t file[TAILLE_FILE];
    int head;
    int tail;
} file_fixe_t;

typedef struct
{
    element_t *file;
    int head;
    int tail;
    int taille;
} file_variable_t;

/// Initialise une pile. La pile
/// doit être vide après initialisation
void pile_fixe_initialiser(pile_fixe_t *pile);

/// Retourne vrai si la pile est vide, 0 sinon
/// (on rappelle qu'en C, 0 est faux, tout le reste est vrai)
int pile_fixe_est_vide(const pile_fixe_t *pile);

/// Ajoute un élément dans la pile pointée par pile
///
/// Retourne 0 si l'élément a pu être ajouté, -1 sinon
/// (en cas de pile pleine par exemple)
int pile_fixe_empiler(pile_fixe_t *pile, element_t element);

/// Supprime un élément de la pile et le copie
/// à l'adresse pointée par p_element.
///
/// Retourne 0 en cas de succès, -1 sinon
/// (si la pile était vide par exemple)
int pile_fixe_depiler(pile_fixe_t *pile, element_t *p_element);

/// Affiche les éléments contenus dans la pile
void pile_fixe_afficher(const pile_fixe_t *pile);


/// Initialise une pile. La pile
/// doit être vide après initialisation.
///
/// Retourne 0 en cas de succès, -1 en cas d'erreur
/// (l'allocation dynamique a échoué par exemple)
int pile_variable_initialiser(pile_variable_t *pile);

/// Retourne vrai si la pile est vide, 0 sinon
/// (on rappelle qu'en C, 0 est faux, tout le reste est vrai)
int pile_variable_est_vide(const pile_variable_t *pile);

/// Ajoute un élément dans la pile pointée par pile
///
/// Retourne 0 si l'élément a pu être ajouté, -1 sinon
/// (en cas de pile pleine par exemple)
int pile_variable_empiler(pile_variable_t *pile, element_t element);

/// Supprime un élément de la pile et le copie
/// à l'adresse pointée par p_element.
///
/// Retourne 0 en cas de succès, -1 sinon
/// (si la pile était vide par exemple)
int pile_variable_depiler(pile_variable_t *pile, element_t *p_element);

/// Affiche les éléments contenus dans la pile
void pile_variable_afficher(const pile_variable_t *pile);

/// Detruit la pile
void pile_variable_detruire(pile_variable_t *pile);

void file_fixe_initialiser(file_fixe_t *file);

int file_fixe_est_vide(const file_fixe_t *file);

int file_fixe_enfiler(file_fixe_t *file, element_t element);

int file_fixe_defiler(file_fixe_t *file, element_t *p_element);

void file_fixe_afficher(const file_fixe_t *file);

int file_variable_initialiser(file_variable_t *file);

int file_variable_est_vide(const file_variable_t *file);

int file_variable_enfiler(file_variable_t *file, element_t element);

int file_variable_defiler(file_variable_t *file, element_t *p_element);

void file_variable_afficher(const file_variable_t *file);

void file_variable_detruire(file_variable_t *file);

void test_pile_fixe(void);

void test_pile_variable(void);

void test_file_fixe(void);

void test_file_variable(void);

#endif //R305_QUEUE_AND_STACK_OPERATIONS_H
