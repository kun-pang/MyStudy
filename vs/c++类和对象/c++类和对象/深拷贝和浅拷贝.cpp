/*2023—8—2*/

//深拷贝与浅拷贝

//浅拷贝：简单的赋值拷贝操作		浅拷贝缺点：对于堆区内存空间的重复释放

//深拷贝：在堆区重新申请，进行拷贝操作 

#include <iostream>

using namespace std;

//人类
class Person{
public:
	Person(){
		cout << "调用默认构造函数！" << endl;
	}

	Person(int  y_age, int y_heignt){
		age = y_age;
		heignt = new int(y_heignt);			//通过new的方式在堆区创建数据，new返回的是指针
		cout << "调用有参构造函数！" << endl;
	}
	
	//没有下面的代码，编译器会报错（但不管有没有报错，没有下面的函数，代码都不合理），
	//理解：1、在text11（）函数里面的局部变量p1、p2都存在栈区，所以释放时会先释放p2后释放p1
	//		2、p1创建的age数据，系统会通过默认的拷贝构造函数将数据浅拷贝给p2，同理p1创建heignt（指针）时，是通过new
	//创建在堆区，所以p1.heignt记录的是堆区y_heignt地址（通过系统的默认拷贝构造函数的p2.heignt也是存的这个）
	//		3、p1、p2在text11（）函数结束后会利用析构函数释放，p2先通过析构函数将堆区y_heignt的数据释放了，然后p1也会调用析构函数对
	//堆区y_heignt进行二次释放（指针悬挂，对同一片内存释放两次），所以出现错误
	Person(const Person &p){
		cout << "调用拷贝构造函数！" << endl;
		age = p.age;
		//heignt = p.heignt;		编译器默认的实现代码
		//深拷贝
		/*int a = *p.heignt;*/
		heignt = new int[*p.heignt];		//让它重新开辟一块堆区内存，用来存放拷贝数据
	
	}



	~Person(){
		//利用析构函数，对堆区的数据进行释放
		if(heignt != NULL){
			delete heignt;		//释放heignt在堆区的空间
			heignt = NULL;		//防止野指针的出现
		}
		cout << "调用析构构造函数！" << endl;
	}
	
	

	int age;
	int * heignt;
};


void text11(){
	Person p1(18,171);

	cout << "p1的年龄：" << p1.age << " 身高：" << *p1.heignt << endl;

	Person p2(p1);

	cout << "p2的年龄：" << p2.age << " 身高：" << *p2.heignt << endl;
}

int main(){
	text11();

	system("pause");
	return 0;
}

//其他源程序影响测试结果