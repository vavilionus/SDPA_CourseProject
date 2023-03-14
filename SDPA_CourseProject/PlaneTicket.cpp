#include <iostream>
#include <iomanip>
#include "PlaneTicket.h"
#include "Flight.h"

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
bool DeleteListOfPlaneTickets(ListOfPlaneTickets*& head, std::string ticket_id) {
	ListOfPlaneTickets* cur = head;
	ListOfPlaneTickets* holder;

	if (cur == NULL) {
		return 0;
	}
	if (head->value.ticket_id == ticket_id) {
		while (cur->next != head) {
			cur = cur->next;
		}
		holder = cur->next;
		cur->next = cur->next->next;
		head = cur->next;
		
		delete holder;
		return  1;
	}
	else {
		while (cur->next->next != head) {
			if (cur->next->value.ticket_id == ticket_id) {
				holder = cur->next;
				cur->next = cur->next->next;
				delete holder;
				return 1;
			}
			cur = cur->next;
		}
		if (cur->next->value.ticket_id == ticket_id) {
			holder = cur->next;
			cur->next = cur->next->next;
			delete holder;
			return 1;
		}
	}
	return 0;
}

bool DeleteListOfPlaneTicketsByFlightID(ListOfPlaneTickets*& head, std::string flight_id) {
	ListOfPlaneTickets* cur = head;
	ListOfPlaneTickets* holder;

	if (cur == NULL) {
		return 0;
	}
	if ((head->next == head)) {
		if (head->value.flight_id == flight_id) {
			holder = head;
			delete holder;
			head = NULL;
			return 1;
		}
		return 0;
	}

	while (head->value.flight_id == flight_id) {
		if ((head->next == head)) {
			if (head->value.flight_id == flight_id) {
				holder = head;
				delete holder;
				head = NULL;
				return 1;
			}
			return 0;
		}
		while (cur->next != head) {
			cur = cur->next;
		}
		holder = cur->next;
		cur->next = cur->next->next;
		head = cur->next;

		delete holder;
	}

	while (cur->next->next != head) {
		if (cur->next->value.flight_id == flight_id) {
			holder = cur->next;
			cur->next = cur->next->next;
			delete holder;
		}
		else {
			cur = cur->next;
		}
	}

	if (cur->next->value.flight_id == flight_id) {
		holder = cur->next;
		cur->next = cur->next->next;
		delete holder;
	}

	if ((head->next == head)) {
		if (head->value.flight_id == flight_id) {
			holder = head;
			delete holder;
			head = NULL;
			return 1;
		}
		return 0;
	}

	return 0;
}

bool DeleteListOfPlaneTicketsByPassportID(Tree*& flight_tree, ListOfPlaneTickets*& head, std::string passport_id) {
	ListOfPlaneTickets* cur = head;
	ListOfPlaneTickets* holder;

	if (cur == NULL) {
		return 0;
	}
	if ((head->next == head)) {
		if (head->value.passport_id == passport_id) {
			FreeSeatsIncreaseTree(flight_tree, head->value.flight_id);
			holder = head;
			delete holder;
			head = NULL;
			return 1;
		}
		return 0;
	}

	while (head->value.passport_id == passport_id) {
		if ((head->next == head)) {
			if (head->value.passport_id == passport_id) {
				FreeSeatsIncreaseTree(flight_tree, head->value.flight_id);
				holder = head;
				delete holder;
				head = NULL;
				return 1;
			}
			return 0;
		}
		FreeSeatsIncreaseTree(flight_tree, head->value.flight_id);
		while (cur->next != head) {
			cur = cur->next;
		}
		holder = cur->next;
		cur->next = cur->next->next;
		head = cur->next;

		delete holder;
	}

	while (cur->next->next != head) {
		if (cur->next->value.passport_id == passport_id) {
			FreeSeatsIncreaseTree(flight_tree, cur->next->value.flight_id);
			holder = cur->next;
			cur->next = cur->next->next;
			delete holder;
		}
		else {
			cur = cur->next;
		}
	}

	if (cur->next->value.passport_id == passport_id) {
		FreeSeatsIncreaseTree(flight_tree, cur->next->value.flight_id);
		holder = cur->next;
		cur->next = cur->next->next;
		delete holder;
	}

	if ((head->next == head)) {
		if (head->value.passport_id == passport_id) {
			FreeSeatsIncreaseTree(flight_tree, head->value.flight_id);
			holder = head;
			delete holder;
			head = NULL;
			return 1;
		}
		return 0;
	}

	return 0;
}

int HowManyTicketsByPassportId(ListOfPlaneTickets*& head, std::string passport_id) {
	int counter = 0;
	ListOfPlaneTickets* cur = head;
	if (!(head)) {
		return counter;
	}
	if (head->value.passport_id == passport_id) {
		counter++;
	}
	cur = cur->next;
	while (cur != head) {
		if (cur->value.passport_id == passport_id) {
			counter++;
		}
		cur = cur->next;
	}
	return counter;
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
