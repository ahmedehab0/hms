#ifndef PATIENT
#define PATIENT
#include <string>
#include "./Person.h"

using namespace std;


class Paitent : public Person {
	private:
		int offset;
		bool hospitalized;
	public:
		void addPaitent();
		void getPaitentById();
		void getAllPaitents();
		void hospitalize();
		void discharge();
		void updatePaitent();
		void deletePaitent();
		bool search();
};

#endif
