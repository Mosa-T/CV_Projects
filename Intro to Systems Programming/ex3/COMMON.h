#ifndef COMMON_H
#define COMMON_H
#include <malloc.h>

#include <stdio.h>
#include <stdbool.h>


typedef struct DDate{
	int day;
	int month;
	int year;
}Date;


bool isEqualDate(Date, Date );			/*Checks to see if the date given by the user is the same as the birthday of an animal*/
void *checked_malloc(unsigned int);
void checked_free(void *);
void check_for_exit();
bool stringCheck(char * a, int size);
void date_input(Date *dateInput);		/* "global" function for date type inputs*/
void wrongInput();
void displayDate(Date *date);			/* "global" function for displaying dates */

#define ALLOC(typ,no) ((typ *) checked_malloc(sizeof(typ)*(no)))
#define FREE(ptr) checked_free(ptr)


#endif
