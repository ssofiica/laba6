#pragma once
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include "Term.h"
#include "MyVector.h"
using namespace std;

const int MAXSIZE = 6;
const int LENTH = 50;
const int TermLength = 20;

class Polynomial {
protected:
	MyVector<Term> poly;
	int polynomDegree;
public:
	Polynomial() : poly(), polynomDegree(0) {};
	Polynomial(int p) : poly(p), polynomDegree(0) {};
	Polynomial(Term term) : poly(term), polynomDegree(term.degree) {};
	Polynomial(const Polynomial& Polynom);
	friend istream& operator>>(istream& in, Polynomial& Polynom);
	friend ostream& operator<<(ostream& out, Polynomial& Polynom);
	friend Polynomial operator+(const Polynomial& PolynomRight, const Polynomial& PolynomLeft);
	friend Polynomial operator*(const Polynomial& PolynomRight, const Polynomial& PolynomLeft);
	Polynomial& operator=(const Polynomial& Polynom);
	Polynomial& operator+=(const Polynomial& Polynom);
	Polynomial& operator*=(const Polynomial& Polynom);
	//Polynomial SortDegree(Polynomial& Polynom);
};

Polynomial::Polynomial(const Polynomial& Polynom) {
	polynomDegree = Polynom.polynomDegree;
	poly = Polynom.poly;
}
istream& operator>>(istream& in, Polynomial& Polynom) {
	char* tmp = new char[LENGTH]; //вводимая строка
	cin.getline(tmp, LENGTH);
	int end = 0;
	char* char_poly = new char[strlen(tmp) + 1];//строка с полиномом: только цифры, Х, - и =
	for (int i = 0; i < strlen(tmp); i++) { //оставляем только цифры, Х, - и +
		if (tmp[i] > 47 && tmp[i] < 58 || tmp[i] == 120 || tmp[i] == 45 || tmp[i] == 43) {
			char_poly[end] = tmp[i];
			end++;
		}
	}
	char_poly[end] = '\0';
	delete[] tmp;
	char* char_term = new char[TermLength]; // строка только с термом
	int k = 0; //счётчик для char_term
	for (int i = 0; i < end; i++) {
		if (char_poly[i] == 43 || i > 0 && char_poly[i] == 45) {
			//если встречаем + или - записываем просчитанный term в полином
			//обнуляем char_term
			char_term[k] = '\0';
			Polynom.poly.add_element(TakeTerm(char_term));
			k = 0;
			if (char_poly[i] == 45) k++;
			for (int j = 0; j < TermLength - 1; j++) {
				char_term[j] = ' ';
			}
			char_term[TermLength - 1] = '\0';
		}
		else {
			//считываем терм в него надо передать char_term
			if (char_poly[i - 1] == 45) char_term[k - 1] = '-'; //если - разделяет полиномы, то сейчас его дописываем, так, как выше его пропустили
			char_term[k] = char_poly[i];
			k++;
		}
	}
	char_term[k] = '\0';
	Polynom.poly.add_element(TakeTerm(char_term));
	delete[] char_term;
	return in;
}
ostream& operator<<(ostream& out, Polynomial& Polynom) {
	for (int i = 0; i < Polynom.poly.Size(); i++) {
		if (i != 0 && Polynom.poly[i].GetCoefficient() > 0) {
			out << '+';
		}
		if (Polynom.poly[i].GetCoefficient() != 0) {
			out << Polynom.poly[i];
		}
	}
	return out;
}
Polynomial operator+(const Polynomial& PolynomRight, const Polynomial& PolynomLeft) {
	int Control = 0;
	Polynomial Sum(PolynomLeft);
	for (int i = 0; i < PolynomRight.poly.Size(); i++) {
		Control = 0;
		for (int j = 0; j < PolynomLeft.poly.Size(); j++) {
			if (PolynomRight.poly[i].GetDegree() == PolynomLeft.poly[j].GetDegree()) {
				Control = 1;
				Sum.poly[j] += PolynomRight.poly[i];
			}
		}
		if (Control == 0) {
			Sum.poly.add_element(PolynomRight.poly[i]);
		}
	}
	//cout << Sum;
	return Sum;
}
Polynomial operator*(const Polynomial& PolynomRight, const Polynomial& PolynomLeft) {
	Polynomial Multi;
	int MultiCoeff = 0;
	int MultiDegree = 0;
	for (int i = 0; i < PolynomRight.poly.Size(); i++) {
		for (int j = 0; j < PolynomLeft.poly.Size(); j++) {
			MultiCoeff = PolynomRight.poly[i].GetCoefficient() * PolynomLeft.poly[j].GetCoefficient();
			MultiDegree = PolynomRight.poly[i].GetDegree() + PolynomLeft.poly[j].GetDegree();
			Multi.poly.add_element(Term(MultiCoeff, MultiDegree));
		}
	}
	int MultiSize = PolynomRight.poly.Size() * PolynomLeft.poly.Size();
	Polynomial FinMulti;//умножение с приведением подобных членов
	int FinMultiCoeff = 0;
	for (int i = 0; i < MultiSize; i++) {
		FinMultiCoeff = 0;
		FinMultiCoeff = Multi.poly[i].GetCoefficient();
		for (int j = i + 1; j < MultiSize- 1; j++) {
			if (Multi.poly[i].GetDegree() == Multi.poly[j].GetDegree()) {
				FinMultiCoeff += Multi.poly[j].GetCoefficient();
				Multi.poly.delete_element(j);
			}
		}
		FinMulti.poly.add_element(Term(FinMultiCoeff, Multi.poly[i].GetDegree()));
	}
	//cout << FinMulti;
	return FinMulti;
}

Polynomial& Polynomial::operator=(const Polynomial& Polynom) {
	this->poly = Polynom.poly;
	this->polynomDegree = Polynom.polynomDegree;
	return *this;
}
Polynomial& Polynomial::operator+=(const Polynomial& Polynom) {
	*this = *this + Polynom;
	return *this;
}
Polynomial& Polynomial::operator*=(const Polynomial& Polynom) {
	*this = *this * Polynom;
	return *this;
}
//Polynomial Polynomial::SortDegree(Polynomial& Polynom) {
//	Polynomial tmp;
//	for (int i = 0; i < Polynom.poly.Size(); i++) {
//		bool flag = 1;
//		for (int j = 0; j < Polynom.poly.Size() - i - 1; j++) {
//			if (Polynom.poly[j].GetDegree() > Polynom.poly[j + 1].GetDegree()) {
//				flag = 0;
//				tmp.poly[0] = 0;
//				tmp.poly[0] = Polynom.poly[j + 1];
//				Polynom.poly[j + 1] = Polynom.poly[j];
//				Polynom.poly[j] = tmp.poly[0];
//			}
//		}
//		if (flag) {
//			break;
//		}
//	}
//	return Polynom;
//}
#endif