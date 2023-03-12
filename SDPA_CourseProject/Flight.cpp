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

Tree* balance(Tree* p) // балансировка узла p
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
    return p; // балансировка не нужна
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

//возвращает 1, если в дереве уже сть такой полет
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

