
#ifndef FOOD_H
#define FOOD_H

#include<stdio.h>
#include "COMMON.h"
#include <string.h>
#include <stdlib.h>


#define MAX_FOOD_LIST 500
#define BARCODE_LENGTH 20
#define COMPANY_NAME_LEN 10
#define NUM_OF_ANIMAL 100
#define LEN_ANIMAL_NAME 10


typedef struct BarcodeCount {
	char barcode[BARCODE_LENGTH + 1];
	int count;
} BarcodeCount;


typedef struct TType_Food {
	char barCode[BARCODE_LENGTH + 1];
	char *companyName;
	char **typeAnimalsFor;
	int numOfAnimalsFor;
	int stock;
	double weight;
	struct TType_Food *right;
	struct TType_Food *left;
}FoodType;

void createFoodList(FoodType **treeFood);							/*To declare a new list was created we must set it, it is most comfortble to set it to NULL*/
void addNewFood(FoodType **treeFood, const char barcode[]);								/*Adds new food type to the list*/
void addNewFoodInput(FoodType **food, const char barcode[]);			/*gets input from the user into the newly declared new food type*/
void deleteFood(FoodType **treeFood, const char *barcode);								/*Given the barcode of a food type, the function will remove it from the list*/
void deleteAllFood(FoodType **treeFood);							/*Deletes all food types in the currect list*/
void displayFood(FoodType **food);								/*Simple function that displays all food types*/
FoodType *findMinFood(FoodType *root);


#endif
