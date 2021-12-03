#include <stdio.h>
#include "ANIMAL.h"
#include "FOOD.h"

/*To declare a new list was created we must set it, it is most comfortble to set it to NULL*/
void createAnimalList(Animal **head)
{
	(*head) = NULL;
}

/*Adds new animal to the list*/
void addNewAnimal(Animal **treeAnimal, char id[])
{
	struct animal* newAnimal;
	if ((*treeAnimal) == NULL){
		newAnimal = ALLOC(Animal, 1);
		(*treeAnimal) = newAnimal;
		addNewAnimalInput(&newAnimal,id);
		newAnimal->right = NULL;
		newAnimal->left = NULL;
		return;
	}
	if (strcmp((*treeAnimal)->id, id) == 0)
		return;
	if (strcmp((*treeAnimal)->id, id) < 0){
		addNewAnimal(&((*treeAnimal)->right), id);
	}
	if (strcmp((*treeAnimal)->id, id) > 0){
		addNewAnimal(&((*treeAnimal)->left), id);
	}
	return;
}
/*gets input from the user into the newly declared new animal*/
void addNewAnimalInput(Animal **animal,const char id[])
{
	char temp[200];

	if ((*animal) == NULL)
	{
		printf("wrong input in addNewAnimalInput\n");
		return;
	}
	printf("please enter animal info\n type: ");
	scanf("%s", temp);
	(*animal)->type = ALLOC(char, (strlen(temp) + 1));
	strcpy((*animal)->type, temp);

	printf("\ncolor:");
	scanf("%s", temp);
	(*animal)->color = (char *)malloc(sizeof(char)*(strlen(temp) + 1));
	strcpy((*animal)->color, temp);

	printf("\nname:");
	scanf("%s", temp);
	(*animal)->name = ALLOC(char, (strlen(temp) + 1));
	strcpy((*animal)->name, temp);

	strcpy(temp, id); /*id*/

	if (strlen(temp) != 5){
		printf("error input in ID animal\n");
		exit(1);
	}
	strcpy((*animal)->id, temp);


	printf("\nDate of Birth:\n");
	date_input(&((*animal))->birthday);

	printf("Birth Place: \n");
	scanf("%s", temp);
	(*animal)->birthPlace = (char *)malloc(sizeof(char)*(strlen(temp) + 1));
	strcpy(((*animal)->birthPlace), temp);

	printf("Health stat(1-100):\n");
	scanf("%d", (&(*animal)->healthStat));
	if ((*animal)->healthStat<1 || (*animal)->healthStat>100){
		printf("wrong input in animal health stat\n");
		exit(1);
	}

	printf("Number of children:\n");
	scanf("%d", &((*animal)->numOfChildren));
	if ((*animal)->numOfChildren > MAX_CHILDREN || (*animal)->numOfChildren < 0) {
		wrongInput();
		exit(1);
	}

	printf("ID of children:\n");
	input_IDofChildren((*animal), (*animal)->numOfChildren);
	printf("Food Type(barcode):\n");
	scanf("%s", temp);
	if (strlen(temp) != BARCODE_LENGTH){
		wrongInput();
		exit(1);
	}
	strcpy((*animal)->foodType, temp);



	printf("Daily meals:\n");
	scanf("%d", &(((*animal))->dailyMeals));
	if ((*animal)->dailyMeals > 10 || (*animal)->dailyMeals < 0) {
		wrongInput();
		exit(1);
	}
}
/*Function used to help set the IDs of the children of currently being created animal into an array*/
void input_IDofChildren(Animal *animal, int numOfChildren)
{
	int j;
	for (j = 0; j < numOfChildren; j++) {
		printf("Please enter ID of children, hit enter after every one ID:\n");
		scanf("%s", animal->idOfChildren[j]);
		if (strlen(animal->idOfChildren[j]) != 5)
		{
			wrongInput();
			j--;
			continue;
		}
	}
}


