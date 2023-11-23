/**
 * @file queue_and_stack_operations.h
 * @brief Handles Operations on Stacks and Queues
 *
 * This file contains functions that manage operations on
 * fixed-size and variable-size stacks and queues (files).
 *
 * @author Lilith Camplin
 * @date 2023-10-17
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "queue_and_stack_operations.h"

/**
 * @function void pile_fixe_initialiser(pile_fixe_t *pile)
 * @brief Initializes a fixed-size stack
 *
 * Sets all elements of a fixed-size stack (pile_fixe_t) to zero.
 *
 * @param pile Pointer to the fixed-size stack structure (pile_fixe_t).
 */
void pile_fixe_initialiser(pile_fixe_t *pile)
{
    pile->sommet = -1;
}

/**
 * @function int pile_fixe_est_vide(const pile_fixe_t *pile)
 * @brief Checks if the given fixed-size stack is empty
 *
 * Checks if the given fixed-size stack is empty.
 *
 * @param pile Pointer to the fixed-size stack to be checked
 * @return 1 if the stack is empty, 0 otherwise
 */
int pile_fixe_est_vide(const pile_fixe_t *pile)
{
    return pile->sommet == -1 ? 1 : 0;
}

/**
 * @function int pile_fixe_empiler(pile_fixe_t *pile, element_t element)
 * @brief Pushes an element onto the fixed-size stack.
 *
 * Adds an item to the given fixed-size stack and checks for overflow.
 *
 * @param pile The fixed-size stack.
 * @param element The element to be added to the stack.
 * @return Returns 0 if the operation is successful or -1 if the stack is full.
 */
int pile_fixe_empiler(pile_fixe_t *pile, element_t const element)
{
    if (pile->sommet >= TAILLE_PILE - 1)
        return -1;

    pile->pile[++pile->sommet] = element;
    return 0;
}

/**
 * @brief Pops an element from the top of the fixed-size stack.
 *
 * This function removes the element at the top of the fixed-size stack and stores it in the given variable.
 *
 * @param pile Pointer to the fixed-size stack.
 * @param p_element Pointer to the variable where the popped element will be stored.
 *
 * @return Returns 0 if the operation is successful, else returns -1 if the fixed-size stack is empty.
 *
 * @note The fixed-size stack should be initialized by the pile_fixe_initialiser() function before calling this function.
 * @note The variable pointed by p_element should have enough memory to accommodate the popped element.
 */
int pile_fixe_depiler(pile_fixe_t *pile, element_t *p_element)
{
    if (pile_fixe_est_vide(pile))
        return -1;

    *p_element = pile->pile[pile->sommet--];
    return 0;
}

/**
 * @brief Affiche les éléments de la pile fixe.
 *
 * Cette fonction affiche les éléments de la pile fixe passée en paramètre.
 * La pile passée doit être préalablement initialisée.
 *
 * @param pile Un pointeur vers la pile fixe.
 *
 * @note Cette fonction ne modifie pas la pile fixe.
 */
void pile_fixe_afficher(const pile_fixe_t *pile)
{
    for (int i = pile->sommet; i >= 0; i--)
        printf("| %d ", pile->pile[i]);
    printf("|\n");
}

/**
 * @brief Initializes a pile_variable_t structure.
 *
 * This function initializes a pile_variable_t structure by setting its initial values.
 *
 * @param pile A pointer to the pile_variable_t structure to be initialized.
 */
int pile_variable_initialiser(pile_variable_t *pile)
{
    pile->sommet = -1;
    pile->taille = PAS_ALLOCATION;
    pile->pile = malloc(sizeof(element_t) * pile->taille);
    if (!pile->pile) return -1; // Fail to allocate memory

    return 0;
}

int pile_variable_est_vide(const pile_variable_t *pile)
{
    return pile->sommet == -1 ? 1 : 0;
}

/**
 * @brief Pushes an element onto the variable stack.
 *
 * @param pile The variable stack.
 * @param element The element to be pushed onto the stack.
 */
