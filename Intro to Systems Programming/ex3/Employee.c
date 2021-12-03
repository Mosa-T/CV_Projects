#include "EMPLOYEE.h"
#include "COMMON.h"



/*To declare a new list was created we must set it, it is most comfortble to set it to NULL*/
void createEmployeeList(Employee **treeFood)
{
	(*treeFood) = NULL;
}


/*Adds new employee to the list*/
void addNewEmployee(Employee **treeEmployee,const char *id)
{
	Employee *newEmp = ALLOC(Employee, 1);
	if ((*treeEmployee) == NULL){
		newEmp = ALLOC(Employee, 1);
		(*treeEmployee) = newEmp;
		addNewEmployeeInput(&newEmp, id);
		newEmp->right = NULL;
		newEmp->left = NULL;
		return;
	}
	if (strcmp((*treeEmployee)->id, id) == 0)
		return;
	if (strcmp((*treeEmployee)->id, id) < 0){
		addNewEmployee(&((*treeEmployee)->right), id);
	}
	if (strcmp((*treeEmployee)->id, id) > 0){
		addNewEmployee(&((*treeEmployee)->left), id);
	}
	return;
}

/*gets input from the user into the newly declared employee*/
void addNewEmployeeInput(Employee **emp, const char *id)
{
	char temp[200];
	if ((*emp) == NULL)
	{
		printf("wrong input in addNewEmployeeInput\n");
		return;
	}

	printf("please input employee info\nname:\n");
	scanf("%s", temp);
	(*emp)->name = ALLOC(char, strlen(temp) + 1);
	strcpy((*emp)->name, temp);

	printf("last name:\n");
	scanf("%s", temp);
	(*emp)->lastName = ALLOC(char, strlen(temp) + 1);
	strcpy((*emp)->lastName, temp);
	strcpy(temp, id);
	if (strlen(temp) != ID_EMPLOYEE) {
		printf("ID already exists or isn't the correct length\n");
		exit(1);
	}
	strcpy((*emp)->id, temp);

	printf("Care for Animals:\n");
	scanf("%d", &((*emp)->careForAnimals));
	if ((*emp)->careForAnimals > 200 || (*emp)->careForAnimals < 0) {
		wrongInput();
		exit(1);
	}
	(*emp)->idOfAnimals = ALLOC(char *, (*emp)->careForAnimals);

	printf("Id of Animal\n");
	input_IDofAnimal(emp, (*emp)->careForAnimals);
	printf("Date of employement: ");
	date_input(&((*emp)->startOfEmplyoment));
}

/*Function used to help set the IDs of the animals that the employee is supervising */
void input_IDofAnimal(Employee **emp, int careForAnimals)
{
	char tempId[6];
	int j;
	for (j = 0; j < careForAnimals; j++)
	{
		printf("please enter ID of Animal in care and enter each time:\n");
		scanf("%s", tempId);
		*((*emp)->idOfAnimals + j) = ALLOC(char, (ID_ANIMAL + 1));
		strcpy(*((*emp)->idOfAnimals + j), tempId);
	}
}

Employee *findMinEmp(Employee *root) {
	Employee *temp;
	if (root == NULL)
		return NULL;
	temp = root;
	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp;
}


