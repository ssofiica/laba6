#pragma once
#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_SIZE = 5;
template <class T>
class MyVector
{
private:
	void resize();
protected:
	int maxsize;
	int size;
	T* pdata;
public:
	MyVector();
	MyVector(T el);
	MyVector(MyVector& v);
	~MyVector();
	void add_element(T el);
	bool delete_element(int i);
	T& operator[] (int i) const;
	void sort();

	bool operator==(const MyVector& v);
	int Size() const { return size; }
	int Maxsize() { return maxsize; }
	int find(T el);
	MyVector& operator=(const MyVector& v);
	friend void scopy(char* s1, const char* s2);
};
void scopy(char* s1, const char* s2);

template<>
MyVector<char*>& MyVector<char*>::operator=(const MyVector& v) {
	maxsize = v.maxsize;
	size = v.size;
	delete[] pdata;
	pdata = new char* [maxsize];
	for (int i = 0; i < size; i++) {
		pdata[i] = new char[strlen(v.pdata[i]) + 1];
		scopy(pdata[i], v.pdata[i]);
	}
	return *this;
}
template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& v) {
	maxsize = v.maxsize;
	size = v.size;
	delete[] pdata;
	pdata = new T[maxsize];
	for (int i = 0; i < size; i++)
		pdata[i] = v.pdata[i];
	return *this;
}
template<class T>
MyVector<T>::MyVector()
{
	maxsize = MAX_SIZE;
	pdata = new T[maxsize];
	size = 0;
}
template<>
MyVector<char*>::MyVector(char* el)
{
	maxsize = MAX_SIZE;
	size = 1;
	pdata = new char* [maxsize];
	if (el != NULL) {
		pdata[0] = new char[strlen(el) + 1];
		scopy(pdata[0], el);
	}
	else (size = 0);
}
template<class T>
MyVector<T>::MyVector(T el)
{
	maxsize = MAX_SIZE;
	size = 1;
	pdata = new T[maxsize];
	pdata[0] = el;
}
template<class T>
ostream& operator<<(ostream& out, MyVector<T>& v)
{
	out << endl;
	for (int i = 0; i < v.Size(); i++) {
		out << v[i] << ' ';
	}
	return out;
}
template<>
MyVector<char*>::MyVector(MyVector& v)
{
	maxsize = v.maxsize;
	size = v.size;
	pdata = new char* [maxsize];
	for (int i = 0; i < size; i++) {
		pdata[i] = new char[strlen(v.pdata[i]) + 1];
		scopy(pdata[i], v.pdata[i]);
	}
}
template<class T>
MyVector<T>::MyVector(MyVector& v)
{
	maxsize = v.maxsize;
	size = v.size;
	pdata = new T[maxsize];
	for (int i = 0; i < size; i++) {
		pdata[i] = new T[strlen(v.pdata[i]) + 1];
		scopy(pdata[i], v.pdata[i]);
	}
}
template<>
MyVector<char*>::~MyVector()
{
	for (int i = 0; i < size; i++)
	{
		delete[] pdata[i];
	}
	delete[] pdata;
}
template<class T>
MyVector<T>::~MyVector()
{
	delete[] pdata;
}
template<>
void MyVector<char*>::resize()
{
	if (size == maxsize) maxsize = maxsize * 15 / 10;
	else {
		if (size < maxsize / 2) maxsize = maxsize * 10 / 15;
		else return;
	}
	char** tmp = new char* [maxsize];
	for (int i = 0; i < size - 1; i++) {
		tmp[i] = new char[strlen(pdata[i]) + 1];
		scopy(tmp[i], pdata[i]);
	}
	for (int i = 0; i < size - 1; i++)
		delete[] pdata[i];
	delete[] pdata;
	pdata = tmp;
}
template<class T>
void MyVector<T>::resize()
{
	if (size == maxsize) maxsize = maxsize * 15 / 10;
	else {
		if (size < maxsize / 2) maxsize = maxsize * 10 / 15;
		else return;
	}
	T* tmp = new T[maxsize];
	for (int i = 0; i < size; i++) {
		tmp[i] = pdata[i];
	}
	delete[] pdata;
	pdata = tmp;
}
template<>
void MyVector<char*>::add_element(char* el)
{
	size++;
	resize();
	pdata[size - 1] = new char[strlen(el) + 1];
	scopy(pdata[size - 1], el);
}
template<class T>
void MyVector<T>::add_element(T el)
{
	size++;
	resize();
	pdata[size - 1] = el;
}
template<>
bool MyVector<char*>::delete_element(int ind)
{
	if ((ind < 0) && (ind >= size)) return 0;
	for (int i = ind; i < size - 1; i++) {
		pdata[i] = pdata[i + 1];
	}
	resize();
	size--;
	return 1;
}
template<class T>
bool MyVector<T>::delete_element(int ind)
{
	if ((ind < 0) && (ind >= size)) return 0;
	for (int i = ind; i < size; i++) {
		pdata[i] = pdata[i + 1];
	}
	size--;
	resize();
	return 1;
}
template<class T>
T& MyVector<T>::operator[] (int ind) const
{
	if ((ind >= 0) || (ind < size)) return pdata[ind];
}
template<>
void MyVector<char*>::sort()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (strcmp(pdata[j], pdata[j + 1]) > 0) {
				char* tmp = new char[strlen(pdata[j]) + 1];
				scopy(tmp, pdata[j]);
				scopy(pdata[j], pdata[j + 1]);
				scopy(pdata[j + 1], tmp);
				delete[] tmp;
			}
		}
	}
}
template<class T>
void MyVector<T>::sort()
{
	T tmp = (T)0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (pdata[j] > pdata[j + 1]) {
				tmp = pdata[j];
				pdata[j] = pdata[j + 1];
				pdata[j + 1] = tmp;
			}
		}
	}
}
template<class T>
bool MyVector<T>::operator==(const MyVector& v) {
	if (Size() == v.Size()) {
		bool k = 1;
		for (int i = 0; i < v.Size(); i++) {
			if (*this != v) {
				k = 0;
				return k;
			}
		}
		return k;
	}
	else return 0;
}
template<>
int MyVector<char*>::find(char* el)
{
	bool flag = false;
	int l = 0;
	int r = size;
	int mid = -1;
	while ((l <= r) && (!flag)) {
		mid = (l + r) / 2;
		if (strcmp(pdata[mid], el) == 0) flag = true;
		if (strcmp(pdata[mid], el) > 0) r = mid - 1;
		else l = mid + 1;
	}
	if (!flag) return -1;
	return mid;
}
template<class T>
int MyVector<T>::find(T el)
{
	bool flag = false;
	int l = 0;
	int r = size;
	int mid = -1;
	while ((l <= r) && (!flag)){
		mid = (l + r) / 2;
		if (pdata[mid] == el) flag = true;
		if (pdata[mid] > el) r = mid - 1;
		else l = mid + 1;
	}
	return mid;
}
void scopy(char* s1, const char* s2)
{

	int i = 0;
	while (s2[i] != '\0') {
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}
#endif