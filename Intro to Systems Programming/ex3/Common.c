#include <stdio.h>
#include <stdlib.h>
#include "COMMON.h"



static unsigned int allocated_blocks = 0;

/*The less i type the better*/
void wrongInput()
{
	printf("Incorrect input please try again\n");
}

/*function not used*/
bool stringCheck(char *a,int size)
{
	int i;
	for (i = 0; i <= size; i++)
	{
		if (*(a + i) == '\0') return true;
	}
	return false;
}

/* "global" function for date type inputs*/
void date_input(Date *dateInput)
{
	bool allCorrect = false;
	if (dateInput == NULL)
	{
		printf("wrong input in date_input\n");
		return;
	}
	do {
		printf("enter info of the date:\n");
		printf("Day:\n");
		scanf("%d", &dateInput->day);
		printf("Month:\n");
		scanf("%d", &dateInput->month);
		printf("Year:\n");
		scanf("%d", &dateInput->year);
		if (dateInput->day > 31 || dateInput->day < 1
			|| dateInput->month > 12 || dateInput->month < 1 
			|| dateInput->year > 2018 || dateInput->year < 1950) {
			wrongInput();
			continue;
		}
		allCorrect = true;
	} while (allCorrect == false);
}

/* "global" function for displaying dates */
void displayDate(Date *date)
{
	printf("day/month/year: %d/%d/%d\n", date->day, date->month, date->year);
}



void *checked_malloc(unsigned int size)
{
	void * ret;

	ret = malloc(size);
	if (!ret) {
		perror("Memory allocation error");
		exit(1);
	}
	allocated_blocks++;
	return ret;
}

void checked_free(void *ptr)
{

	free(ptr);
	allocated_blocks--;
	return;
}

void check_for_exit() {
	if (allocated_blocks) {
		fprintf(stderr, "Memory leak: %d memory blocks still allocated \n", allocated_blocks);
		exit(1);
	}
	return;
}

/*Checks to see if the date given by the user is the same as the birthday of an animal*/
bool isEqualDate(Date dateGiven,Date animalDate)
{
	if (dateGiven.day == animalDate.day && dateGiven.year == animalDate.year && dateGiven.month == animalDate.month) return true;
	return false;
}