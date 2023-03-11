#ifndef Interface_h
#define Interface_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
//1.Регистрация нового пассажира
void CreatePassenger(ListOfPassengers* arr[]);
//2

//3 Отображение всех зарегестрированных пользователей(1. только паспорт и фио 2. вся ифа)
void ShowAllPassenger(ListOfPassengers* arr[]);

std::string PassportIdInput();
std::string NameInput();
int HowManyDays(int x, int y);
std::string DateInput();
void reader(int* a, int horiz_low, int horiz_high);

#endif 
