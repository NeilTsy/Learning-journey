/** @file listy.h
 *  @brief Function prototypes for the linked list.
 */
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define MAX_WORD_LEN 50

/**
 * @brief An struct that represents a node in the linked list.
 */
typedef struct node {
    char *artist;
    char *song;
    int year;
    int popularity;
    double danceability;
    double energy;
    struct node *next;
} node_t;

/**
 * Function protypes associated with a linked list.
 */
node_t *new_node(char *artist, char *song, int year, double danceability, double energy, int popularity);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
double compare_songs(node_t *song1, node_t *song2, const char *required_column);
node_t *add_inorder(node_t *list, node_t *new, const char *required_column);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void apply(node_t *, void (*fn)(node_t *, void *), void *arg);

#endif
