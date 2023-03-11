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
		std::cout << std::endl;
	}
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