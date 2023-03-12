#include <iostream>
#include <iomanip>
#include "PlaneTicket.h"

void AddListOfPlaneTickets(ListOfPlaneTickets*& head, PlaneTicket elem) {
	ListOfPlaneTickets* cur = head;
	ListOfPlaneTickets* p = new ListOfPlaneTickets;
	p->value = elem;

	if (cur == NULL) {
		p->next = p;
		head = p;
	}
	else {
		while (cur->next != head) {

			cur = cur->next;
		}
		cur->next = p;
		p->next = head;
	}
}

void ShowListOfPlaneTickets(ListOfPlaneTickets* head) {
	ListOfPlaneTickets* cur = head;
	if (!(head)) {
		std::cout << "\nEMPTY" << std::endl;
		return;
	}
	else {
		std::cout << "| " << std::setw(13) << cur->value.passport_id << " | " << std::setw(8) << cur->value.flight_id << " | " << std::setw(9) << cur->value.ticket_id << " | " << std::endl;
		std::cout << "|---------------|----------|-----------|" << std::endl;
		cur = cur->next;
	}
	
	//std::cout << "/-----------------------------------------------------------------------------------------------------------------\\" << std::endl;
	//std::cout << "|  passport Id  |            Full Name           |            Authority           | Date of issue | Date of birth |" << std::endl;
	//std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl;
	while (cur!=head)
	{
		std::cout << "| " << std::setw(13) << cur->value.passport_id << " | " << std::setw(8) << cur->value.flight_id << " | " << std::setw(9) << cur->value.ticket_id << " | " << std::endl;
		std::cout << "|---------------|----------|-----------|" << std::endl;
		cur = cur->next;
	}
	//голова ураборо+са
	/*
	std::cout << "AND HERE IS HEAD AGAIN!\n";
	std::cout << "| " << std::setw(13) << cur->value.passport_id << " | " << std::setw(8) << cur->value.flight_id << " | " << std::setw(9) << cur->value.ticket_id << " | " << std::endl;
	std::cout << "|---------------|----------|-----------|" << std::endl;
	cur = cur->next;
	*/
	std::cout << std::endl;
	
}

void ConvertIn(ListOfPlaneTickets*& head) {
    ListOfPlaneTickets* cur = head;
    while (cur->next != head) {
        cur = cur->next;
    }
    cur->next = nullptr;
}

void ConvertOut(ListOfPlaneTickets*& head) {
    ListOfPlaneTickets* cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = head;
}

void quickSort(ListOfPlaneTickets*& root)
{
    // trivial lists are just returned immediately
    if (!root || !(root->next))
        return;

    ListOfPlaneTickets* lhs = nullptr, ** pplhs = &lhs;
    ListOfPlaneTickets* rhs = nullptr, ** pprhs = &rhs;
    ListOfPlaneTickets* pvt = root;
    root = root->next;
    pvt->next = nullptr;

    while (root)
    {
        if (root->value.ticket_id < pvt->value.ticket_id)
        {
            *pplhs = root; // tack on lhs list end
            pplhs = &(*pplhs)->next;
        }
        else
        {
            *pprhs = root; // tack on rhs list end
            pprhs = &(*pprhs)->next;
        }
        root = root->next;
    }

    // terminate both list. note that the pivot is still
    //  unlinked, and will remain so until we merge
    *pplhs = *pprhs = nullptr;

    // invoke on sublists.
    quickSort(lhs);
    quickSort(rhs);

    // find end of lhs list, slip the pivot into  position, then 
    //  tack on the rhs list.
    while (*pplhs)
        pplhs = &(*pplhs)->next;
    *pplhs = pvt;
    pvt->next = rhs;

    // set final output
    root = lhs;
}

void ListQuickSort(ListOfPlaneTickets*& root) {
    ConvertIn(root);
    quickSort(root);
    ConvertOut(root);
}
