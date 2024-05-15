#include "../headers/staff.h"
#include "appoinment.cpp"

int Appointments :: nextID = 1;

void appointmentsMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/APPOINTMENTS\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Book an appointment\n";
        cout << "[02] : Get appointment details\n";
        cout << "[03] : Show all appointments\n\n";
        cout << "[4] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> purpose;

        if (purpose == 1)
        {
            Appointments a;
            a.book_appointment();
        }
        else if (purpose == 2)
        {
        }
        else if (purpose == 3)
        {
        }
        else if (purpose == 4)
        {
            exit = true;
            break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }

        cout << endl;
        cout << endl;

        getchar();
    }
    return;
}


void doctorsMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/PATIENTS\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Register a new doctor\n";
        cout << "[02] : Fetch doctor details from history\n";
        cout << "[03] : Get details of all registered doctors\n";
	cout << "[04] : Update doctor details\n";
	cout << "[05] : Delete a registerd doctor from history\n";
        cout << "[06] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> purpose;

        if (purpose == 1)
        {
		Doctors p;
		p.Insertdoctor();
        }
        else if (purpose == 2)
        {
		Doctors p;
		p.searchByID();
        }
        else if (purpose == 3)
        {
		Doctors p;
		p.displayalldoctors();

        }
        else if (purpose == 4)
        {
		Doctors p;
		p.Update();
        }
        else if (purpose == 5)
        {
		Doctors p;
		p.deletedoctor();
        }
        else if (purpose == 6)
        {
		exit = true;
		break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }


        cout << endl;
        cout << endl;

    }
    return;
}


void patientsMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/PATIENTS\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Register a new patient\n";
        cout << "[02] : Fetch patient details from history\n";
        cout << "[03] : Get details of all registered patients\n";
	cout << "[04] : Update paitent details\n";
	cout << "[05] : Delete a registerd paitent from history\n";
        cout << "[06] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> purpose;

        if (purpose == 1)
        {
		Paitent p;
		p.addPaitent();
        }
        else if (purpose == 2)
        {
		Paitent p;
		p.getPaitentById();
        }
        else if (purpose == 3)
        {
		Paitent p;
		p.getAllPaitents();

        }
        else if (purpose == 4)
        {
		Paitent p;
		p.updatePaitent();
        }
        else if (purpose == 5)
        {
		Paitent p;
		p.deletePaitent();
        }
        else if (purpose == 6)
        {
		exit = true;
		break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }


        cout << endl;
        cout << endl;

    }
    return;
}

void staffMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/PATIENTS\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Register a new staff member\n";
        cout << "[02] : Fetch staff details from history\n";
        cout << "[03] : Get details of all registered staff\n";
	cout << "[04] : Update paitent details\n";
	cout << "[05] : Delete a registerd staff member from history\n";
        cout << "[06] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> purpose;

        if (purpose == 1)
        {
		Staff p;
		p.addStaff();
        }
        else if (purpose == 2)
        {
		Staff p;
		p.getStaffById();
        }
        else if (purpose == 3)
        {
		Staff p;
		p.getAllStaffs();

        }
        else if (purpose == 4)
        {
		Staff p;
		p.updateStaff();
        }
        else if (purpose == 5)
        {
		Staff p;
		p.deleteStaff();
        }
        else if (purpose == 6)
        {
		exit = true;
		break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }


        cout << endl;
        cout << endl;

    }
    return;
}
int main() {
while (1)
    {
	system("clear");
        int category = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect a category:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : APPOINTMENTS\n";
        cout << "[02] : PATIENTS\n";
        cout << "[03] : DOCTORS\n";
        cout << "[04] : Staff\n";
	cout << "[05] : Exit\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> category;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n";
        if (category == -1)
        {
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "\nShutting Down System...\n";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            break;
        }
        else if (category == 1)
        {
		system("clear");
            appointmentsMenu();
        }
        else if (category == 2)
        {
	    system("clear");
            patientsMenu();
        }
        else if (category == 3)
        {
		system("clear");
            doctorsMenu();
        }
        else if (category == 4)
        {
		system("clear");
            staffMenu();
        }
	else if (category == 5) {
		break;
	}
	else 
	{
		cout << "invalid choice\n";
	}
    }
}
