#include <stdio.h>
#include <stdlib.h>
#include "ANIMAL.h"
#include "COMMON.h"
#include "EMPLOYEE.h"
#include "FOOD.h"
#include "DisplayMenu.h"
/*********************************************************************************************/
/*                 											 */
/*				 																			 */	
/*********************************************************************************************/
int main()
{
	Animal *treeAnimal;
	FoodType *treeFood;
	Employee *treeEmployee;
	LinkedEmployee *head;
	head = NULL;
	createAnimalList(&treeAnimal);
	createFoodList(&treeFood);
	createEmployeeList(&treeEmployee);
	DisplayMenu(&treeAnimal, &treeFood, &treeEmployee , &head); /*displays and handles every input/output*/
	return 0;
}

