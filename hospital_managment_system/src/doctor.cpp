#include <iostream>
#include <string>
#include <fstream>
#include "../headers/Person.h"
using namespace std;
class Doctors :public Person
{
	/*
	*
	id
	string first_name;
	string last_name;
	char gender;
	int age;
	string address;
	string phone_number;
	*/
	string speciality;
public:
	void Insertdoctor()
	{
		input();
		cout << "Enter the doctor's speciality : \n";
		getline(cin,speciality);
		//---------------------------------------------
		ofstream indexfile = ofstream("primary.txt");
		if (!indexfile.is_open())
		{
			cout << "ERROR! index File can't open it.\n";
			return;
		}
		ofstream myfile=ofstream("doctors.txt");
		if (!myfile.is_open())
		{
			cout << "ERROR! can't open the file \n";
			return;
		}

		long long offset = myfile.tellp();
		indexfile << id << "|" << offset << endl;
		//----------------------------------------
		myfile.write((char*)&id, sizeof(int));
		myfile.put('|');
		//------------------------------
		myfile.write((char*)&first_name, first_name.length());
		myfile.put(' ');
		myfile.write((char*)&last_name, last_name.length());
		myfile.put('|');
		//----------------------------------
		myfile.write((char*)&gender, sizeof(char));
		myfile.put('|');
		//--------------------------------------
		myfile.write((char*)&age, sizeof(int));
		myfile.put('|');
		//--------------------------------
		myfile.write((char*)&address, address.length());
		myfile.put('|');
		//------------------------------------
		myfile.write((char*)&phone_number, phone_number.length());
		myfile.put('|');
		//-------------------------------
		myfile.write((char*)&speciality, speciality.length());
		myfile.put('|');
		//----------------------------------------
		myfile << endl;
		myfile.close();
		indexfile.close();
	}
	void searchByID() {

		long long ID,offset,i;
		cout << "Enter Id\n";
		cin >> ID;
		bool flag = false;
		//-------------------------------------------
		ifstream myfile = ifstream("Doctors.txt");
		if (!myfile.is_open())
		{
			cout << "ERROR! can't open the file \n";
			return;
		}
		ifstream indexfile = ifstream("primary.txt");
		if (!indexfile.is_open())
		{
			cout << "ERROR! index File can't open it.\n";
			return;
		}
		//-------------------------------------------
		indexfile.seekg(0, ios::beg);
		while (indexfile.getline((char*)&i, sizeof(int), '|'))
		{
			if (i == ID)
			{
				flag = true;
				indexfile >> offset;
				break;
			}
		}
		//--------------------------------------
		if (flag)
		{
			myfile.seekg(offset);
			myfile.getline((char*)&ID, sizeof(int), '|');//id
			myfile.getline((char*)&first_name, first_name.size(), ' ');//first_name
			myfile.getline((char*)&last_name, last_name.size(), '|');//last_name
			myfile.getline((char*)&gender, sizeof(char), '|');
			myfile.getline((char*)&age, sizeof(int), '|');
			myfile.getline((char*)&address, address.size(), '|');
			myfile.getline((char*)&phone_number, phone_number.size(), '|');
			myfile.getline((char*)&speciality, speciality.size(), '|');
			//--------------------------------------------------------
			cout << "ID : " << ID << endl;
			cout << "First_Name : " << first_name << endl;
			cout << "Last_Name : " << last_name << endl;
			cout << "Gender : " << gender << endl;
			cout << "Age : " << age << endl;
			cout << "Address : " << address << endl;
			cout << "Phone_number : " << phone_number << endl;
			cout << "Speciality : " << speciality << endl;
		}
		else
			cout << "NOT Found..!\n";
		myfile.close();
		indexfile.close();

	}
	void displayalldoctors()
	{
		ifstream myfile = ifstream("Doctors.txt");
		if (myfile.is_open())
		{
			myfile.seekg(0, ios::beg);
			int N = 5;
			int i;
			while (N)
			{
				myfile.getline((char*)&i,sizeof(int), '|');//id
				myfile.getline((char*)&first_name,first_name.size(), ' ');//first_name
				myfile.getline((char*)&last_name, last_name.size(), '|');//last_name
				myfile.getline((char*)&gender,sizeof(char), '|');
				myfile.getline((char*)&age, sizeof(int),'|');
				myfile.getline((char*)&address, address.size(), '|');
				myfile.getline((char*)&phone_number, phone_number.size(), '|');
				myfile.getline((char*)&speciality, speciality.size(), '|');
				//-------------------------------------------------------------
				cout << "ID : " << i << endl;
				cout << "First_Name : " << first_name << endl;
				cout << "Last_Name : " << last_name << endl;
				cout << "Gender : " << gender << endl;
				cout << "Age : " << age << endl;
				cout << "Address : " << address << endl;
				cout << "Phone_number : " << phone_number << endl;
				cout << "Speciality : " << speciality << endl;
				if (myfile.eof())
					break;
			}
			myfile.close();
		}
		else
			cout << "ERROR! can't open the file \n";
	}
	void deletedoctor()
	{
		string key, pos, pid, page, pgender;
		int found = 0, newpos, indexKey;
		ifstream index("primary.txt");
		ifstream  myfile("doctors.txt");
		ofstream temp("temp.txt", ios::app);
		ofstream tempindex("tempindex.txt", ios::app);

		cout << "Enter the paitent's id\n", cin >> indexKey;
		while (getline(index, key, '|')) {
			getline(index, pos);
			if (stoi(key) != indexKey) {
				myfile.seekg(stoi(pos));
				getline(myfile, pid, '|');
				getline(myfile, first_name, '|');
				getline(myfile, last_name, '|');
				getline(myfile, page, '|');
				getline(myfile, pgender, '|');
				getline(myfile, address, '|');
				getline(myfile, phone_number, '|');
				getline(myfile, speciality, '|');

				newpos = temp.tellp();
				temp << pid << "|" << first_name << "|" << last_name << "|" << page << "|" << pgender << "|"
					<< address << "|" << phone_number << "|" << speciality << "\n";
				tempindex << pid << "|" << newpos << "\n";
			}
			else {
				found = 1;
			}
		}
		index.close();
		myfile.close();

		if (found) {
			remove("patient.txt");
			rename("temp.txt", "patient.txt");
			remove("paitent_id.txt");
			rename("tempindex.txt", "paitent_id.txt");
			cout << "paitent with id: " << indexKey << "has been deleted successfully\n";
		}
		else {
			remove("temp.txt");
			remove("tempindex.txt");
			cout << "there is no paitent with the id " << indexKey << " ,check the paitent id and try again\n";
			deletedoctor();
		}
		temp.close();
		tempindex.close();
	}
	void Update()
	{
		string key, pos, pid, page, pgender;
		int indexKey, found = 0, newpos;
		//------------------------------------------------
		ifstream index("primary.txt");
		ifstream paitent("doctors.txt");
		ofstream temp("temp.txt", ios::app);
		ofstream tempindex("tempindex.txt", ios::app);
		//----------------------------------------------------
		cout << "Enter the speciality's id\n";
		cin >> indexKey;
		while (getline(index, key, '|'))
		{
			getline(index, pos, '|');
			if (stoi(key) == indexKey)
			{
				index.seekg(0);
				while (getline(index, key, '|'))
				{
					getline(index, pos);
					if (stoi(key) != indexKey)
					{
						paitent.seekg(stoi(pos));
						getline(paitent, pid, '|');
						getline(paitent, first_name, '|');
						getline(paitent, last_name, '|');
						getline(paitent, page, '|');
						getline(paitent, pgender, '|');
						getline(paitent, address, '|');
						getline(paitent, phone_number, '|');
						getline(paitent, speciality, '|');

						newpos = temp.tellp();
						temp << pid << "|" << first_name << "|" << last_name << "|" << page << "|" << pgender << "|"
							<< address << "|" << phone_number << "|" << speciality << "\n";

						tempindex << pid << "|" << newpos << "\n";
					}
				}
				found++;
			}
		}
		if (found)
		{
			Person::input();
			cout << "Enter the speciality's doctor's name\n";
			cin.ignore();
			getline(cin, speciality);
			int offset = temp.tellp();
			temp << indexKey << "|" << first_name << "|" << last_name << "|" << age << "|"
				<< gender << "|" << address << "|" << phone_number << "|"
				<< speciality << "\n";

			tempindex << indexKey << "|" << offset << "\n";
			remove("patient.txt");
			rename("temp.txt", "doctors.txt");
			remove("paitent_id.txt");
			rename("tempindex.txt", "primary.txt");
			cout << "record updated successfully\n";
		}
		else
		{
			cout << "no record found\n";
		}
		index.close();
		paitent.close();
		temp.close();
		tempindex.close();
	}
};