/*Gets a food's barcode from user, searches through all the animals and counts the number of animals with said barcode set as their food type*/
int animalNumberWithGivenFoodKind(Animal *animal)
{
	char givenBarcode[BARCODE_LENGTH+1];
	printf("enter Barcode:\n");
	scanf("%s", givenBarcode);
	if (animal == NULL || givenBarcode == NULL)
	{
		printf("wrong input in animalNumberWithGivenFoodKind\n");
		return -1;
	}
	return animalNumberWithGivenFoodKind_REC(animal, givenBarcode);
}

int animalNumberWithGivenFoodKind_REC(Animal *animal,const char *barcode)
{
	if (animal == NULL)
		return 0;
	if (strcmp(animal->foodType, barcode) == 0){
		return 1 + animalNumberWithGivenFoodKind_REC(animal->right, barcode) + animalNumberWithGivenFoodKind_REC(animal->left, barcode);
		
	}
	else{
		return 0 + animalNumberWithGivenFoodKind_REC(animal->right, barcode) + animalNumberWithGivenFoodKind_REC(animal->left, barcode);
	}
}



/*Gets a colour from user, searches through all the animals and counts the number of animals with said colour set as their colour*/
int animalNumberWithGivenColor(Animal *animal)
{
	Animal *root = animal;
	char givenColor[200];
	printf("enter the color:\n");
	scanf("%s", givenColor);
	if (animal == NULL || givenColor == NULL)
	{
		printf("wrong input in animalNumberWithGivenColor\n");
		return -1;
	}

	return animalNumberWithGivenColor_REC(root, givenColor);
}

int animalNumberWithGivenColor_REC(Animal *animal, char *color)
{
	if (animal == NULL)
		return 0;
	if (strcmp(animal->color, color) == 0){
		return 1 + animalNumberWithGivenColor_REC(animal->right, color) + animalNumberWithGivenColor_REC(animal->left, color);

	}
	else{
		return 0 + animalNumberWithGivenColor_REC(animal->right, color) + animalNumberWithGivenColor_REC(animal->left, color);
	}

}

Animal *findMin(Animal *root) {
	Animal *temp;
	if (root == NULL) 
		return NULL;
	temp = root;
	while (temp->left != NULL) 
	{
		temp = temp->left;
	}
	return temp;
}
/*Given the ID of an animal, the function will remove it from the list*/
void deleteAnimal(Animal **treeAnimal,const char *id)
{
	int k;
	char tempID[200];
	if (*treeAnimal == NULL) return;
	if (strcmp((*treeAnimal)->id, id) > 0)
		deleteAnimal(&((*treeAnimal)->left), id);
	else if (strcmp((*treeAnimal)->id, id) < 0)
		deleteAnimal(&((*treeAnimal)->right), id);
	else {
		Animal *left = (*treeAnimal)->left;
		Animal *right = (*treeAnimal)->right;
		Animal *temp = *treeAnimal;
		if (!left && !right) {
			FREE((*treeAnimal)->type);
			FREE((*treeAnimal)->color);
			FREE((*treeAnimal)->name);
			FREE((*treeAnimal)->birthPlace);
			FREE(*treeAnimal);
			*treeAnimal = NULL;
			return;
		}
		else if (left && !right) {
			*treeAnimal = left;
			FREE(temp->type);
			FREE(temp->color);
			FREE(temp->name);
			FREE(temp->birthPlace);
			FREE(temp);
			return;
		}
		else if (!left && right) {
			*treeAnimal = right;
			FREE(temp->type);
			FREE(temp->color);
			FREE(temp->name);
			FREE(temp->birthPlace);
			FREE(temp);
			return;
		}
		else {
			temp = findMin(right); /*need to swapp ALL the info between them*/
			strcpy(tempID, (*treeAnimal)->id);
			strcpy((*treeAnimal)->id, temp->id);
			strcpy(temp->id, tempID);
	



			(*treeAnimal)->name = (char *)realloc((*treeAnimal)->name, strlen(temp->name));
			strcpy((*treeAnimal)->name, temp->name);


			(*treeAnimal)->type = (char *)realloc((*treeAnimal)->type, strlen(temp->type));
			strcpy((*treeAnimal)->type, temp->type);

			for (k = 0; k < (*treeAnimal)->numOfChildren; k++)
			{
				temp->idOfChildren[k][0] = (*treeAnimal)->idOfChildren[k][0];
				strcpy(*((*treeAnimal)->idOfChildren + k), *(temp->idOfChildren + k));
			}
			(*treeAnimal)->numOfChildren = (temp->numOfChildren);
			(*treeAnimal)->birthday.day = temp->birthday.day;
			(*treeAnimal)->birthday.month = temp->birthday.month;
			(*treeAnimal)->birthday.year = temp->birthday.year;

	
			(*treeAnimal)->color = (char *) realloc((*treeAnimal)->color, strlen(temp->color));
			strcpy((*treeAnimal)->color, temp->color);

			(*treeAnimal)->birthPlace = (char *)realloc((*treeAnimal)->birthPlace, strlen(temp->birthPlace));
			strcpy((*treeAnimal)->birthPlace, temp->birthPlace);
			(*treeAnimal)->dailyMeals = temp->dailyMeals;
			(*treeAnimal)->healthStat = temp->healthStat;

			

			strcpy((*treeAnimal)->foodType, temp->foodType);
			deleteAnimal(&((*treeAnimal)->right), tempID);
		}
	}
}


