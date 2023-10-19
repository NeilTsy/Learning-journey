/** @file music_manager.c
 *  @brief A small program to analyze songs data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Victoria L.
 *  @author Shiyu Tang
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "emalloc.h"

#define MAX_LINE_LEN 80

void free_list(node_t *list);
void process_file(node_t **list, char *line, char *sort_By, int display);
void read_csv(char *argv[]);
void generate_output_csv(node_t *list, const char *sort_By, int display);

/**
 * @brief Read and process a CSV file based on the command-line arguments.
 *
 * @param argv The list of arguments passed to the program.
 */
void read_csv(char *argv[]) {
    strtok(argv[3], "=");
    char* filename = strtok(NULL, "=");
    strtok(argv[2],"=");
    int display = atoi(strtok(NULL, "="));
    strtok(argv[1],"=");
    char *sort_By = strtok(NULL, "=");

    FILE *file = fopen(filename, "r");
    char line[1024];
    node_t* list = NULL;

    fgets(line,sizeof(line),file);
   
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        process_file(&list, line,sort_By,display);
    }

    fclose(file);
    generate_output_csv(list,sort_By,display);
    free_list(list);
}

/**
 * @brief Process a line from the CSV file and add a new node to the linked list.
 *
 * @param list The pointer to the linked list.
 * @param line The line read from the CSV file.
 * @param sort_By The column to sort by.
 * @param display The number of top songs to display.
 */
void process_file(node_t **list, char *line, char *sort_By, int display) {
    char *token = strtok(line, ",");
    char *artist = token;
    char *song = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    int year = atoi(strtok(NULL, ","));
    int popularity = atoi(strtok(NULL, ","));
    double danceability = atof(strtok(NULL, ","));
    double energy = atof(strtok(NULL, ","));
     
    node_t *new_node_cur = new_node(artist, song, year, danceability, energy, popularity);
    *list = add_inorder(*list, new_node_cur, sort_By);
}

/**
 * @brief Generate the output CSV file based on the sorted linked list.
 *
 * @param list The sorted linked list of songs.
 * @param sort_By The column to sort by.
 * @param display The number of top songs to display.
 */
void generate_output_csv(node_t *list, const char *sort_By, int display) {
    FILE *file = fopen("output.csv", "w");

    fprintf(file, "artist,song,year,%s\n", sort_By);

    node_t *current = list;
    int count = 0;
    while (current != NULL && count < display) {
        if (strcmp(sort_By, "popularity") == 0) {
            fprintf(file, "%s,%s,%d,%d\n", current->artist, current->song, current->year, current->popularity);
        } else if (strcmp(sort_By, "energy") == 0) {
            fprintf(file, "%s,%s,%d,%g\n", current->artist, current->song, current->year, current->energy);
        } else if (strcmp(sort_By, "danceability") == 0) {
            fprintf(file, "%s,%s,%d,%g\n", current->artist, current->song, current->year, current->danceability);
        }
        current = current->next;
        count++;
    }

    fclose(file);
}

/**
 * @brief Free the memory allocated for the linked list.
 *
 * @param list The linked list to free.
 */
void free_list(node_t *list) {
    node_t *current = list;
    node_t *next;

    while (current != NULL) {
        next = current->next;
        free(current->artist);
        free(current->song);
        free(current);
        current = next;
    }
}

/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */

int main(int argc, char *argv[])
{
   if(argc != 4){
        return 1;
    }
    read_csv(argv);
    // TODO: your code.
    return 0;
}
