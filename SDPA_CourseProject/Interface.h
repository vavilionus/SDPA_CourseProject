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

//2. Delete passenger info
void DeletePassanger(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);

//4. Clear ALL passangers data
void ClearAllPassangersData(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);

//3 ����������� ���� ������������������ �������������(1. ������ ������� � ��� 2. ��� ���)
void ShowPassenger(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);
void ShowAllPassenger(ListOfPassengers* arr[]);

//5. Add new Flightd
void CreateFlight(Tree*& flight_tree);

//6. Delete Flight
void DeleteFlight(Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);

//8. Clear ALL Flights
void ClearAllFlightData(Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);

//9. Buy ticket
void BuyTicket(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);

//10. Return ticket
void ReturnTicket(Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);

std::string PassportIdInput();
std::string FlightIdInput();
std::string NameInput();
int HowManyDays(int x, int y);
std::string DateInput();
std::string TimeInput();
std::string PlaneTicketIdInput();
void reader(int* a, int horiz_low, int horiz_high);

//devtools
bool load(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list, std::string fname);
void loadProceeder(Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list);


#endif 
