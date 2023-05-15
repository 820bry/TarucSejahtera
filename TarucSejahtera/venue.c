#include "main.h"

void venue() {//main function
	int opt = 0;
	char ans;

	do{
		menu();//runs the menu fucntion
		printf("\nEnter your option > ");
		scanf("%d", &opt);
		rewind(stdin);

		menuOpt(opt);

		printf("\nDo you still want to use other function of the program? ( Y = Yes and N = No) > ");
		scanf("%c", &ans);
		rewind(stdin);
		while (toupper(ans) != 'Y' && toupper(ans) != 'N') {
			printf("\nInvalid Input...\n");
			printf("\nDo you still want to use other function of the program? ( Y = Yes and N = No) > ");
			scanf("%c", &ans);
			rewind(stdin);
		}
		system("cls");
		if (toupper(ans) == 'N') {
			system("cls");
			printf("Thank you for using this program...\n");
		}
	} while (opt != 7 && toupper(ans) == 'Y');
}


void addRecords() {//add records function
	FILE* wptr;
	wptr = fopen("venue.dat", "ab");//Open file to append
	VenueInfo venue;//Structure variable for venue
	char ans;
	//Validation Variables


	//file checking validation
	if (wptr == NULL) {
		printf("File occurred error while opening...\n");
		exit(-1);
	}

	printf("Adding Venue Records\n");
	printf("--------------------\n");

	//loop of adding records
	do {//prompt for information of venue
		printf("Enter Venue ID (eg. Lab301) > ");
		scanf("%[^\n]", &venue.venueID);
		rewind(stdin);

		category();
		printf("Enter type of category (eg. A for Lab) > ");
		scanf("%c", &venue.category);
		rewind(stdin);
		while (toupper(venue.category) != 'A' && toupper(venue.category) != 'B' && toupper(venue.category) != 'C') {
			printf("\nInvalid Input...\n");
			category();
			printf("Enter type of category (eg. A for Lab) > ");
			scanf("%c", &venue.category);
			rewind(stdin);
		}

		printf("Enter the description of venue (eg. computer lab) > ");
		scanf("%[^\n]", &venue.description);
		rewind(stdin);

		printf("Enter the maximum number of visitors allowed > ");
		scanf("%d", &venue.maxVisitors);
		rewind(stdin);

		printf("Enter the current number of visitors in venue > ");
		scanf("%d", &venue.numOfVisitors);
		rewind(stdin);
		while (venue.numOfVisitors > venue.maxVisitors) {
			printf("\nInvalid number of current number of visitors input...\n");
			printf("\nEnter the current number of visitors in venue > ");
			scanf("%d", &venue.numOfVisitors);
			rewind(stdin);
		}

		printf("Enter the date of venue being sanitized\n");
		printf("Day   > ");
		scanf("%d", &venue.sanitization.day);
		rewind(stdin);
		while (venue.sanitization.day > 31) {
			printf("\nInvalid Day Entered...\n");
			printf("Input Day from the number of 1 to 31\n");
			printf("\nDay   > ");
			scanf("%d", &venue.sanitization.day);
			rewind(stdin);
		}

		printf("Month > ");
		scanf("%d", &venue.sanitization.month);
		rewind(stdin);
		while (venue.sanitization.month > 12) {
			printf("\nInvalid Month Entered...\n");
			printf("Input Month from the number of 1 to 12\n");
			printf("\nMonth > ");
			scanf("%d", &venue.sanitization.month);
			rewind(stdin);
		}

		printf("Year  > ");
		scanf("%d", &venue.sanitization.year);
		rewind(stdin);
		
		//write all the informations to file venue.dat
		fwrite(&venue, sizeof(VenueInfo), 1, wptr);
		
		printf("\nRecord Added Succesfully...\n");//print successful message

		printf("\nDo you still want to add another record ? (Y for yes, N for no) > ");
		scanf("%c", &ans);
		rewind(stdin);
		if (toupper(ans) != 'Y' && toupper(ans) != 'N') {//validation for user's choice
			printf("Invalid input...\n");
			printf("\nDo you still want to add another record ? (Y for yes, N for no) > ");
			scanf("%c", &ans);
			rewind(stdin);
		}
	} while (toupper(ans) != 'N');
	fclose(wptr);//Close file
}

