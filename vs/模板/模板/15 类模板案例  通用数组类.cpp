/*2023-8-24*/

//通用数组类要求：
//1、可以对内置数据类型以及自定义数据类型的数据进行存储
//2、将数组中的数据存储到堆区
//3、构造函数中可以传入数组的容量
//4、提供对应的拷贝构造函数函数以及operator=防止浅拷贝问题
//5、提供尾插法和尾删法对数组中的数据进行增加和删除
//6、可以通过下标发方式访问数组的元素
//7、可以获取数组中当前元素个数和数组的容量


#include <iostream>
#include <string>

using namespace std;

//通用数组模板
template<typename T2>
class MyArray{
public:

	//初始化
	MyArray(int num){
		this->m_Num = num;
		*m_Array = new T2[this->m_Num];
	}

	//重载=
	MyArray& operator=(T2 &p){
		if(this->m_Array != NULL){
			delete this->m_Array;
			this->m_Array = NULL;
		}

		this->m_Array = p.m_Array;

		return *this;
	}


	MyArray(const MyArray &p){
		this->m_Num = p.m_Num;
		if(p.m_Array != NULL){
			this->m_Array = p.m_Array;
		}else{
			cout << "拷贝数组为空!" << endl;
		}
	}



	//释放堆区空间
	~MyArray(){
		if(this->m_Num != nullptr){
			for(int i = 0; i < this->m_Num; i++ ){
				delete this->m_Array[i];
				this->m_Array[i] = NULL;
			}
		}
	}

	//数组的容量
	int m_Num;
	//指针 用于维护堆区数组数据
	T2 *m_Array;
};




void test01(){
	
}


int main(){

	test01();

	system("pause");
	return 0;
}