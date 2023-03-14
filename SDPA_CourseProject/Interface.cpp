#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <algorithm>
#include <cctype>
#include "Passenger.h"
#include "Interface.h"
#include "Flight.h"
#include "PlaneTicket.h"


//1
void CreatePassenger(ListOfPassengers* arr[]) {
    Passenger elem;
    std::string passport_id = "NNNN-NNNNNN";
    std::cout << "Input passport ID (NNNN-NNNNNN):" << std::endl << "\t";
    passport_id = PassportIdInput();
    if (!IsIdUnique(arr, passport_id)) {
        std::cout << "This Passport ID is alredy in the system!" << std::endl;
        return;
    }
    elem.passport_id = passport_id;
    std::cout << "Input your fullname :" << std::endl << "\t";
    elem.full_name = NameInput();
    std::cout << "Input Authorty :" << std::endl << "\t";
    elem.place = NameInput();
    std::cout << "Input date of issue (NN.NN.NNNN):" << std::endl << "\t";
    elem.date_of_issue = DateInput();
    std::cout << "Input date of birth (NN.NN.NNNN):" << std::endl << "\t";
    elem.date_of_birth = DateInput();
    AddHash(arr, elem);
}

//2. Delete passenger info
void DeletePassanger(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list) {
    Passenger elem;
    int operathion_choice;
    std::string passport_id = "NNNN-NNNNNN";
    std::cout << "Input passport ID (NNNN-NNNNNN):" << std::endl << "\t";
    passport_id = PassportIdInput();
    if (IsIdUnique(arr, passport_id)) {
        std::cout << "This Passport ID isn't present in the system!" << std::endl;
        return;
    }
    if (HowManyTicketsByPassportId(plane_tickets_list, passport_id) != 0) {
        std::cout << "This passanger have " << HowManyTicketsByPassportId(plane_tickets_list, passport_id) << " bought tickets." << std::endl;
        std::cout << "Are you sure you want to delete this Passanger, and return those tickets?" << std::endl
            << "\tYes - 1; No - 2 \n\tIN:   ";
        std::cin >> operathion_choice;
        reader(&operathion_choice, 1, 2);
        if (operathion_choice == 2) {
            std::cout << "\n\nDeletion is stopped!" << std::endl;
            return;
        }
        else {
            DeleteListOfPlaneTicketsByPassportID(flight_tree, plane_tickets_list, passport_id);
        }
    }
    std::cout << std::endl;
    DeleteHash(arr, passport_id);
    std::cout << std::endl;
}