/*Given the barcode of an employee, the function will remove it from the list*/
void deleteEmployee(Employee **treeEmployee, const char *id)
{
	char tempID[200];
	int k,i;
	if (*treeEmployee == NULL) return;
	if (strcmp((*treeEmployee)->id, id) > 0)
		deleteEmployee(&((*treeEmployee)->left), id);
	else if (strcmp((*treeEmployee)->id, id) < 0)
		deleteEmployee(&((*treeEmployee)->right), id);
	else {
		Employee *left = (*treeEmployee)->left;
		Employee *right = (*treeEmployee)->right;
		Employee *temp = *treeEmployee;
		if (!left && !right) {
			FREE((*treeEmployee)->name);
			FREE((*treeEmployee)->lastName);
			for (i = 0; i < (*treeEmployee)->careForAnimals; i++) {
				FREE(*((*treeEmployee)->idOfAnimals + i));
			}
			FREE(*treeEmployee);
			*treeEmployee = NULL;
			return;
		}
		else if (left && !right) {
			*treeEmployee = left;
			FREE(temp->name);
			FREE(temp->lastName);
			for (i = 0; i < (temp)->careForAnimals; i++) {
				FREE(*((temp)->idOfAnimals + i));
			}
			FREE(temp);
			return;
		}
		else if (!left && right) {
			*treeEmployee = right;
			FREE(temp->name);
			FREE(temp->lastName);
			for ( i = 0; i < (temp)->careForAnimals; i++) {
				FREE(*((temp)->idOfAnimals + i));
			}
			FREE(temp);
			return;
		}
		else {
			temp = findMinEmp(right);
			strcpy(tempID, (*treeEmployee)->id);
			strcpy((*treeEmployee)->id, temp->id);
			strcpy(temp->id, tempID);

			(*treeEmployee)->name = (char *)realloc((*treeEmployee)->name, strlen(temp->name));
			strcpy((*treeEmployee)->name, temp->name);


			(*treeEmployee)->lastName = (char *)realloc((*treeEmployee)->lastName, strlen(temp->lastName));
			strcpy((*treeEmployee)->lastName, temp->lastName);
			
			(*treeEmployee)->idOfAnimals = (char **)realloc((*treeEmployee)->idOfAnimals, temp->careForAnimals);
			for (k = 0; k < (*treeEmployee)->careForAnimals; k++)
			{
				strcpy(*(((*treeEmployee)->idOfAnimals) + k), *((temp->idOfAnimals) + k));
			}
		
			(*treeEmployee)->careForAnimals = temp->careForAnimals;
			(*treeEmployee)->startOfEmplyoment.day = temp->startOfEmplyoment.day;
			(*treeEmployee)->startOfEmplyoment.month = temp->startOfEmplyoment.month;
			(*treeEmployee)->startOfEmplyoment.year = temp->startOfEmplyoment.year;
		
			deleteEmployee(&((*treeEmployee)->right), tempID);
		}
	}
}

/*Deletes all employees in the currect list*/
void deleteAllEmployee(Employee **treeEmployee)
{
	int i;
	if ((*treeEmployee) == NULL)
	{
		return;
	}
	deleteAllEmployee(&((*treeEmployee)->right));
	deleteAllEmployee(&((*treeEmployee)->left));
	FREE((*treeEmployee)->name);
	FREE((*treeEmployee)->lastName);
	for (i = 0; i < (*treeEmployee)->careForAnimals; i++)
	{
		FREE(*((*treeEmployee)->idOfAnimals + i));
	}
	FREE((*treeEmployee)->idOfAnimals);
	FREE((*treeEmployee));
	(*treeEmployee) = NULL;
}


/*Simple function that displays all employees*/
void printEmployee(Employee **emp)
{
	int k;
	Employee *temp = (*emp);
	if ((*emp) == NULL) return;
	printf("Name: %s\n", temp->name);
	printf("Last name: %s\n", temp->lastName);
	printf("ID: %s\n", temp->id);
	printf("Care for Animals: %d\n", temp->careForAnimals);
	for (k = 0; k < temp->careForAnimals; k++)
	{
		printf("Number of cared for animal: %d\n", k + 1);
		printf("ID: %s\n", temp->idOfAnimals[k]);
	}
	printf("start of employement: ");
	displayDate(&(temp->startOfEmplyoment));
	printEmployee(&(temp->right));
	printEmployee(&(temp->left));

}

void findEmployeeById(Employee **treeEmployee, const char *id)
{
	int k;
	Employee *temp = (*treeEmployee);
	if (*treeEmployee == NULL) return;
	if (strcmp((*treeEmployee)->id, id) > 0)
		findEmployeeById(&((*treeEmployee)->left), id);
	if (strcmp((*treeEmployee)->id, id) < 0)
		findEmployeeById(&((*treeEmployee)->right), id);
	if (strcmp((*treeEmployee)->id, id) == 0)
	{
		printf("Name: %s\n", temp->name);
		printf("Last name: %s\n", temp->lastName);
		printf("ID: %s\n", temp->id);
		printf("Care for Animals: %d\n", temp->careForAnimals);
		for (k = 0; k < temp->careForAnimals; k++)
		{
			printf("Number of cared for animal: %d\n", k + 1);
			printf("ID: %s\n", temp->idOfAnimals[k]);
		}
		printf("start of employement: ");
		displayDate(&(temp->startOfEmplyoment));
	}
}