void searchRecords() {//search record function
	FILE* rptr;
	rptr = fopen("venue.dat", "rb");//Open file to read
	VenueInfo venue[20];//structure of venue
	char venueID[7];//store temporary veneuID
	char ans;//user's input
	int found = 0;//variable for string compare
	int i = 0;//loop for scan
	int records = 0;//variable to store number of records

	if (rptr == NULL) {//file checking validation
		printf("File occurred error while opening...\n");
		exit(-1);
	}
	//loop for retrieving file information
	
	while (fread(&venue[i], sizeof(VenueInfo), 1, rptr) != 0){
		i++;
		records++;
	}
	fclose(rptr);//Close file

	//loop for searching
	do {
		printf("Searching Venue Records\n");
		printf("-----------------------\n");
		printf("Enter Venue ID > ");
		scanf("%s", &venueID);
		rewind(stdin);

		for (int i = 0; i < records; i++) {
			if (strcmp(venueID, venue[i].venueID ) == 0) {
				found = 1;
				printf("\nRecord Found...\n");
				category();
				printf("\nVenue ID             > %s\n", venue[i].venueID);
				printf("Venue Category       > %c\n", venue[i].category);
				printf("Venue Description    > %s\n", venue[i].description);
				printf("Nax Visitors         > %d\n", venue[i].maxVisitors);
				printf("Current visitors     > %d\n", venue[i].numOfVisitors);
				printf("Date of Sanitization > %d-%d-%d\n", venue[i].sanitization.day, venue[i].sanitization.month, venue[i].sanitization.year);
			}
		}
		if (!found) 
			printf("\nRecord Not Found...\n");
			
			printf("\nAny more record to search? (Y = Yes) > ");
			scanf("%c", &ans);
			rewind(stdin);
			while (toupper(ans) != 'Y' && toupper(ans) != 'N') {
				printf("Invalid Input...\n");
				printf("\nAny more record to search? (Y = Yes) > ");
				scanf("%c", &ans);
				rewind(stdin);
			}

	} while (toupper(ans) == 'Y');
}

