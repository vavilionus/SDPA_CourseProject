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

int main()
{
    
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
    while (true) {
        std::cout << "\nPlease choose operathion:\n    1. New passenger registration\n    2. Delete passenger info\n    3. Show passengers  info\n    4. Clear ALL passangers data\n    5. Add new Flight\n    6. Delete Flight\n    7. Show Flight info\n    8. Clear ALL Flights\n    9. Buy ticket\n    10. Return ticket\n    0. Escape program\n    (Warning! all unsaved information will Disappear)\n\nIN: ";
        std::cin >> operathion_choice;
        reader(&operathion_choice, 0, 10);

        switch (operathion_choice) {
        case 0:
            //тут нужна очистка всех структур
            //free_Price(&list);

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
            
            break;

        case 3:

            ShowAllPassenger(hash_table);
            
            break;

        case 4:
            
            break;

        case 5:
            CreateFlight(flight_tree);
            
            break;

        case 6:
            
            break;

        case 7:
            std::cout << "/---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----\\" << std::endl;
            std::cout << "|    ID   |             Company            |            Deparure            |             Arrival            |  Dep.Date  | DTime |seats|sfree|" << std::endl;
            std::cout << "|---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----|" << std::endl;

            SymmericalShowTree(flight_tree);
            break;

        case 8:
            
            break;

        case 9:
            BuyTicket(hash_table, flight_tree, plane_ticket_list);
            ShowListOfPlaneTickets(plane_ticket_list);
            break;
        case 10:
            ReturnTicket(flight_tree, plane_ticket_list);
            ShowListOfPlaneTickets(plane_ticket_list);
            break;
        }



    }
    



    /*
    Flight a, b, c;
    a.flight_id = "AAB-000";
    b.flight_id = "AAA-001";
    c.flight_id = "AAA-002";
    flight_tree = AddTreeElem(flight_tree, a);
    flight_tree = AddTreeElem(flight_tree, b);
    if (!(FindTreeBool(flight_tree, c))) {
        flight_tree = AddTreeElem(flight_tree, c);
    }
    ShowTree(flight_tree);
    */

    //std::string tst = DateInput();
    
    //std::cout << HowManyDays(3, 2023) << std::endl;
    //std::cout << IsIdUnique(hash_table, "1111-111111") << std::endl;
    //AddHash(hash_table, a);
    //std::cout << IsIdUnique(hash_table, "1111-111111") << std::endl;

    //проверка списка
    PlaneTicket a;
    a.ticket_id = "000000012";
    AddListOfPlaneTickets(plane_ticket_list, a);
    a.ticket_id = "000000001";
    AddListOfPlaneTickets(plane_ticket_list, a);
    a.ticket_id = "000000007";
    AddListOfPlaneTickets(plane_ticket_list, a);
    a.ticket_id = "000000005";
    AddListOfPlaneTickets(plane_ticket_list, a);
    a.ticket_id = "000000002";
    AddListOfPlaneTickets(plane_ticket_list, a);
    ShowListOfPlaneTickets(plane_ticket_list);
    std::cout << "---------------------\n";
    ListQuickSort(plane_ticket_list);
    ShowListOfPlaneTickets(plane_ticket_list);
    
    
    return 0;
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();
}

