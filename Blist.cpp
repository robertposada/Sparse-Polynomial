/*
Name(s): Kevin Nguyen & Robert Posada
Date: 11/09/2015
CS-102
Project #2
*/

#include <iostream>
#include <algorithm>
#include "Blist.h"
using namespace std;

// getters for Bnode - WORKS
template <class T>
T Bnode<T>::getVal(void) {
    return value;
}

template <class T>
Bnode<T>* Bnode<T>::getNext() {
    return next;
}

template <class T>
Bnode<T>* Bnode<T>::getPrev() {
    return prev;
}

// getters for Blist - WORKS
template <class T>
Bnode<T>* Blist<T>::getFront() {
    return front;
}
template <class T>
Bnode<T>* Blist<T>::getBack() {
    return back;
}

// checks if the list is empty
template <class T>
bool Blist<T>::empty(void) {
    if (front == nullptr) {
        return true; // the list is empty
    }
    else {
        return false; // the list is not empty
    }
}

// pop a node from the back - WORKS
template <class T>
T Blist<T>::pop_back(void) {
    // assumes list is not empty
    Bnode<T> *temp = back;
    T ret = temp->value;
    if (front == back) {
        front = back = nullptr;
    }
    else {
        back = back->prev;
        back->next = nullptr;
    }
    delete temp;
    size--;
    return ret;
}

// pop a node from the front - WORKS
template <class T>
T Blist<T>::pop_front(void) {
    Bnode<T> *temp = front;
    T ret = temp->value;
    if (front == back) {
        front = back = nullptr;
    }
    else {
        front = front->next;
        front->prev = nullptr;
    }
    delete temp;
    size--;
    return ret;
}

// push a node onto the back - WORKS
template <class T>
void Blist<T>::push_back(T value) {
    Bnode<T> *newNode = new Bnode<T>;
    if (back == nullptr) { // the list is empty
        newNode->value = value;
        newNode->next = newNode->prev = nullptr;
        front = back = newNode;
    }
    else {
        newNode->value = value;
        newNode->prev = back;
        back->next = newNode;
        newNode->next = nullptr;
        back = newNode;
    }
    size++;
    return;
}

// push a node onto the front - WORKS
template <class T>
void Blist<T>::push_front(T value) {
    Bnode<T> *newNode = new Bnode<T>;
    if (back == nullptr) { // the list is empty
        newNode->value = value;
        newNode->next = newNode->prev = nullptr;
        front = back = newNode;
    }
    else {
        newNode->value = value;
        newNode->next = front;
        front->prev = newNode;
        newNode->prev = nullptr;
        front = newNode;
    }
    size++;
    return;
}

// array access operator - WORKS
template <class T>
T Blist<T>::operator [](const int index) {
    Bnode<T> *runner = front;
    for (int i = 0; i < index; i++) {
        runner = runner->next;
    }
    return runner->value; // returns the value of the node at specified index
}

// default constructor - WORKS
template <class T>
Blist<T>::Blist() {
    front = back = nullptr;
    size = 0;
}

// array constructor - WORKS
template <class T>
Blist<T>::Blist(T arr[], int sz) {
    front = back = nullptr;
    size = 0;
    for (int i = 0; i < sz; i++) {
        push_back(arr[i]);
    }
}

// copy constructor - WORKS
template <class T>
Blist<T>::Blist(const Blist<T>& list) {
    front = back = nullptr;
        size = 0;
    Bnode<T> *r1 = list.front;
    while (r1 != nullptr) {
        push_back(r1->value);
        r1 = r1->next;
    }
}

// destructor
template <class T>
Blist<T>::~Blist(void) {
    Bnode<T> *current = front;
    while (current != nullptr) {
        Bnode<T> *next = current->next;
        delete current;
        current = next;
    }
    front = back = nullptr;
}

// assignment operator - WORKS
template <class T>
Blist<T> Blist<T>::operator =(const Blist<T>& list) {
    this->~Blist(); // empty the list first
    size = 0;
    Bnode<T> *current = list.front;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
    return *this;
}

// print function - WORKS
template <class T>
void Blist<T>::print(char symbol, void (*print)(T value)) {
    Bnode<T> *runner = front;
    while (runner->next != nullptr) {
        print(runner->value);
        cout << ' ' << symbol << ' ';
        runner = runner->next;
    }
    print(runner->value);
    return;

}

// get size - WORKS
template <class T>
int Blist<T>::getSize() {
    return size;
}

// bubble sort - WORKS
template <class T>
void Blist<T>::bsort(Bnode<T> *left, Bnode<T> *right) {
    Bnode<T> *l = left;
    for (int i = 0; i < getPos(right); i++) {
        while (l->next != right->next) {
            if (l->value > l->next->value) {
                T temp = l->next->value;
                l->next->value = l->value;
                l->value = temp;
            }
            l = l->next;
        }
        l = left;
    }
}

// bubble sort w/ cmp - PENDING
template <class T>
void Blist<T>::bsort(Bnode<T> *left, Bnode<T> *right, int (*cmp)(T val, T val2)) {
    Bnode<T> *l = left;
    for (int i = 0; i < getPos(right); i++) {
        while (l->next != right->next) {
            if (cmp(l->value, l->next->value) == 1) {
                T temp = l->next->value;
                l->next->value = l->value;
                l->value = temp;
            }
            l = l->next;
        }
        l = left;
    }
}

// insert - WORKS
template <class T>
void Blist<T>::insert(Bnode<T> *p, T val) {
    if (p->next == nullptr || p == nullptr) {
        push_front(val);
    }
    else {
        Bnode<T> *q = new Bnode<T>;
        q->value = val;
        q->next = p->next;
        q->prev = p;
        p->next->prev = q;
        p->next = q;
    }
    return;
}

// deletes a node from the list - WORKS
template <class T>
void Blist<T>::del(Bnode<T>* p) {
    if (front == p) {
        pop_front();
    }
    else if (back == p) {
        pop_back();

    }
    else if (p != nullptr) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        size--;
    }
    return;
}

// creates a sublist of the given linked list - WORKS
template <class T>
Blist<T> Blist<T>::sublist(Bnode<T> *b, Bnode<T> *e) {
    Bnode<T> *temp;
    Blist<T> list;
    temp = b;
    do {
        list.push_back(temp->value);
        temp = temp->next;
    } while (temp != e->next);
    return list;
}

// returns a pointer to the node at index - WORKS
template <class T>
Bnode<T>* Blist<T>::at(const int& index) {
    Bnode<T> *temp = front;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp;
}

// gives the position of given node in list
template <class T>
int Blist<T>::getPos(Bnode<T> *p) {
    int position = 0;
    Bnode<T> *temp = front;
    while (temp != p) {
        position++;
        temp = temp->next;
    }
    return position;
}
















