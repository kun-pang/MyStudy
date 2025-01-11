/*2023—7—24*/
/*指针 函数 数组*/

//封装一个函数，利用冒泡排序，实现对于整型数组的升序排序

#include <iostream>

using namespace std;

//冒泡排序
void MaoPao01(int a, int* p) {    //获取数组的首地址
    cout << "排序前的数组" << endl;
    for (int i = 0; i < a; i++) {
        cout << *(p + i) << "  ";
    }
    cout << endl;
    //控制冒泡的轮数
    for (int i = 0; i < (a - 1); i++) {
        //每轮比较次数
        for (int j = 0; j < (a - i - 1); j++) {
            if (*(p + j) > *(p + j + 1)) {
                int t = *(p + j);
                *(p + j) = *(p + j + 1);
                *(p + j + 1) = t;
            }
        }
    }
    cout << "排序后的数组" << endl;
    for (int i = 0; i < a; i++) {
        cout << *(p + i) << "  ";
    }
}

int main8t() {
    //获取数组个数
    int x0 = 0;
    cout << "请输入数组的长度：" << endl;
    cin >> x0;

    int* maoPao = new int[x0];    //动态数组  可以用结构体

    //获取数组的数值
    cout << "请输入长度为" << x0 << "的数组：" << endl;
    for (int i = 0; i < x0; i++) {
        cin >> maoPao[i];
    }

    //调用冒泡排序的自定义函数
    MaoPao01(x0, maoPao);

	system("pause");

    delete[] maoPao;    //释放动态数组内存

    return 0;
}