/*Deletes all animals in the currect list*/
void deleteAllAnimals(Animal **treeAnimal)
{
	if ((*treeAnimal) == NULL)
	{
		printf("list was emptied\n");
		return;
	}
	deleteAllAnimals(&((*treeAnimal)->right));
	deleteAllAnimals(&((*treeAnimal)->left));
	FREE((*treeAnimal)->type);
	FREE((*treeAnimal)->color);
	FREE((*treeAnimal)->name);
	FREE((*treeAnimal)->birthPlace);
	FREE(*treeAnimal);
	(*treeAnimal) = NULL;
}




/*Gets the list of animals and food types, for every barcode of food from each food type, 
the function will repeatedly go through the animals list to check how much and how many have that same barcode of food type
and will add it up, the three that were seen the most will be displayed as the three most popular types of food */
void threePopularFoods(Animal **treeAnimal, FoodType **treeFood)
{
	Animal *tempAnimal = (*treeAnimal);
	FoodType *tempFood = (*treeFood);
	BarcodeCount first, second, third;
	first.count = 0;
	second.count = 0;
	third.count = 0;
	strcpy(first.barcode, "not set");
	strcpy(second.barcode, "not set");
	strcpy(third.barcode, "not set");
	insertPopularFood(&first, &second, &third, tempAnimal, tempFood);

	if (strcmp(first.barcode, "not set") == 0 || strcmp(second.barcode, "not set") == 0 || strcmp(third.barcode, "not set") == 0) {
		printf("Not enough different kinds of food to compare");
		return;
	}
	printf("the three popluar foods is :\n");
	printf("First place: \nBarcode: %s \nnumber consumed:%d\n ", first.barcode, first.count);
	printf("Second place: \nBarcode: %s \nnumber consumed:%d\n ", second.barcode, second.count);
	printf("Third place : \nBarcode: %s \nnumber consumed:%d\n ", third.barcode, third.count);
}

void insertPopularFood(BarcodeCount *first, BarcodeCount *second, BarcodeCount *third, Animal *treeAnimal, FoodType *treeFood) {
	int cnt = 0;
	if (treeFood == NULL)
		return;
	cnt = countDailyMealsOfAnimals_REC(treeAnimal, treeFood->barCode);
	if (first->count < cnt && second->count < cnt && third->count < cnt)
	{
		if (first->count != 0)
		{
			third->count = second->count;
			strcpy(third->barcode, second->barcode);
			second->count = first->count;
			strcpy(second->barcode, first->barcode);
		}
		first->count = cnt;
		strcpy(first->barcode, treeFood->barCode);
	}
	if (second->count < cnt && third->count < cnt && first->count > cnt)
	{
		if (second->count != 0)
		{
			third->count = second->count;
			strcpy(third->barcode, second->barcode);
		}
		second->count = cnt;
		strcpy(second->barcode, treeFood->barCode);
	}
	if (third->count < cnt && second->count > cnt && first->count > cnt)
	{
		third->count = cnt;
		strcpy(third->barcode, treeFood->barCode);
	}
	insertPopularFood(first, second, third, treeAnimal, treeFood->right);
	insertPopularFood(first, second, third, treeAnimal, treeFood->left);

}

