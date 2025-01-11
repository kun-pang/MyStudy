/*2023—7—25*/
/*结构体案例2  */

/*
英雄结构体(5个)
	姓名，年龄，性别
最后利用冒泡算法，通过年龄进行一个升序排序，最后打印
*/

#include <iostream>
#include <string>

using namespace std;




//定义一个英雄结构体
struct YingXiong{
	string name;	//姓名
	int age;		//年龄
	string gender;	//性别
};


//声明函数
void PaiXu(YingXiong yx[], int len);
void printfYX(YingXiong *t, int len);

int main9t2(){
	int len;
	//创建一个英雄数组
	YingXiong yx[5] = {
		{"刘备", 23, "男"},
		{"关羽", 22, "男"},
		{"张飞", 20, "男"},
		{"赵云", 21, "男"},
		{"貂蝉", 19, "女"}
	};

	//调用冒泡排序
	len = sizeof(yx) / sizeof(yx[0]);
	PaiXu(yx, len);

	system("pause");
	return 0;
}

//打印函数
void printfYX(YingXiong *t, int len){
	for(int i = 0; i < len; i++){
		cout << "英雄姓名：" << t[i].name << endl;
		cout << "英雄年龄：" << t[i].age << endl;
		cout << "英雄性别：" << t[i].gender << endl;
	}
}

//冒泡排序函数
void PaiXu(YingXiong *yx, int len){
	for(int i = 0; i < len -1; i++){
		for(int j = 0; j < len - i -1; j++){
			if(yx[j].age > yx[j + 1].age){
				YingXiong t;
				t = yx[j];
				yx[j] = yx[j + 1];
				yx[j + 1] = t;
				/*t[0].name = yx[j].name;
				t[0].age = yx[j].age;
				t[0].gender = yx[j].gender;

				yx[j].name = yx[j + 1].name;
				yx[j].age = yx[j + 1].age;
				yx[j].gender = yx[j + 1].gender;

				yx[j + 1].name = t[0].name;
				yx[j + 1].age = t[0].age;
				yx[j + 1].gender = t[0].gender;*/
			}
		}
	}
	//调用打印函数
	printfYX(yx, len);
}