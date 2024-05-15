#ifndef PERSON
#define PERSON

using namespace std;
#include <string>

class Person {
	public:
		static int nextid;
		int id;
		string first_name;
		string last_name;
		char gender;
		int age;
		string address;
		string phone_number;

	public:
		Person();
		void input();
		void display();
};

#endif
