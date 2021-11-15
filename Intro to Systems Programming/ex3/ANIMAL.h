#ifndef ANIMAL_H
#define ANIMAL_H


#include <stdio.h>
#include <stdlib.h>
#include "COMMON.h"
#include "FOOD.h"
#include <string.h>



#define MAX_ID 5
#define SIZE_OF_ANIMAL_LIST 10000
#define MAX_TYPE 10
#define MAX_COLOR 7
#define MAX_NAME_ANIMAL 10
#define MAX_BIRTHPLACE 10
#define MAX_CHILDREN 1000
#define BARCODE_LENGTH 20
#define MAX_HEALTH 100



typedef struct animal {
	char *type;
	char *color;
	char *name;
	char id[MAX_ID + 1];
	Date birthday;
	char *birthPlace;
	int healthStat;
	int numOfChildren;
	char idOfChildren[MAX_CHILDREN + 1][MAX_ID + 1];
	char foodType[BARCODE_LENGTH + 1];
	int dailyMeals;
	struct	animal *right;
	struct animal *left;
}Animal;

void createAnimalList(Animal **head);										/*To declare a new list was created we must set it, it is most comfortble to set it to NULL*/
void addNewAnimal(Animal **treeAnimal, char id[]);							/*Adds new animal to the list*/
void addNewAnimalInput(Animal **animal, const char id[]);					/*gets input from the user into the newly declared new animal*/
void input_IDofChildren(Animal *animal, int numOfChildren);					/*Function used to help set the IDs of the children of currently being created animal into an array*/
int animalNumberWithGivenFoodKind(Animal *animal);							/*Gets a food's barcode from user, searches through all the animals and counts the number of animals with said barcode set as their food type*/
int animalNumberWithGivenFoodKind_REC(Animal *animal, const char *barcode);	/* same as above but recursive */
int animalNumberWithGivenColor(Animal *animal);								/*Gets a colour from user, searches through all the animals and counts the number of animals with said colour set as their colour*/
int animalNumberWithGivenColor_REC(Animal *animal, char *color);			/* counts number of animals the color is given the same and returns the count*/
Animal *findMin(Animal *root);												/*finds min ID of animal in the tree*/
void deleteAnimal(Animal **treeAnimal, const char *id);						/*Given the ID of an animal, the function will remove it from the list*/
void deleteAllAnimals(Animal **treeAnimal);									/*Deletes all animals in the currect list*/
void threePopularFoods(Animal **treeAnimal, FoodType **treeFood);			/*read at function*/
void displayAnimal(Animal  **animalList);									/*Simple function that displays an animal*/
void printAnimalsForGivenBirthYear_REC(Animal **treeAnimal, Date dateGiven);/*An additional GAN HI exclusive function, prints animals with the given date as their birthday*/
double averageNumOfChildren(Animal **animal, int *cntAnimals, double *sumChild);
void displayAllAnimal(Animal  **animalList);								/*Simple function that goes through the list of animals and displays each one*/
void insertPopularFood(BarcodeCount *first, BarcodeCount *second, BarcodeCount *third, Animal *treeAnimal, FoodType *treeFood); /*inserts inside the Barcode counts the barcodes*/
double averageNumOfChildren(Animal **animal, int *cntAnimals, double *sumChild); /*caucaltes the average numbers of children */
int countDailyMealsOfAnimals_REC(Animal *animal, const char *barcode);		/*gets barcode and returns how much food is eaten by given that barcode of food*/


#endif
