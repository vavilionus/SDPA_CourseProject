#include <iostream>
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