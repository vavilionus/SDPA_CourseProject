#ifndef PlaneTicket_h
#define PlaneTicket_h

#include <iostream>
#include <string>
#include <iomanip>

struct PlaneTicket {
	std::string passport_id = "NNNN-NNNNNN";// 4 - 6 цифр
	std::string flight_id = "AAA-NNN";// 3 заглавные буквы?
	std::string ticket_id = "NNNNNNNNN";// 9 цифр
	
};

struct ListOfPlaneTickets {
	PlaneTicket value;
	ListOfPlaneTickets* next = NULL;
};

void AddListOfPlaneTickets(ListOfPlaneTickets*& head, PlaneTicket elem);
bool DeleteListOfPlaneTickets(ListOfPlaneTickets*& head, std::string ticket_id);
bool DeleteListOfPlaneTicketsByFlightID(ListOfPlaneTickets*& head, std::string flight_id);
void ShowListOfPlaneTickets(ListOfPlaneTickets* head);

void ConvertIn(ListOfPlaneTickets*& root);
void ConvertOut(ListOfPlaneTickets*& root);
void quickSort(ListOfPlaneTickets*& root);
void ListQuickSort(ListOfPlaneTickets*& root);
//quick sort part
/*
struct ListOfPlaneTickets* getTail(struct ListOfPlaneTickets* cur);
struct ListOfPlaneTickets* partition(struct ListOfPlaneTickets* head, struct ListOfPlaneTickets* end, struct ListOfPlaneTickets** newHead, struct ListOfPlaneTickets** newEnd);
struct ListOfPlaneTickets* quickSortRecur(struct ListOfPlaneTickets* head, struct ListOfPlaneTickets* end);
void quickSort(struct ListOfPlaneTickets** headRef);
*/

#endif 