int countDailyMealsOfAnimals_REC(Animal *animal, const char *barcode)
{
	if (animal == NULL)
		return 0;

	if (strcmp(animal->foodType, barcode) == 0) {
		return  animal->dailyMeals + countDailyMealsOfAnimals_REC(animal->right, barcode) + countDailyMealsOfAnimals_REC(animal->left, barcode);

	}
	return 0 + countDailyMealsOfAnimals_REC(animal->right, barcode) + countDailyMealsOfAnimals_REC(animal->left, barcode);;
}
/*Simple function that displays an animal*/
void displayAnimal(Animal  **animalList)
{
	int k;
	if ((*animalList) == NULL) return;
	printf("Type: %s\n", (*animalList)->type);
	printf("Color: %s\n", (*animalList)->color);
	printf("Name: %s\n", (*animalList)->name);
	printf("ID: %s\n", (*animalList)->id);
	printf("Birthday:");
	displayDate(&((*animalList)->birthday));
	printf("Birth place: %s\n", (*animalList)->birthPlace);
	printf("Heath stat: %d\n", (*animalList)->healthStat);
	printf("Number of children: %d\n", (*animalList)->numOfChildren);
	for (k = 0; k < (*animalList)->numOfChildren; k++)
	{
		printf("Id of num %d chilren:\n", k + 1);
		printf("ID: %s\n", (*animalList)->idOfChildren[k]);
	}
	printf("Food Type: %s\n", (*animalList)->foodType);
	printf("Daily meals: %d\n", (*animalList)->dailyMeals);
}

/*An additional GAN HI exclusive function, prints animals with the given date as their birthday*/
void printAnimalsForGivenBirthYear_REC(Animal **treeAnimal, Date dateGiven)
{
	if ((*treeAnimal) == NULL){
		return;
	}
	if (isEqualDate(dateGiven, (*treeAnimal)->birthday))
		displayAnimal(treeAnimal);
	printAnimalsForGivenBirthYear_REC(&((*treeAnimal)->right), dateGiven); 
	printAnimalsForGivenBirthYear_REC(&((*treeAnimal)->left), dateGiven);

}




/*Simple function that goes through the list of animals and displays each one*/
void displayAllAnimal(Animal  **animalList)
{
	Animal *temp = (*animalList);
	int k;
	if ((temp) == NULL) return;
	printf("Type: %s\n", (temp)->type);
	printf("Color: %s\n", (temp)->color);
	printf("Name: %s\n", (temp)->name);
	printf("ID: %s\n", (temp)->id);
	printf("Birthday:");
	displayDate(&((temp)->birthday));
	printf("Birth place: %s\n", (temp)->birthPlace);
	printf("Heath stat: %d\n", (temp)->healthStat);
	printf("Number of children: %d\n", (temp)->numOfChildren);
	for (k = 0; k < (temp)->numOfChildren; k++)
	{
		printf("Id of num %d chilren:\n", k + 1);
		printf("ID: %s\n", (temp)->idOfChildren[k]);
	}
	printf("Food Type: %s\n", (temp)->foodType);
	printf("Daily meals: %d\n\n\n", (temp)->dailyMeals);
	displayAllAnimal(&((temp)->right));
	displayAllAnimal(&((temp)->left));
}

double averageNumOfChildren(Animal **animal,int *cntAnimals,double *sumChild) /*cntAnimals = 0; sumChild = 0;*/
{
	if ((*animal) == NULL)
		return 0;
	++(*cntAnimals);
	(*sumChild) += (*animal)->numOfChildren;
	averageNumOfChildren(&((*animal)->right), (cntAnimals), sumChild);
	averageNumOfChildren(&((*animal)->left), (cntAnimals), sumChild);
	return (*sumChild) / (*cntAnimals);
}