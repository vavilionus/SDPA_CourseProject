#ifndef Passenger_h
#define Passenger_h

#include <iostream>
#include <string>
#include <iomanip>

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
void DeleteListOfPassengers(ListOfPassengers** head, std::string delete_id);
void ShowListOfPassengers(ListOfPassengers* head);
int HashFunc(std::string key);
void AddHash(ListOfPassengers* arr[], Passenger elem);
void DeleteHash(ListOfPassengers* arr[], std::string passport_id);
void FreeListOfPassengers(ListOfPassengers** head);
bool IsIdUnique(ListOfPassengers* arr[], std::string id);

#endif 
