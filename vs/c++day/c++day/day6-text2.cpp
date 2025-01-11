/*2023—7—17*/
/*数组元素逆置  */

/*
元素逆序排列
*/

#include <iostream>

using namespace std;

int main6t2(){
	//定义两个数组，一个存储顺序数组，一个存储逆序数组
	int arr0[5] = {1,3,4,52,3};
	int arr1[5];

	//数组逆向排序
	for(int i = 0; i < 5; i++){
		arr1[5-1-i] = arr0[i];
	}
	
	//输出两个数组
	for(int i = 0; i < 5; i++){
		cout << arr0[i] << "  ";
	}
	cout << endl;
	for(int i = 0; i < 5; i++){
		cout << arr1[i] << "  ";
	}

	cout << endl;

	int start = 0;		//起始下标
	int end = sizeof(arr0)/sizeof(arr0[0]) - 1;			//末尾下标
	while(start < end){
		int t;			//中间变量
		t = arr0[start];
		arr0[start] = arr0[end];	
		arr0[end] = t;			//交互
		start++;				//起始下标往中间走
		end--;					//末尾下标往中间走
	}
	for(int i = 0; i < 5; i++){
		cout << arr0[i] << "  ";
	}


	system("pause");

	return 0;
}