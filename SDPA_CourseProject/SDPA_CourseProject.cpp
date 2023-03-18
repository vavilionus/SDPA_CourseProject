#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif
#include <iostream>
#include "Passenger.h"
#include "Interface.h"
#include "Flight.h"
#include "PlaneTicket.h"
#include <Windows.h>


int main()
{
    //SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE) ,ENABLE_LINE_INPUT);
    int operathion_choice;
    ListOfPassengers* hash_table[100];
    Tree* flight_tree = NULL;
    ListOfPlaneTickets* plane_ticket_list = NULL;
    for (int i = 0; i < 100; i++) {
        hash_table[i] = NULL;
    }

    

    load(hash_table, flight_tree, plane_ticket_list, "load.txt");
    ListQuickSort(plane_ticket_list);
    loadProceeder(flight_tree, plane_ticket_list);
    //std::cout << IsWordContains("Amsterdam", "ma") << std::endl << std::endl;
    while (true) {
        std::cout << "\nPlease choose operathion:\n    1. New passenger registration\n    2. Delete passenger info\n    3. Show passengers  info\n    4. Clear ALL passangers data\n    5. Add new Flight\n    6. Delete Flight\n    7. Show Flight info\n    8. Clear ALL Flights\n    9. Buy ticket\n    10. Return ticket\n    0. Escape program\n    (Warning! all unsaved information will Disappear)\n\nIN: ";
        std::cin >> operathion_choice;
        reader(&operathion_choice, 0, 10);

        switch (operathion_choice) {
        case 0:
            //тут нужна очистка всех структур
            //free_Price(&list);
            flight_tree = ClearTreeElem(flight_tree);
            for (int i = 0; i < 100; i++) {
                ClearListOfPassengers(&hash_table[i]);
            }
            ClearListOfPlaneTickets(plane_ticket_list);
            delete[] *hash_table;
            
            delete flight_tree;
            std::cout << "\n\nProgram is finoshed!" << std::endl;
            return 0;
            _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
            _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
            _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
            _CrtDumpMemoryLeaks();

        case 1:
            CreatePassenger(hash_table);
            break;

        case 2:
            DeletePassanger(hash_table, flight_tree, plane_ticket_list);
            break;

        case 3:

            ShowPassenger(hash_table, flight_tree, plane_ticket_list);
            
            break;

        case 4:
            ClearAllPassangersData(hash_table, flight_tree, plane_ticket_list);
            break;

        case 5:
            CreateFlight(flight_tree);
            
            break;

        case 6:
            ShowListOfPlaneTickets(plane_ticket_list);
            DeleteFlight(flight_tree, plane_ticket_list);
            ShowListOfPlaneTickets(plane_ticket_list);
            break;

        case 7:
            
            ShowFlight(hash_table, flight_tree, plane_ticket_list);
            break;

        case 8:
            ClearAllFlightData(flight_tree, plane_ticket_list);
            break;

        case 9:
            ShowListOfPlaneTickets(plane_ticket_list);
            BuyTicket(hash_table, flight_tree, plane_ticket_list);
            ShowListOfPlaneTickets(plane_ticket_list);
            break;
        case 10:
            ShowListOfPlaneTickets(plane_ticket_list);
            ReturnTicket(flight_tree, plane_ticket_list);
            ShowListOfPlaneTickets(plane_ticket_list);
            break;
        }



    }
    
    return 0;
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();
}

