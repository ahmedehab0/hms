#include "../headers/Person.h"
#include <iostream>
#include <limits> // for numeric_limits
#include <ios>
#include <cctype>
#include <string>
using namespace std;

int Person :: nextid = 1;

Person::Person() {
	id = nextid++;
}

void Person::input() {
	cout << "Enter your first name\n";
	cin.ignore();
	getline(cin, first_name);
	cout << "Enter your last name\n";
	cin.ignore();
	getline(cin, last_name);
	cout << "Choose your Gender M/F\n";
	cin >> gender;
	gender = toupper(gender);
	while (gender != 'M' && gender != 'F') {
		cout << "you have to choose M(male) or F(female)\n";
		cin >> gender;
		gender = toupper(gender);
	}

	cout<< "Enter your age\n";
	while (!(cin >> age)) {
		cout << "enter a valid age\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cout << "Enter your address\n";
	cin.ignore();
	getline(cin, address);
	cout << "Enter your phone number with the country code\n";
	cin >> phone_number;
}
