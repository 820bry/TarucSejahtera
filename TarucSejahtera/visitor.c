#include "main.h"

/*

Text reading and printing format:
%s|%s|%c|%s|%.2lf|%02d/%02d/%04d|%02d:%02d|
Name, IC, Category, Venue, Temperature, Date (Day, Month, Year), Time (Hour, Minute)

*/
void visitor() 
{

	int input;

	do {
		printf("Visitors Management Module\n");
		printf("==========================\n");
		printf("Options:\n");
		printf("1 - Add Visitor Entry\n");
		printf("2 - Search Visitors\n");
		printf("3 - Modify Visitor Entry\n");
		printf("4 - Display Visitors\n");
		printf("5 - Delete Visitor Entry\n");
		printf("6 - Export Visitor Data as CSV\n");
		printf("7 - Exit Module\n");

		printf("Please enter an option (1 to 7) : ");
		scanf("%d", &input);
		rewind(stdin);

		system("cls");

		switch (input)
		{
		case 1:
			addVisitor();
			system("pause");
			system("cls");
			break;
		case 2:
			searchVisitor();
			system("pause");
			system("cls");
			break;
		case 3:
			modifyVisitor();
			system("pause");
			system("cls");
			break;
		case 4:
			displayVisitor();
			system("pause");
			system("cls");
			break;
		case 5:
			deleteVisitor();
			system("pause");
			system("cls");
			break;
		case 6:
			exportVisitor();
			system("pause");
			system("cls");
			break;
		case 7:
			break;
		default:
			printf("Invalid option entered. Please try again.\n");
			system("pause");
			system("cls");
			break;
		}


	} while (input != 7);
}

void addVisitor()
{
	VisitorInfo input;

	FILE* fptr;

	// Start of file writing
	fptr = fopen("visitor.txt", "a");
	if (fptr == NULL)
	{
		printf("There was a problem trying to read visitor data.\n");
		exit(-1);
	}

	printf("Please enter the visitor's name: ");
	scanf("%[^\n]", &input.name);
	rewind(stdin);

	printf("Please enter the visitor's IC (in xxxxxx-xx-xxxx): ");
	scanf("%[^\n]", &input.ic);
	rewind(stdin);

	printf("\n");
	printf("Categories:\n");
	printf("- Student  : A\n");
	printf("- Lecturer : B\n");
	printf("- Staff    : C\n");
	printf("Please enter the category of the visitor: ");
	scanf("%c", &input.category);
	rewind(stdin);

	printf("Please enter the name of the venue: ");
	scanf("%[^\n]", &input.venue);
	rewind(stdin);

	printf("Please enter the temperature of the visitor: ");
	scanf("%lf", &input.temperature);
	rewind(stdin);

	printf("Please enter the date (in xx/xx/xxxx): ");
	scanf("%d/%d/%d", &input.date.day, &input.date.month, &input.date.year);
	rewind(stdin);

	printf("Please enter the time (in xx:xx): ");
	scanf("%d:%d", &input.time.hour, &input.time.minute);
	rewind(stdin);

	fprintf(fptr, "%s|%s|%c|%s|%.2lf|%02d/%02d/%04d|%02d:%02d|\n", input.name, input.ic, input.category, input.venue, input.temperature, input.date.day, input.date.month, input.date.year, input.time.hour, input.time.minute);

	printf("\nEntry successfully added.\n\n");

	fclose(fptr);
	// End of file writing
}

