/*********************************************************************************

    id: ***********
    name: Mosa Thoukwho
    this program takes inputed letters and displays the maximum number of way to re-arrange those said letters.

**********************************************************************************/

// Include files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FIRST_INDEX 0
#define MAX_SIZE 20

//Function prototypes
char *input_command();
int size_letters(char *array, int size);
void re_arrange(char *, int, int);
void swap(char *, char *);



int main()
{
    int size;
    char *string;
    string = input_command();
    size = size_letters(string, MAX_SIZE+1);
    re_arrange(string, FIRST_INDEX, size-1);
    return 0;
}

//Function to print possible combinations of string
void re_arrange(char *string, int start_point, int size)
{
   int current_point;
   if (start_point == size) printf("%s\n", string);

   else{
       for (current_point = start_point; current_point <= size; current_point++){
          swap((string+start_point), (string+current_point));
          re_arrange(string, start_point+1, size);
          swap((string+start_point), (string+current_point)); //gets rid of the second "abc" that pops up!
        }
    }
}

//Function to swap values between two indexes
void swap(char *letter_1, char *letter_2)
{
    char temp;
    temp = *letter_1;
    *letter_1 = *letter_2;
    *letter_2 = temp;
}

//Redefines size of string to correct size
int size_letters(char *array, int size)
{
    int new_size;
    new_size = strlen(array);
    array = (char *)realloc(array, new_size * sizeof(char));
    return new_size;
}

//Gets input and returns a string
char *input_command()
{
    char *array = (char *)malloc(MAX_SIZE+1 * sizeof(char));
    printf("\nPlease enter chars: ");
    gets(array);
    return array;
}
