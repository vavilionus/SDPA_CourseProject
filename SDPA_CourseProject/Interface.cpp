#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include "Passenger.h"
#include "Interface.h"

//1
void CreatePassenger(ListOfPassengers* arr[]) {
    Passenger elem;
    std::string passport_id = "NNNN-NNNNNN";
    std::cout << "Input passport ID:" << std::endl << "\t";
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
    std::cout << "Input date of issue :" << std::endl << "\t";
    elem.date_of_issue = DateInput();
    std::cout << "Input date of birth :" << std::endl << "\t";
    elem.date_of_birth = DateInput();
    AddHash(arr, elem);
}


//3
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

    while (std::cin.fail() || a.size() < 2 || a.size() > 30) {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nIncorrect data!\nPlease input a new one.(2 <= length <= 30)\n\nIN: ";
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