void searchVisitor()
{
	VisitorInfo tmp[20], results[20];
	int count = 0, resultCount = 0, searchBy;

	// user inputs
	char inputName[20], inputCategory, inputVenue[10];
	VisitorDate inputDate;

	FILE* fptr;
	fptr = fopen("visitor.txt", "r");

	if (fptr == NULL)
	{
		printf("There was a problem trying to read visitor data.\n");
		exit(-1);
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%lf|%d/%d/%d|%d:%d|\n", &tmp[count].name, &tmp[count].ic, &tmp[count].category, &tmp[count].venue, &tmp[count].temperature, &tmp[count].date.day, &tmp[count].date.month, &tmp[count].date.year, &tmp[count].time.hour, &tmp[count].time.minute) != EOF)
	{
		count++;
	}

	do {
		printf("Search by:\n");
		printf("1 - Visitor Name\n");
		printf("2 - Visitor Category\n");
		printf("3 - Venue Name\n");
		printf("4 - Date\n");
		printf("5 - Exit\n");

		printf("Please enter an option (1 to 5) : ");
		scanf("%d", &searchBy);
		rewind(stdin);

		printf("\n");

		switch (searchBy)
		{
		case 1: // search by name
			printf("Please enter the name you would like to search for (ignores capitalization): ");
			scanf("%[^\n]", &inputName);
			rewind(stdin);

			for (int i = 0; i < count; i++)
			{
				if (strcmp(inputName, tmp[i].name) == 0)
				{
					results[resultCount] = tmp[i];
					resultCount++;
				}
			}

			break;
		case 2: // search by category
			printf("Categories:\n");
			printf("- Student  : A\n");
			printf("- Lecturer : B\n");
			printf("- Staff    : C\n");
			printf("Please enter the category you would like to search for: ");
			scanf("%c", &inputCategory);
			rewind(stdin);

			for (int i = 0; i < count; i++)
			{
				if (inputCategory == tmp[i].category)
				{
					results[resultCount] = tmp[i];
					resultCount++;
				}
			}

			break;
		case 3: // search by venue
			printf("Please enter the venue you would like to search for (ignores capitalization): ");
			scanf("%[^\n]", &inputVenue);
			rewind(stdin);

			for (int i = 0; i < count; i++)
			{
				if (strcmp(inputVenue, tmp[i].venue) == 0)
				{
					results[resultCount] = tmp[i];
					resultCount++;
				}
			}

			break;
		case 4: // date and time
			printf("Please enter a specific date you want to search (in xx/xx/xxxx format) : ");
			scanf("%d/%d/%d", &inputDate.day, &inputDate.month, &inputDate.year);
			rewind(stdin);

			for (int i = 0; i < count; i++)
			{
				if (inputDate.day == tmp[i].date.day && inputDate.month == tmp[i].date.month && inputDate.year == tmp[i].date.year)
				{
					results[resultCount] = tmp[i];
					resultCount++;
				}
			}

			break;
		case 5: // exit
			break;
		default:
			printf("Invalid number entered.\n");
			system("pause");
			system("cls");
			break;
		}
	} while (searchBy <= 0 || searchBy >= 6);

	if (searchBy != 5)
	{
		printf("\n");

		printf("+----+----------------------+----------------+----------+------------+------+------------+-------+\n");
		printf("| No.|         Name         |       IC       | Category |    Venue   | Temp.|    Date    |  Time |\n");
		printf("+----+----------------------+----------------+----------+------------+------+------------+-------+\n");
		for (int i = 0; i < resultCount; i++)
		{
			printf("| %2d | %20s | %12s | %8s | %10s | %.1lf | %02d/%02d/%02d | %02d:%02d |\n", i + 1, results[i].name, results[i].ic, getCategory(results[i].category), results[i].venue, results[i].temperature, results[i].date.day, results[i].date.month, results[i].date.year, results[i].time.hour, results[i].time.minute);
			printf("+----+----------------------+----------------+----------+------------+------+------------+-------+\n");
		}
		printf("%d result(s) found.\n", resultCount);
		printf("\n");
	}
}

void displayVisitor()
{
	int count = 0;

	FILE* fptr;
	VisitorInfo tmp;

	fptr = fopen("visitor.txt", "r");
	if (fptr == NULL)
	{
		printf("There was a problem trying to read visitor data.\n");
		exit(-1);
	}

	printf("+----+----------------------+----------------+----------+------------+------+------------+-------+\n");
	printf("| No.|         Name         |       IC       | Category |    Venue   | Temp.|    Date    |  Time |\n");
	printf("+----+----------------------+----------------+----------+------------+------+------------+-------+\n");
	
	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%lf|%d/%d/%d|%d:%d|\n", &tmp.name, &tmp.ic, &tmp.category, &tmp.venue, &tmp.temperature, &tmp.date.day, &tmp.date.month, &tmp.date.year, &tmp.time.hour, &tmp.time.minute) != EOF) {
		printf("| %2d | %20s | %12s | %8s | %10s | %.1lf | %02d/%02d/%02d | %02d:%02d |\n", count + 1, tmp.name, tmp.ic, getCategory(tmp.category), tmp.venue, tmp.temperature, tmp.date.day, tmp.date.month, tmp.date.year, tmp.time.hour, tmp.time.minute);
		printf("+----+----------------------+----------------+----------+------------+------+------------+-------+\n");
		count++;
	}

	printf("\n");

	fclose(fptr);
}

