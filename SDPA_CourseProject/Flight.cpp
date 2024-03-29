#include <iostream>
#include <iomanip>
#include "Flight.h"

int getheight(struct Tree*& elem) {
    if (elem) return elem->height;
    return 0;
}

int bfactor(struct Tree*& elem) {
    return getheight(elem->right) - getheight(elem->left);
}

void fixheight(struct Tree*& elem) {
    if (getheight(elem->left) > getheight(elem->right)) elem->height = getheight(elem->left) + 1;
    else elem->height = getheight(elem->right) + 1;
}

Tree* right_rotate(struct Tree*& elem) {
    Tree* holder = elem->left;
    elem->left = holder->right;
    holder->right = elem;
    fixheight(elem);
    fixheight(holder);
    return holder;
}

Tree* Big_right_rotate(struct Tree*& elem) {
    fixheight(elem);
    elem->left = left_rotate(elem->left);
    return right_rotate(elem);
}

Tree* left_rotate(struct Tree*& elem) {
    Tree* holder = elem->right;
    elem->right = holder->left;
    holder->left = elem;
    fixheight(elem);
    fixheight(holder);
    return holder;
}

Tree* Big_left_rotate(struct Tree*& elem) {
    fixheight(elem);
    elem->right = right_rotate(elem->right);
    return left_rotate(elem);
}

Tree* find_min(Tree*& Root) {
    if (!(Root->left)) return Root;
    find_min(Root->left);
}

Tree* rem_min(Tree*& Root) {
    if (!(Root->left)) return Root->right;
    Root->left = rem_min(Root->left);
    return balance(Root);
}

Tree* balance(Tree* p) // ������������ ���� p
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = right_rotate(p->right);
        return left_rotate(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = left_rotate(p->left);
        return right_rotate(p);
    }
    return p; // ������������ �� �����
}

Tree* AddTreeElem(Tree* Root, Flight n) {
    Tree* cur = Root;
    if (cur == NULL) {
        Tree* p = new Tree;
        p->right = NULL;
        p->left = NULL;
        p->value = n;
        p->height = 1;
        return p;
    }
    if (cur->value.flight_id == n.flight_id) {
        std::cout << "Errore, elements must be uniqe!\n" << std::endl;
        return cur;
    }
    if (n.flight_id < cur->value.flight_id) {
        cur->left = AddTreeElem(cur->left, n);
    }
    else {
        cur->right = AddTreeElem(cur->right, n);
    }
    return balance(cur);
}

Tree* DeleteTreeElem(struct Tree*& Root, Flight value) {
    if (!Root) {
        std::cout << "\nThere is nothing to delete!\n\n";
        return NULL;
    }
    if (value.flight_id < Root->value.flight_id) Root->left = DeleteTreeElem(Root->left, value);
    else if (value.flight_id > Root->value.flight_id) Root->right = DeleteTreeElem(Root->right, value);
    else {
        Tree* L = Root->left;
        Tree* R = Root->right;
        delete Root;
        if (!R) return L;
        Tree* min = find_min(R);
        min->right = rem_min(R);
        min->left = L;
        return balance(min);
    }
    return balance(Root);
}

Tree* ClearTreeElem(struct Tree*& p) {
    if (p != NULL) {
        if (p->left) ClearTreeElem(p->left);
        if (p->right) ClearTreeElem(p->right);
        delete p;
        return NULL;
    }
}

//���������� 1, ���� � ������ ��� ��� ����� �����
bool FindTreeBool(struct Tree*& Root, Flight value) {
    Tree* cur = Root;
    if (!(cur)) {
        return 0;
    }
    while (cur) {
        if (cur->value.flight_id == value.flight_id) {
            return 1;
        }
        if (value.flight_id > cur->value.flight_id) {
            cur = cur->right;
        }
        else {

            cur = cur->left;
        }
    }
    return 0;
}

void ShowTreeElem(struct Tree*& Root, std::string flight_id) {
    Tree* p = Root;
    if (!(p)) {
        return ;
    }
    while (p) {
        if (p->value.flight_id == flight_id) {
            std::cout << "| " << std::setw(7) << p->value.flight_id << " | " << std::setw(30) << p->value.company_name << " | "
                << std::setw(30) << p->value.departure_name << " | " << std::setw(30) << p->value.arrival_name << " | "
                << std::setw(10) << p->value.date_of_departure << " | "
                << std::setw(5) << p->value.time_of_departure << " | " << std::setw(3) << p->value.seat_amount << " | "
                << std::setw(3) << p->value.free_seat_amount << " | " << std::endl;
            std::cout << "|---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----|" << std::endl;
            return;
        }
        if (flight_id > p->value.flight_id) {
            p = p->right;
        }
        else {

            p = p->left;
        }
    }
    return;
}

bool isFreeSeatsTreeBool(struct Tree*& Root, Flight value) {
    Tree* cur = Root;
    if (!(cur)) {
        return 0;
    }
    while (cur) {
        if (cur->value.flight_id == value.flight_id) {
            if (cur->value.free_seat_amount != 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
        if (value.flight_id > cur->value.flight_id) {
            cur = cur->right;
        }
        else {

            cur = cur->left;
        }
    }
    return 0;
}

Flight TakeElemTree(struct Tree*& Root, Flight value) {
    Tree* cur = Root;
    if (!(cur)) {
        return value;
    }
    while (cur) {
        if (cur->value.flight_id == value.flight_id) {
            value = cur->value;
        }
        if (value.flight_id > cur->value.flight_id) {
            cur = cur->right;
        }
        else {

            cur = cur->left;
        }
    }
    return value;
}

void FreeSeatsDeacreseTree(struct Tree*& Root, std::string flight_id) {
    Tree* cur = Root;
    if (!(cur)) {
        return ;
    }
    while (cur) {
        if (cur->value.flight_id == flight_id) {
            cur->value.free_seat_amount--;
            return ;
        }
        if (flight_id > cur->value.flight_id) {
            cur = cur->right;
        }
        else {

            cur = cur->left;
        }
    }
    return ;
}

void FreeSeatsIncreaseTree(struct Tree*& Root, std::string flight_id) {
    Tree* cur = Root;
    if (!(cur)) {
        return;
    }
    while (cur) {
        if (cur->value.flight_id == flight_id) {
            cur->value.free_seat_amount++;
            return;
        }
        if (flight_id > cur->value.flight_id) {
            cur = cur->right;
        }
        else {

            cur = cur->left;
        }
    }
    return;
}

void SymmericalShowTree(Tree* p) {
    if (!p) return;

    SymmericalShowTree(p->left);
    std::cout << "| " << std::setw(7) << p->value.flight_id << " | " << std::setw(30) << p->value.company_name << " | "
        << std::setw(30) << p->value.departure_name << " | " << std::setw(30) << p->value.arrival_name << " | " 
        << std::setw(10) << p->value.date_of_departure << " | "
        << std::setw(5) << p->value.time_of_departure << " | " << std::setw(3) << p->value.seat_amount << " | "
        << std::setw(3) << p->value.free_seat_amount << " | " << std::endl;
    std::cout << "|---------|--------------------------------|--------------------------------|--------------------------------|------------|-------|-----|-----|" << std::endl;
    SymmericalShowTree(p->right);
}

//dev func
void ShowTree(Tree* p, int indent)
{
    if (p != NULL) {
        if (p->left) ShowTree(p->left, indent + 4);
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        std::cout << p->value.flight_id << "\n ";
        if (p->right) ShowTree(p->right, indent + 4);
    }
}

