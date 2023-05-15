#include "main.h"

void admin()
{
	int option;

	do {
		printf("Administrative Staff Module\n\n");

		printf("1. Register Staff\n");
		printf("2. Search Staffs\n");
		printf("3. Modify Staff Info\n");
		printf("4. List Staff\n");
		printf("5. Delete Staff Info\n");
		printf("6. Export Staff Data\n");
		printf("7. Exit Module\n");
		printf("Enter an option (1-7) : ");
		scanf("%d", &option);
		rewind(stdin);
		system("cls");

		switch (option)
		{
		case 1:
			addAdmin();
			system("pause");
			system("cls");
			break;
		case 2:
			searchAdmin();
			system("pause");
			system("cls");
			break;
		case 3:
			modifyAdmin();
			system("pause");
			system("cls");
			break;
		case 4:
			displayAdmin();
			system("pause");
			system("cls");
			break;
		case 5:
			deleteAdmin();
			system("pause");
			system("cls");
			break;
		case 6:
			exportAdmin();
			system("pause");
			system("cls");
			break;
		case 7:
			break;
		default:
			printf("Invalid option. Try again");
			system("pause");
			system("cls");
			break;
		}

	} while (option != 7);
}

void addAdmin()
{
	AdminInfo info;

	printf("Enter the ID of the staff (e.g. M123) : ");
	scanf("%s", &info.id);
	rewind(stdin);

	printf("Enter the name of the staff : ");
	scanf("%[^\n]", &info.name);
	rewind(stdin);

	printf("Enter the position of the staff : ");
	scanf("%[^\n]", &info.position);
	rewind(stdin);

	printf("Faculties:\n");
	printf("\tFAFB - Faculty of Accountancy, Finance and Business\n");
	printf("\tFOAS - Faculty of Applied Science\n");
	printf("\tFOCS - Faculty of Computing and Information Technology\n");
	printf("\tFOBE - Faculty of Built Environment\n");
	printf("\tFOET - Faculty of Engineering and Technology\n");
	printf("\tFCCI - Faculty of Communication and Creative Industries\n");
	printf("\tFSSH - Faculty of Social Science and Humanities\n");
	printf("Enter the faculty of the staff (e.g. FOCS) : ");
	scanf("%s", &info.faculty);

	printf("Enter a password : ");
	scanf("%s", &info.password);

	printf("Enter the phone number for the staff : ");
	scanf("%s", &info.phone);

	FILE* fptr;
	fptr = fopen("admin.txt", "a");

	if (fptr == NULL)
	{
		printf("Error while writing data into file");
		exit(-1);
	}

	fprintf(fptr, "%s|%s|%s|%s|%s|%s|\n", info.id, info.name, info.position, info.faculty, info.password, info.phone);
	printf("Staff info added successfully\n");
	fclose(fptr);
}

