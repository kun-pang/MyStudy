/*2023-8-8*/

/*
电脑主要组成部件为CPU (用于计算)，显卡(用于显示)，内存条(用于存储)
将每个零件封装出抽象基类，并且提供不同的厂商生产不同的零件，例如Intel厂 商和Lenovo厂商
创建电脑类提供让电脑工作的函数，并且调用每个零件工作的接口
测试时组装三台不同的电脑进行工作

*/

#include <iostream>
#include <string>

using namespace std;

//cpu抽象类
class Cpu{
public:
	//计算虚函数
	virtual void caloulate() = 0;

};



//显卡抽象类
class VideoCard{
public:
	//显示虚函数
	virtual void display() = 0;

	
};



//内存条抽象类
class Memory{
public:	
	//存储虚函数
	virtual void storage() = 0;


};



//英特cpu类 
class InterCpu : public Cpu{
public:
	void caloulate(){
		cout << "英特cpu计算！" << endl;
	}

	
};

//英特显卡类 
class InterVideoCard : public VideoCard{
public:
	void display(){
		cout << "英特显卡显示！" << endl;
	}
};

///英特内存条类 
class InterMemory : public Memory{
public:
	void storage(){
		cout << "英特内存条存储！" << endl;
	}
};

//联想cpu类 
class LenovoCpu : public Cpu{
public:
	void caloulate(){
		cout << "联想cpu计算！" << endl;
	}
};

//联想显卡类 
class LenovoVideoCard : public VideoCard{
public:
	void display(){
		cout << "联想显卡显示！" << endl;
	}
};

//联想内存条类 
class LenovoMemory : public Memory{
public:
	void storage(){
		cout << "联想内存条存储！" << endl;
	}
};

//电脑类
class Computer{
public:
	//获取三个零件的构造函数
	Computer(Cpu *cpu, VideoCard *videoCard, Memory *memory){
		m_Cpu = cpu;
		m_VideoCard = videoCard;
		m_Memory = memory;

	}

	//三个构造接口函数
	void doWork(){
		cout << "您组装的电脑：" << endl;
		m_Cpu->caloulate();
		m_VideoCard->display();
		m_Memory->storage();
	}
	
	//析构函数
	~Computer(){
		if(m_Cpu != NULL || m_VideoCard != NULL|| m_Memory != NULL){
			cout << "Computer析构函数" << endl;
			delete m_Cpu;
			delete m_VideoCard;
			delete m_Memory;
			//防止野指针
			m_Cpu = NULL;
			m_VideoCard = NULL;
			m_Memory = NULL;
		}
	}

private:
	Cpu *m_Cpu;
	VideoCard *m_VideoCard;
	Memory *m_Memory;
};


void text(){
	Computer c1(new InterCpu, new LenovoVideoCard, new LenovoMemory);
	c1.doWork();

	Computer c2(new LenovoCpu, new LenovoVideoCard, new LenovoMemory);
	c2.doWork();
}

int main(){
	text();

	system("pause");
	return 0;
}