#include "main.h"

void visitsExits()
{
	int choice;

	do {
		printf("Visits and Exits Management Module\n");
		printf("----------------------------------\n");
		printf("1. Add New Visit\n");
		printf("2. Search Visits\n");
		printf("3. Modify Visit Info\n");
		printf("4. Display Visit Entries\n");
		printf("5. Delete Visit Entry\n");
		printf("6. Export Visits List\n");
		printf("7. Exit Module\n");
		printf("Enter an option (1 to 7) : ");
		scanf("%d", &choice);
		rewind(stdin);

		switch (choice)
		{
		case 1:
			system("cls");
			addVisit();
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			searchVisit();
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			modifyVisit();
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			displayVisit();
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");
			deleteVisit();
			system("pause");
			system("cls");
			break;
		case 6:
			system("cls");
			exportVisit();
			system("pause");
			system("cls");
			break;
		case 7:
			break;
		default:
			printf("Invalid number entered. Please try again");
			system("pause");
			system("cls");
			break;
		}

	} while (choice != 7);
}

void addVisit()
{
	VisitInfo tmp;

	FILE* fptr;
	fptr = fopen("visits.dat", "ab");
	if (fptr == NULL)
	{
		printf("Error while opening data file");
		exit(-1);
	}

	printf("Add New Visit Entry\n");
	printf("-------------------\n");
	
	printf("Enter the date of visit (xx/xx/xxxx) : ");
	scanf("%d/%d/%d", &tmp.date.day, &tmp.date.month, &tmp.date.year);
	rewind(stdin);

	printf("\n");
	printf("Enter the time the visitor entered (xx:xx) : ");
	scanf("%d:%d", &tmp.startTime.hour, &tmp.startTime.minute);
	rewind(stdin);
	printf("Enter the time the visitor exited  (xx:xx) : ");
	scanf("%d:%d", &tmp.endTime.hour, &tmp.endTime.minute);
	rewind(stdin);
	printf("\n");

	printf("Enter the visitor's IC (xxxxxx-xx-xxxx) : ");
	scanf("%s", &tmp.visitorIC);
	rewind(stdin);

	printf("Enter the venue ID : ");
	scanf("%s", &tmp.venueID);
	rewind(stdin);

	printf("Enter the visitor's temperature : ");
	scanf("%lf", &tmp.temp);
	rewind(stdin);

	fwrite(&tmp, sizeof(VisitInfo), 1, fptr);

	fclose(fptr);

	printf("\nVisit entry added\n");

}

void searchVisit()
{
	VisitInfo tmp[20];
	int count = 0, resultCount = 0;
	VisitDate input;

	FILE* fptr;
	fptr = fopen("visits.dat", "rb");
	if (fptr == NULL)
	{
		printf("Error while reading data file");
		exit(-1);
	}
	while (fread(&tmp[count], sizeof(VisitInfo), 1, fptr) != 0)
	{
		count++;
	}
	fclose(fptr);

	printf("Enter a date to search for (xx/xx/xxxx) : ");
	scanf("%d/%d/%d", &input.day, &input.month, &input.year);
	rewind(stdin);
	printf("\n");

	printf("+----+------------+---------+---------+-----------------+---------+------+\n");
	printf("| No.|    Date    |   Time  |   Time  |        IC       |  Venue  | Temp.|\n");
	printf("|    |            | Entered |  Exited |                 |    ID   |      |\n");
	printf("+----+------------+---------+---------+-----------------+---------+------+\n");
	for (int i = 0; i < count; i++)
	{
		if (tmp[i].date.day == input.day && tmp[i].date.month == input.month && tmp[i].date.year == input.year)
		{
			printf("| %2d | %02d/%02d/%04d |  %02d:%02d  |  %02d:%02d  | %15s | %7s | %.1lf |\n", resultCount + 1, tmp[i].date.day, tmp[i].date.month, tmp[i].date.year, tmp[i].startTime.hour, tmp[i].startTime.minute, tmp[i].endTime.hour, tmp[i].endTime.minute, tmp[i].visitorIC, tmp[i].venueID, tmp[i].temp);
			printf("+----+------------+---------+---------+-----------------+---------+------+\n");
			resultCount++;
		}
	}

	if (resultCount == 0)
	{
		printf("No results found\n");
	}
	else {
		printf("%d result(s) found\n", resultCount);
	}
	printf("\n");
}

