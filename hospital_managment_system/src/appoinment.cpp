#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include <cctype>
#include "../headers/Paitent.h"
#include "doctor.cpp"
using namespace std;
class Appointments 
{
private:
	static int nextId;
	int id;
	string AppointmentDate;
	Doctors doctor;
	string AppointmentTime;
	Paitent paitent;
public:
	Appointments() {
		id = nextId++;
	}
	void book_appointment()
	{
		char ans;
		string day, status, counter;
		int offset, booked = 0;
		ifstream app("appoinments.txt");
		ofstream book("booked.txt", ios::app);
		ofstream index("book_index.txt", ios::app);

		if (!app) {
			cout << "Error opening file\n";
			return;
		}

		cout << "is the paitent already registered (y:Yes || N: No)?\n";
		cin >> ans;
		if (toupper(ans) == 'N') {
			cout << "Register first\n";
			paitent.addPaitent();
		} else if (toupper(ans) == 'Y') {
			if (!paitent.search()) {
				cout << "couldn't find the paitent, try registering first\n";
				paitent.addPaitent();
			}
		}

		cout << "availble days\n\n\n";
		while (getline(app, counter, '|')) {
			getline(app, day, '|');
			getline(app, status);
			cout << counter << "- " << day << " ->\t" << status << "\n";
		}
	
		cout << "enter doctor name\n";
		getline(cin, doctor.first_name);
		cout << "enter patient Name\n";
		cin.ignore();
		getline(cin, paitent.first_name);

		cout << "Choose an availble appointment\n";
		cin >> AppointmentTime;
		
		while (stoi(AppointmentTime) < 1 && stoi(AppointmentTime) > 21) {
			cout << "choose an option from 1 to 21\n";
			cin >> AppointmentTime;
		}
		fstream appp("appoinments.txt", ios::in|ios::out);
		appp.seekg(0);
		while (getline(appp, counter, '|')) {
			getline(appp, day, '|');
			offset = appp.tellg();
			getline(appp, status);
			
			if (counter == AppointmentTime) {
				appp.seekp(offset);
				if (status == "  booked ") {
					cout << "appointment already booked\n";
				}
				appp << "  booked \n";
				booked = 1;
				break;
			}
		}
		if (booked) {
			if (!book) {
				cout << "Error opening file\n";
				return;
			}
			offset = book.tellp();
			book << id << "|" << doctor.first_name<< "|" << paitent.first_name << "|" << day << "\n";
			index << id << "|" << offset << "\n";
		}

		app.close();
		book.close();
		index.close();
	}
};

int Appointments :: nextId = 1;

int main() {
	Appointments app;
	app.book_appointment();
}