//3
void ShowPassenger(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list) {
    int operathion_choice;
    int passangers_flights_size;
    bool flag_is_flight_unic = 1;
    std::string* passangers_flights = NULL;
    std::string passport_id;
    std::string full_name, full_name_holder;
    int ticket_counter = 0;
    ListOfPassengers* cur;
    ListOfPlaneTickets* ticket_cur = plane_tickets_list;
    std::cout << "\nPlease choose operathion:\n    1. Show all pasangers passport info\n    2. Show passangers Flight info\n    3. Show passengers info by fullname\n\nIN: ";

    std::cin >> operathion_choice;
    reader(&operathion_choice, 1, 3);
    switch (operathion_choice) {
    case (1):
        ShowAllPassenger(arr);
        
        break;
    case (2):
        std::cout << "Input passport ID (NNNN-NNNNNN):" << std::endl << "\t";
        passport_id = PassportIdInput();
        if (IsIdUnique(arr, passport_id)) {
            std::cout << "This Passport ID isn't present in the system!" << std::endl;
            return;
        }

        std::cout << "/-----------------------------------------------------------------------------------------------------------------\\" << std::endl;
        std::cout << "|  passport Id  |            Full Name           |            Authority           | Date of issue | Date of birth |" << std::endl;
        std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl;
        cur = arr[HashFunc(passport_id)];
        while (cur->value.passport_id != passport_id)
        {
            cur = cur->next;
        }
        std::cout << "| " << std::setw(13) << cur->value.passport_id << " | " << std::setw(30) << cur->value.full_name << " | " << std::setw(30) << cur->value.place << " | " << std::setw(13) << cur->value.date_of_issue << " | " << std::setw(13) << cur->value.date_of_issue << " | " << std::endl;
        std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl << std::endl;
        
        
        passangers_flights_size = HowManyTicketsByPassportId(plane_tickets_list, passport_id);
        if (passangers_flights_size == 0) {
            return;
        }
        passangers_flights = new std::string [passangers_flights_size];

        if (plane_tickets_list->value.passport_id == passport_id) {
            passangers_flights[ticket_counter++] = plane_tickets_list->value.flight_id;
        }
        ticket_cur = ticket_cur->next;

        while (ticket_cur != plane_tickets_list) {
            flag_is_flight_unic = 1;
            if (ticket_cur->value.passport_id == passport_id){
                for (int i = 0; i < ticket_counter; i++) {
                    if (passangers_flights[i] == ticket_cur->value.flight_id) {
                        flag_is_flight_unic = 0;
                    }
                }
                if (flag_is_flight_unic) {
                    passangers_flights[ticket_counter++] = ticket_cur->value.flight_id;
                }
            }
            ticket_cur = ticket_cur->next;
        }
        std::cout << "Passangers Flights: " << std::endl;
        std::cout << "/---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----\\" << std::endl;
        std::cout << "|    ID   |             Company            |            Deparure            |             Arrival            |  Dep.Date  | DTime |seats|sfree|" << std::endl;
        std::cout << "|---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----|" << std::endl;
        for (int i = 0; i < ticket_counter; i++) {
            ShowTreeElem(flight_tree, passangers_flights[i]);
        }
        delete[] passangers_flights;
        break;

    case (3):
        std::cout << "Input a searching word: :" << std::endl << "\t";
        full_name = NameInput();
        std::transform(full_name.begin(), full_name.end(), full_name.begin(),
            [](unsigned char c) { return std::tolower(c); });
        std::cout << "\nResult(s) that fulfill your request:\n" << std::endl;
        std::cout << "/------------------------------------------------\\" << std::endl;
        std::cout << "|  passport Id  |            Full Name           |" << std::endl;
        std::cout << "|---------------|--------------------------------|" << std::endl;

        for (int i = 0; i < 100; i++) {
            if (!(arr[i])) {
                continue;
            }
            else {
                cur = arr[i];
                //std::cout << "/-----------------------------------------------------------------------------------------------------------------\\" << std::endl;
                //std::cout << "|  passport Id  |            Full Name           |            Authority           | Date of issue | Date of birth |" << std::endl;
                //std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl;
                while (cur)
                {
                    full_name_holder = cur->value.full_name;
                    std::transform(full_name_holder.begin(), full_name_holder.end(), full_name_holder.begin(),
                        [](unsigned char c) { return std::tolower(c); });
                    if ((full_name_holder).contains((full_name))) {
                        std::cout << "| " << std::setw(13) << cur->value.passport_id << " | " << std::setw(30) << cur->value.full_name << " | " << std::endl;
                        std::cout << "|---------------|--------------------------------|" << std::endl;
                    }
                    cur = cur->next;
                }

            }
        }
            
        break;
    }
    
}
void ShowAllPassenger(ListOfPassengers* arr[]) {
    int operathion_choose;
    //std::cout << "/-----------------------------------------------------------------------------------------------------------------\\" << std::endl;
    //std::cout << "|  passport Id  |            Full Name           |            Authority           | Date of issue | Date of issue |" << std::endl;
    //std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl;
    /*std::cout << "\nPlease choose operathion:\n    1. Show ALL info\n    2. Show only paasport ID, fullname and isue date\n" << std::endl;
    std::cin >> operathion_choose;
    reader(&operathion_choose, 1, 2);*/
    //возможно стоит добавить ропцию вывода всех рейсов вместе с инфой о паспорте?
    std::cout << "/-----------------------------------------------------------------------------------------------------------------\\" << std::endl;
    std::cout << "|  passport Id  |            Full Name           |            Authority           | Date of issue | Date of birth |" << std::endl;
    std::cout << "|---------------|--------------------------------|--------------------------------|---------------|---------------|" << std::endl;
    for (int i = 0; i < 100; i++) {
        if (arr[i]) {
            ShowListOfPassengers(arr[i]);
        }
    }

}

//4. Clear ALL passangers data
void ClearAllPassangersData (ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list) {
    int operathion_choice;
    ListOfPassengers* cur;
    std::cout << "Are you sure you want to delete all Passangers, and return all tickets?" << std::endl
        << "\tYes - 1; No - 2 \n\tIN:   ";
    std::cin >> operathion_choice;
    reader(&operathion_choice, 1, 2);
    if (operathion_choice == 2) {
        std::cout << "\n\Passangers wipe is stopped!" << std::endl;
        return;
    }
    else {
        for (int i = 0; i < 100; i++) {
            cur = arr[i];
            if (!cur) {
                continue;
            }
            else {
                while(cur != NULL){
                    DeleteListOfPlaneTicketsByPassportID(flight_tree, plane_tickets_list, cur->value.passport_id);
                    cur = cur->next;
                }
            }
            ClearListOfPassengers(&(arr[i]));
            arr[i] = NULL;
        }
    }
}

