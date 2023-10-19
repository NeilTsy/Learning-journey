/** @file q_array_rotate.c
 *  @brief Submission program for Lab 04.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{

        // variable to store the final answer
        int factorial = 1;

        // WRITE YOUR CODE TO DO COMMAND LINE INPUT CHECKING HERE
        if(argc != 2){
                printf("You haven't provide the number or provide more than 1 argument!\n");
                return 1;
        }
        char *input = argv[1];
        for (int i = 0; input[i] != '\0'; i++) {
             if (!isdigit(input[i])) {
                 printf("The input is not a number!\n");
                 return 1;
             }
        }
        // Takes the command line input and converts it into int.
        int num = atoi(argv[1]);

        // WRITE YOUR CODE TO DO THE FACTORIAL CALCULATIONS HERE
        for(int i = 1; i<=num; i++){
                factorial = factorial * i;
        }
        printf("%d\n", factorial);
        return 0;
}
