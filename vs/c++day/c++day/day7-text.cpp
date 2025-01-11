/*2023—7—18*/
/*成绩统计 */

/*二维数组
3个同学成绩如下：
			语文		数学		英语
张三		100			100			100
李四		90			50			100
王五		60			70			80
*/

#include <iostream>
#include <string>
#include <sstream>			//stringstream头文件

using namespace std;

int main7t() {
    // 定义一个二维数组存储信息
    string core[][5] = {
        {"姓名", "语文", "数学", "英语", "总计1"},
        {"", "0", "0", "0", "0"},
        {"", "0", "0", "0", "0"},
        {"", "0", "0", "0", "0"},
        {"总计2", "0", "0", "0", "0"}
    };		//注意如果是{0}而非{“0”}的话，会报错
	/*string arr[1][1] = {{0}};*/

    // 获取信息
    cout << "请输入学生成绩：" << endl;
    for (int j = 1; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            cin >> core[j][i];
        }
    }

    // 打印三个信息
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 5; i++) {
            cout << core[j][i] << "  ";
        }
        cout << endl;
    }

    // 统计每个人、每科的总成绩进行统计
    for (int i = 1; i < 5; i++) {
        int sum = 0;
        for (int j = 1; j < 4; j++) {
            sum += stoi(core[j][i]); // 将字符串转换为整数进行求和
        }
        stringstream ss;

		/*它是一个流类，可以用于在内存中进行字符串的输入和输出操作。
		`std::stringstream` 类的主要功能是将不同类型的数据转换为字符串，
		并提供一种简单的方式来处理字符串。
		它提供了与输入/输出流类似的接口，可以向 `std::stringstream` 中写入数据，然后从中读取数据。*/

        ss << sum; // 将整数写入 stringstream
        ss >> core[4][i]; // 将 stringstream 中的字符串读取到总计行
		
		//to_string在2010之中是不被允许的
    }

    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 5; i++) {
            cout << core[j][i] << "  ";
        }
        cout << endl;
    }

    system("pause");

    return 0;
}