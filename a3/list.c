/** @file list.c
 *  @brief Implementation of a linked list.
 *
 * Based on the implementation approach described in "The Practice
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"

/**
 * @brief Create a new node with the given attributes.
 *
 * This function dynamically allocates memory for a new node and initializes its attributes
 * with the provided values.
 *
 * @param artist The artist of the song.
 * @param song The title of the song.
 * @param year The year the song was released.
 * @param danceability The danceability score of the song.
 * @param energy The energy score of the song.
 * @param popularity The popularity score of the song.
 * @return A pointer to the newly created node.
 */
node_t *new_node(char *artist, char *song, int year, double danceability, double energy, int popularity) {
    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    temp->artist = (char *)emalloc((strlen(artist) + 1) * sizeof(char));
    strcpy(temp->artist, artist);

    temp->song = (char *)emalloc((strlen(song) + 1) * sizeof(char));
    strcpy(temp->song, song);

    temp->year = year;
    temp->danceability = danceability;
    temp->energy = energy;
    temp->popularity = popularity;

    temp->next = NULL;

    return temp;
}

/**
 * Function:  add_front
 * --------------------
 * @brief  Allows to add a node at the front of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the new head of the list.
 *
 */
node_t *add_front(node_t *list, node_t *new)
{
    new->next = list;
    return new;
}

/**
 * Function:  add_end
 * ------------------
 * @brief  Allows to add a node at the end of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *add_end(node_t *list, node_t *new)
{
    node_t *curr;

    if (list == NULL)
    {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next)
        ;
    curr->next = new;
    new->next = NULL;
    return list;
}

/**
 * @brief Compare two songs based on the specified required column.
 *
 * This function compares two songs based on the specified required column. It returns a value
 * indicating the order of the songs. If the songs have different values for the required column,
 * the difference between the values is returned. If the songs have the same value for the required
 * column, the comparison is based on the song title.
 *
 * @param song1 The first song to compare.
 * @param song2 The second song to compare.
 * @param required_column The required column to compare the songs by (e.g., "popularity", "energy", "danceability").
 * @return A negative value if song1 is less than song2, a positive value if song1 is greater than song2,
 *         and 0 if the songs are equal based on the required column.
 */
double compare_songs(node_t *song1, node_t *song2, const char *required_column)
{
    if (strcmp(required_column, "popularity") == 0)
    {
        if (song1->popularity != song2->popularity)
        {
            return song1->popularity - song2->popularity;
        }
    }
    else if (strcmp(required_column, "energy") == 0)
    {
        if (song1->energy != song2->energy)
        {
            return song1->energy - song2->energy;
        }
    }
    else if (strcmp(required_column, "danceability") == 0)
    {
        if (song1->danceability != song2->danceability)
        {
            return song1->danceability - song2->danceability;
        }
    }
    return (double)strcmp(song1->song, song2->song);
}

/**
 * @brief Insert a new song node into the linked list in descending order based on the required column.
 *
 * This function inserts a new song node into the linked list in descending order based on the specified
 * required column. The new node is inserted at the appropriate position to maintain the descending order.
 * If the new node should be inserted at the beginning of the list, it becomes the new head of the list.
 *
 * @param list The current head of the linked list.
 * @param new The new song node to insert.
 * @param required_column The required column to determine the order of the songs (e.g., "popularity", "energy", "danceability").
 * @return The updated head of the linked list after inserting the new node.
 */
node_t *add_inorder(node_t *list, node_t *new, const char *required_column)
{
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (list == NULL)
    {
        return new;
    }
    double result = compare_songs(new, list, required_column);
    if (result>= 0)
    {
        new->next = list;
        return new;
    }
    for (curr = list; curr != NULL; curr = curr->next)
    {
        result = compare_songs(new, curr, required_column);

        // If the new song should be inserted between prev and curr
        if (result >= 0)
        {
            prev->next = new;
            new->next = curr;
            return list;
        }
        prev = curr;
    }
    prev->next = new;
    new->next = NULL;
    return list;
}

/**
 * Function:  peek_front
 * ---------------------
 * @brief  Allows to get the head node of the list.
 *
 * @param list The list to get the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *peek_front(node_t *list)
{
    return list;
}

/**
 * Function:  remove_front
 * -----------------------
 * @brief  Allows removing the head node of the list.
 *
 * @param list The list to remove the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *remove_front(node_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->next;
}

/**
 * Function: apply
 * --------------
 * @brief  Allows to apply a function to the list.
 *
 * @param list The list (i.e., pointer to head node) where the function will be applied.
 * @param fn The pointer of the function to be applied.
 * @param arg The arguments to be applied.
 *
 */
void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for (; list != NULL; list = list->next)
    {
        (*fn)(list, arg);
    }
}
