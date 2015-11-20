/*
 Name(s): Kevin Nguyen & Robert Posada
 Date: 11/09/2015
 CS-102
 Project #2
 */

#include <iostream>
#include <string>
#include <sstream>
#include "Blist.h"
#include "Blist.cpp"

using namespace std;

class Monomial {   // represents coeff * x^deg
    int deg;
    double coeff;
public:
    // constructors
    Monomial(); // default constructor
    Monomial(double c, int d);
    Monomial(const Monomial& mObject); // copy constructor
    int getDegree() {return deg;}
    double getCoeff() {return coeff;}
    friend int cmpDeg(Monomial p, Monomial q);
    friend int cmpCoeff(Monomial p, Monomial q);
    friend void printM(Monomial p);
};

Monomial::Monomial() {
    deg = 0;
    coeff = 0;
}

Monomial::Monomial(double c, int d) {
    coeff = c;
    deg = d;
}

Monomial::Monomial(const Monomial& mObject) {
    deg = mObject.deg;
    coeff = mObject.coeff;
}

// Compare function for Monomial degrees
int cmpDeg(Monomial p, Monomial q) {
    int result = 0;
    if (p.deg > q.deg) {
        result = 1;
    }
    else if (p.deg < q.deg) {
        result = -1;
    }
    return result;
}

// Compare function for Monomial coefficients
int cmpCoeff(Monomial p, Monomial q) {
    int result = 0;
    if (p.coeff > q.coeff) {
        result = 1;
    }
    else if (p.coeff < q.coeff) {
        result = -1;
    }
    return result;
}

// print function for Monomials
void printM(Monomial p) {
    cout << p.coeff << "x^" << p.deg;
}

// --Function pointers for cmp functions-- //
// --------------------------------------- //
int (*deg)(Monomial, Monomial) = cmpDeg;

int (*con)(Monomial, Monomial) = cmpCoeff;

void (*prnt)(Monomial) = printM;
// --------------------------------------- //

// Simplify function for Polynomial operations
Blist<Monomial> simplify(Blist<Monomial> poly) {
    Blist<Monomial> calpoly;
    for (int j = 0; j < poly.getSize() - 1; j++) {
        if (poly[j].getDegree() == poly[j+1].getDegree()) {
            calpoly.push_back(Monomial(poly[j].getCoeff() + poly[j+1].getCoeff(), poly[j].getDegree()));
            j++;
        }
        else {
            calpoly.push_back(Monomial(poly[j].getCoeff(), poly[j].getDegree()));
        }
        if (j + 1 == poly.getSize() - 1) { // checks if j is equal to the last index of poly
            calpoly.push_back(Monomial(poly[j+1].getCoeff(), poly[j+1].getDegree()));
        }
    }
    bool sorted = false;
    while (sorted == false) {
        sorted = true;
        for (int i = 0; i < calpoly.getSize() - 1; i++) {
            if (calpoly[i].getDegree() == calpoly[i+1].getDegree()) {
                sorted = false;
            }
        }
        if (sorted == false) {
            Blist<Monomial> list = calpoly;
            calpoly = simplify(list);
        }
    }

    return calpoly;
}

// Overloaded addition operator
Blist<Monomial> operator + (Blist<Monomial> poly1, Blist<Monomial> poly2) {
    Blist<Monomial> poly, calpoly;
    poly = poly1;
    for (int i = 0; i < poly2.getSize(); i++) {
        poly.push_back(poly2[i]);
    }
    poly.bsort(poly.getFront(), poly.getBack(), deg);
    calpoly = simplify(poly); // calls the simplify function
    
    return calpoly;
}

// Overloaded multiplication operator
Blist<Monomial> operator * (Blist<Monomial> poly1, Blist<Monomial> poly2) {
    Blist<Monomial> poly, calpoly;
    for (int i = 0; i < poly1.getSize(); i++) {
        for (int j = 0; j < poly2.getSize(); j++) {
            poly.push_back(Monomial(poly1[i].getCoeff() * poly2[j].getCoeff(), poly1[i].getDegree() + poly2[j].getDegree()));
        }
    }
    poly.bsort(poly.getFront(), poly.getBack(), deg);
    calpoly = simplify(poly); // calls the simplify function
    
    return calpoly;
}

void userPoly(int& term, int arrd[], int arrc[], Monomial poly[]) {
    string sline;
    cout << endl << "Degrees: " << endl;
    for (int i = 0; i < term; i++) {
        getline(cin, sline);
        stringstream(sline) >> arrd[i];
    }
    cout << endl << "Coefficients: " << endl;
    for (int i = 0; i < term; i++) {
        getline(cin, sline);
        stringstream(sline) >> arrc[i];
    }
    for (int i = 0; i < term; i++) {
        poly[i] = Monomial(arrc[i], arrd[i]);
    }
}

int main()
{
    string sline;
    int term1, term2;
    cout << "SPARSE POLYNOMIAL" << endl;
    cout << "=================" << endl << endl;
    cout << "Polynomial 1:" << endl << "Number of terms: ";
    getline(cin, sline);
    stringstream(sline) >> term1;
    int arrd[term1], arrc[term1];
    Monomial *arr = new Monomial[term1];
    userPoly(term1, arrd, arrc, arr);
    
    cout << endl << "Polynomial 2:" << endl << "Number of terms: ";
    getline(cin, sline);
    stringstream(sline) >> term2;
    int arrd2[term2], arrc2[term2];
    Monomial *arr2 = new Monomial[term2];
    userPoly(term2, arrd2, arrc2, arr2);
    
    Blist<Monomial> poly1(arr, term1);
    Blist<Monomial> poly2(arr2, term2);
    delete [] arr;
    delete [] arr2;
    Blist<Monomial> poly3, poly4;
    
    cout << endl << "Poly1 = ";
    poly1.print('+', prnt);
    cout << endl << "Poly2 = ";
    poly2.print('+', prnt);
    cout << endl << endl;;
    
    poly3 = poly1 + poly2;
    cout << "Poly1 + Poly2 = ";
    poly3.print('+', prnt);
    cout << endl << endl;
    
    poly4 = poly1 * poly2;
    cout << "Poly1 * Poly2 = ";
    poly4.print('+', prnt);
    cout << endl;
    
    return 0;
}
