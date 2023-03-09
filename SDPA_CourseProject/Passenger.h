#ifndef Passenger_h
#define Passenger_h

#include <iostream>
#include <string>

struct Passenger {
	std::string passport_id = "NNNN-NNNNNN";
	std::string place = "PLACE";
	std::string date_of_issue = "xx.xx.xxxx";
	std::string full_name = "Place holder";
	std::string date_of_birth = "xx.xx.xxxx";
};

struct ListOfPassengers {
	Passenger value;
	ListOfPassengers* next = NULL;
};

void AddListOfPassengers(ListOfPassengers** head ,Passenger elem);
int HashFunc(std::string key);
void AddHash(ListOfPassengers* arr[], Passenger elem);
bool IsIdUnique(ListOfPassengers* arr[], std::string id);

#endif 