//5. Add new Flight
void CreateFlight(Tree*& flight_tree) {
    Flight elem;
    std::string departure_name;
    std::string arrival_name;
    std::cout << "Input flight ID (AAA-NNN):" << std::endl << "\t";
    elem.flight_id = FlightIdInput();
    if (FindTreeBool(flight_tree, elem)) {
        std::cout << "\nThis Flight ID is alredy in the system!\n" << std::endl;
        return;
    }
    std::cout << "Input flight company name:" << std::endl << "\t";
    elem.company_name = NameInput();
    std::cout << "Input departure of the flight:" << std::endl << "\t";
    elem.departure_name = NameInput();
    std::cout << "Input arrival of the flight:" << std::endl << "\t";
    elem.arrival_name = NameInput();
    departure_name = elem.departure_name;
    arrival_name = elem.arrival_name;
    std::transform(departure_name.begin(), departure_name.end(), departure_name.begin(),
        [](unsigned char c) { return std::tolower(c); });
    std::transform(arrival_name.begin(), arrival_name.end(), arrival_name.begin(),
        [](unsigned char c) { return std::tolower(c); });
    if ((departure_name) == (arrival_name)) {
        std::cout << "\nDeparture and arrival cannot be the same!\n" << std::endl;
        return;
    }
    std::cout << "Input date of deaprture (NN.NN.NNNN):" << std::endl << "\t";
    elem.date_of_departure = DateInput();
    std::cout << "Input time of deaprture (NN:NN):" << std::endl << "\t";
    elem.time_of_departure = TimeInput();
    std::cout << "Input amount of seats:" << std::endl << "\t";
    std::cin >> elem.seat_amount;
    reader(&elem.seat_amount, 20, 853); // Airbus A380 - max amount of passangers
    elem.free_seat_amount = elem.seat_amount;
    
    


    flight_tree = AddTreeElem(flight_tree, elem);
}

//6. Delete Flight
void DeleteFlight(Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list) {
    Flight elem;
    int operathion_choice;
    std::cout << "Input flight ID (AAA-NNN):" << std::endl << "\t";
    elem.flight_id = FlightIdInput();
    if (!FindTreeBool(flight_tree, elem)) {
        std::cout << "\nThis Flight ID is NOT present in the system!\n" << std::endl;
        return;
    }
    elem = TakeElemTree(flight_tree, elem);
    if ((elem.seat_amount - elem.free_seat_amount) != 0) {
        std::cout << "\nThis Flight have " << elem.seat_amount - elem.free_seat_amount << " bought tickets!\n" << std::endl;
        std::cout << "Are you sure you want to delete this Flight, and return those tickes?" << std::endl 
            << "\tYes - 1; No - 2 \n\tIN:   ";
        std::cin >> operathion_choice;
        reader(&operathion_choice, 1, 2);
        if (operathion_choice == 2) {
            std::cout << "\n\nDeletion is stopped!" << std::endl;
            return;
        }
        else {
            DeleteListOfPlaneTicketsByFlightID(plane_tickets_list, elem.flight_id);
        }
    }
    flight_tree = DeleteTreeElem(flight_tree, elem);
    std::cout << "\n\nDeletion is succesefull!" << std::endl;

}

