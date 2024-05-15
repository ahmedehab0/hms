#include "../headers/staff.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <limits>
#include <cstdlib>

using namespace std;

const string FILE_NAME = "Staff.txt";
const string INDEX_FILE = "Staff_id.txt";

/**
 *addStaff - function that gets the Staff data and then save it in an external file
 *
 *return: void
 */
void Staff::addStaff() {
	//Person input function
	int offset;

	Person::input();

	cout << "Enter the Staff's department\n";
	cin.ignore();
	getline(cin, department);

	//write the Staff's data to a file
	ofstream staff(FILE_NAME, ios::app);
	if (!staff) {
		cout << "unable to save the patient's data, please try again\n";
		addStaff();
		Person::nextid--;
	}

	offset = staff.tellp();
	staff << id << "|" << first_name << "|" << last_name << "|" << age << "|"
		<< gender << "|" << address << "|" << phone_number << "|"
		<< department << "\n";

	//save the Staff id in a seperate file(primary indexing)
	ofstream index(INDEX_FILE, ios::app);
	if (!index) {
		return;
	}

	index << id << "|" << offset << "\n";

	staff.close();
	index.close();
	cout << "Staff record added successfully\n";
	cout << "Staff's id is " << id << "\n";
	return;
}

/**
 *getStaffById - search for a Staff by thier id and print their details
 *
 *return: void
 */
void Staff::getStaffById() {
	string line, pos, page, pgender, pid;
	int  indexKey, found = 0;
	ifstream staff(FILE_NAME);
	ifstream index(INDEX_FILE);

	cout << "Enter the Staff's id \n", cin >> indexKey;
	while (getline(index, line, '|')) {
		getline(index, pos);
		if (stoi(line) == indexKey) {
			staff.seekg(stoi(pos));
			getline(staff, pid, '|');
			getline(staff, first_name, '|');
			getline(staff, last_name, '|');
			getline(staff, page, '|');
			getline(staff, pgender, '|');
			getline(staff, address, '|');
			getline(staff, phone_number, '|');
			getline(staff, department, '|');

			found = 1;
			break;
		}
	}

	if (found) {
		cout << "first name\t\t" << "last name\t\t" << "age\t\t" << "gender\t\t"
			<< "address\t\t" << "phone_number\t\t" << "department\t\t\n";

		cout << first_name << "\t\t\t" << last_name << "\t\t\t" << page << "\t\t" << pgender << "\t\t"
			<< address << "\t\t" << phone_number << "\t\t\t" << department << "\t\t\t\n";
	}
	else {
		cout << "there is no staff with the id " << indexKey << " ,check the staff id and try again\n";
	}
	index.close();
	staff.close();
}

/**
 *geAllstaffs - function that prints all staffs in the history
 *
 *return: void
 */
void Staff::getAllStaffs() {
	string pid, page, pgender;
	int length = 1;
	ifstream staff(FILE_NAME);

	while (!staff.eof() && length <= 5) {
		getline(staff, pid, '|');
		getline(staff, first_name, '|');
		getline(staff, last_name, '|');
		getline(staff, page, '|');
		getline(staff, pgender, '|');
		getline(staff, address, '|');
		getline(staff, phone_number, '|');
		getline(staff, department, '|');

		cout << "id\t\t" << "first name\t\t" << "last name\t\t" << "age\t\t" << "gender\t\t"
			<< "address\t\t" << "phone_number\t\t" << "department\t\t\n";

		cout << pid << "\t\t" << first_name << "\t\t\t" << last_name << "\t\t\t" << page << "\t\t" << pgender << "\t\t"
			<< address << "\t\t" << phone_number << "\t\t\t" << department << "\t\t\t\n";
		++length;
	}
}

/**
 *updateStaff - method to update a Staff's information
 *
 *Return: void
 */
void Staff::updateStaff() {
	string key, pos, pid, page, pgender;
	int indexKey, found = 0, newpos, offset;
	ifstream index(INDEX_FILE);
	ifstream staff(FILE_NAME);
	ofstream temp("temp.txt", ios::app);
	ofstream tempindex("tempindex.txt", ios::app);

	cout << "Enter the Staff's id\n", cin >> indexKey;
	while (getline(index, key, '|')) {
		getline(index, pos, '|');
		if (stoi(key) == indexKey) {
			index.seekg(0);
			while (getline(index, key, '|')) {
				getline(index, pos);
				if (stoi(key) != indexKey) {
					staff.seekg(stoi(pos));
					getline(staff, pid, '|');
					getline(staff, first_name, '|');
					getline(staff, last_name, '|');
					getline(staff, page, '|');
					getline(staff, pgender, '|');
					getline(staff, address, '|');
					getline(staff, phone_number, '|');
					getline(staff, department, '|');

					newpos = temp.tellp();
					temp << pid << "|" << first_name << "|" << last_name << "|" << page << "|" << pgender << "|"
						<< address << "|" << phone_number << "|" << department << "\n";

					tempindex << pid << "|" << newpos << "\n";
				}
			}
			found++;
		}
	}

	if (found) {
		Person::input();

		cout << "Enter the staff's doctor's name\n";
		cin.ignore();
		getline(cin, department);
		offset = temp.tellp();
		temp << indexKey << "|" << first_name << "|" << last_name << "|" << age << "|"
			<< gender << "|" << address << "|" << phone_number << "|"
			<< department << "\n";

		tempindex << indexKey << "|" << offset << "\n";
		remove("staff.txt");
		rename("temp.txt", "staff.txt");
		remove("staff_id.txt");
		rename("tempindex.txt", "staff_id.txt");
		cout << "record updated successfully\n";
	}
	else {
		cout << "no record found\n";
	}
	index.close();
	staff.close();
	temp.close();
	tempindex.close();
}

/**
 *deletestaff - delete a staff record from history
 *
 *Return: void
 */
void Staff::deleteStaff() {
	string key, pos, pid, page, pgender;
	int found = 0, newpos, indexKey;
	ifstream index(INDEX_FILE);
	ifstream staff(FILE_NAME);
	ofstream temp("temp.txt", ios::app);
	ofstream tempindex("tempindex.txt", ios::app);

	cout << "Enter the staff's id\n", cin >> indexKey;
	while (getline(index, key, '|')) {
		getline(index, pos);
		if (stoi(key) != indexKey) {
			staff.seekg(stoi(pos));
			getline(staff, pid, '|');
			getline(staff, first_name, '|');
			getline(staff, last_name, '|');
			getline(staff, page, '|');
			getline(staff, pgender, '|');
			getline(staff, address, '|');
			getline(staff, phone_number, '|');
			getline(staff, department, '|');

			newpos = temp.tellp();
			temp << pid << "|" << first_name << "|" << last_name << "|" << page << "|" << pgender << "|"
				<< address << "|" << phone_number << "|" << department << "\n";
			tempindex << pid << "|" << newpos << "\n";
		}
		else {
			found = 1;
		}
	}
	index.close();
	staff.close();

	if (found) {
		remove("staff.txt");
		rename("temp.txt", "staff.txt");
		remove("staff_id.txt");
		rename("tempindex.txt", "staff_id.txt");
		cout << "staff with id: " << indexKey << "has been deleted successfully\n";
	}
	else {
		remove("temp.txt");
		remove("tempindex.txt");
		cout << "there is no staff with the id " << indexKey << " ,check the staff id and try again\n";
		deleteStaff();
	}
	temp.close();
	tempindex.close();
}


int main() {
	Staff staff;
	staff.addStaff();
	staff.getAllStaffs();
	return 0;
}
