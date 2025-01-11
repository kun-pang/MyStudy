/*2023—7—13*/
//练习 三只小猪称重

#include <iostream>

using namespace std;

int main2t(){
	//初始化
	int pig_a = 0,pig_b = 0,pig_c = 0;
	//获取三只小猪重量  展示三只小猪重量
	cout << "请分别输入小猪a，b，c的重量。" << endl;
	cin >> pig_a >> pig_b >> pig_c;
	cout << "a猪" << pig_a << endl;
	cout << "b猪" << pig_b << endl;
	cout << "c猪" << pig_c << endl;

	//三只小猪先比较a，b两只，重的与c进行比较
	if(pig_a > pig_b){
		if(pig_a > pig_c && pig_b != pig_c){
			//选择最轻
			if(pig_c > pig_b){
				//a > c > b
				cout << "最重的小猪是：pig_a;" << "最轻的小猪是：pig_b" << endl;	 
			}else{
				//a > b > c
				cout << "最重的小猪是：pig_a;" << "最轻的小猪是：pig_c" << endl;
			}
		}else if(pig_c == pig_b){
				cout << "最重的小猪是：pig_a;" << "最轻的小猪是：pig_b、pig_c" << endl;
		}else{// c > a > b
			cout << "最重的小猪是：pig_c;" << "最轻的小猪是：pig_b" << endl;
		}
	}else if(pig_a == pig_b){
		if(pig_a > pig_c && pig_a != pig_c){
			cout << "最重的小猪是：pig_a、pig_b;" << "最轻的小猪是：pig_c" << endl;
		}else if(pig_a == pig_c){
			cout << "三只一样重;" << endl;
		}else{
			cout << "最重的小猪是：pig_c;" << "最轻的小猪是：pig_a、pig_b" << endl;
		}
	}else{   //b > a
		if(pig_b > pig_c && pig_a != pig_c){
			//选择最轻
			if(pig_c > pig_a){
				//b > c > a
				cout << "最重的小猪是：pig_b;" << "最轻的小猪是：pig_a" << endl;	 
			}else{
				//b > a > c
				cout << "最重的小猪是：pig_b;" << "最轻的小猪是：pig_c" << endl;
			}
		}else if(pig_c == pig_a){
			cout << "最重的小猪是：pig_b;" << "最轻的小猪是：pig_a、pig_c" << endl;
		}else if(pig_c == pig_b){
			cout << "最重的小猪是：pig_b、pig_c;" << "最轻的小猪是：pig_a" << endl;
		}else{ //c > b > a
			cout << "最重的小猪是：pig_c;" << "最轻的小猪是：pig_a" << endl;
		}
	}


	system("pause");

	return 0;
}