void modifyRecords() {//modify records function
	FILE* rptr;
	FILE* wptr;
	rptr = fopen("venue.dat", "rb");//open file to read

	VenueInfo venue[20];
	char ans, cont;//variable to accept user's input
	char venueID[7];//variable to check for ID
	char newID[7], newCategory, newDescription[31];//variable to store new items
	int newMax, newCurrent, day, month, year;//variable to store new items
	int found = 0, opt;//variables for comparing ID and get user's option
	int i = 0;//variable for looping
	int records = 0;//variable to store number of records

	if (rptr == NULL) {//file checking validation
		printf("File occurred error while opening...\n");
		exit(-1);

	}

	while (fread(&venue[i], sizeof(VenueInfo), 1, rptr) != 0) {//read data in file and store it into structure
		i++;
		records++;
	}
	fclose(rptr);//close file

	//looping of modifying
	printf("Modifying Venue Records\n");
	printf("-----------------------\n");
	do {
		printf("Enter Venue ID > ");
		scanf("%[^\n]", &venueID);
		rewind(stdin);

		for (int i = 0; i < records; i++) {
			if (strcmp(venueID, venue[i].venueID) == 0) {
				found = 1;
				printf("\nRecord Found...\n");
				printf("\n");
				category();
				printf("\nVenue ID             > %s\n", venueID);
				printf("Venue Category       > %c\n", venue[i].category);
				printf("Venue Description    > %s\n", venue[i].description);
				printf("Nax Visitors         > %d\n", venue[i].maxVisitors);
				printf("Current visitors     > %d\n", venue[i].numOfVisitors);
				printf("Date of Sanitization > %d-%d-%d\n", venue[i].sanitization.day, venue[i].sanitization.month, venue[i].sanitization.year);
				printf("\n");

				//display Modify Options Menu
				modifyMenu();
				opt = 0;

				while (opt != 1 && opt != 2 && opt != 3 && opt != 4 && opt != 5 && opt != 6) {
					printf("\nChoose one of the option to modify > ");
					scanf("%d", &opt);
					rewind(stdin);
					//switch casse for user selection
					switch (opt) {
					case 1: {
						printf("Enter New Venue ID > ");
						scanf("%s", &newID);
						rewind(stdin);
						printf("Are you sure to update? (Y = Yes) > ");
						scanf("%c", &cont);
						rewind(stdin);

						if (toupper(cont) != 'Y') {
							printf("\nModification Unsuccessful...\n");
						}
						else {
							strcpy(venue[i].venueID, newID);
							wptr = fopen("venue.dat", "wb");
							for (i = 0; i < records; i++) {
								fwrite(&venue[i], sizeof(VenueInfo), 1, wptr);
							}
							fclose(wptr);
							printf("\nModification Successful...\n");
						}
						break;
					}
					case 2: {
						category();
						printf("Enter New Venue Category > ");
						scanf("%c", &newCategory);
						rewind(stdin);
						printf("Are you sure to update? (Y = Yes) > ");
						scanf("%c", &cont);
						rewind(stdin);

						if (toupper(cont) != 'Y') {
						printf("\nModification Unsuccessful...\n");
						}
						else {
							venue[i].category = newCategory;
							wptr = fopen("venue.dat", "wb");
							for (i = 0; i < records; i++) {
								fwrite(&venue[i], sizeof(VenueInfo), 1, wptr);
							}
							fclose(wptr);
							printf("\nModification Successful...\n");
						}
						break;
					}
					case 3: {
						printf("Enter New Venue Description > ");
						scanf("%[^\n]", &newDescription);
						rewind(stdin);
						printf("Are you sure to update? (Y = Yes) > ");
						scanf("%c", &cont);
						rewind(stdin);
						if (toupper(cont) != 'Y') {
							printf("\nModification Unsuccessful...\n");
						}
						else {
							strcpy(venue[i].description, newDescription);
							wptr = fopen("venue.dat", "wb");
							for (i = 0; i < records; i++) {
								fwrite(&venue[i], sizeof(VenueInfo), 1, wptr);
							}
							fclose(wptr);
							printf("\nModification Successful...\n");
						}
						break;
					}
					case 4: {
						printf("Enter New Venue Maximum Number of Visitors > ");
						scanf("%d", &newMax);
						rewind(stdin);
						printf("Are you sure to update? (Y = Yes) > ");
						scanf("%c", &cont);
						rewind(stdin);
						if (toupper(cont) != 'Y') {
							printf("\nModification Unsuccessful...\n");
						}
						else {
							venue[i].maxVisitors = newMax;
							wptr = fopen("venue.dat", "wb");
							for (i = 0; i < records; i++) {
								fwrite(&venue[i], sizeof(VenueInfo), 1, wptr);
							}
							fclose(wptr);
							printf("\nModification Successful...\n");
						}
						break;
					}
					case 5: {
						printf("Enter New Venue Current Visitors > ");
						scanf("%d", &newCurrent);
						rewind(stdin);
						printf("Are you sure to update? (Y = Yes) > ");
						scanf("%c", &cont);
						rewind(stdin);
						if (toupper(cont) != 'Y') {
							printf("\nModification Unsuccessful...\n");
						}
						else {
							venue[i].numOfVisitors = newCurrent;
							wptr = fopen("venue.dat", "wb");
							for (i = 0; i < records; i++) {
								fwrite(&venue[i], sizeof(VenueInfo), 1, wptr);
							}
							fclose(wptr);
							printf("\nModification Successful...\n");
						}
						break;
					}
					case 6: {
						printf("Enter New Venue Sanitization Date\n");
						printf("Day > ");
						scanf("%d", &day);
						rewind(stdin);

						printf("Month > ");
						scanf("%d", &month);
						rewind(stdin);

						printf("Year > ");
						scanf("%d", &year);
						rewind(stdin);

						printf("Are you sure to update? (Y = Yes) > ");
						scanf("%c", &cont);
						rewind(stdin);

						if (toupper(cont) != 'Y') {
							printf("\nModification Unsucessful...\n");
						}
						else {
							venue[i].sanitization.day = day;
							venue[i].sanitization.month = month;
							venue[i].sanitization.year = year;
							wptr = fopen("venue.dat", "wb");
							for (i = 0; i < records; i++) {
								fwrite(&venue[i], sizeof(VenueInfo), 1, wptr);
							}
							fclose(wptr);
							printf("\nModification Successful...\n");
						}
						break;

					}
					default: {
						printf("\nInvalid Input...\n");
						break;
					}
					}
				}
			}
		}
		if (found != 1)
			printf("\nRecord Not Found...\n");
			
		printf("\nDo you still want to modify others? (Y = Yes) > ");//prompt for user whether want to modify other data
		scanf("%c", &ans);
		rewind(stdin);

		while (toupper(ans) != 'Y' && toupper(ans) != 'N') {
			printf("\nInvalid Input...\n");
			printf("\nDo you still want to modify others? (Y = Yes) > ");//prompt for user whether want to modify other data
			scanf("%c", &ans);
			rewind(stdin);
		}

	} while (toupper(ans) == 'Y');
}

