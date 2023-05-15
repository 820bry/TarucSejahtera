#include "main.h"

void main()
{
	int input;

	title();

	printf("Welcome to TARUC Sejahtera!\n");
	printf("(Please ensure that the console window is maximized to avoid display issues.)\n");
	printf("\n");

	do {
		printf("Options:\n");
		printf("1 - Visitor Information Management Module\n");
		printf("2 - Venue Information Management Module\n");
		printf("3 - Administrative Staff Management Module\n");
		printf("4 - Visits and Exits Management Module\n");
		printf("5 - Exit Program\n");

		printf("Please enter an option (1 to 5) : ");
		scanf("%d", &input);
		rewind(stdin);

		system("cls");

		switch (input)
		{
		case 1: // visitor
			visitor();
			break;
		case 2: // venue
			venue();
			break;
		case 3: // admin
			admin();
			break;
		case 4: // visits & exits
			visitsExits();
			break;
		case 5:
			break;
		default:
			printf("Invalid option entered. Please try again.");
			system("pause");
			system("cls");
			break;
		}

	} while (input != 5);

}

void title()
{
	printf("               _____  _____  _____  _____  _____ \n");
	printf("              |_   _||  _  || __  ||  |  ||     |\n");
	printf("                | |  |     ||    -||  |  ||   --|\n");
	printf("                |_|  |__|__||__|__||_____||_____|\n");
	printf(" _____  _____     __  _____  _____  _____  _____  _____  _____ \n");
	printf("|   __||   __| __|  ||  _  ||  |  ||_   _||   __|| __  ||  _  |\n");
	printf("|__   ||   __||  |  ||     ||     |  | |  |   __||    -||     |\n");
	printf("|_____||_____||_____||__|__||__|__|  |_|  |_____||__|__||__|__|\n");

	printf("\n");
}