void modifyVisit()
{
	VisitInfo tmp[20];
	int count = 0, input, option;
	char confirm = 'N', inputIc[15], inputVenue[7];
	double inputTemp;

	VisitDate inputDate;
	VisitTime inputTime;

	FILE* fptr;
	fptr = fopen("visits.dat", "rb");
	if (fptr == NULL)
	{
		printf("Error while reading data file\n");
		exit(-1);
	}
	while (fread(&tmp[count], sizeof(VisitInfo), 1, fptr) != 0)
	{
		count++;
	}
	fclose(fptr);

	displayVisit();

	if (count == 0)
	{
		printf("No entries in data file\n");
	}
	else {
		printf("Enter the number for the visit entry you would like to delete (1 to %d) : ", count);
		scanf("%d", &input);
		rewind(stdin);

		// validation
		while (input < 1 || input > count)
		{
			printf("The number you entered does not exist. Try again (1 to %d) : ", count);
			scanf("%d", &input);
			rewind(stdin);
		}

		for (int i = 0; i < count; i++)
		{
			if (input == i + 1)
			{
				do {
					printf("Options:\n");
					printf("1. Date\n");
					printf("2. Time Entered\n");
					printf("3. Time Exited\n");
					printf("4. IC\n");
					printf("5. Venue ID\n");
					printf("6. Temperature\n");
					printf("7. Exit\n");
					printf("What would you like to modify (1-7) : ");
					scanf("%d", &option);
					rewind(stdin);
					printf("\n");

					switch (option)
					{
					case 1: // date
						printf("Enter a date (xx/xx/xxxx) : ");
						scanf("%d/%d/%d", &inputDate.day, &inputDate.month, &inputDate.year);
						rewind(stdin);
						printf("\n");
						printf("Old date: %02d/%02d/%04d\n", tmp[i].date.day, tmp[i].date.month, tmp[i].date.year);
						printf("New date: %02d/%02d/%04d\n", inputDate.day, inputDate.month, inputDate.year);
						printf("\n");
						printf("Confirm? (Y = yes, N = no) : ");
						scanf("%c", &confirm);
						rewind(stdin);

						while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
						{
							printf("Invalid character. Try again: ");
							scanf("%c", &confirm);
							rewind(stdin);
						}

						if (toupper(confirm) == 'Y')
						{
							tmp[i].date = inputDate;
							printf("Visitor date modified\n");

							system("pause");
							system("cls");
						}

						break;
					case 2: // time entered
						printf("Enter a time (xx:xx) : ");
						scanf("%d:%d", &inputTime.hour, &inputTime.minute);
						rewind(stdin);
						printf("\n");
						printf("Old entered time: %02d:%02d\n", tmp[i].startTime.hour, tmp[i].startTime.minute);
						printf("New entered time: %02d:%02d\n", inputTime.hour, inputTime.minute);
						printf("\n");
						printf("Confirm? (Y = yes, N = no) : ");
						scanf("%c", &confirm);
						rewind(stdin);

						while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
						{
							printf("Invalid character. Try again: ");
							scanf("%c", &confirm);
							rewind(stdin);
						}

						if (toupper(confirm) == 'Y')
						{
							tmp[i].startTime = inputTime;
							printf("Visitor entered time modified\n");

							system("pause");
							system("cls");
						}

						break;
					case 3: // time exit
						printf("Enter a time (xx:xx) : ");
						scanf("%d:%d", &inputTime.hour, &inputTime.minute);
						rewind(stdin);
						printf("\n");
						printf("Old exit time: %02d:%02d\n", tmp[i].endTime.hour, tmp[i].endTime.minute);
						printf("New exit time: %02d:%02d\n", inputTime.hour, inputTime.minute);
						printf("\n");
						printf("Confirm? (Y = yes, N = no) : ");
						scanf("%c", &confirm);
						rewind(stdin);

						while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
						{
							printf("Invalid character. Try again: ");
							scanf("%c", &confirm);
							rewind(stdin);
						}

						if (toupper(confirm) == 'Y')
						{
							tmp[i].endTime = inputTime;
							printf("Visitor exit time modified\n");

							system("pause");
							system("cls");
						}

						break;
					case 4: // ic
						printf("Enter IC : ");
						scanf("%[^\n]", &inputIc);
						rewind(stdin);
						printf("\n");
						printf("Old IC: %s\n", tmp[i].visitorIC);
						printf("New IC: %s\n", inputIc);
						printf("\n");
						printf("Confirm? (Y = yes, N = no) : ");
						scanf("%c", &confirm);
						rewind(stdin);

						while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
						{
							printf("Invalid character. Try again: ");
							scanf("%c", &confirm);
							rewind(stdin);
						}

						if (toupper(confirm) == 'Y')
						{
							strcpy(tmp[i].visitorIC, inputIc);
							printf("Visitor IC modified\n");

							system("pause");
							system("cls");
						}

						break;
					case 5: // venue id
						printf("Enter venue ID : ");
						scanf("%[^\n]", &inputVenue);
						rewind(stdin);
						printf("\n");
						printf("Old venue ID: %s\n", tmp[i].venueID);
						printf("New venue ID: %s\n", inputVenue);
						printf("\n");
						printf("Confirm? (Y = yes, N = no) : ");
						scanf("%c", &confirm);
						rewind(stdin);

						while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
						{
							printf("Invalid character. Try again: ");
							scanf("%c", &confirm);
							rewind(stdin);
						}

						if (toupper(confirm) == 'Y')
						{
							strcpy(tmp[i].venueID, inputVenue);
							printf("Venue ID modified\n");

							system("pause");
							system("cls");
						}

						break;
					case 6: // temperature
						printf("Enter temperature : ");
						scanf("%lf", &inputTemp);
						rewind(stdin);
						printf("\n");
						printf("Old IC: %.1lf\n", tmp[i].temp);
						printf("New IC: %.1lf\n", inputTemp);
						printf("\n");
						printf("Confirm? (Y = yes, N = no) : ");
						scanf("%c", &confirm);
						rewind(stdin);

						while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
						{
							printf("Invalid character. Try again: ");
							scanf("%c", &confirm);
							rewind(stdin);
						}

						if (toupper(confirm) == 'Y')
						{
							tmp[i].temp = inputTemp;
							printf("Visitor temperature modified\n");

							system("pause");
							system("cls");
						}

						break;
					case 7: // exit
						break;
					default:
						printf("Invalid option\n");
						system("pause");
						system("cls");
						break;
					}

					if (!option < 1 || !option >= 7)
					{
						fptr = fopen("visits.dat", "wb");
						
						for (int i = 0; i < count; i++)
						{
							fwrite(&tmp[i], sizeof(VisitInfo), 1, fptr);
						}

						fclose(fptr);
					}
				} while (option != 7);
			}
		}
	}
}

