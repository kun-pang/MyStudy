#pragma once
#include <iostream>
#include <string>

using namespace std;

//ÀàÄ£°å
template<typename T1, typename T2 >
class Person{
public:
	Person(T1 name, T2 age);

	void showPerson();

	T1 m_Name;
	T2 m_Age;
};