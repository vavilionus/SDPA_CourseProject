#ifndef Interface_h
#define Interface_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "PlaneTicket.h"
#include "Passenger.h"
#include "Flight.h"



//1.����������� ������ ���������
void CreatePassenger(ListOfPassengers* arr[]);
//2

//3 ����������� ���� ������������������ �������������(1. ������ ������� � ��� 2. ��� ���)
void ShowAllPassenger(ListOfPassengers* arr[]);

//5. Add new Flightd
void CreateFlight(Tree*& flight_tree);

//9. Buy ticket
void BuyTicket(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);

std::string PassportIdInput();
std::string FlightIdInput();
std::string NameInput();
int HowManyDays(int x, int y);
std::string DateInput();
std::string TimeInput();
void reader(int* a, int horiz_low, int horiz_high);

//devtools
bool load(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list, std::string fname);
void loadProceeder(Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);


#endif 