void searchAdmin()
{
	AdminInfo tmp[20], results[20];
	int count = 0, resultCount = 0, option;

	char input[20];

	FILE* fptr;
	fptr = fopen("admin.txt", "r");

	if (fptr == NULL)
	{
		printf("Error while reading data from file");
		exit(-1);
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|\n", &tmp[count].id, &tmp[count].name, &tmp[count].position, &tmp[count].faculty, &tmp[count].password, &tmp[count].phone) != EOF)
	{
		count++;
	}

	fclose(fptr);

	do {
		printf("Options\n");
		printf("\t1. Name\n");
		printf("\t2. Position\n");
		printf("\t3. Faculty\n");
		printf("\t4. Exit Search\n");
		printf("Enter an option to search by (1 to 4) : ");
		scanf("%d", &option);
		rewind(stdin);

		switch (option)
		{
		case 1: // name
			printf("Enter the name you want to search for: ");
			scanf("%[^\n]", &input);
			rewind(stdin);

			for (int i = 0; i < count; i++)
			{
				if (strcmp(input, tmp[i].name) == 0)
				{
					results[resultCount] = tmp[i];
					resultCount++;
				}
			}

			break;
		case 2: // position
			printf("Enter the position you want to search for: ");
			scanf("%[^\n]", &input);
			rewind(stdin);

			for (int i = 0; i < count; i++)
			{
				if (strcmp(input, tmp[i].position) == 0)
				{
					results[resultCount] = tmp[i];
					resultCount++;
				}
			}

			break;
		case 3: // faculty
			printf("\nFaculties:\n");
			printf("\tFAFB - Faculty of Accountancy, Finance and Business\n");
			printf("\tFOAS - Faculty of Applied Science\n");
			printf("\tFOCS - Faculty of Computing and Information Technology\n");
			printf("\tFOBE - Faculty of Built Environment\n");
			printf("\tFOET - Faculty of Engineering and Technology\n");
			printf("\tFCCI - Faculty of Communication and Creative Industries\n");
			printf("\tFSSH - Faculty of Social Science and Humanities\n");
			printf("Enter the faculty of the staff (e.g. FOCS) : ");
			scanf("%s", &input);

			for (int i = 0; i < count; i++)
			{
				if (strcmp(input, tmp[i].faculty) == 0)
				{
					results[resultCount] = tmp[i];
					resultCount++;
				}
			}

			break;
		case 4: // exit
			break;
		default:
			printf("\nInvalid option entered\n");
			system("pause");
			system("cls");
			break;
		}
	} while (option < 1 || option > 4);

	if (option != 4)
	{
		printf("\nSearch found %d result(s):\n\n", resultCount);

		printf("+------+----------------------+----------------------+---------+------------+-------------+\n");
		printf("|  ID  |         Name         |       Position       | Faculty |  Password  |  Phone No.  |\n");
		printf("+------+----------------------+----------------------+---------+------------+-------------+\n");
		for (int i = 0; i < resultCount; i++)
		{
			printf("| %4s | %20s | %20s | %7s | %10s | %11s |\n", results[i].id, results[i].name, results[i].position, results[i].faculty, results[i].password, results[i].phone);
			printf("+------+----------------------+----------------------+---------+------------+-------------+\n");
		}

		printf("\n");
	}

}

void modifyAdmin()
{
	AdminInfo tmp[20];
	char inputId[5];
	int count = 0, option;

	char input[20], cont = 'N', confirm;

	FILE* fptr;

	do {
		fptr = fopen("admin.txt", "r");
		if (fptr == NULL)
		{
			printf("Error while reading data from file.");
			exit(-1);
		}
		while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|\n", &tmp[count].id, &tmp[count].name, &tmp[count].position, &tmp[count].faculty, &tmp[count].password, &tmp[count].phone) != EOF)
		{
			count++;
		}
		fclose(fptr);

		displayAdmin();

		if (count == 0)
		{
			printf("Nothing to modify as there are no entries..\n");
		}
		else {

			printf("Enter the staff ID you would like to modify: ");
			scanf("%s", &inputId);
			rewind(stdin);

			printf("\n");
			for (int i = 0; i < count; i++)
			{
				if (strcmp(inputId, tmp[i].id) == 0)
				{
					do {
						printf("Options:\n");
						printf("\t1. ID\n");
						printf("\t2. Name\n");
						printf("\t3. Position\n");
						printf("\t4. Faculty\n");
						printf("\t5. Password\n");
						printf("\t6. Phone Number\n");
						printf("\t7. Exit\n");
						printf("Enter the value you would like to modify (1-7): ");
						scanf("%d", &option);
						rewind(stdin);

						printf("\n");

						switch (option)
						{
						case 1: // id
							printf("Current ID: %s\n\n", tmp[i].id);

							printf("Enter a new ID: ");
							scanf("%s", &input);
							rewind(stdin);

							printf("[%s] will be changed to [%s]\n", tmp[i].id, input);
							printf("Confirm modifications? (Y = yes, N = no) : ");
							scanf("%c", &confirm);
							rewind(stdin);

							// validation
							while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
							{
								printf("Invalid character. Please enter Y (for yes) or N (for no): ");
								scanf("%c", &confirm);
								rewind(stdin);
							}

							if (toupper(confirm) == 'Y')
							{
								strcpy(tmp[i].id, input);
								printf("ID updated\n");

								system("pause");
								system("cls");
							}

							break;
						case 2: // name
							printf("Current Name: %s\n\n", tmp[i].name);

							printf("Enter a new name: ");
							scanf("%[^\n]", &input);
							rewind(stdin);

							printf("[%s] will be changed to [%s]\n", tmp[i].name, input);
							printf("Confirm modifications? (Y = yes, N = no) : ");
							scanf("%c", &confirm);
							rewind(stdin);

							// validation
							while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
							{
								printf("Invalid character. Please enter Y (for yes) or N (for no): ");
								scanf("%c", &confirm);
								rewind(stdin);
							}

							if (toupper(confirm) == 'Y')
							{
								strcpy(tmp[i].name, input);
								printf("Name updated\n");

								system("pause");
								system("cls");
							}

							break;
						case 3: // position
							printf("Current Position: %s\n\n", tmp[i].position);

							printf("Enter a new position: ");
							scanf("%[^\n]", &input);
							rewind(stdin);

							printf("[%s] will be changed to [%s]\n", tmp[i].position, input);
							printf("Confirm modifications? (Y = yes, N = no) : ");
							scanf("%c", &confirm);
							rewind(stdin);

							// validation
							while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
							{
								printf("Invalid character. Please enter Y (for yes) or N (for no): ");
								scanf("%c", &confirm);
								rewind(stdin);
							}

							if (toupper(confirm) == 'Y')
							{
								strcpy(tmp[i].position, input);
								printf("Position updated\n");

								system("pause");
								system("cls");
							}

							break;
						case 4: // faculty
							printf("Current Faculty: %s\n\n", tmp[i].faculty);

							printf("\nFaculties:\n");
							printf("\tFAFB - Faculty of Accountancy, Finance and Business\n");
							printf("\tFOAS - Faculty of Applied Science\n");
							printf("\tFOCS - Faculty of Computing and Information Technology\n");
							printf("\tFOBE - Faculty of Built Environment\n");
							printf("\tFOET - Faculty of Engineering and Technology\n");
							printf("\tFCCI - Faculty of Communication and Creative Industries\n");
							printf("\tFSSH - Faculty of Social Science and Humanities\n");

							printf("Enter new faculty: ");
							scanf("%[^\n]", &input);
							rewind(stdin);

							printf("[%s] will be changed to [%s]\n", tmp[i].faculty, input);
							printf("Confirm modifications? (Y = yes, N = no) : ");
							scanf("%c", &confirm);
							rewind(stdin);

							// validation
							while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
							{
								printf("Invalid character. Please enter Y (for yes) or N (for no): ");
								scanf("%c", &confirm);
								rewind(stdin);
							}

							if (toupper(confirm) == 'Y')
							{
								strcpy(tmp[i].faculty, input);
								printf("Faculty updated\n");

								system("pause");
								system("cls");
							}

							break;
						case 5: // password
							printf("Current Password: %s\n\n", tmp[i].password);

							printf("Enter a new password: ");
							scanf("%[^\n]", &input);
							rewind(stdin);

							printf("[%s] will be changed to [%s]\n", tmp[i].password, input);
							printf("Confirm modifications? (Y = yes, N = no) : ");
							scanf("%c", &confirm);
							rewind(stdin);

							// validation
							while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
							{
								printf("Invalid character. Please enter Y (for yes) or N (for no): ");
								scanf("%c", &confirm);
								rewind(stdin);
							}

							if (toupper(confirm) == 'Y')
							{
								strcpy(tmp[i].password, input);
								printf("Password updated\n");

								system("pause");
								system("cls");
							}

							break;
						case 6: // phone number
							printf("Current Phone Number: %s\n\n", tmp[i].phone);

							printf("Enter a new phone number: ");
							scanf("%[^\n]", &input);
							rewind(stdin);

							printf("[%s] will be changed to [%s]\n", tmp[i].phone, input);
							printf("Confirm modifications? (Y = yes, N = no) : ");
							scanf("%c", &confirm);
							rewind(stdin);

							// validation
							while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
							{
								printf("Invalid character. Please enter Y (for yes) or N (for no): ");
								scanf("%c", &confirm);
								rewind(stdin);
							}

							if (toupper(confirm) == 'Y')
							{
								strcpy(tmp[i].phone, input);
								printf("Phone number updated\n");

								system("pause");
								system("cls");
							}

							break;
						case 7: // exit
							break;
						default:
							printf("Invalid option entered\n");
							system("pause");
							system("cls");

							break;
						}

						if (!option < 1 || !option >= 7)
						{
							fptr = fopen("admin.txt", "w");
							
							for (int i = 0; i < count; i++)
							{
								fprintf(fptr, "%s|%s|%s|%s|%s|%s|\n", tmp[i].id, tmp[i].name, tmp[i].position, tmp[i].faculty, tmp[i].password, tmp[i].phone);
							}

							fclose(fptr);
						}

					} while (option != 7);
					break;
				}
				else if (i + 1 == count)
				{
					printf("No staff ID found\n");
				}
			}

			printf("Do you want to continue modifying? (Y = yes, N = no) : ");
			scanf("%c", &cont);
			rewind(stdin);

			// validation
			while (toupper(cont) != 'Y' && toupper(cont) != 'N')
			{
				printf("Invalid character entered\n");
				system("pause");
				system("cls");

				printf("Do you want to continue modifying? (Y = yes, N = no) : ");
				scanf("%c", &cont);
				rewind(stdin);
			}

			system("cls");

		}


	} while (toupper(cont) == 'Y');
}

void displayAdmin()
{
	AdminInfo tmp;
	int count = 0;

	FILE* fptr;
	fptr = fopen("admin.txt", "r");
	if (fptr == NULL)
	{
		printf("Error while reading data from file.");
		exit(-1);
	}

	printf("+------+----------------------+----------------------+---------+------------+-------------+\n");
	printf("|  ID  |         Name         |       Position       | Faculty |  Password  |  Phone No.  |\n");
	printf("+------+----------------------+----------------------+---------+------------+-------------+\n");

	while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|\n", &tmp.id, &tmp.name, &tmp.position, &tmp.faculty, &tmp.password, &tmp.phone) != EOF)
	{
		printf("| %4s | %20s | %20s | %7s | %10s | %11s |\n", tmp.id, tmp.name, tmp.position, tmp.faculty, tmp.password, tmp.phone);
		printf("+------+----------------------+----------------------+---------+------------+-------------+\n");
		count++;
	}

	printf("\n%d staff(s) recorded\n", count);

	fclose(fptr);

}

void deleteAdmin()
{
	AdminInfo tmp[20];
	int count = 0;
	char inputId[5];

	FILE* fptr;
	fptr = fopen("admin.txt", "r");
	if (fptr == NULL)
	{
		printf("Error while reading data from file.");
		exit(-1);
	}
	while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|\n", &tmp[count].id, &tmp[count].name, &tmp[count].position, &tmp[count].faculty, &tmp[count].password, &tmp[count].phone) != EOF)
	{
		count++;
	}
	fclose(fptr);

	displayAdmin();

	if (count == 0)
	{
		printf("Nothing to delete as there are no entries..");
	}
	else {
		printf("Enter the staff ID you would like to delete: ");
		scanf("%[^\n]", &inputId);
		rewind(stdin);

		for (int i = 0; i < count; i++)
		{
			if (strcmp(inputId, tmp[i].id) == 0)
			{
				fptr = fopen("admin.txt", "w");

				for (int a = 0; a < count; a++)
				{
					if (strcmp(inputId, tmp[a].id) != 0)
					{
						fprintf(fptr, "%s|%s|%s|%s|%s|%s|\n", tmp[a].id, tmp[a].name, tmp[a].position, tmp[a].faculty, tmp[a].password, tmp[a].phone);
					}
				}

				fclose(fptr);
				printf("Entry deleted\n");
				break;
			}
			else if (i + 1 == count)
			{
				printf("No staff ID found\n");
			}
		}
	}
}

void exportAdmin()
{
	AdminInfo tmp;

	FILE* fptr, *output;
	fptr = fopen("admin.txt", "r");
	output = fopen("adminData.csv", "w");
	if (fptr == NULL)
	{
		printf("Error while reading data from file");
		exit(-1);
	}

	fprintf(output, "id,name,position,faculty,password,phone no\n");
	while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|\n", &tmp.id, &tmp.name, &tmp.position, &tmp.faculty, &tmp.password, &tmp.phone) != EOF)
	{
		fprintf(output, "%s,%s,%s,%s,%s,%s\n", tmp.id, tmp.name, tmp.position, tmp.faculty, tmp.password, tmp.phone);
	}

	printf("CSV file generated\n");

	fclose(fptr);
	fclose(output);
}