
#include <iostream>
#include "Passenger.h"
#include "Interface.h"
#include "Flight.h"

int main()
{
    int operathion_choice;
    ListOfPassengers* hash_table[100];
    Tree* flight_tree = NULL;
    for (int i = 0; i < 100; i++) {
        hash_table[i] = NULL;
    }
    /*
    while (true) {
        std::cout << "\nPlease choose operathion:\n    1. New passenger registration\n    2. Delete passenger info\n    3. Show all passengers passport info\n    4. Clear ALL passangers data\n    0. Escape program\n    (Warning! all unsaved information will Disappear)\n\nIN: ";
        std::cin >> operathion_choice;
        reader(&operathion_choice, 0, 3);

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
            
            break;

        case 6:
            
            break;

        case 7:
            
            break;

        case 8:
            
            break;

        }



    }
    */



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


    
    return 0;
}

