/*2023—7—16*/
/*乘法口诀表 */

#include <iostream>

using namespace std;

int main5t(){
	//外层 列数
	for(int j = 1; j < 10; j++){
		//内层 行数
		for(int i = 1; i <= j; i++){
			cout << j << "*" << i << "=" << j*i << "   ";
		}
		cout << endl;
	}

	system("pause");

	return 0;
}