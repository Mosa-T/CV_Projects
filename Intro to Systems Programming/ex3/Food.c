#include "FOOD.h"


/*To declare a new list was created we must set it, it is most comfortble to set it to NULL*/
void createFoodList(FoodType **treeFood)
{
	(*treeFood) = NULL;
}

/*Adds new food type to the list*/
void addNewFood(FoodType **treeFood,const char barcode[])
{
	struct TType_Food* newFood;
	if ((*treeFood) == NULL){
		newFood = ALLOC(FoodType, 1);
		(*treeFood) = newFood;
		addNewFoodInput(&newFood, barcode);
		newFood->right = NULL;
		newFood->left = NULL;
		return;
	}
	if (strcmp((*treeFood)->barCode, barcode) == 0)
		return;
	if (strcmp((*treeFood)->barCode, barcode) < 0){
		addNewFood(&((*treeFood)->right), barcode);
	}
	if (strcmp((*treeFood)->barCode, barcode) > 0){
		addNewFood(&((*treeFood)->left), barcode);
	}
	return;
}

/*gets input from the user into the newly declared new food type*/
void addNewFoodInput(FoodType **food, const char barcode[])
{
	int j;
	char temp[200];
	if ((*food) == NULL)
	{
		printf("wrong input in addNewFoodInput hoooooooooooooooooooooooo\n");
		return;
	}
	strcpy(temp, barcode);
	if (strlen(temp) != BARCODE_LENGTH) {
		printf("ID already exists or isn't the correct length\n");
		exit(1);
	}
	strcpy(((*food)->barCode), temp);

	printf("please enter food info\n company name:\n");
	scanf("%s", temp);
	(*food)->companyName = ALLOC(char, strlen(temp) + 1);
	strcpy((*food)->companyName, temp);

	printf("The number of animals that it's for(1-100):\n");
	scanf("%d",&((*food)->numOfAnimalsFor));
	if (((*food)->numOfAnimalsFor) > 100 || ((*food)->numOfAnimalsFor) < 1) {
		wrongInput();
		exit(1);
	}
	(*food)->typeAnimalsFor = ALLOC(char *, (*food)->numOfAnimalsFor);

	for (j = 0; j < ((*food)->numOfAnimalsFor); j++) {
		printf("\nthe type of animal that it's for, number %d: ", (j + 1));
		scanf("%s", temp);
		*((*food)->typeAnimalsFor + j) = ALLOC(char, strlen(temp) + 1);
		strcpy(*((*food)->typeAnimalsFor + j), temp);
	}

	printf("Stock(0-10000):\n");
	scanf("%d", &((*food)->stock));
	if ((*food)->stock > 10000 || (*food)->stock < 0) {
		wrongInput();
		exit(1);
	}
	printf("Weight(1-50):\n");
	scanf("%lf", &((*food)->weight));
	if ((*food)->weight > 50 || (*food)->weight < 1) {
		wrongInput();
		exit(1);
	}
}


FoodType *findMinFood(FoodType *root) {
	FoodType *temp;
	if (root == NULL)
		return NULL;
	temp = root;
	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp;
}


/*Given the barcode of a food type, the function will remove it from the list*/
void deleteFood(FoodType **treeFood, const char *barcode)
{
	int i,k;
	char tempID[200];
	if (*treeFood == NULL) return;
	if (strcmp((*treeFood)->barCode, barcode) > 0)
		deleteFood(&((*treeFood)->left), barcode);
	else if (strcmp((*treeFood)->barCode, barcode) < 0)
		deleteFood(&((*treeFood)->right), barcode);
	else {
		FoodType *left = (*treeFood)->left;
		FoodType *right = (*treeFood)->right;
		FoodType *temp = *treeFood;
		if (!left && !right) {
			FREE((*treeFood)->companyName);
			for (i = 0; i < (*treeFood)->numOfAnimalsFor; i++) {
				FREE(*((*treeFood)->typeAnimalsFor + i));
			}
			FREE(*treeFood);
			*treeFood = NULL;
			return;
		}
		else if (left && !right) {
			*treeFood = left;
			FREE((temp)->barCode);
			FREE((temp)->companyName);
			for (i = 0; i < (temp)->numOfAnimalsFor; i++) {
				FREE(*((temp)->typeAnimalsFor + i));
			}
			FREE(temp);
			temp = NULL;
			return;
		}
		else if (!left && right) {
			*treeFood = right;
			FREE((temp)->companyName);
			for (i = 0; i < (temp)->numOfAnimalsFor; i++) {
				FREE(*((temp)->typeAnimalsFor + i));
			}
			FREE(temp);
			temp = NULL;
			return;
		}
		else {
			temp = findMinFood(right); /*need to swapp ALL the info between them */
			strcpy(tempID, (*treeFood)->barCode);
			strcpy((*treeFood)->barCode, temp->barCode);
			strcpy(temp->barCode, tempID);




			(*treeFood)->companyName = (char *)realloc((*treeFood)->companyName, strlen(temp->companyName));
			strcpy((*treeFood)->companyName, temp->companyName);

			(*treeFood)->numOfAnimalsFor = temp->numOfAnimalsFor;

			(*treeFood)->typeAnimalsFor = (char **)realloc((*treeFood)->typeAnimalsFor, temp->numOfAnimalsFor);
			for ( k = 0; k < (*treeFood)->numOfAnimalsFor; k++)
			{
				*((*treeFood)->typeAnimalsFor + k) = (char *)realloc((*treeFood)->typeAnimalsFor, strlen(*(temp->typeAnimalsFor)+k));
				strcpy(*((*treeFood)->typeAnimalsFor + k), *(temp->typeAnimalsFor + k));
			}
			(*treeFood)->stock = temp->stock;
			(*treeFood)->weight = temp->weight;

			deleteFood(&((*treeFood)->right), tempID);
		}
	}
}

/*Deletes all food types in the currect list*/
void deleteAllFood(FoodType **treeFood)
{
	int i;
	if ((*treeFood) == NULL)
	{
		printf("list was emptied\n");
		return;
	}
	deleteAllFood(&((*treeFood)->right));
	deleteAllFood(&((*treeFood)->left));
	FREE((*treeFood)->companyName);
	for (i = 0; i < (*treeFood)->numOfAnimalsFor; i++)
	{
		FREE(*((*treeFood)->typeAnimalsFor + i));
	}
	FREE((*treeFood)->typeAnimalsFor);
	FREE((*treeFood));
	(*treeFood) = NULL;
}




/*Simple function that displays all food types*/
void displayFood(FoodType **food)
{
	FoodType *food1 = (*food);
	int k = 0;
	if (food1 == NULL) return;
	printf("Info of food:\n");
	printf("Barcode: %s\n", food1->barCode);
	printf("Company name: %s\n", food1->companyName);
	printf("Type animals the food for:\n");
	for (k = 0; k < food1->numOfAnimalsFor; k++)
	{
		printf("Type animal %d: %s\n",(k+1), *((food1->typeAnimalsFor)+k));
	}
	printf("Stock: %d\n", food1->stock);
	printf("Weight: %.2f\n\n", food1->weight);
	displayFood(&(food1->right));
	displayFood(&(food1->left));

}