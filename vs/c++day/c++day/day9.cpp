/*2023—7—25*/
/*结构体  */

/*结构体
	结构体概念--自定义数据类型
	结构体语法--struct 结构体名 { 结构体成员列表 };
	结构体创建变量的方式
		1.struct 结构体名 变量名
		2.struct 结构体名 = { 成员1值，成员2值······}
		3.创建结构体时顺便把创建变量

	结构体数组
		语法--struct 结构体名 数组名[元素个数] = {{}，{}，{}······}；

	结构体指针
		利用"->"访问结构体中的属性

	结构体嵌套
	
	结构体做函数参数

	结构体const的使用
*/

#include <iostream>
#include <string>

using namespace std;

enum Gender{		//性别
	男,女
};

//结构体--学生类
struct Student{
	//学生数据类型的属性(成员列表)
	string name;	//名字
	int age;		//年龄
	int id;			//学号
	Gender gdr;		//性别
}s3;
//3.创建结构体时顺便把创建变量

struct Teacher{
	string name;	//姓名
	int age;		//工龄
	int id;			//工号
	Student stu;	//所带学生
};

//声明打印学生信息的函数
//值传递（不改变实参）  对于大数据的内容比较吃内存空间
void Students1( Student s);
//地址传递(改变实参)	只改变形参 用常量指针（只读不写）
void Students2( Student * s);
void Students3(const Student * s);

int main9(){
	//创建具体学生变量
	//创建变量时，struct关键次可以省略
	struct Student s1;

	//2.struct 结构体名 = { 成员1值，成员2值······}
	struct Student s2 = {"张三",18,02};

	//1.struct 结构体名 变量名
	//给学生赋值  结构体变量通过“.”访问
	s1.name = "李四";
	s1.age = 19;
	s1.id = 01;

	s3.name = "王五";
	s3.age = 20;
	s3.id = 03;

	cout << "01." << s1.name << " " << s1.age << endl;
	cout << "02." << s2.name << " " << s2.age << endl;
	cout << "03." << s3.name << " " << s3.age << endl;
	cout << endl;


	//结构体数组
	Student stuArr[4] = {
		{"张三",18,01},
		{"李四",19,02},
		{"张三",18,01},
		{"王五",20,03}
	};

	for(int i = 0; i < 4; i++){
		cout << "更改前：" << stuArr[i].name << " "  
			<< stuArr[i].age << " " << stuArr[i].id <<endl;
	}

	//给结构体数组里面的元素赋值
	stuArr[2].name = "赵六";
	stuArr[2].age = 21;
	stuArr[2].id = 04;

	for(int i = 0; i < 4; i++){
		cout << "更改后：" << stuArr[i].name << " "  
			<< stuArr[i].age << " " << stuArr[i].id <<endl;
	}
	cout << endl;

	//结构体指针
	Student *p = &s1;
	//访问结构体元素
	cout << p->name << " " << p->age << " " << p->id << endl;

	//嵌套结构体
	Teacher t;
	t.name = "万老师";
	t.age = 8;
	t.id = 01;
	/*t.stu = {"小一",20,06,"男"};  不允许这样赋值*/
	t.stu.name = "小一";
	t.stu.age = 20;
	t.stu.id = 06;
	t.stu.gdr = 男;
	cout << t.name << " " << t.age << " " << t.id 
		<< " S所带学生： " << t.stu.name << " " << t.stu.age
		<< " " << t.stu.id << " " << t.stu.gdr << endl;
	cout << endl;

	//结构体做函数参数
	Students1(s1);
	cout << " id变化了吗？" << s1.id << endl;
	Students2(&s2);
	cout << " id变化了吗？" << s2.id << endl;
	cout << endl;

	//结构体const的使用
	Students3(&s3);

	system("pause");
	return 0;
}

void Students1( Student s){
	s.id = 00;
	cout << s.name << "恋爱了！" << endl;
}

void Students2( Student * s){
	s->id = 100;
	cout << s->name << "失恋了！" << endl;
}
void Students3(const Student * s){
	//s->id = 100;  报错 加入常量指针只读不写
	cout << s->name << "失恋了！" << endl;
}