void findEmployeeBycareForAnimals(Employee **treeEmp, int careForAnimals,LinkedEmployee **head)
{
	int k = 0;
	if ((*treeEmp) == NULL) return;

	if ((*treeEmp)->careForAnimals == careForAnimals){
		LinkedEmployee *newEmp = ALLOC(LinkedEmployee, 1);
		LinkedEmployee *temp = *head;
		LinkedEmployee *prev = NULL;
		newEmp->name = ALLOC(char, (strlen((*treeEmp)->name) + 1));
		newEmp->lastName = ALLOC(char, (strlen((*treeEmp)->lastName) + 1));
		newEmp->idOfAnimals = ALLOC(char *, (*treeEmp)->careForAnimals);
		strcpy(newEmp->name, (*treeEmp)->name);
		strcpy(newEmp->lastName, (*treeEmp)->lastName);
		for (k = 0; k < (*treeEmp)->careForAnimals; k++)
		{
			*(newEmp->idOfAnimals + k) = ALLOC(char, (ID_ANIMAL + 1));
			strcpy(*(newEmp->idOfAnimals + k), *((*treeEmp)->idOfAnimals + k));
		}
		newEmp->careForAnimals = (*treeEmp)->careForAnimals;
		newEmp->startOfEmplyoment.day = (*treeEmp)->startOfEmplyoment.day;
		newEmp->startOfEmplyoment.month = (*treeEmp)->startOfEmplyoment.month;
		newEmp->startOfEmplyoment.year = (*treeEmp)->startOfEmplyoment.year;
		strcpy(newEmp->id, (*treeEmp)->id);
		newEmp->next = NULL;
		if ((*head) == NULL)				/* in case the list is empty, we insert it into the first index */
		{
			(*head) = newEmp;
			(*head)->next = NULL;
			findEmployeeBycareForAnimals(&((*treeEmp)->right), careForAnimals, head);
			findEmployeeBycareForAnimals(&((*treeEmp)->left), careForAnimals, head);
			return;
		}
		while (temp && strcmp(newEmp->id, temp->id) > 0) {
			prev = temp;
			temp = temp->next;
		}
		if (prev == NULL) {
			temp = (*head);
			(*head) = newEmp;
			(*head)->next = temp;
			findEmployeeBycareForAnimals(&((*treeEmp)->right), careForAnimals, head);
			findEmployeeBycareForAnimals(&((*treeEmp)->left), careForAnimals, head);
			return;
		}
		prev->next = newEmp;
		newEmp->next = temp;
	}
	findEmployeeBycareForAnimals(&((*treeEmp)->right), careForAnimals, head);
	findEmployeeBycareForAnimals(&((*treeEmp)->left), careForAnimals, head);

}

void displayLinkedList(LinkedEmployee **emp)
{
	int k;
	LinkedEmployee *temp = (*emp);
	if ((*emp) == NULL) return;
	printf("Name: %s\n", temp->name);
	printf("Last name: %s\n", temp->lastName);
	printf("ID: %s\n", temp->id);
	printf("Care for Animals: %d\n", temp->careForAnimals);
	for (k = 0; k < temp->careForAnimals; k++)
	{
		printf("Number of cared for animal: %d\n", k + 1);
		printf("ID: %s\n", temp->idOfAnimals[k]);
	}
	printf("start of employement: ");
	displayDate(&(temp->startOfEmplyoment));
	displayLinkedList(&(temp->next));
}

void findEmployee(Employee **treeEmp, LinkedEmployee **head)
{
	int i;
	char tempID[ID_EMPLOYEE + 1];
	printf("please choose option how to find Employe:\n");
	printf("enter the number (1) to find by ID:\n");
	printf("enter the number (2) to find by how many animals are taken care by him the employee:\n");
	printf("enter the number (3) to return to the menu:\n");
	scanf("%d", &i);
	if (i == 1){
		printf("please enter the id(9 digits):\n");
		scanf("%s", tempID);
		if (strlen(tempID) != 9)
			exit(1);
		findEmployeeById(treeEmp, tempID);
		return;
	}
	if (i == 2)
	{
		printf("please enter the number care for animals:\n");
		scanf("%d", &i);
		if (i < 0)
			exit(1);
		findEmployeeBycareForAnimals(treeEmp, i, head);
		return;
	}
	if (i == 3)
	{
		return;
	}
}


void deleteAllLinkedEmployee(LinkedEmployee **head)
{
	int i;
	if ((*head) == NULL)
	{
		return;
	}
	deleteAllLinkedEmployee(&((*head)->next));
	FREE((*head)->name);
	FREE((*head)->lastName);
	for (i = 0; i < (*head)->careForAnimals; i++)
	{
		FREE(*((*head)->idOfAnimals + i));
	}
	FREE((*head));
	(*head) = NULL;
}