//7. Show Flight
void ShowFlight(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list) {
    int operathion_choice, passengers_size, ticket_counter, flag_is_unic;
    ticket_counter = 0;
    std::string flight_id;
    std::string* passangers;
    ListOfPlaneTickets* ticket_cur = plane_tickets_list;
    Flight elem;
    Passenger passenger_elem;
    
    
    std::cout << "\nPlease choose operathion:\n    1. Show all flights info\n    2. Show Flights info by ID\n    3. Show passengers info by arrival name\n\nIN: ";

    std::cin >> operathion_choice;
    reader(&operathion_choice, 1, 3);
    switch (operathion_choice) {
    case(1):
        std::cout << "/---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----\\" << std::endl;
        std::cout << "|    ID   |             Company            |            Deparure            |             Arrival            |  Dep.Date  | DTime |seats|sfree|" << std::endl;
        std::cout << "|---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----|" << std::endl;

        SymmericalShowTree(flight_tree);
        break;
    case(2):
        std::cout << "Input flight ID (AAA-NNN):" << std::endl << "\t";
        flight_id = FlightIdInput();
        elem.flight_id = flight_id;
        if (!FindTreeBool(flight_tree, elem)) {
            std::cout << "\nThis Flight ID is NOT present in the system!\n" << std::endl;
            return;
        }
        elem = TakeElemTree(flight_tree, elem);
        std::cout << "/---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----\\" << std::endl;
        std::cout << "|    ID   |             Company            |            Deparure            |             Arrival            |  Dep.Date  | DTime |seats|sfree|" << std::endl;
        std::cout << "|---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----|" << std::endl;

        std::cout << "| " << std::setw(7) << elem.flight_id << " | " << std::setw(30) << elem.company_name << " | "
            << std::setw(30) << elem.departure_name << " | " << std::setw(30) << elem.arrival_name << " | "
            << std::setw(10) << elem.date_of_departure << " | "
            << std::setw(5) << elem.time_of_departure << " | " << std::setw(3) << elem.seat_amount << " | "
            << std::setw(3) << elem.free_seat_amount << " | " << std::endl;
        std::cout << "|---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----|" << std::endl;

        passengers_size = HowManyTicketsByFlightId(plane_tickets_list, flight_id);
        if (passengers_size == 0) {
            std::cout << "\nThis Flight ID has no passengers in the system!\n" << std::endl;
            return;
        }
        passangers = new std::string[passengers_size];

        
        if (plane_tickets_list->value.flight_id == flight_id) {
            passangers[ticket_counter++] = plane_tickets_list->value.passport_id;
        }
        ticket_cur = ticket_cur->next;

        while (ticket_cur != plane_tickets_list) {
            flag_is_unic = 1;
            if (ticket_cur->value.flight_id == flight_id) {
                for (int i = 0; i < ticket_counter; i++) {
                    if (passangers[i] == ticket_cur->value.passport_id) {
                        flag_is_unic = 0;
                    }
                }
                if (flag_is_unic) {
                    passangers[ticket_counter++] = ticket_cur->value.passport_id;
                }
            }
            ticket_cur = ticket_cur->next;
        }
        std::cout << "\nResult(s) that fulfill your request:\n" << std::endl;
        std::cout << "/------------------------------------------------\\" << std::endl;
        std::cout << "|  passport Id  |            Full Name           |" << std::endl;
        std::cout << "|---------------|--------------------------------|" << std::endl; 
        for (int i = 0; i < ticket_counter; i++){
            passenger_elem = TakeListOfPassengersElem(arr, passangers[i]);
            std::cout << "| " << std::setw(13) << passenger_elem.passport_id << " | " << std::setw(30) << passenger_elem.full_name << " | " << std::endl;
            std::cout << "|---------------|--------------------------------|" << std::endl;
        }
        delete[] passangers;

        break;
    }
    

}

//8. Clear ALL Flights
void ClearAllFlightData(Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list) {
    int operathion_choice;
    ListOfPassengers* cur;
    std::cout << "Are you sure you want to delete all Passangers, and return all tickets?" << std::endl
        << "\tYes - 1; No - 2 \n\tIN:   ";
    std::cin >> operathion_choice;
    reader(&operathion_choice, 1, 2);
    if (operathion_choice == 2) {
        std::cout << "\n\Passangers wipe is stopped!" << std::endl;
        return;
    }
    else {
        flight_tree = ClearTreeElem(flight_tree);
        ClearListOfPlaneTickets(plane_tickets_list);
        plane_tickets_list = NULL;
    }
}
//9. Buy ticket
void BuyTicket(ListOfPassengers* arr[] ,Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list) {
    std::string passport_id = "NNNN-NNNNNN";
    std::string flight_id;
    std::string ticket_id;
    Flight holder;
    PlaneTicket elem;
    ListOfPlaneTickets* cur = plane_tickets_list;
    int counter = 0;

    if (!(flight_tree)) {
        std::cout << "\nThere is no flights in the system!\n" << std::endl;
        return;
    }

    std::cout << "Input passport ID (NNNN-NNNNNN):" << std::endl << "\t";
    passport_id = PassportIdInput();
    if (IsIdUnique(arr, passport_id)) {
        std::cout << "This Passport ID isn't present in the system!" << std::endl;
        return;
    }
    elem.passport_id = passport_id;
    std::cout << "Input flight ID (AAA-NNN):" << std::endl << "\t";
    flight_id = FlightIdInput();
    holder.flight_id = flight_id;
    if (!FindTreeBool(flight_tree, holder)) {
        std::cout << "\nThis Flight ID isn't present in the system!\n" << std::endl;
        return;
    }
    if (!isFreeSeatsTreeBool(flight_tree, holder)) {
        std::cout << "\nThis Flight has no more free seats!\n" << std::endl;
        return;
    }
    elem.flight_id = flight_id;
    if (!plane_tickets_list){
        counter = 0;
    }
    else if (stoi(cur->value.ticket_id) !=0) {
        counter = 0;
    }
    else {
        while (cur->next != plane_tickets_list) {
            counter++;
            if (stoi(cur->next->value.ticket_id) !=counter) {
                counter--;
                break;
            }
            cur = cur->next;
        }
        counter++;
    }
    ticket_id = std::to_string(counter);
    while(ticket_id.size() != 9){
        ticket_id.insert(ticket_id.begin(), '0');
    }
    elem.ticket_id = ticket_id;

    AddListOfPlaneTickets(plane_tickets_list, elem);
    ListQuickSort(plane_tickets_list);
    FreeSeatsDeacreseTree(flight_tree, flight_id);
}