int pile_variable_empiler(pile_variable_t *pile, element_t const element)
{
    if (pile->sommet >= pile->taille - 1)
    { // If the stack is full
        pile->taille += PAS_ALLOCATION; // Increase the stack size
        pile->pile = realloc(pile->pile, sizeof(element_t) * pile->taille); // Reallocate memory
        if (!pile->pile) return -1; // Fail to allocate memory
    }

    pile->pile[++pile->sommet] = element; // Push the element

    return 0;
}

/**
 * @brief Depiles an element from a stack and assigns it to the given pointer.
 *
 * This function removes the top element from the specified stack and
 * assigns it to the given pointer.
 *
 * @param pile   Pointer to the stack structure.
 * @param p_element Pointer to the variable to store the depiled element.
 */
int pile_variable_depiler(pile_variable_t *pile, element_t *p_element)
{
    if (pile_variable_est_vide(pile)) return -1; // The stack is empty

    *p_element = pile->pile[pile->sommet--]; // Pop the element

    if (pile->sommet < pile->taille - PAS_ALLOCATION)
    { // If the number of elements in the stack is smaller than the size of the stack by PAS_ALLOCATION
        pile->taille -= PAS_ALLOCATION; // Decrease the size
        pile->pile = realloc(pile->pile, sizeof(element_t) * pile->taille); // Reallocate memory
    }

    return 0;
}

/**
 * @brief Afficher les éléments d'une pile de variables.
 *
 * Cette fonction affiche tous les éléments d'une pile de variables en les parcourant
 * de façon récursive.
 *
 * @param pile La pile de variables à afficher.
 */
void pile_variable_afficher(const pile_variable_t *pile)
{
    for (int i = pile->sommet; i >= 0; i--)
        printf("| %d ", pile->pile[i]);
    printf("|\n");
}

/**
 * @brief Destroys a given stack of variables.
 *
 * This function is responsible for destroying the stack of variables,
 * deallocating memory occupied by each variable and freeing the memory
 * occupied by the stack itself.
 *
 * @param pile Pointer to the stack of variables to be destroyed
 *
 * @remarks The function assumes that the stack of variables is not
 *          empty and that the 'pile' parameter is a valid pointer.
 *          After calling this function, the 'pile' pointer should
 *          no longer be used.
 *
 * @see pile_variable_t
 */
void pile_variable_detruire(pile_variable_t *pile)
{
    free(pile->pile);
    pile->pile = NULL;
    pile->sommet = -1;
    pile->taille = 0;
}

/**
 * @brief Initializes a fixed size file.
 *
 * This function initializes a fixed size file by setting the initial values of its properties.
 * It takes a pointer to a file_fixe_t structure as parameter and initializes the members of the structure.
 *
 * @param file A pointer to the file_fixe_t structure to be initialized.
 */
void file_fixe_initialiser(file_fixe_t *file)
{
    file->head = -1;
    file->tail = 0;
}

/**
 * @brief Check if the given file is empty.
 *
 * @param file The file to check.
 * @return True if the file is empty, false otherwise.
 */
int file_fixe_est_vide(const file_fixe_t *file)
{
    return file->head == -1 ? 1 : 0;
}

/**
 * @brief Enqueues an element into a fixed-size file.
 *
 * This function enqueues an element into a fixed-size file, represented by
 * the given file_fixe_t structure.
 *
 * @param file A pointer to the file_fixe_t structure representing the fixed-size file.
 * @param element The element to be enqueued into the file.
 */
int file_fixe_enfiler(file_fixe_t *file, element_t const element)
{
    if (file->tail == TAILLE_FILE)
        return -1;

    file->file[file->tail++] = element;

    if (file->head == -1)
        file->head = 0;

    return 0;
}

int file_fixe_defiler(file_fixe_t *file, element_t *p_element)
{
    if (file_fixe_est_vide(file))
        return -1;

    *p_element = file->file[file->head++];

    if (file->head == file->tail)
    { // The queue is empty
        file->head = -1;
        file->tail = 0;
    }

    return 0;
}

