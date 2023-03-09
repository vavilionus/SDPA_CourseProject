#ifndef Interface_h
#define Interface_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

void CreatePassenger(ListOfPassengers* arr[]);

std::string PassportIdInput();
std::string NameInput();
int HowManyDays(int x, int y);
std::string DateInput();


#endif 