//10. Return ticket
void ReturnTicket(Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list) {
    std::string ticket_id, flight_id;
    ListOfPlaneTickets* cur = plane_tickets_list;
    if (!(flight_tree)) {
        std::cout << "\nThere is no flights in the system!\n" << std::endl;
        return;
    }
    if (!(plane_tickets_list)) {
        std::cout << "\nThere is no plane tickets in the system!\n" << std::endl;
        return;
    }
    std::cout << "Input Plane ticket ID (NNNNNNNNN):" << std::endl << "\t";
    ticket_id = PlaneTicketIdInput();
    if (plane_tickets_list->value.ticket_id == ticket_id) {
        flight_id = plane_tickets_list->value.flight_id;
    }
    else {
        cur = cur->next;
        while (cur != plane_tickets_list) {
            if (cur->value.ticket_id == ticket_id) {
                flight_id = cur->value.flight_id;
                break;
            }
            cur = cur->next;
        }
    }
    if (DeleteListOfPlaneTickets(plane_tickets_list, ticket_id)) {
        std::cout << "\nDeleted successfully.\n" << std::endl;
        FreeSeatsIncreaseTree(flight_tree, flight_id);
    }
    else {
        std::cout << "\nDeleted UNsuccessfully!\n" << std::endl;
    }
    

}

std::string PassportIdInput() {
    std::string a;
    int size;
    bool flag_mistake = 0;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    getline(std::cin, a, '\n');
    size = a.size();
    if (size) {
        while (size != 0 && a[0] == ' ' || (a[0] == '\t')) {
            a.erase(0, 1);
            --size;
        }
        while (size != 0 && a[size - 1] == ' ' || (a[0] == '\t')) {
            a.erase(--size, 1);
        }
    }

    if (a.size() == 11 && a[4] == '-') {
        for (int i = 0; i < 11; i++){
            if (i == 4) continue;
            if (!((a[i] >= '0') && (a[i] <= '9'))) {
                flag_mistake = 1;
                break;
            }
        }
    }
    else {
        flag_mistake = 1;
    }

    while (std::cin.fail() || flag_mistake) {
        flag_mistake = 0;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nIncorrect data!\nPlease input a new one. Passport number FORMAT: NNNN-NNNNNN\n\nIN: ";
        getline(std::cin, a, '\n');
        size = (a).size();
        if (size) {
            while (size != 0 && (a)[0] == ' ' || (a[0] == '\t')) {
                (a).erase(0, 1);
                --size;
            }
            while (size != 0 && (a)[size - 1] == ' ' || (a[0] == '\t')) {
                (a).erase(--size, 1);
            }
        }

        if (a.size() == 11 && a[4] == '-') {
            for (int i = 0; i < 11; i++) {
                if (i == 4) continue;
                if (!((a[i] >= '0') && (a[i] <= '9'))) {
                    flag_mistake = 1;
                    break;
                }
            }
        }
        else {
            flag_mistake = 1;
        }
    }

    size = (a).size();
    for (int i = 1; i < size; i++) {
        if ((a)[i - 1] == ' ' && (a)[i] == ' ') {
            (a).erase(--i, 1);

            size--;
        }
    }
    return a;

}