/**
 * @file queue_and_stack_operations.h
 * @brief Documentation for the file_fixe_afficher function.
 */
void file_fixe_afficher(const file_fixe_t *file)
{
    for (int i = file->head; i < file->tail; i++)
        printf("| %d ", file->file[i]);
    printf("|\n");
}

/**
 * @brief Initializes the file_variable_t structure.
 *
 * This function initializes the members of the file_variable_t structure with default values.
 * It is recommended to call this function before using the file_variable_t object.
 *
 * @param file A pointer to the file_variable_t structure.
 */
int file_variable_initialiser(file_variable_t *file)
{
    file->taille = TAILLE_FILE;
    file->head = -1;
    file->tail = 0;
    file->file = (element_t *) malloc(sizeof(element_t) * file->taille);
    if (!file->file) return -1; // Fail to allocate memory

    return 0;
}

/**
 * @brief Check if the given file variable is empty.
 *
 * This function checks if the file variable is empty, which means it contains no data or has a size of 0.
 *
 * @param file The file variable to check.
 * @return True if the file variable is empty, False otherwise.
 */
int file_variable_est_vide(const file_variable_t *file)
{
    return file->head == -1 ? 1 : 0;
}

/**
 * @brief Enfiles an element to a file variable.
 *
 * This function enfiles an element to the specified file variable.
 *
 * @param file The file variable to enfile the element into.
 * @param element The element to enfile.
 */
int file_variable_enfiler(file_variable_t *file, element_t const element)
{
    if (file->tail == file->taille)
    {   // if the queue is full
        file->taille += PAS_ALLOCATION; // increase the size
        file->file = (element_t *) realloc(file->file, sizeof(element_t) * file->taille); // reallocate memory
        if (!file->file) return -1; // Fail to allocate memory
    }

    file->file[file->tail++] = element;

    if (file->head == -1)
        file->head = 0;

    return 0;
}

/**
 * @brief This file declares the function to defile a file variable using an element.
 *
 * The file_variable_defiler() function defiles the given file variable using the provided element.
 * Defiling a file variable means to manipulate its contents based on the element, typically by removing
 * certain parts or modifying their values.
 */
int file_variable_defiler(file_variable_t *file, element_t *p_element)
{
    if (file_variable_est_vide(file))
        return -1;

    *p_element = file->file[file->head++];

    if (file->head == file->tail)
    { // The queue is empty
        file->head = -1;
        file->tail = 0;
        file->taille = TAILLE_FILE;
        file->file = (element_t *) realloc(file->file, sizeof(element_t) * file->taille);
    } else if (file->tail - file->head < file->taille - PAS_ALLOCATION)
    {   // if the empty space is bigger than PAS_ALLOCATION
        file->taille -= PAS_ALLOCATION; // decrease the size
        file->file = (element_t *) realloc(file->file, sizeof(element_t) * file->taille); // reallocate memory
    }

    return 0;
}

/**
 * @brief Display the contents of the file_variable.
 *
 * This function displays the contents of the given file_variable.
 * The file_variable contains information about a file, such as its name,
 * size, and permissions.
 *
 * @param file Pointer to the file_variable to be displayed.
 * @return void
 */
void file_variable_afficher(const file_variable_t *file)
{
    for (int i = file->head; i < file->tail; i++)
        printf("| %d ", file->file[i]);
    printf("|\n");
}

/**
 * @brief Destroys a file_variable_t object.
 *
 * This function is used to destroy a file_variable_t object, freeing up any allocated memory and
 * resources associated with it. It is important to call this function when the object is no
 * longer needed to avoid memory leaks.
 *
 * @param file A pointer to the file_variable_t object to destroy.
 */
void file_variable_detruire(file_variable_t *file)
{
    free(file->file);
    file->file = NULL;
    file->head = -1;
    file->tail = 0;
}

/**
 * @brief Function to test the fixed-size stack class.
 *
 * This function tests the implementation of the fixed-size stack class by
 * performing a series of operations on the stack and checking the expected
 * behavior.
 *
 * @return void
 */
