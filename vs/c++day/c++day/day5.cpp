/*2023—7—16*/
/*程序流程结构  */


/*程序结构
	嵌套结构		
	跳转语句	break语句  退出循环  使用场景：switch语句、循环语句、嵌套语句
				continue	跳过本次循环未执行的语句，继续执行下一次循环
				goto		无条件跳转  【goto 标记】 若标记存在，执行goto语句后，
							直接跳转到标记语句上  标记约定成俗的规定：大写
*/

#include <iostream>

using namespace std;

int main5(){
	//打印菱形星图
	//获取打印层数
	int i,j;
	int n;	//层数
	cout << "请输入打印层数（奇数）：" << endl;
	cin >> n;

	for(j = 1; j < (n + 1); j++){
		int u;	//存储空格数
		int k;	//去负号
		int o;	//记录每层打印的星号个数
		u = (n + 1) / 2 - j;

		//打印上半层
		if(j <= (n + 1) / 2){
			o = 2 * j - 1;
			for(i = 1; i <= u; i++){
				cout << " ";
			}
			for(i = 1; i <= o;i++){
				cout << "*";
			}
			cout << endl;
		}else{		//打印下半层
			k = -u;
			o = 2 * ((n + 1) - j) - 1;
			for(i = 1; i <= k;i++){
				cout << " ";
			}
			for(i = 1; i <= o;i++){
				cout << "*" ;
			}
			cout << endl;
		}
	}
 /*  *
    ***
   *****
  *******
   *****
    ***
     * */
	cout << endl;

	//continue  不会退出循环
	//输出0-100偶数
	for(i = 0; i <= 100 ; i++){
		if(i % 2 != 0){
			continue;		//不退出循环
		}
		cout << i << endl;
		if(i == 50){
			break;			//退出循环
		}
	}
	cout << endl;

	//goto语句
	cout << "1" << endl;
	cout << "2" << endl;
	 
	goto S0;

	cout << "3" << endl;

	S0:				//用冒号确认标记
	cout << "4" << endl;
	cout << "5" << endl;
	cout << endl;

	//数组

	system("pause");

	return 0;
}