std::string FlightIdInput() {
    std::string a;
    int size;
    bool flag_mistake = 0;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    getline(std::cin, a, '\n');
    size = a.size();
    if (size) {
        while (size != 0 && a[0] == ' ' || (a[0] == '\t')) {
            a.erase(0, 1);
            --size;
        }
        while (size != 0 && a[size - 1] == ' ' || (a[0] == '\t')) {
            a.erase(--size, 1);
        }
    }

    if (a.size() == 7 && a[3] == '-') {
        for (int i = 0; i < 3; i++) {
            if ((!(a[i] >= 'A' && a[i] <= 'Z')) && (!(a[i] >= 'a' && a[i] <= 'z'))) {
                flag_mistake = 1;
                break;
            }

        }
        
        for (int i = 4; i < 7; i++){
            if (!((a[i] >= '0') && (a[i] <= '9'))) {
                flag_mistake = 1;
                break;
            }
        }
    }
    else {
        flag_mistake = 1;
    }

    while (std::cin.fail() || flag_mistake) {
        flag_mistake = 0;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nIncorrect data!\nPlease input a new one. Passport number FORMAT: AAA-NNN\n\nIN: ";
        getline(std::cin, a, '\n');
        size = (a).size();
        if (size) {
            while (size != 0 && (a)[0] == ' ' || (a[0] == '\t')) {
                (a).erase(0, 1);
                --size;
            }
            while (size != 0 && (a)[size - 1] == ' ' || (a[0] == '\t')) {
                (a).erase(--size, 1);
            }
        }

        if (a.size() == 7 && a[3] == '-') {
            for (int i = 0; i < 3; i++) {
                if ((!(a[i] >= 'A' && a[i] <= 'Z')) && (!(a[i] >= 'a' && a[i] <= 'z'))) {
                    flag_mistake = 1;
                    break;
                }

            }

            for (int i = 4; i < 7; i++) {
                if (!((a[i] >= '0') && (a[i] <= '9'))) {
                    flag_mistake = 1;
                    break;
                }
            }
        }
        else {
            flag_mistake = 1;
        }
    }

    size = (a).size();
    for (int i = 1; i < size; i++) {
        if ((a)[i - 1] == ' ' && (a)[i] == ' ') {
            (a).erase(--i, 1);

            size--;
        }
    }
    for (int i = 0; i < 3; i++) {
        a[i] = toupper(a[i]);

    }

    return a;
}

std::string NameInput() {
    std::string a;
    int size;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    getline(std::cin, a, '\n');
    size = a.size();
    if (size) {
        while (size != 0 && a[0] == ' ' || (a[0] == '\t')) {
            a.erase(0, 1);
            --size;
        }
        while (size != 0 && a[size - 1] == ' ' || (a[0] == '\t')) {
            a.erase(--size, 1);
        }
    }
    size = a.size();
    for (int i = 1; i < size; i++) {
        if ((a)[i - 1] == ' ' && (a)[i] == ' ') {
            (a).erase(--i, 1);

            size--;
        }
    }

    while (std::cin.fail() || a.size() < 2 || a.size() > 30 || (a.find_first_of("0123456789,!@#$%^&*()_+-=./|{}[]") <= 30)) {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nIncorrect data!\nPlease input a new one.(2 <= length <= 30, and no numbers or spec symbols)\n\nIN: ";
        getline(std::cin, a, '\n');
        size = (a).size();
        if (size) {
            while (size != 0 && (a)[0] == ' ' || (a[0] == '\t')) {
                (a).erase(0, 1);
                --size;
            }
            while (size != 0 && (a)[size - 1] == ' ' || (a[0] == '\t')) {
                (a).erase(--size, 1);
            }
        }
        size = a.size();
        for (int i = 1; i < size; i++) {
            if ((a)[i - 1] == ' ' && (a)[i] == ' ') {
                (a).erase(--i, 1);

                size--;
            }
        }
    }

    size = (a).size();
    for (int i = 1; i < size; i++) {
        if ((a)[i - 1] == ' ' && (a)[i] == ' ') {
            (a).erase(--i, 1);

            size--;
        }
    }
    return a;

}

int HowManyDays (int x, int y) {
    return 28 + ((x + (x / 8)) % 2) + 2 % x + ((1 + (1 - (y % 4 + 2) % (y % 4 + 1)) * ((y % 100 + 2) % (y % 100 + 1)) + (1 - (y % 400 + 2) % (y % 400 + 1))) / x) + (1 / x) - (((1 - (y % 4 + 2) % (y % 4 + 1)) * ((y % 100 + 2) % (y % 100 + 1)) + (1 - (y % 400 + 2) % (y % 400 + 1))) / x); 
}

