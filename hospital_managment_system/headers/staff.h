#ifndef STAAF_H
#define STAAF_H

#include "Person.h"
#include <iostream>
#include <string>
using namespace std;
class Staff : public Person
{

private:
	
	string department;

public:
	void addStaff();
	void getStaffById();
	void getAllStaffs();
	void updateStaff();
	void deleteStaff();
};

#endif
