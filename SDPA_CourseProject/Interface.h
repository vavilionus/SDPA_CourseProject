#ifndef Interface_h
#define Interface_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "Passenger.h"
#include "Flight.h"
#include "PlaneTicket.h"


//1.����������� ������ ���������
void CreatePassenger(ListOfPassengers* arr[]);
//2

//3 ����������� ���� ������������������ �������������(1. ������ ������� � ��� 2. ��� ���)
void ShowAllPassenger(ListOfPassengers* arr[]);

//5. Add new Flightd
void CreateFlight(Tree* flight_tree);

std::string PassportIdInput();
std::string NameInput();
int HowManyDays(int x, int y);
std::string DateInput();
void reader(int* a, int horiz_low, int horiz_high);

#endif 