void displayVisit()
{
	VisitInfo tmp;
	int count = 0;

	FILE* fptr;
	fptr = fopen("visits.dat", "rb");
	if (fptr == NULL)
	{
		printf("Error while reading data file");
		exit(-1);
	}

	printf("+----+------------+---------+---------+-----------------+---------+------+\n");
	printf("| No.|    Date    |   Time  |   Time  |        IC       |  Venue  | Temp.|\n");
	printf("|    |            | Entered |  Exited |                 |    ID   |      |\n");
	printf("+----+------------+---------+---------+-----------------+---------+------+\n");

	while (fread(&tmp, sizeof(VisitInfo), 1, fptr) != 0)
	{
		printf("| %2d | %02d/%02d/%04d |  %02d:%02d  |  %02d:%02d  | %15s | %7s | %.1lf |\n", count + 1, tmp.date.day, tmp.date.month, tmp.date.year, tmp.startTime.hour, tmp.startTime.minute, tmp.endTime.hour, tmp.endTime.minute, tmp.visitorIC, tmp.venueID, tmp.temp);
		printf("+----+------------+---------+---------+-----------------+---------+------+\n");
		count++;
	}
	printf("%d entries recorded\n", count);
	fclose(fptr);
}

void deleteVisit()
{
	VisitInfo tmp[20];
	int count = 0, input;

	FILE* fptr;
	fptr = fopen("visits.dat", "rb");
	if (fptr == NULL)
	{
		printf("Error while reading data file\n");
		exit(-1);
	}
	while (fread(&tmp[count], sizeof(VisitInfo), 1, fptr) != 0)
	{
		count++;
	}
	fclose(fptr);

	displayVisit();

	if (count == 0)
	{
		printf("No entries in data file\n");
	}
	else {
		printf("Enter the number for the visit entry you would like to delete (1 to %d) : ", count);
		scanf("%d", &input);
		rewind(stdin);

		// validation
		while (input < 1 || input > count)
		{
			printf("The number you entered does not exist. Try again (1 to %d) : ", count);
			scanf("%d", &input);
			rewind(stdin);
		}

		fptr = fopen("visits.dat", "wb");
		for (int i = 0; i < count; i++)
		{
			if (input != i + 1)
			{
				fwrite(&tmp[i], sizeof(VisitInfo), 1, fptr);
			}
		}
		fclose(fptr);
		printf("Entry deleted\n");
	}
}

void exportVisit()
{
	VisitInfo tmp;

	FILE* fptr, * csv;
	fptr = fopen("visits.dat", "rb");
	csv = fopen("visitLog.csv", "w");
	if (fptr == NULL)
	{
		printf("Error while reading data file\n");
		exit(-1);
	}
	fprintf(csv, "date,time entered,time exited,visitor ic,venue id,temperature\n");
	while (fread(&tmp, sizeof(VisitInfo), 1, fptr) != 0)
	{
		fprintf(csv, "%02d/%02d/%04d,%02d:%02d,%02d:%02d,%s,%s,%.1lf\n", tmp.date.day, tmp.date.month, tmp.date.year, tmp.startTime.hour, tmp.startTime.minute, tmp.endTime.hour, tmp.endTime.minute, tmp.visitorIC, tmp.venueID, tmp.temp);
	}
	printf("CSV file successfully created\n");
	fclose(fptr);
	fclose(csv);
}