void displayRecords() {//display records function
	FILE* rptr;
	rptr = fopen("venue.dat", "rb");//Open file to read

	VenueInfo venue;//venue array with size of 20
	int i;//variable for looping
	int totalRecords = 0;//variable to store total number of records

	//file checking validation
	if (rptr == NULL) {
		printf("File occurred error while opening...\n");
		exit(-1);
	}
	//display table
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("|\t\t\t\t\t  Displaying Records of Every Venue     \t\t\t\t\t|\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");;
	printf("|%-10s | %-10s | %-31s | %-20s | %-17s | %-10s     |\n", "Venue ID", "Category", "Description", "Max No. of Visitors", "Current Visitors", "Date");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	while (fread(&venue, sizeof(VenueInfo), 1, rptr) != 0) {//read and print out all the data from the file
		printf("|%-10s | %-10c | %-31s | %-20d | %-17d | %-2d - %-2d- %-4d  |\n", venue.venueID, toupper(venue.category), venue.description, venue.maxVisitors, venue.numOfVisitors, venue.sanitization.day, venue.sanitization.month, venue.sanitization.year);
		totalRecords++;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("Total Numbers of Records is %d\n", totalRecords);

	fclose(rptr);//Close file

}

void deleteRecords() {//delete records function
	FILE* rptr;
	FILE* wptr;
	rptr = fopen("venue.dat", "rb");

	VenueInfo venue[20];
	int i = 0, records = 0;
	int found = 0;
	char ans, cont;
	char venueID[7];

	if (rptr == NULL) {
		printf("File occurred error while opening...\n");
		exit(-1);
	}

	while (fread(&venue[i], sizeof(VenueInfo), 1, rptr) != 0) {
		i++;
		records++;
	}
	
	fclose(rptr);

	do {
		printf("Deleting Venue Records\n");
		printf("----------------------\n");
		printf("Enter Venue ID > ");
		scanf("%[^\n]", &venueID);
		rewind(stdin);

		for (int i = 0; i < records; i++) {
			if (strcmp(venueID, venue[i].venueID) == 0) {
				found = 1;
				printf("\nRecord Found...\n");
				printf("\n");
				category();
				printf("\nVenue ID             > %s\n", venueID);
				printf("Venue Category       > %c\n", venue[i].category);
				printf("Venue Description    > %s\n", venue[i].description);
				printf("Nax Visitors         > %d\n", venue[i].maxVisitors);
				printf("Current visitors     > %d\n", venue[i].numOfVisitors);
				printf("Date of Sanitization > %d-%d-%d\n", venue[i].sanitization.day, venue[i].sanitization.month, venue[i].sanitization.year);
				printf("\n");

				printf("Are you sure to delete this record? (Y = Yes and N = No) > ");
				scanf("%c", &ans);
				rewind(stdin);

				switch (toupper(ans)) {
				case 'Y': {
					strcpy(venue[i].venueID, venue[i + 1].venueID);
					venue[i].category = venue[i + 1].category;
					strcpy(venue[i].description, venue[i + 1].description);
					venue[i].maxVisitors = venue[i + 1].maxVisitors;
					venue[i].numOfVisitors = venue[i + 1].numOfVisitors;
					venue[i].sanitization.day = venue[i + 1].sanitization.day;
					venue[i].sanitization.month = venue[i + 1].sanitization.month;
					venue[i].sanitization.year = venue[i + 1].sanitization.year;
					
					wptr = fopen("venue.dat", "wb");
					for (i = 0; i < (records - 1); i++) {
						fwrite(&venue[i], sizeof(VenueInfo), 1, wptr);
					}
					fclose(wptr);
					printf("\nRecord successfully Deleted...\n"); break;
				}
				case 'N': {
					printf("\nRecord Not Deleted...\n"); break;
				}
				default: {
					printf("\nInvalid Input...\n");
					printf("Are you sure to delete this record? ( Y = Yes and N = No) > ");
					scanf("%c", &ans);
					rewind(stdin); break;
				}
				}
			}
		}
		if (!found)
			printf("\nNo Recorded Found...\n");

		printf("\nDo you still want to delete other records? ( Y = Yes and N = No) > ");
		scanf("%c", &cont);
		rewind(stdin);

	} while (toupper(cont) == 'Y');
}
void venueReport() {//venue report displaying function
	char ans;
	int opt;

	printf("Venue Report\n");
	printf("------------\n");
	do {
		reportType();
		printf("\nChoose an option to view the type of report > ");
		scanf("%d", &opt);
		rewind(stdin);
		
		reportOpt(opt);//report option function
		
		printf("\nDo you still want to view other reports? ( Y = Yes and N = No) > ");
		scanf("%c", &ans);
		rewind(stdin);
		system("cls");

	} while (toupper(ans) == 'Y');
}

void category() {//category list
	printf("Type of Category\n");
	printf("A - Laboratory\n");
	printf("B - Classroom\n");
	printf("C - Lecture Hall\n");
}

void menu() {//menu
	printf("Options of Venue Information Module\n");
	printf("-----------------------------------\n");
	printf("1. Add Venue Records\n");
	printf("2. Search Venue Records\n");
	printf("3. Modify Venue Records\n");
	printf("4. Display Venue Records\n");
	printf("5. Delete Venue Records\n");
	printf("6. View Venue Reports\n");
	printf("7. Exit Module\n");
}

void modifyMenu() {//modify menu
	printf("Options of Modifying Venue Information\n");
	printf("--------------------------------------\n");
	printf("1. Modify Venue's ID\n");
	printf("2. Modify Venue's Category\n");
	printf("3. Modify Veneu's Description\n");
	printf("4. Modify Venue's Maximum Number of Visitors\n");
	printf("5. Modify Venue's Current Number of Visitors\n");
	printf("6. Modify Venue's Date of Sanitization\n");
}

void reportType() {//report type menu
	printf("Type of Reports\n");
	printf("---------------\n");
	printf("1. Venue's Visitors Attendance Report\n");
	printf("2. Venue's Sanitization Date Report\n");
}

int reportOpt(int opt) {//report option function
	FILE* rptr;

	VenueInfo venue;

	char status[30];
	int remain = 0;
	int day = 0, month = 0, year = 0;

	switch (opt) {
	case 1: {
		system("cls");
		rptr = fopen("venue.dat", "rb");
		if (rptr == NULL) {
			printf("File occurred error while opening...\n");
			exit(-1);
		}

		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("|\t\t\t\t\tDisplaying Venue's Visitors Attendance Report\t\t\t\t\t|\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("| %-10s | %-30s | %-30s | %-25s \t\t|\n", "Venue ID", "No. of Maximum Visitors", "No, of Visitors Attended", "No. of Visitors Absent");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		while (fread(&venue, sizeof(VenueInfo), 1, rptr) != 0) {
			//calculation of visitors absent
			remain = venue.maxVisitors - venue.numOfVisitors;
			printf("| %-10s | %-30d | %-30d | %-25d \t\t|\n", venue.venueID, venue.maxVisitors, venue.numOfVisitors, remain);
			printf("------------------------------------------------------------------------------------------------------------------------\n");
		}
		fclose(rptr);
		break;
	}
	case 2: {
		system("cls");
		rptr = fopen("venue.dat", "rb");
		if (rptr == NULL) {
			printf("File occurred error while opening...\n");
			exit(-1);
		}

		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("|\t\t\t\t\tDisplaying Venue's Sanitization Date Report\t\t\t\t\t|\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("| %-10s | %-35s | %-35s | %-15s \t\t|\n", "Venue ID", "Last Sanitization Date", "No. of Day of Not Sanitized", "Status");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		while (fread(&venue, sizeof(VenueInfo), 1, rptr) != 0) {

			//get current day's date from computer
			SYSTEMTIME t;
			GetLocalTime(&t);

			//calculation of day
			month = t.wMonth - venue.sanitization.month;
			year = t.wYear - venue.sanitization.year;
			day = (t.wDay - venue.sanitization.day) + (month * 31) + (year * 365);

			if (day > 1) {
				strcpy(status, "Not Safe");
			}
			else {
				strcpy(status, "Safe");
			}

			printf("| %-10s | %2d - %2d -%4d \t\t\t   | %3d \t\t\t\t | %-15s \t\t|\n", venue.venueID, venue.sanitization.day, venue.sanitization.month, venue.sanitization.year, day, status);
			printf("------------------------------------------------------------------------------------------------------------------------\n");
		}
		fclose(rptr);
		break;
	}
	default: {
		printf("\nInvalid Input...\n");
		break;
	}
	}
}

int menuOpt(int opt) {//menu option function

	switch (opt) {
	case 1: {system("cls"); addRecords(); break; }//clean the console and run addRecords function
	case 2: {system("cls"); searchRecords(); break; }//clean the console and run searchRecords function
	case 3: {system("cls"); modifyRecords(); break; }//clean the console and run modifyRecords function
	case 4: {system("cls"); displayRecords(); break; }//clean the console and run displayRecords function
	case 5: {system("cls"); deleteRecords(); break; }//clean the console and run deleteRecords function
	case 6: {system("cls"); venueReport(); break; }//clean the console and run venueReport function
	case 7: {//clean the console and exit the program
		break;
	}
	default: {//validation for the menu input
		printf("\nInvalid option...\n");
		break;
	}
	}
}