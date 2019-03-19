#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

struct EachPart {
	string day, month, year;
	string assignment, category;
};

string currentDate();

void TheEvent();
void EditNameCount(const string);
void AddEvent(EachPart list[], int& size);
bool is_number(const string& s);
bool ValidDates(string month, string day, string year);




string n3 = "\n\n\n";

int dateorder = 1;

int reminderorder = 0;

string currentDate() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[7];
	tstruct = *localtime(&now);
	strftime(buf, 8, "%Y%m%d", &tstruct);
	return buf;
}

void TheEvent() {
	string EventAns1;
	cout << "Would you like to review or edit your reminders? (y/n)" << endl;
	getline(cin, EventAns1);
	if (EventAns1 == "n") {
		cout << "Hmm...";
		return;
	}
	else if (EventAns1 != "y") {
		perror("Invalid answer. Program will exit.");
		return;
	}
	ifstream infile("name.txt");
	EachPart TheList[20];
	int size = 0;
	string OneLine;
	while (getline(infile, OneLine)) {
		istringstream TheLine(OneLine);
		getline(TheLine, TheList[size].month, '\t');
		getline(TheLine, TheList[size].day, '\t');
		getline(TheLine, TheList[size].year, '\t');
		getline(TheLine, TheList[size].category, '\t');
		getline(TheLine, TheList[size].assignment, '\t');
		size++;
	}
	cout << n3;
	string todaydate = currentDate();

	
	string EventAns;
	while (EventAns != "6") {
		cout << n3 + "What would you like to do?\n"
			+ "1 = Check events.\n" + "2 = Add events.\n"
			+ "3 = Delete events.\n" + "4 = Exit.\n";
		getline(cin, EventAns);
		if (!(is_number(EventAns))) {

		}
		switch (stoi(EventAns)) {
		case 1: {
			CheckEvent(TheList, size);
		
			break;
		}
		case 2: {
			AddEvent(TheList, size);
			break;
		}
		case 3: {
			DeleteEvent(TheList, size);
			
			break;
		}
		default: {
			
			cout << "You gave a weird answer. You can try again.\n";
			break;
		}
		}

	}
	infile.close();

}

void CheckEvent(EachPart list[], int& size) {
	string checkAns;
	if (size == 0) {
		cout << "You currently have no events! Would you like to add some?(y/n)\n";
		getline(cin, checkAns);
		if (checkAns == "y") {
			AddEvent(list, size);
		}
		else {
			return;
		}
	}
}


void AddEvent(EachPart list[], int& size) {
	EachPart New;
	cout << n3 + "What is the name of this assignment?\n";
	getline(cin, New.assignment);
	cout << "What is the category of this assignment?\n";
	getline(cin, New.category);
	cout << "Month, day, year on EACH SEPARATE LINE\n";
	getline(cin, New.month); getline(cin, New.day); getline(cin, New.year);

	while (!(ValidDates(New.month, New.day, New.year))) {
		cout << "Invalide date." << New.month << "/" << New.day << "/" << New.year << "Do it again until it's right.\n";
		cout << "Enter your new date in these order: Month, day, year on EACH SEPARATE LINE\n";
		getline(cin, New.month); getline(cin, New.day); getline(cin, New.year);
	}
}
void DeleteEvent(EachPart list[], int& size) {
	if (size == 0) {
		cout << n3 + "There is nothing to delete. This function will stop";
		return;
	}
	string ItemToRemove;
	cout << n3 + "Which event would you like to remove?\n";
	int i = 0;
	cout << "0.\tNot remove anything\n";
	getline(cin, ItemToRemove);
	if (!(is_number(ItemToRemove))) {
		cout << "Wrong input. Will not delete.";
		return;
	}
	int index = stoi(ItemToRemove);
	if (index == 0) {
		cout << "Not removing anything\n";
		return;
	}
	for (int j = index - 1; j < size - 1; j++) {
		list[j] = list[j + 1];
	}
	size--;
	return;
}
bool is_number(const string& s) {
	int i = 0;
	while (s[i]) {
		if (!(isdigit(s[i]))) return false;
		i++;
	}
	return true;
}
	bool ValidDates(string month, string day, string year) {
		if (!(is_number(month) && is_number(day) && is_number(year))) {
			return false;
		}
		int day1 = stoi(day), year1 = stoi(year), month1 = stoi(month);
		if (day1 < 0)
			return false;
		if (year1 < 0)
			return false;
		switch (month1) {
		case 1: case 3: case 5:
		case 7: case 8: case 10:
		case 12:
			if (day1 > 31)
				return false;
			break;
		case 4: case 6:
		case 9: case 11:
			if (day1 > 30)
				return false;
			break;
		case 2:
			if (year1 % 4 == 0 && day1 > 29)
				return false;
			if (day1 > 28)
				return false;
			break;
		default:
			cout << "Try again\n";
			return false;
			break;
		}
		return true;
	}