std::string DateInput() {
    std::string a;
    int size;
    bool flag_mistake = 0;
    int day = 0;
    int month = 0;
    int year = 0;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    getline(std::cin, a, '\n');
    size = a.size();
    if (size) {
        while (size != 0 && a[0] == ' ') {
            a.erase(0, 1);
            --size;
        }
        while (size != 0 && a[size - 1] == ' ') {
            a.erase(--size, 1);
        }
    }

    if (a.size() == 10 && a[2] == '.' && a[5] == '.') {
        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) continue;
            if (!((a[i] >= '0') && (a[i] <= '9'))) {
                flag_mistake = 1;
                break;
            }
        }
        day = std::stoi( a.substr(0, 2));
        month = std::stoi(a.substr(3, 2));
        year = std::stoi(a.substr(6, 4));
        std::cout << HowManyDays(month, year) << std::endl;
        if (month > 12 || day > HowManyDays(month, year)) {
            flag_mistake = 1;
        }
        

    }
    else {
        flag_mistake = 1;
    }

    while (std::cin.fail() || flag_mistake) {
        flag_mistake = 0;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nIncorrect data!\nPlease input a new one. Date number FORMAT: NN.NN.NNNN\n\nIN: ";
        getline(std::cin, a, '\n');
        size = (a).size();
        if (size) {
            while (size != 0 && (a)[0] == ' ' || (a[0] == '\t')) {
                (a).erase(0, 1);
                --size;
            }
            while (size != 0 && (a)[size - 1] == ' ' || (a[0] == '\t')) {
                (a).erase(--size, 1);
            }
        }


        if (a.size() == 10 && a[2] == '.' && a[5] == '.') {
            for (int i = 0; i < 10; i++) {
                if (i == 2 || i == 5) continue;
                if (!((a[i] >= '0') && (a[i] <= '9'))) {
                    flag_mistake = 1;
                    break;
                }
            }
            day = std::stoi(a.substr(0, 2));
            month = std::stoi(a.substr(3, 2));
            year = std::stoi(a.substr(6, 4));
            std::cout << HowManyDays(month, year) << std::endl;
            if (month > 12 || day > HowManyDays(month, year)) {
                flag_mistake = 1;
            }


        }
        else {
            flag_mistake = 1;
        }
    }

    size = (a).size();
    for (int i = 1; i < size; i++) {
        if ((a)[i - 1] == ' ' && (a)[i] == ' ') {
            (a).erase(--i, 1);

            size--;
        }
    }
    return a;

}

std::string TimeInput() {
    std::string a;
    int size;
    bool flag_mistake = 0;
    int hour, minute;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    getline(std::cin, a, '\n');
    size = a.size();
    if (size) {
        while (size != 0 && a[0] == ' ') {
            a.erase(0, 1);
            --size;
        }
        while (size != 0 && a[size - 1] == ' ') {
            a.erase(--size, 1);
        }
    }

    if (a.size() == 5 && a[2] == ':' ){
        for (int i = 0; i < 5; i++) {
            if (i == 2) continue;
            if (!((a[i] >= '0') && (a[i] <= '9'))) {
                flag_mistake = 1;
                break;
            }
        }
        hour = std::stoi(a.substr(0, 2));
        minute = std::stoi(a.substr(3, 2));
        
        if (hour >= 24 || minute >= 60) {
            flag_mistake = 1;
        }


    }
    else {
        flag_mistake = 1;
    }

    while (std::cin.fail() || flag_mistake) {
        flag_mistake = 0;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nIncorrect data!\nPlease input a new one. Time number FORMAT: NN:NN\n\nIN: ";
        getline(std::cin, a, '\n');
        size = (a).size();
        if (size) {
            while (size != 0 && (a)[0] == ' ' || (a[0] == '\t')) {
                (a).erase(0, 1);
                --size;
            }
            while (size != 0 && (a)[size - 1] == ' ' || (a[0] == '\t')) {
                (a).erase(--size, 1);
            }
        }


        if (a.size() == 5 && a[2] == ':') {
            for (int i = 0; i < 5; i++) {
                if (i == 2) continue;
                if (!((a[i] >= '0') && (a[i] <= '9'))) {
                    flag_mistake = 1;
                    break;
                }
            }
            hour = std::stoi(a.substr(0, 2));
            minute = std::stoi(a.substr(3, 2));

            if (hour >= 24 || minute >= 60) {
                flag_mistake = 1;
            }


        }
        else {
            flag_mistake = 1;
        }
    }

    size = (a).size();
    for (int i = 1; i < size; i++) {
        if ((a)[i - 1] == ' ' && (a)[i] == ' ') {
            (a).erase(--i, 1);

            size--;
        }
    }
    return a;

}

std::string PlaneTicketIdInput() {
    std::string a;
    int size;
    bool flag_mistake = 0;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    getline(std::cin, a, '\n');
    size = a.size();
    if (size) {
        while (size != 0 && a[0] == ' ' || (a[0] == '\t')) {
            a.erase(0, 1);
            --size;
        }
        while (size != 0 && a[size - 1] == ' ' || (a[0] == '\t')) {
            a.erase(--size, 1);
        }
    }

    if (a.size() == 9) {
        for (int i = 0; i < 9; i++) {
            if (!((a[i] >= '0') && (a[i] <= '9'))) {
                flag_mistake = 1;
                break;
            }
        }
    }
    else {
        flag_mistake = 1;
    }

    while (std::cin.fail() || flag_mistake) {
        flag_mistake = 0;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nIncorrect data!\nPlease input a new one. Passport number FORMAT: NNNNNNNNN\n\nIN: ";
        getline(std::cin, a, '\n');
        size = (a).size();
        if (size) {
            while (size != 0 && (a)[0] == ' ' || (a[0] == '\t')) {
                (a).erase(0, 1);
                --size;
            }
            while (size != 0 && (a)[size - 1] == ' ' || (a[0] == '\t')) {
                (a).erase(--size, 1);
            }
        }

        if (a.size() == 9) {
            for (int i = 0; i < 9; i++) {
                if (!((a[i] >= '0') && (a[i] <= '9'))) {
                    flag_mistake = 1;
                    break;
                }
            }
        }
        else {
            flag_mistake = 1;
        }
    }

    size = (a).size();
    for (int i = 1; i < size; i++) {
        if ((a)[i - 1] == ' ' && (a)[i] == ' ') {
            (a).erase(--i, 1);

            size--;
        }
    }
    return a;

}

