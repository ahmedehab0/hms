#include "../headers/Paitent.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <limits>
#include <cstdlib>

const string FILE_NAME = "patient.txt";
const string INDEX_FILE = "paitent_id.txt";

/**
 *addPatient - function that gets the patient data and then save it in an external file
 *
 *return: void
 */
void Paitent :: addPaitent() {
	//Person input function
	Person::input();

	//write the Paitent's data to a file
	ofstream paitent(FILE_NAME, ios::app);
	if (!paitent) {
		cout << "unable to save the patient's data, please try again\n";
		addPaitent();
		Person::nextid--;
	}
	
	offset = paitent.tellp();
	paitent << id << "|" << first_name << "|" << last_name << "|" << age << "|"
		<< gender << "|" << address << "|" << phone_number << "\n";

	//save the paitent id in a seperate file(primary indexing)
	ofstream index(INDEX_FILE, ios::app);
	if (!index) {
		return;	
	}
	
	index << id << "|" << offset << "\n";

	paitent.close();
	index.close();
	cout << "patient record added successfully\n";
	cout << "paitent's id is " << id << "\n";
	return;
}

/**
 *getPaitentById - search for a paitent by thier id and print their details
 *
 *return: void 
 */
void Paitent :: getPaitentById() {
	string line, pos, page, pgender, pid;
	int  indexKey, found = 0;
	ifstream paitent(FILE_NAME);
	ifstream index(INDEX_FILE);

	cout << "Enter the paitent's id \n", cin >> indexKey;
	while (getline(index, line, '|')) {
		getline(index, pos);
		if (stoi(line) == indexKey) {
			paitent.seekg(stoi(pos));
			getline(paitent, pid, '|');	
			getline(paitent, first_name, '|');
			getline(paitent, last_name, '|');
			getline(paitent, page, '|');
			getline(paitent, pgender, '|');
			getline(paitent, address, '|');
			getline(paitent, phone_number, '|');

			found = 1;
			break;
		}
	}

	if (found) {
		cout << "first name\t\t" << "last name\t\t" << "age\t\t" << "gender\t\t" 
			<< "address\t\t" << "phone_number\t\t\n";
		
		cout << first_name << "\t\t\t" << last_name << "\t\t\t" << page << "\t\t" << pgender << "\t\t" 
			<< address << "\t\t" << phone_number << "\t\t\t\n";
	} else {
		cout << "there is no paitent with the id " << indexKey << " ,check the paitent id and try again\n";
	}
	index.close();
	paitent.close();	
}
/**
 *search - search for a paitent by id
 *
 *Return: true if found, false if not
 */
bool Paitent :: search() {
	int found = 0, indexKey;
	string line, pos;
	ifstream index(INDEX_FILE);

	cout << "Enter the paitent's id \n", cin >> indexKey;
	while (getline(index, line, '|')) {
		getline(index, pos);
		if (stoi(line) == indexKey) {
			found = 1;
			break;
		}
	}
	if (found) {
		return true;
	}
	return false;
}

/**
 *geAllPaitents - function that prints all paitents in the history
 *
 *return: void
 */
void Paitent :: getAllPaitents() {
	string pid, page, pgender;
	int length = 1;
	ifstream paitent(FILE_NAME);

	while (!paitent.eof() && length <= 5) {
		getline(paitent, pid, '|');	
		getline(paitent, first_name, '|');
		getline(paitent, last_name, '|');
		getline(paitent, page, '|');
		getline(paitent, pgender, '|');
		getline(paitent, address, '|');
		getline(paitent, phone_number, '|');

		cout << "id\t\t" << "first name\t\t" << "last name\t\t" << "age\t\t" << "gender\t\t" 
			<< "address\t\t" << "phone_number\t\t\n";
		
		cout << pid << "\t\t"<< first_name << "\t\t\t" << last_name << "\t\t\t" << page << "\t\t" << pgender << "\t\t" 
			<< address << "\t\t" << phone_number << "\t\t\t\n";
		++length;
	}
}

/**
 *updatePaitent - method to update a paitent's information
 *
 *Return: void
 */
void Paitent :: updatePaitent() {
	string key, pos, pid, page, pgender;
	int indexKey, found = 0, newpos;
	ifstream index(INDEX_FILE);
	ifstream paitent(FILE_NAME);
	ofstream temp("temp.txt", ios::app);
	ofstream tempindex("tempindex.txt", ios::app);

	cout << "Enter the paitent's id\n", cin >> indexKey;
	while (getline(index, key, '|')) {
		getline(index, pos, '|');
		if (stoi(key) == indexKey) {
			index.seekg(0);
			while (getline(index, key, '|')) {
				getline(index, pos);
				if (stoi(key) != indexKey) {
					paitent.seekg(stoi(pos));
					getline(paitent, pid, '|');	
					getline(paitent, first_name, '|');
					getline(paitent, last_name, '|');
					getline(paitent, page, '|');
					getline(paitent, pgender, '|');
					getline(paitent, address, '|');
					getline(paitent, phone_number, '|');
			
					newpos = temp.tellp();
					temp << pid << "|" << first_name << "|" << last_name << "|" << page << "|" << pgender << "|" 
						<< address << "|" << phone_number << "\n";

					tempindex << pid << "|" << newpos << "\n";
				}
			}
			found++;
		}
	}

	if (found) {
		Person::input();

		offset = temp.tellp();
		temp << indexKey << "|" << first_name << "|" << last_name << "|" << age << "|"
			<< gender << "|" << address << "|" << phone_number << "\n";
		
		tempindex << indexKey << "|" << offset << "\n";
		remove("patient.txt");
		rename("temp.txt", "patient.txt");
		remove("paitent_id.txt");
		rename("tempindex.txt", "paitent_id.txt");
		cout << "record updated successfully\n";
	} else {
		cout << "no record found\n";
	}
	index.close();
	paitent.close();
	temp.close();
	tempindex.close();
}

/**
 *deletePaitent - delete a paitent record from history
 *
 *Return: void
 */
void Paitent :: deletePaitent() {
	string key, pos, pid, page, pgender;
	int found = 0, newpos, indexKey;
	ifstream index(INDEX_FILE);
	ifstream paitent(FILE_NAME);
	ofstream temp("temp.txt", ios::app);
	ofstream tempindex("tempindex.txt", ios::app);

	cout << "Enter the paitent's id\n", cin >> indexKey;
	while (getline(index, key, '|')) {
		getline(index, pos);
		if (stoi(key) != indexKey) {
			paitent.seekg(stoi(pos));
			getline(paitent, pid, '|');	
			getline(paitent, first_name, '|');
			getline(paitent, last_name, '|');
			getline(paitent, page, '|');
			getline(paitent, pgender, '|');
			getline(paitent, address, '|');
			getline(paitent, phone_number, '|');
			
			newpos = temp.tellp();
			temp << pid << "|" << first_name << "|" << last_name << "|" << page << "|" << pgender << "|" 
				<< address << "|" << phone_number << "\n";
			tempindex << pid << "|" << newpos << "\n";
		} else {
			found = 1;
		}
	} 
	index.close();
	paitent.close();	

	if (found) {
		remove("patient.txt");
		rename("temp.txt", "patient.txt");
		remove("paitent_id.txt");
		rename("tempindex.txt", "paitent_id.txt");
		cout << "paitent with id: " << indexKey << "has been deleted successfully\n";
	} else {
		remove("temp.txt");
		remove("tempindex.txt");
		cout << "there is no paitent with the id " << indexKey << " ,check the paitent id and try again\n";
		deletePaitent();
	}
	temp.close();
	tempindex.close();
}
