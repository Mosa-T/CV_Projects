#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <stdio.h>
#include <stdlib.h>


#include "ANIMAL.h"
#include "FOOD.h"
#include "COMMON.h"
#include "EMPLOYEE.h"

void DisplayMenu(Animal **treeAnimal, FoodType **treeFood, Employee **treeEmployee, LinkedEmployee **head);	/*recieves the heads of each type from main, will pass them to be used*/
void DisplayMenuOptions();																					/*Basic printf display of the main menu*/
void switchOption(int option, Animal **treeAnimal, FoodType **treeFood, Employee **treeEmployee, LinkedEmployee **head);	/*uses the three different types of lists for all the functions requested through the input "option" */

#endif