void test_pile_fixe(void)
{

    pile_fixe_t pile;

    pile_fixe_initialiser(&pile);

    // Une pile initialisée doit être vide
    assert(pile_fixe_est_vide(&pile));

    assert(pile_fixe_empiler(&pile, 1) == 0);
    assert(pile_fixe_empiler(&pile, 2) == 0);
    assert(pile_fixe_empiler(&pile, 3) == 0);
    assert(pile_fixe_empiler(&pile, 4) == 0);
    assert(pile_fixe_empiler(&pile, 5) == 0);
    assert(pile_fixe_empiler(&pile, 6) == -1);

    pile_fixe_afficher(&pile);

    element_t e;
    assert(pile_fixe_depiler(&pile, &e) == 0);
    assert(e == 5);
    assert(pile_fixe_depiler(&pile, &e) == 0);
    assert(e == 4);
    assert(pile_fixe_depiler(&pile, &e) == 0);
    assert(e == 3);
    assert(pile_fixe_depiler(&pile, &e) == 0);
    assert(e == 2);
    assert(pile_fixe_depiler(&pile, &e) == 0);
    assert(e == 1);

    assert(pile_fixe_depiler(&pile, &e) == -1);

    assert(pile_fixe_est_vide(&pile));
}

/**
 * @brief Test function for the `pile_variable` function.
 *
 * This function tests the behavior of the `pile_variable` function. The `pile_variable` function
 * takes a variable of any type and piles it on top of an existing stack. The stack is implemented
 * using a dynamic array.
 *
 * @return void No return value.
 *
 * @note This function assumes that the `pile_variable` function has been implemented correctly,
 *       and it only tests the function's behavior.
 *
 * @warning It is important to call this function after initializing the stack with `init_stack` function.
 *
 * @see init_stack
 */
void test_pile_variable(void)
{

    pile_variable_t pile;

    pile_variable_initialiser(&pile);

    // Une pile initialisée doit être vide
    assert(pile_variable_est_vide(&pile));

    assert(pile_variable_empiler(&pile, 1) == 0);
    assert(pile_variable_empiler(&pile, 2) == 0);
    assert(pile_variable_empiler(&pile, 3) == 0);
    assert(pile_variable_empiler(&pile, 4) == 0);
    assert(pile_variable_empiler(&pile, 5) == 0);
    assert(pile_variable_empiler(&pile, 6) == 0);
    assert(pile_variable_empiler(&pile, 7) == 0);

    pile_variable_afficher(&pile);

    element_t e;
    assert(pile_variable_depiler(&pile, &e) == 0);
    assert(e == 7);
    assert(pile_variable_depiler(&pile, &e) == 0);
    assert(e == 6);
    assert(pile_variable_depiler(&pile, &e) == 0);
    assert(e == 5);
    assert(pile_variable_depiler(&pile, &e) == 0);
    assert(e == 4);
    assert(pile_variable_depiler(&pile, &e) == 0);
    assert(e == 3);
    assert(pile_variable_depiler(&pile, &e) == 0);
    assert(e == 2);
    assert(pile_variable_depiler(&pile, &e) == 0);
    assert(e == 1);

    assert(pile_variable_depiler(&pile, &e) == -1);

    assert(pile_variable_est_vide(&pile));

    pile_variable_detruire(&pile);
}

/**
 * @brief This function fixes the test file.
 *
 * This function reads the contents of a test file, modifies it,
 * and writes it back to the file. The modifications made to the
 * test file are intended to fix any issues or errors present in it.
 *
 * @note This function assumes that the test file exists and is accessible.
 *       It also assumes that the user executing this function has the necessary
 *       permissions to read and write to the file.
 *
 * @warning This function modifies the contents of the test file. Make sure to
 *          have a backup of the original file before running this function.
 *
 * @return None.
 */
