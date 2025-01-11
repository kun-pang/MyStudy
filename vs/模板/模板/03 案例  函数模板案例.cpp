/*2023-8-20*/

//案例描述：
//	利用函数模板封装一个排序函数，可以对不用数据类型数组进行排序
//	排序规则从大到小，排序算法为选择排序
//	分别利用char数组和int数组进行测试

#include <iostream>

using namespace std;


template<typename T>
//选择排序函数
//不能为"T b" 否则for循环无法运行
void mySwap(T *a, int b){		
	for(int i = 0; i < b; i++ ){
		int Max = i;		//假定为当前下标的数组为最大值
		for(int j = i + 1; j < b; j++){
			if(a[Max] < a[j]){
				Max = j;
			}
		}

		if(Max != i){
			T t = a[i];
			a[i] = a[Max];
			a[Max] = t;
		}
	}
	cout << "交换完成!" << endl;
}



void test01(){
	int a[3] = {1, 7, 4};
	char b[5] = {'a', 'b','A', 'B','c'};

	//这里用 sizeof(b) / sizeof(char)	计算大小更好

	cout << "未排序前：" << endl;
	for(int i = 0; i < 3; i++){
		cout << a[i] << " ";
	}
	cout  << endl;
	for(int i = 0; i < 5; i++){
		cout << b[i] << " ";
	}
	

	mySwap(a, 3);
	mySwap(b, 5);

	for(int i = 0; i < 3; i++){
		cout << a[i] << " ";
	}
	cout  << endl;
	for(int i = 0; i < 5; i++){
		cout << b[i] << " ";
	}
}

int main(){

	test01();

	system("pause");
	return 0;
}