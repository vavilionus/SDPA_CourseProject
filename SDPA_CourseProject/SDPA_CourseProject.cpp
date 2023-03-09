
#include <iostream>
#include "Passenger.h"
#include "Interface.h"

int main()
{
    
    ListOfPassengers* hash_table[100];
    for (int i = 0; i < 100; i++) {
        hash_table[i] = NULL;
    }
    Passenger a;
    a.full_name = "GOD";
    a.passport_id = "1111-111111";
    
    //std::string tst = DateInput();
    
    //std::cout << HowManyDays(3, 2023) << std::endl;
    //std::cout << IsIdUnique(hash_table, "1111-111111") << std::endl;
    //AddHash(hash_table, a);
    //std::cout << IsIdUnique(hash_table, "1111-111111") << std::endl;

    //CreatePassenger(hash_table);
    //CreatePassenger(hash_table);
    a.date_of_birth = DateInput();
    

}