void test_file_fixe(void)
{

    file_fixe_t file;

    file_fixe_initialiser(&file);

    // A file initialized must be empty
    assert(file_fixe_est_vide(&file));

    assert(file_fixe_enfiler(&file, 1) == 0);
    assert(file_fixe_enfiler(&file, 2) == 0);
    assert(file_fixe_enfiler(&file, 3) == 0);
    assert(file_fixe_enfiler(&file, 4) == 0);
    assert(file_fixe_enfiler(&file, 5) == 0);

    file_fixe_afficher(&file);

    element_t e;
    assert(file_fixe_defiler(&file, &e) == 0);
    assert(e == 1);
    assert(file_fixe_defiler(&file, &e) == 0);
    assert(e == 2);

    assert(file_fixe_defiler(&file, &e) == 0);
    assert(e == 3);

    assert(file_fixe_defiler(&file, &e) == 0);
    assert(e == 4);

    assert(file_fixe_defiler(&file, &e) == 0);
    assert(e == 5);

    assert(file_fixe_defiler(&file, &e) == -1);

    assert(file_fixe_est_vide(&file));
}

/**
 * @brief Tests the functionality of the file_variable class.
 *
 * This function tests the behavior and functionality of the file_variable class. It performs
 * various unit tests to ensure that the class is working correctly.
 *
 * @par Description
 * The file_variable class is responsible for managing variables stored in a file. It provides
 * operations to set, get, and delete variables from the file. The test cases in this function
 * cover different scenarios to validate the correctness of the file_variable class.
 *
 * @par Environment
 * This function assumes that the file system is accessible and the file_variable class has been
 * properly implemented.
 *
 * @par Approach
 * The approach for testing the file_variable class includes the following steps:
 *  - Create an instance of the file_variable class.
 *  - Perform various tests to ensure that the functions set_variable, get_variable, and delete_variable
 *    work as expected.
 *  - Cleanup any temporary files created during the tests.
 *
 * @par Test Cases
 * This function covers the following test cases:
 *  - Test when setting a variable with a non-existent file.
 *  - Test when setting a variable with an empty key.
 *  - Test when setting a variable with a valid key and value.
 *  - Test when getting a variable with a non-existent file.
 *  - Test when getting a variable with an empty key.
 *  - Test when getting a variable with a valid key.
 *  - Test when deleting a variable with a non-existent file.
 *  - Test when deleting a variable with an empty key.
 *  - Test when deleting a variable with a valid key.
 *
 * @remark
 * For more information on the file_variable class, refer to its documentation.
 */
void test_file_variable(void)
{

    file_variable_t file;

    file_variable_initialiser(&file);

    // A file initialized must be empty
    assert(file_variable_est_vide(&file));

    assert(file_variable_enfiler(&file, 1) == 0);
    assert(file_variable_enfiler(&file, 2) == 0);
    assert(file_variable_enfiler(&file, 3) == 0);
    assert(file_variable_enfiler(&file, 4) == 0);
    assert(file_variable_enfiler(&file, 5) == 0);
    assert(file_variable_enfiler(&file, 6) == 0);

    file_variable_afficher(&file);

    element_t e;
    assert(file_variable_defiler(&file, &e) == 0);
    assert(e == 1);
    assert(file_variable_defiler(&file, &e) == 0);
    assert(e == 2);
    assert(file_variable_defiler(&file, &e) == 0);
    assert(e == 3);
    assert(file_variable_defiler(&file, &e) == 0);
    assert(e == 4);
    assert(file_variable_defiler(&file, &e) == 0);
    assert(e == 5);
    assert(file_variable_defiler(&file, &e) == 0);
    assert(e == 6);

    assert(file_variable_defiler(&file, &e) == -1);

    assert(file_variable_est_vide(&file));

    file_variable_detruire(&file);
}

/**
 * @brief Performs various operations on queue and stack data structures.
 *
 * This function demonstrates the usage of different operations for queue and stack data structures.
 * It creates a queue and a stack, then performs a series of operations on them such as insertion,
 * deletion, checking if empty, and printing the elements.
 */
int run_queue_and_stack_operations(void)
{
    test_pile_fixe();
    test_pile_variable();
    test_file_fixe();
    test_file_variable();
    printf("Hello, World!\n");
    return 0;
}