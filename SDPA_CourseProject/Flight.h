#ifndef Flight_h
#define Flight_h

#include <iostream>
#include <string>
#include <iomanip>

struct Flight {
	std::string flight_id = "AAA-NNN";
	std::string company_name = "PLACE";
	std::string departure_name = "xx.xx.xxxx";
	std::string arrival_name = "Place holder";
	std::string date_of_departure = "xx.xx.xxxx";
	std::string time_of_departure = "xx.xx.xxxx";
	int seat_amount = 0;
	int free_seat_amount = 0;
};

struct Tree {
	//Tree* previous;
	Tree* left;
	Tree* right;
	Flight value;
	int height;
};

Tree* balance(Tree* p);

int getheight(struct Tree*& elem);
int bfactor(struct Tree*& elem);
void fixheight(struct Tree*& elem);

Tree* left_rotate(struct Tree*& elem);
Tree* Big_left_rotate(struct Tree*& elem);
Tree* right_rotate(struct Tree*& elem);
Tree* Big_right_rotate(struct Tree*& elem);
Tree* find_min(Tree*& Root);
Tree* rem_min(Tree*& Root);
Tree* balance(Tree* p);

Tree* AddTreeElem(Tree* Root, Flight n);
Tree* DeleteTreeElem(struct Tree*& Root, Flight value);
bool FindTreeBool(struct Tree*& Root, Flight value);

//dev
void ShowTree(Tree* p, int indent = 0);

#endif 