/*2023—7—17*/
/*五只小猪称重  */

/*
判断五只小猪体重，打印最重的小猪
*/

#include <iostream>

using namespace std;

int main6t1(){
	//定义小猪体重
	int x = 1;
	int *pag = new int[x]; // 使用动态内存分配  内含指针基本原理

	//获取小猪个数
	cout << "请输入小猪个数：" << endl;
	cin >> x;


	//获取小猪体重
	cout << "请输入" << x <<"只小猪的体重：" <<endl;
	for(int i = 0; i < x; i++){
		cin >> pag[i];
	}

	//取出小猪，进行逐个比较
	//第一个位置，放最重小猪，五个1 2 4 3 4
	for(int i = 0;i < x; i++){
		int arr[1] = {0};
		for(int j = x-1; j > i; j--){
			if(pag[i] < pag[j]){
				arr[0] = pag[i];
				pag[i] = pag[j];
				pag[j] = arr[0];
			}else{
				continue;
			}
		}
	
	}

	//输出最重小猪
	for(int i = 0; i < x; i++){
		cout << pag[i] << endl;
	}
	cout << "最重小猪为：" << pag[0] << endl;


	/*局外定义一个最大值，将数组的每个值挨个与之比较，如果大于max 则赋值给max，然后继续比较
	int max = 0;
	for(int i = 0; i < 5; i++){
		if(max < pag[i]){
			max = pag[i];
		}
	}
	cout << max << endl;
	*/

	system("pause");

	return 0;
}