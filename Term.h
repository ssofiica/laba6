#pragma once
#ifndef TERM_H
#define TERM_H
#include <iostream>
#include "Polynomial.h"
using namespace std;

#define LENGTH 30
class Polynomial;

class Term {
protected:
	int coefficient;
	int degree;
public:
	Term(int c = 0, int d = 0) : coefficient(c), degree(d) {};
	int GetCoefficient() { return coefficient; };
	int GetDegree() { return degree; };
	Term& operator+=(const Term& term);
	friend Term operator+(const Term& TermRight, const Term& TermLeft);
	friend ostream& operator<<(ostream& out, Term& term);
	friend Term TakeTerm(char* char_term);
	friend class Polynomial;
	//+=
};
Term& Term::operator+=(const Term& term) {
	coefficient += term.coefficient;
	return *this;
}
Term operator+(const Term& TermRight, const Term& TermLeft) {
	Term tmp;
	tmp.coefficient = TermLeft.coefficient + TermRight.coefficient;
	tmp.degree = TermLeft.degree + TermRight.degree;
	return tmp;
}
ostream& operator<<(ostream& out, Term& term) { //3x0 как 3, 3x1 как 3x, 1x3 как x^3, -3x2  как -3x^2 
	if (term.GetCoefficient() == 0) {
		out << "0";
		return out;
	}
	switch (term.GetDegree()) {
	case 0: out << term.GetCoefficient(); break;
	case 1:
		if (term.GetCoefficient() == 1) out << "x";
		else if (term.GetCoefficient() == -1) out << "-x";
		else out << term.GetCoefficient() << "x";
		break;
	default:
		if (term.GetCoefficient() == 1) out << "x^" << term.GetDegree();
		else if (term.GetCoefficient() == -1) out << "-x^" << term.GetDegree();
		else out << term.GetCoefficient() << "x^" << term.GetDegree();
		break;
	}
	return out;
}

Term TakeTerm(char* char_term){
	Term term;
	char part[5] = { ' ', ' ', ' ', ' ', '\0' };
	bool ControlSymbolX = 0; // наличие аргумента Х
	int ControlCoeff = 0; // наличия коэффициента
	size_t ControlDegree = 0;// наличие степени
	for (int i = 0; i < strlen(char_term); i++) {
		if (char_term[i] == 120) {
			ControlSymbolX = 1;
			if (ControlCoeff == 0) term.coefficient = 1;
			else
				if (ControlCoeff < 2) {
					if (part[0] == '-') {
						term.coefficient = -1;
					}
					else term.coefficient = atoi(part);
				}
				else term.coefficient = atoi(part);
			for (int j = 0; j < strlen(part); j++) {
				part[j] = ' ';
			}
			ControlDegree = 0;
		}
		else {
			part[i] = char_term[i];
			ControlCoeff++;
			ControlDegree = 1;
		}
	}
	if (ControlSymbolX == 0) {
		term.coefficient = atoi(part);
		term.degree = 0;
		return term;
	}
	if (ControlDegree == 1)
		term.degree = atoi(part);
	else term.degree = 1;
	return term;
}
#endif