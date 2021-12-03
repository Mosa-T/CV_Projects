#ifndef EMPLOYEE_H
#define EMPLOYEE_H


#include<stdio.h>
#include "COMMON.h"
#include <string.h>
#include <stdlib.h>


#define MAX_EMPLOYEE_LIST 100
#define MAX_NAME_EMPLOYE 20
#define LAST_NAME 20
#define MAX_IN_CARE 200
#define ID_EMPLOYEE 9
#define ID_ANIMAL 5

typedef struct EEmploye {
	char *name;
	char *lastName;
	char id[ID_EMPLOYEE + 1];
	int careForAnimals;
	char **idOfAnimals;
	Date startOfEmplyoment;
	struct EEmploye *right;
	struct EEmploye *left;
}Employee;


typedef struct LinkedEEmploye {
	char *name;
	char *lastName;
	char id[ID_EMPLOYEE + 1];
	int careForAnimals;
	char **idOfAnimals;
	Date startOfEmplyoment;
	struct LinkedEEmploye *next;
}LinkedEmployee;

void createEmployeeList(Employee **treeFood);						/*To declare a new list was created we must set it, it is most comfortble to set it to NULL*/
void addNewEmployee(Employee **treeEmployee, const char *id);		/*Adds new employee to the list*/
void addNewEmployeeInput(Employee **emp, const char *id);			/*gets input from the user into the newly declared employee*/
void input_IDofAnimal(Employee **emp, int careForAnimals);			/*Function used to help set the IDs of the animals that the employee is supervising */
void deleteEmployee(Employee **treeEmployee, const char *id);		/*Given the barcode of an employee, the function will remove it from the list*/
void deleteAllEmployee(Employee **treeEmployee);					/*Deletes all employees in the currect list*/
void printEmployee(Employee **emp);									/*Simple function that displays all employees*/
void findEmployeeById(Employee **treeEmployee, const char *id);		/*gets id and finds the employee*/
void findEmployeeBycareForAnimals(Employee **treeEmp, int careForAnimals, LinkedEmployee **head); /*gets number care for animals makes linked list of employee by number of care for animals*/
void findEmployee(Employee **treeEmp, LinkedEmployee **head);		/* opens list by which mean to find employee*/
void displayLinkedList(LinkedEmployee **emp);
void deleteAllLinkedEmployee(LinkedEmployee **head);
Employee *findMinEmp(Employee *root);
#endif