void modifyVisitor()
{
	VisitorInfo tmp[20];	
	int count = 0, input;

	char inputName[20], inputIc[15], inputCategory, inputVenue[10];
	double inputTemp;
	VisitorDate inputDate;
	VisitorTime inputTime;

	FILE* fptr;
	fptr = fopen("visitor.txt", "r");

	if (fptr == NULL)
	{
		printf("There was a problem trying to read visitor data.\n");
		exit(-1);
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%lf|%d/%d/%d|%d:%d|\n", &tmp[count].name, &tmp[count].ic, &tmp[count].category, &tmp[count].venue, &tmp[count].temperature, &tmp[count].date.day, &tmp[count].date.month, &tmp[count].date.year, &tmp[count].time.hour, &tmp[count].time.minute) != EOF)
	{
		count++;
	}

	fclose(fptr);

	displayVisitor();

	printf("Please enter the number for the visitor entry you would like to modify : ");
	scanf("%d", &input);
	rewind(stdin);

	printf("\n");

	for (int i = 0; i < count; i++)
	{
		if (input == i + 1)
		{
			do
			{
				printf("Modify List:\n");
				printf("1 - Name\n");
				printf("2 - IC\n");
				printf("3 - Category\n");
				printf("4 - Venue\n");
				printf("5 - Temperature\n");
				printf("6 - Date\n");
				printf("7 - Time\n");
				printf("8 - Exit Modifying\n");

				printf("Please enter the data you would like to modify (1 to 8) : ");
				scanf("%d", &input);
				rewind(stdin);

				switch (input)
				{
				case 1: // name
					printf("Please enter a new name: ");
					scanf("%[^\n]", &inputName);
					rewind(stdin);

					strcpy(tmp[i].name, inputName);

					printf("Name successfully modified.\n");

					system("pause");
					system("cls");
					break;
				case 2: // ic
					printf("Please enter the new IC (in xxxxxx-xx-xxxx format) : ");
					scanf("%[^\n]", &inputIc);
					rewind(stdin);

					strcpy(tmp[i].ic, inputIc);

					printf("IC successfully modified.\n");

					system("pause");
					system("cls");

					break;
				case 3: // category
					printf("Categories:\n");
					printf("- Student  : A\n");
					printf("- Lecturer : B\n");
					printf("- Staff    : C\n");
					printf("Please enter the new category for the visitor: ");
					scanf("%c", &inputCategory);
					rewind(stdin);

					tmp[i].category = inputCategory;

					printf("Category successfully modified.\n");

					system("pause");
					system("cls");

					break;
				case 4: // venue
					printf("Please enter the new venue name: ");
					scanf("%[^\n]", &inputVenue);
					rewind(stdin);

					strcpy(tmp[i].venue, inputVenue);

					printf("Venue successfully modified.\n");

					system("pause");
					system("cls");

					break;
				case 5: // temperature
					printf("Please enter the new temperature for the visitor: ");
					scanf("%lf", &inputTemp);
					rewind(stdin);

					tmp[i].temperature = inputTemp;

					printf("Temperature successfully modified.\n");

					system("pause");
					system("cls");

					break;
				case 6: // date
					printf("Please enter the new date (in xx/xx/xxxx): ");
					scanf("%d/%d/%d", &inputDate.day, &inputDate.month, &inputDate.year);
					rewind(stdin);

					tmp[i].date = inputDate;

					printf("Date successfully modified.\n");

					system("pause");
					system("cls");

					break;
				case 7: // time
					printf("Please enter the time (in xx:xx): ");
					scanf("%d:%d", &inputTime.hour, &inputTime.minute);
					rewind(stdin);

					tmp[i].time = inputTime;

					printf("Time successfully modified.\n");

					system("pause");
					system("cls");

					break;
				case 8:
					break;
				default:
					printf("Invalid number/character entered.\n");
					system("pause");
					system("cls");
					break;
				}

				fptr = fopen("visitor.txt", "w");

				for (int i = 0; i < count; i++)
				{
					fprintf(fptr, "%s|%s|%c|%s|%.2lf|%02d/%02d/%04d|%02d:%02d|\n", tmp[i].name, tmp[i].ic, tmp[i].category, tmp[i].venue, tmp[i].temperature, tmp[i].date.day, tmp[i].date.month, tmp[i].date.year, tmp[i].time.hour, tmp[i].time.minute);
				}

				fclose(fptr);

			} while (input != 8);
			break;
		}
		else if (i + 1 == count) // end of record w/o match
		{
			printf("Invalid number/character entered.\n");
		}
	}

	fptr = fopen("visitor.txt", "w");

	for (int i = 0; i < count; i++)
	{
		fprintf(fptr, "%s|%s|%c|%s|%.2lf|%02d/%02d/%04d|%02d:%02d|\n", tmp[i].name, tmp[i].ic, tmp[i].category, tmp[i].venue, tmp[i].temperature, tmp[i].date.day, tmp[i].date.month, tmp[i].date.year, tmp[i].time.hour, tmp[i].time.minute);
	}

	fclose(fptr);

}

void deleteVisitor()
{
	VisitorInfo tmp[20];
	int count = 0, input;

	FILE* fptr;
	fptr = fopen("visitor.txt", "r");

	if (fptr == NULL)
	{
		printf("There was a problem trying to read visitor data.\n");
		exit(-1);
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%lf|%d/%d/%d|%d:%d|\n", &tmp[count].name, &tmp[count].ic, &tmp[count].category, &tmp[count].venue, &tmp[count].temperature, &tmp[count].date.day, &tmp[count].date.month, &tmp[count].date.year, &tmp[count].time.hour, &tmp[count].time.minute) != EOF) 
	{
		count++;
	}

	fclose(fptr);

	displayVisitor();

	printf("Please enter the number for the visitor entry you would like to delete : ");
	scanf("%d", &input);
	rewind(stdin);

	for (int i = 0; i < count; i++)
	{
		if (input == i + 1)
		{

			fptr = fopen("visitor.txt", "w");

			for (int a = 0; a < count; a++)
			{
				if (input != a + 1)
				{
					fprintf(fptr, "%s|%s|%c|%s|%.2lf|%02d/%02d/%04d|%02d:%02d|\n", tmp[a].name, tmp[a].ic, tmp[a].category, tmp[a].venue, tmp[a].temperature, tmp[a].date.day, tmp[a].date.month, tmp[a].date.year, tmp[a].time.hour, tmp[a].time.minute);
				}
			}

			fclose(fptr);
			printf("Record deleted.\n");
			break;
		}
		else if (i + 1 == count) // end of record w/o match
		{
			printf("Invalid number/character entered.\n");
		}
	}
}

void exportVisitor()
{
	VisitorInfo tmp;

	FILE* fptr, *csv;
	fptr = fopen("visitor.txt", "r");
	csv = fopen("visitorData.csv", "w");

	if (fptr == NULL)
	{
		printf("There was a problem trying to read visitor data.\n");
		exit(-1);
	}

	fprintf(csv, "name,ic,category,venue,temperature,date,time\n");
	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%lf|%d/%d/%d|%d:%d|\n", &tmp.name, &tmp.ic, &tmp.category, &tmp.venue, &tmp.temperature, &tmp.date.day, &tmp.date.month, &tmp.date.year, &tmp.time.hour, &tmp.time.minute) != EOF)
	{
		fprintf(csv, "%s,%s,%s,%s,%.1lf,%d/%d/%d,%d:%d\n", tmp.name, tmp.ic, getCategory(tmp.category), tmp.venue, tmp.temperature, tmp.date.day, tmp.date.month, tmp.date.year, tmp.time.hour, tmp.time.minute);
	}

	printf("CSV file generated.\n");

	fclose(fptr);
	fclose(csv);

}

const char* getCategory(char input)
{
	switch (input)
	{
	case 'A':
		return "Student";
		break;
	case 'B':
		return "Lecturer";
		break;
	case 'C':
		return "Staff";
		break;
	default:
		return "Unknown";
		break;
	}
}