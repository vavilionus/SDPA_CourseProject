#include <iostream>
#include <iomanip>
#include "Passenger.h"

void AddListOfPassengers (ListOfPassengers** head, Passenger elem) {
	ListOfPassengers* cur = *head;
	ListOfPassengers* p = new ListOfPassengers;
	p->value = elem;
	
	if (cur == NULL) {
		p->next = NULL;
		*head = p;
	}
	else {
		while (cur->next){
			
			cur = cur->next; 
		}
		cur->next = p;
		p->next = NULL;
	}
}

void DeleteListOfPassengers(ListOfPassengers** head, std::string delete_id) {
	ListOfPassengers* cur = *head;
	ListOfPassengers* holder;
	if (!(*head)) {
		std::cout << "There is nothing to delete." << std::endl;
		return;
	}
	else if ((*head)->value.passport_id == delete_id) {
		holder = (*head);
		(*head) = (*head)->next;
		delete holder;
		std::cout << "element with id: " << delete_id << " - is deleted, and all data related to it.";
		return;
	}
	else {
		while (cur->next->next) {
			if (cur->next->value.passport_id == delete_id) {
				holder = cur->next;
				cur->next = cur->next->next;
				delete holder;
				std::cout << "element with id: " << delete_id << " - is deleted, and all data related to it.";
				return;
			}
			cur = cur->next;
		}
		if (cur->next->value.passport_id == delete_id) {
			holder = cur->next;
			cur->next = NULL;
			std::cout << "element with id: " << delete_id << " - is deleted, and all data related to it.";
			delete holder;
			return;
		}
	}
	std::cout << "element with id: " << delete_id << " isn't found";
}

void ClearListOfPassengers(ListOfPassengers** head) {
	if (!*(head)) {
		return;
	}
	ListOfPassengers* cur = NULL;
	while ((*head)->next) {
		cur = *head;
		*head = (*head)->next;
		delete cur;
	}
	delete *head;

}

void ShowListOfPassengers(ListOfPassengers* head) {
	ListOfPassengers* cur = head;
	if (!(head)) {
		std::cout << "\nEMPTY" << std::endl;
		return;
	}
	else {
		//std::cout << "/-----------------------------------------------------------------------------------------------------------------\\" << std::endl;
		//std::cout << "|  passport Id  |            Full Name           |            Authority           | Date of issue | Date of birth |" << std::endl;
		//std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl;
		while (cur)
		{
			std::cout << "| " << std::setw(13) << cur->value.passport_id << " | " << std::setw(30) << cur->value.full_name << " | " << std::setw(30) << cur->value.place << " | " << std::setw(13) << cur->value.date_of_issue << " | " << std::setw(13) << cur->value.date_of_issue << " | " << std::endl;
			std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl;
			cur = cur->next;
		}
		
	}
}

Passenger TakeListOfPassengersElem(ListOfPassengers* arr[], std::string passsanger_id) {
	ListOfPassengers* cur = arr[HashFunc(passsanger_id)];
	Passenger elem;
	if (cur == NULL) {
		return elem;
	}
	else {
		while (cur->next) {
			if (cur->value.passport_id == passsanger_id) {
				return cur->value;
			}
			cur = cur->next;
		}
		if (cur->value.passport_id == passsanger_id) {
			return cur->value;
		}
	}
	return elem;
}

void ShowListOfPassengersLite(ListOfPassengers* head) {
	ListOfPassengers* cur = head;
	if (!(head)) {
		std::cout << "\nEMPTY" << std::endl;
		return;
	}
	else {
		//std::cout << "/-----------------------------------------------------------------------------------------------------------------\\" << std::endl;
		//std::cout << "|  passport Id  |            Full Name           |            Authority           | Date of issue | Date of birth |" << std::endl;
		//std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl;
		while (cur)
		{
			std::cout << "| " << std::setw(13) << cur->value.passport_id << " | " << std::setw(30) << cur->value.full_name << " | " << std::setw(30) << cur->value.place << " | " << std::setw(13) << cur->value.date_of_issue << " | " << std::setw(13) << cur->value.date_of_issue << " | " << std::endl;
			std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl;
			cur = cur->next;
		}
		std::cout << std::endl;
	}
}

// возвращаает ключ элемента Passanger по номеру паспорта
int HashFunc(std::string key) {
	int result = 0;
	for (int i = 0; i < 11; i++) {
		result += pow(key[i], 2) * (i + 1);
	}
	result = result % 100;
	return result;
}

//добавляет элемент Passenger в хэш таблицу 
void AddHash(ListOfPassengers* arr[], Passenger elem) {

	AddListOfPassengers(&arr[HashFunc(elem.passport_id)], elem);
	
}
void DeleteHash(ListOfPassengers* arr[], std::string passport_id) {

	DeleteListOfPassengers(&arr[HashFunc(passport_id)], passport_id);

}

void FreeListOfPassengers(ListOfPassengers** head) {
	ListOfPassengers* cur = NULL;
	if (*head) {
		while ((*head)->next) {
			cur = *head;
			*head = (*head)->next;
			delete cur;
		}
	}
	delete* head;
}


//проверяет уникальность номера пвспорта в таблице
bool IsIdUnique(ListOfPassengers* arr[], std::string id) {
	ListOfPassengers* cur = arr[HashFunc(id)];
	if (cur == NULL) {
		return 1;
	}
	else {
		while (cur->next) {
			if (cur->value.passport_id == id) {
				return 0;
			}
			cur = cur->next;
		}
		if (cur->value.passport_id == id) {
			return 0;
		}
	}
	return 1;
}