// cheak int input
void reader(int* a, int horiz_low = -2147483648, int horiz_high = 2147483647) {
    while (std::cin.fail() || (std::cin.get() != '\n') || *a < horiz_low || *a > horiz_high) {
        std::cin.clear();
        //std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nIncorrect data(" << horiz_low << ";" << horiz_high << ")\n";
        std::cout << " Please input new one: ";
        std::cin >> *a;
        std::cout <<std::endl;
    }
}

//dev tools
bool load(ListOfPassengers* arr[], Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list, std::string fname) {
    std::ifstream fr;
    Passenger passanger;
    Flight flight;
    PlaneTicket ticket;
    int size;
    fr.open(fname);

    std::string passport_id, place, date_of_issue, full_name, date_of_birth;
    std::string flight_id, company_name, departure_name, arrival_name, date_of_departure, time_of_departure;
    std::string seat_amount, free_seat_amount, ticket_id;
    std::string test;
    std::string tag;
    int c = -1;
    bool c_flag;
    int cursor, count;
    if (!fr.is_open()) {
        return 0;
    }
    else {
        while (!fr.eof()) {
            c_flag = 0;
            count = 0;
            cursor = fr.tellg();
            getline(fr, test, '\n');
            for (int i = 0; i < test.size(); i++) {
                if (test[i] == '|') count++;
            }
            if (count != 0) fr.seekg(cursor);
            else continue;
            //cout <<"cur before" << fr.tellg() << endl;
            getline(fr, tag, '|');
            if (tag == "*")
            {
                getline(fr, passport_id, '|');
                getline(fr, place, '|');
                getline(fr, date_of_issue, '|');
                getline(fr, full_name, '|');
                getline(fr, date_of_birth, '\n');
                passanger.passport_id = passport_id;
                passanger.place = place;
                passanger.date_of_issue = date_of_issue;
                passanger.full_name = full_name;
                passanger.date_of_birth = date_of_birth;
                AddHash(arr, passanger);
            }
            else if (tag == "№") {
                getline(fr, flight_id, '|');
                getline(fr, company_name, '|');
                getline(fr, departure_name, '|');
                getline(fr, arrival_name, '|');
                getline(fr, date_of_departure, '|');
                getline(fr, time_of_departure, '|');
                getline(fr, seat_amount, '|');
                getline(fr, free_seat_amount, '\n');
                flight.flight_id = flight_id;
                flight.company_name = company_name;
                flight.departure_name = departure_name;
                flight.arrival_name = arrival_name;
                flight.date_of_departure = date_of_departure;
                flight.time_of_departure = time_of_departure;
                flight.seat_amount = std::stoi(seat_amount);
                flight.free_seat_amount = std::stoi(free_seat_amount);
                flight_tree = AddTreeElem(flight_tree, flight);
            }
            else if (tag == "$") {
                getline(fr, passport_id, '|');
                getline(fr, flight_id, '|');
                getline(fr, ticket_id, '\n');
                ticket.passport_id = passport_id;
                ticket.flight_id = flight_id;
                ticket.ticket_id = ticket_id;
                AddListOfPlaneTickets(plane_tickets_list, ticket);
                
                
            }
            else {
                //fr.seekg(cursor);
                continue;
            }
            
            
            //cout << "cur after" << fr.tellg() << endl;

            
        }

    }
    return 1;
}

void loadProceeder(Tree*& flight_tree, ListOfPlaneTickets*& plane_tickets_list) {
    ListOfPlaneTickets* cur = plane_tickets_list;
    Flight holder;
    if (!(plane_tickets_list)) {
        return;
    }
    while (cur->next != plane_tickets_list) {
        holder.flight_id = cur->value.flight_id;
        if (isFreeSeatsTreeBool(flight_tree, holder)) {
            
            FreeSeatsDeacreseTree(flight_tree, cur->value.flight_id);
        }
        
        cur = cur->next;
        
    }
    if (isFreeSeatsTreeBool(flight_tree, holder)) {

        FreeSeatsDeacreseTree(flight_tree, cur->value.flight_id);
    }
    
    //last
    return;
}