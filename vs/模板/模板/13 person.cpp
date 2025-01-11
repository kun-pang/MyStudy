#include "13 person.h"

template<typename T1, typename T2 >
Person<T1, T2>::Person(T1 name, T2 age){
	this->m_Name = name;
	this->m_Age = age;
}

template<typename T1, typename T2 >
void Person<T1, T2>::showPerson(){
	cout << "name:" << this->m_Name << " age:" << this->m_Age << endl; 
}