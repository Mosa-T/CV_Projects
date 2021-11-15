#include <stdio.h>
#include "DisplayMenu.h"


/*recieves the heads of each type from main, will pass them to be used*/
void DisplayMenu(Animal **treeAnimal, FoodType **treeFood, Employee **treeEmployee, LinkedEmployee **head)
{
	int option = 0;
	printf("Welcome\n");
	printf("pick the wanted option and then press enter:\n");
	while (option != 20)	/*loop to keep the user in the options menu*/
	{
		DisplayMenuOptions();
		scanf("%d", &option);
		if (option <0 || option > 20){
			printf("wrong input\n");
			continue;
		}
		switchOption(option, treeAnimal, treeFood, treeEmployee, head);
	}
}

/*Basic printf display of the main menu*/
void DisplayMenuOptions()
{
	printf("\nMain Menu:\n\n");
	printf("Animal options\n");
	printf("(1) Add new Animal\n");
	printf("(2) Animal number with given food kind\n");
	printf("(3) Animal number with given color\n");
	printf("(4) Three popular foods(note in order to display rankings you must first create both food and animal lists)\n");
	printf("(5) print animals for given birth year\n");
	printf("(6) to print average number of children\n");
	printf("(7) delete  Animal list\n");
	printf("(8) delete all Animal list\n\n");
	printf("Food options\n");
	printf("(9) Add new food\n");
	printf("(10) Delete food\n");
	printf("(11) Delete all food\n\n");
	printf("Employee options\n");
	printf("(12) Add new employee\n");
	printf("(13) find Employee\n");
	printf("(14) Delete employee\n");
	printf("(15) Delete all employees\n\n");
	printf("Display lists(note in order to display list you must first create it):\n");
	printf("(16) To display Animal list:\n");
	printf("(17) To display Food list:\n");
	printf("(18) To display Employee list:\n");
	printf("(19) Exit\n");
}

/*uses the three different types of lists for all the functions requested through the input "option" */
/*note that GAN_HI is defined so we get access to additional options								 */
void switchOption(int option, Animal **treeAnimal, FoodType **treeFood, Employee **treeEmployee, LinkedEmployee **head)
{
	Date date;
	char animalID[6];
	char givenBarcode[BARCODE_LENGTH + 1];
	char idEmp[ID_EMPLOYEE + 1];
	int temp1;
	double temp2;
	switch (option)
	{
	case (1) :
		printf("please enter ID of the Animal(5 digits):\n");
		scanf("%s", animalID);
		if (strlen(animalID) != 5){
			printf("Wrong input of id\n");
			exit(1);
		}
		addNewAnimal(treeAnimal, animalID);
		break;
	case (2) :
		printf("Number of animals with given food type is :%d\n\n", animalNumberWithGivenFoodKind(*treeAnimal));
		break;
	case (3) :
		printf("Number of animals with given colour: %d\n\n", animalNumberWithGivenColor(*treeAnimal));
		break;
	case (4) :
		threePopularFoods(treeAnimal, treeFood);
		break;
	case (5) :
		date_input(&date);
		printAnimalsForGivenBirthYear_REC(treeAnimal, date);
		break;
	case (6) :
		temp1 = 0;
		temp2 = 0;
		printf("%.2f", averageNumOfChildren(treeAnimal, &temp1, &temp2));
		break;
	case (7) :
		printf("please enter ID of the Animal(5 digits):\n");
		scanf("%s", animalID);
		if (strlen(animalID) != 5){
			printf("Wrong input of id\n");
			exit(1);
		}
		deleteAnimal(treeAnimal, animalID);
		break;
	case (8) :
		deleteAllAnimals(treeAnimal);
		break;
	case (9) :
		printf("enter Barcode(20 digits):\n");
		scanf("%s", givenBarcode);
		if (strlen(givenBarcode) != 20){
			printf("Wrong input of barcode\n");
			exit(1);
		}
		addNewFood(treeFood, givenBarcode);
		break;
	case (10) :
		printf("enter Barcode(20 digits):\n");
		scanf("%s", givenBarcode);
		if (strlen(givenBarcode) != 20){
			printf("Wrong input of barcode\n");
			exit(1);
		}
		deleteFood(treeFood, givenBarcode);
		break;
	case (11) :
		deleteAllFood(treeFood);
		break;
	case (12) :
		printf("enter id employee (9 digits):\n");
		scanf("%s", idEmp);
		if (strlen(idEmp) != 9){
			printf("Wrong input of barcode\n");
			exit(1);
		}
		addNewEmployee(treeEmployee, idEmp);
		break;
	case (13) :
		findEmployee(treeEmployee, head);
		displayLinkedList(head);
		deleteAllLinkedEmployee(head);
		break;
	case (14) :
		printf("enter id employee (9 digits):\n");
		scanf("%s", idEmp);
		if (strlen(idEmp) != 9){
			printf("Wrong input of barcode\n");
			exit(1);
		}
		deleteEmployee(treeEmployee, idEmp);
		break;
	case (15) :
		deleteAllEmployee(treeEmployee);
		break;
	case (16) :
		displayAllAnimal(treeAnimal);
		break;
	case (17) :
		displayFood(treeFood);
		break;
	case (18) :
		printf("\nInfo of employees:\n");
		printEmployee(treeEmployee);
		break;
	case (19) :
	    deleteAllEmployee(treeEmployee);
	    deleteAllFood(treeFood);
	    deleteAllAnimals(treeAnimal);
		exit(0);
		break;
	default:
		option = 0;
		break;
	}
}
