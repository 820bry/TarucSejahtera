#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#pragma warning (disable:4996)
#pragma warning (disable:6031)

// Main Functions Start

void title();

// Main Functions End


// Visitors Module Start

typedef struct {
	int day;
	int month;
	int year;
} VisitorDate;

typedef struct {
	int hour;
	int minute;
} VisitorTime;

typedef struct {
	char name[20];
	char ic[15]; // ic in xxxxxx-xx-xxxx format
	char category; // use alphabets to determine category; determine later
	char venue[10];
	double temperature;
	VisitorDate date; // date: in DD/MM/YYYY format
	VisitorTime time; // time: in HH:MM format
} VisitorInfo;

void visitor();

// Additional Functions
void addVisitor();
void searchVisitor();
void modifyVisitor();
void displayVisitor();

void deleteVisitor();
void exportVisitor();

const char* getCategory(char);

// Visitors Module End

// Venue Module Start

//structure of date including day, month, year
typedef struct {
	int day, month, year;
}VenueDate;

//structure of Venue Information
typedef struct {
	char venueID[7];//ID of the venue
	char category;//Category of the venue
	char description[31];//Description of the venue
	int maxVisitors;//Maximum number of visitors available
	int numOfVisitors;//Current number of visitors in the venue
	VenueDate sanitization;//Last sanitization date of the venue
}VenueInfo;

void venue();

//function declaration
void addRecords();
void searchRecords();
void modifyRecords();
void displayRecords();
void deleteRecords();
void venueReport();
void category();
void menu();
void modifyMenu();
void reportType();
int reportOpt(int opt);
int menuOpt(int opt);

// Venue Module End

// Admin Module Start

void admin();

typedef struct {
	char id[5];
	char name[20];
	char position[20];
	char faculty[5];
	char password[10];
	char phone[13];
} AdminInfo;

void addAdmin();
void searchAdmin();
void modifyAdmin();
void displayAdmin();

void deleteAdmin();
void exportAdmin();

// Admin Module End

// Visits and Exits Module Start

void visitsExits();

typedef struct {
	int day, month, year;
} VisitDate;

typedef struct {
	int hour, minute;
} VisitTime;

typedef struct {
	VisitDate date;
	VisitTime startTime;
	VisitTime endTime;
	char visitorIC[15];
	char venueID[7];
	double temp;
} VisitInfo;


void addVisit();
void searchVisit();
void modifyVisit();
void displayVisit();

void deleteVisit();
void exportVisit();

// Visits and Exits Module End