/*2023—7—25*/
/*结构体案例1  */

/*
3个老师，每个老师5个学生
	老师：姓名、工号
	学生：姓名、学号、分数
打印老师以及老师下面的学生

*/

#include <iostream>
#include <string>
#include <cstdlib>		
#include <ctime>		

using namespace std;

//定义学生结构体
struct Student{
	int id;			//学号
	string name;	//姓名
	int score;		//成绩
};

//定义老师结构体
struct Teacher{
	int id;			//工号
	string name;	//姓名
	Student stu[5];	//所带带领的学生
};


//声明函数
void printfTS(Teacher *t);
void all(Teacher arr[], int len);

int main9t1(){
	// 设置随机种子
	srand(time(NULL));

	//创建老师的数组变量
	Teacher tea[3] = {
		{1,"李老师",{
			{1,"刘一",56},
			{2,"陈二",73},
			{3,"张三",57},
			{4,"李四",98},
			{5,"王五",60}
		}},
		{2,"王老师",{
			{6,"赵六",76},
			{7,"孙七",87},
			{8,"周八",98},
			{9,"吴九",48},
			{10,"郑十",64}
		}},
		{3,"郑老师",{
			{11,"徐十一",36},
			{12,"邓十二",83},
			{13,"元十三",87},
			{14,"唐十四",78},
			{15,"黄十五",60}
		}}
	};

	Teacher arr1[3];
	int len;

	//调用打印函数
	printfTS(tea);

	//调用赋值函数
	len = sizeof(arr1) / sizeof(arr1[0]);
	all(arr1,len);

	//调用打印函数
	printfTS(arr1);
	

	system("pause");
	return 0;
}

//打印函数
void printfTS(Teacher *t){
	//指针数组 t[i]
	for(int i = 0; i < 3; i++){
		cout << t[i].id << " " << t[i].name << endl;
		for(int j = 0; j < 5; j++){
			cout <<"所带的学生 " << t[i].stu[j].id << " " << t[i].stu[j].name 
			<< " " << t[i].stu[j].score << endl;
		}
	}
}

//给数组赋值
void all(Teacher arr[], int len){
	//标号
	string nameS = "ABCDE";
	for(int i = 0; i < len; i++){
		arr[i].id = i + 1;
		arr[i].name = "Teacher_";
		arr[i].name += nameS[i];	//实现每个老师名字不一样

		for(int j = 0; j < 5; j++){
			arr[i].stu[j].id = j + 1;
			arr[i].stu[j].name = "Student";
			arr[i].stu[j].name += nameS[i];
			arr[i].stu[j].score = rand()%101;
		}
	}
}