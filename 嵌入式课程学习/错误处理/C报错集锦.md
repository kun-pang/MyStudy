[TOC]

## 问题 1：使用命令进行编译时，发现无法编译

- 问题命令：

	- ```powershell
		gcc test.c -og test   
		
		gcc test.c -o  -g test
		```

- 解决方法：

	- `gcc test.c -g -o  test`  （没有-og 的参数，-o 后面接可执行程序名）

- 注意事项

	- 使用 CLion 软件时，应该选择  **c 可执行程序**  。如果选择 **c 库** ，正常程序会报错

## 问题 2：在多文件编译时，目标源文件不都在当前目录

- 环境补充

	- ```powershell
		# 目录结构：
		\---cProject
		+---day01
		|       helloWord.c
		|       helloWord.exe
		|       
		\---day02
		   |   test.c
		   |   test.exe
		   |   test01.c
		   |   test01.exe
		   |   test02.c
		   |
		   \---include
		           test02.h   
		# 蓝色表示目录 灰色表示文件，在vscode的终端中通过“ tree /f /a ”来生成该结构
		```

- 问题命令：`gcc test01.c test02.c -o test01`

	- 编译报错

		- ```powershell
			cc1.exe: fatal error: test01.c: No such file or directory
			compilation terminated.
			cc1.exe: fatal error: test02.c: No such file or directory
			compilation terminated.
			```

- 解决方式：明确目标源文件位置，通过-I 告知头文件位置，将可执行文件生成在.\cProject\day02\下

	- ```powershell
		gcc .\cProject\day02\test01.c .\cProject\day02\test02.c -I .\cProject\day02\include\ -o .\cProject\day02\test01
		```

## 问题 3：比较时，数据类型不一致m.b == 0xff

- ```c
	typedef union {
	int a;
	. b;
	}my_endianUnion;    
	
	int main()
	{
	my_endianUnion m;
	memset(&m,0,sizeof(m));     
	m.a = 0xff;                
	
	if(m.b == 0xff)       				// 问题出处
	   printf("Little endian!\n");
	else
	   printf("Big endian!\n");
	
	return 0;
	}
	
	// 错误   
	/*
		m.b == 0xff 
			编译器比较时，将m.b变化成int类型进行比较,即0xffffffff（m.b的比较时的值）与0xff比较
	*/
	
	// 解决方式
	/*
		1.使用在int或者char都不会变化的值，如1  
			m.a = 0x1;		m.b == 0x1;
		2.使用unsigned char来声明变量b
			unsigned char b;
	
		注意：char在不同的编译器下，可能代表unsigned char 或者 signed char
	*/
	```

## 问题4：在windows终端使用c打印中文乱码问题

- ```c
	// 解决方法1 使用SetConsoleOutputCP(65001)告诉终端使用UTF8编码格式
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <windows.h>			// SetConsoleOutputCP的头文件
	
	int main()
	{
	SetConsoleOutputCP(65001);           //解决中文乱码
	int left = 1;
	int right = 100;
	int rand_num;
	srand(time(NULL));
	rand_num = (rand() % (right - left + 1)) + left;
	for (int i = 0; i < 5; i++)
	{
	   int guess_num;
	   // fgets
	   printf("count:%d, 请输⼊猜测的数据:\n", 5 - i);
	   scanf("%d", &guess_num);
	   if (guess_num > rand_num)
	   {
	       printf("猜⼤了\n");
	   }
	   else if (guess_num < rand_num)
	   {
	       printf("猜⼩了\n");
	   }
	   else
	   {
	       printf("你真聪明\n");
	       break;
	   }
	}
	printf("再来⼀次\n");
	return 0;
	}
	
	// 解决方法2 将文本编码格式换成GBK编码
	
	// 解决方法3 gcc -fexe-charset=gbk 让生成的可执行文件的编码格式为GBK
	```

## 问题 5：使用goto跳转到scanf()函数位置会死循环

- ```c
	for(int i = 0; i < 5; i++){
	input1:        
	// 获取数字
	printf("可以猜测次数:%d/5,请输入猜测数字（100~200）: \n", i + 1);
	int ref = scanf("%d",&user_num);
	// 处理非法数字
	if(ref != 1 || user_num < 100 || user_num > 200){
	   goto input1;						// 问题情况出处
	}
	}
	
	// goto跳回去以后 scanf的缓冲区中数据没有清理，导致scanf一直读取错误的数据，陷入死循环
	```

- ```c
	// 解决方法：
	if(ref != 1 || user_num < 100 || user_num > 200){
	while(getchar() = '\n');			// getchar() 会将缓冲区的数据拿走（清空或者转移），一次只拿一个字符
	goto input1;						
	}
	```

## 问题 6：将变量名当作了地址（**变量名是指里面值，获取本身的地址需要&；函数名和数组名才是地址**）

- ```c
	int num = 10;
	int *p = &num;
	// int **pp = p;		// p实际指的是num的地址，*p是指num的值
	int **pp = &p;			// pp指p的地址，*pp是指num的地址，**pp是指num的值。
	
	```

## 问题 7：char *p = "ni hao"; p[3] = '\0'; 试图修改只读区的数据，导致程序崩溃

```c
#include <stdio.h>

int main(){


#ifdef Z
// 编译器会将 多个相同字符串 优化到同一块内存中，所以p与p1指向同一个地方
char *p = "ni hao";                 // "ni hao"这些字符串，在运行后会放到一块只读区
char *p1 = "ni hao";                // *p指向的就是这个只读区的地址
#endif

#ifndef Z
char p[] = "ni hao";
char p1[] = "ni hao";
#endif

int i = 0;

while (p[i] != '\0'){
   printf("%c",p[i]);
   i++;
}

printf("\n");
i = 0;

while (p1[i] != '\0'){
   printf("%c",p1[i]);
   i++;
}

#ifndef Z
p[3] = '\0';                  // 如果是指针p不能通过这个方式修改只读区的内容
#endif

#ifdef Z
printf("\n");
printf("%p %p",p,p1);
#endif

printf("\n");
i = 0;

while (p[i] != '\0'){
   printf("%c",p[i]);
   i++;
}

printf("\n");
i = 0;

while (p1[i] != '\0'){
   printf("%c",p1[i]);
   i++;
}

return 0;
}

/*
解决方法 
使用数组来接收字符串，这样编译器会在栈区开辟空间
*/
```

## 问题 8：类型不匹配的赋值

- ```c
	int main()
	{
	char ch[5] = {"aa", "bb"}; // 问题代码
	for (int i = 0; i < sizeof(ch) / sizeof(ch[0]); i++)
	{
	   printf("%c ", ch[5]);
	}
	return 0;
	}
	
	/*
	{"aa","bb"};本质上是两个地址  char   !=  char*
	
	改进: char *ch[5] = {"aa","bb"};
	*/
	```

## 问题 9：空指针导致程序崩溃

- ```c
	#include <stdio.h>
	#include <string.h>
	
	int main(){
	
	  char *p1 = "abcdef";
	  char *p2 = NULL;				// 问题代码
	  printf("%s\t%s",p1,p2);
	  printf("\n");
	
	  // 官方的
	  strcpy(p2,p1);
	  printf("%s\t",p2);
	  p2 = NULL;				//
	  strncpy(p2,p1,3);
	  printf("%s\t",p2);
	
	  return 0;
	}
	
	/* 
	// *p2是一个空指针，没有指向任何内存，导致后面拷贝时，编译器不知道怎么存储
	
	char *p2 = NULL;	改为  char p2[100] = {0};
	*/
	```

## 问题 10：指针指向问题(指针越界访问)

- ```c
	int main(int argc, char **argv){
	// 命令行传入的参数 .\tt.exe 01\0123 abc 123
	for(int i = 0; i < argc; i++){
	printf("%s ",argv[i]);              
	}
	
	printf("\n");
	
	// 不使用argc
	while(*argv != NULL){
	printf("%s ",*argv);
	argv++;
	}
	
	printf("\n---");
	/* atoi(): 将字符串 转成 整型 */
	int sum = 200 + atoi(argv[3]); 	// 问题代码           
	
	printf("%d",sum);
	...
	    
	/*
	程序不会有结果，因为指针argv移动到了 "123"之后的位置(指针越界)  
	argv前面一直在移动该指针，现在argv[3] 又要在其基础上在偏移3个位置，导致越界
	
	// 使用临时变量记录指针原始位置
	char **p = argv;
	....
	int sum = 200 + atoi(p[3]); 	
	*/
	```

## 问题 11：二维数组的初始化

- ```c
	int *p1 = NULL;      
	int *p2 = NULL;         
	int *arrp2[][] = {p1,p2}; 	// 问题代码
	
	
	/* 解决 */
	// 编译器无法自动推导二维及以上的数组中的成员个数，需要显示的声明
	int *arrp2[2][2] = {p1,p2};
	int *arrp2[][2] = {p1, p2};
	```

## 问题 12：目录有中文名，编译不通过

- ```shell
	PS E:\project\cProject> gcc .\day09\test02.c -o tt
	Assembler messages:
	Fatal error: can't create C:\Users\?
	```

- ```powershell
	## 现在使用的是MSYS的gcc编译程序，它默认在C:\Users\你的用户名\AppData\Local\Temp\下面生成临时的.i、.o等文件，但是有中文名，导致乱码不能正常生成。需要手动更改（ps：clion等软件的会自动将临时文件生成改到他们对应的目录下）
	## $env:Temp="E:\project\cProject\temp" 与  $env:TMP="E:\project\cProject\temp" 是临时的，只有当前的终端有效
	## 如果需要可以添加到环境变量中
	PS E:\project\cProject> $env:Temp="E:\project\cProject\temp"        
	PS E:\project\cProject> $env:TMP="E:\project\cProject\temp"
	PS E:\project\cProject> gcc .\day09\test02.c -o tt
	```

## 问题 13：使用循环时会被该变的变量作为条件，导致死循环

- ```c
	typedef struct 
	{
	Element *data;            /* 记录顺序表的起始地址 */
	unsigned int num;         /* 顺序表中空间总个数 */
	unsigned int cnt;         /* 顺序表中元素个数 */
	unsigned int initial_num; /* 记录用户传入的最初的大小 */
	}DSeqList;
	...
	int dSeqListAdd(DSeqList *list, Element const elem)
	{
	/* 检查参数 */
	if (list == NULL)
	{
	   printf("add: list = NULL\n");
	   return 1;
	}
	
	/* 顺序表满了 */
	if (list->cnt >= list->num)
	{
	  /* 扩容 */
	int num = list->num * 2;
	  int size = num * sizeof(Element);
	  Element *new_list = (Element *)malloc(size);
	  memset(new_list, 0, size);
	memcpy(new_list, list->data, list->cnt * sizeof(Element));
	  free(list->data);
	  list->data = new_list;
	  list->num = num;
	}
	
	/* 直接添加新的元素 更新管理结构体 -> 需要判断顺序表有没有满 */
	list->data[list->cnt] = elem;
	list->cnt++;
	printf("add: ok!\n");
	return 0;
	}
	...
	void dSeqListTest()
	{
	DSeqList *list = dSeqListCreate(10);
		...
	for(int i = 1; i < list->num * 3; i++) /* 问题代码 */
	{
	dSeqListAdd(list, i);
	}
	dSeqlListPrintf(list, "dilatation");
	
	
	dSeqListFree(list);
	}
	```

- ```c
	/* 使用list->num作为条件，但是每次循环dSeqListDel会可能会改变其值，导致循环无法结束，陷入死循环 */
	/* 改成循环中不会改变的值 */
	/* list->num 改成 list->initial_num */
	```


## 问题14：为了让vscode的终端能显示中文，使用了全局的`settings.json`的文件，导致vscode不会项目目录生成.vscode

- 问题描述：使用了全局的settings.json，同时将微软的C/C++插件卸载，导致出现进入目录不会自动创建.vscode文件夹以及相关的配置文件

- 解决方式

  1. 使用Clangd插件（前提使用的MingGW中的必须包含`bin\clangd.exe`）【注意：clangd插件的代码提示语微软的C++插件有冲突，需要禁用微软的C++插件】

  2. 使用vscode打开项目，再当前项目下创建一个`.vscode`文件夹，进行项目隔离

  3. 在`.vscode`文件夹下创建`settings.json`，进行如下配置

    - ```json
      {
        // clangd插件识别项目目录
        "clangd.arguments": [
          "--background-index",							// 后台建立索引
          "--compile-commands-dir=${workspaceFolder}",	// 指定 compile_commands.json 文件的查找目录  如果没有使用compile_commands.json 可以省略
          "--enable-config",								// 启用项目级配置文件（.clangd 文件） 如果没有使用.clangd 文件可以省略
          "--query-driver=gcc",    						// 配置使用的編譯器
          "--log=verbose"									// 设置日志输出级别为详细
        ],
        "terminal.integrated.env.windows": {
          "LANG": "zh_CN.UTF-8"
        },
      
        // 中文乱码解决
        "terminal.integrated.defaultProfile.windows": "PowerShell",
      
        "terminal.integrated.profiles.windows": {
          "PowerShell": {
            "source": "PowerShell",
            "args": [
              "-NoExit",
              "-ExecutionPolicy",
              "Bypass",
              "-Command",
              "[Console]::OutputEncoding = [System.Text.Encoding]::UTF8; [Console]::InputEncoding = [System.Text.Encoding]::UTF8"
            ],
            "env": {
              "LANG": "zh_CN.UTF-8",
              "LC_ALL": "zh_CN.UTF-8"
            }
          }
        },
      
        "terminal.integrated.env.windows": {
          "LANG": "zh_CN.UTF-8",
          "LC_ALL": "zh_CN.UTF-8"
        },
      
        // 额外推荐设置（提升中文体验）
        "terminal.integrated.scrollback": 10000,
        "terminal.integrated.fontFamily": "Consolas, 'Microsoft YaHei Mono', monospace",
        "terminal.integrated.fontSize": 14
      }
      ```

  4. 使用简单方式，即在项目目录下创建`compile_flags.txt`,与`.vscode`同级，配置内容如下

    - ```txt
      -Iexercise/inc
      添加其他项目的头文件
      -I.
      -I${workspaceFolder}/exercise/inc
      -std=c11
      -Wall
      -g
      ```
      
    - 一行就是一个参数，后续可以将 项目其他文件夹的目录下的inc使用`-I`告知clangd
  
    - 解决：`src/.c`文件中`#include “.h”`文件能正确识别到`inc/.h`文件,并且有代码提示
  
  
  
  
  
  ## 问题15：头文件环路问题
  
  ```c
  #ifndef __HTTP_PROTOCOL_H__
  #define __HTTP_PROTOCOL_H__
  
  #include <stdint.h>
  #include "epoll.h"		// 与另外一个头文件形成环路
  
  #define PARSE_SUCCESS               0   // 解析成功
  #define ERR_EMPTY_REQUEST          -1   // 空请求或缓冲区无数据
  #define ERR_INVALID_METHOD         -2   // 不支持或不合法的请求方法 (非 GET/POST)
  #define ERR_URL_NOT_FOUND          -3   // 找不到 URL 分隔符
  #define ERR_URL_TOO_LONG           -4   // URL 长度超过接收缓冲区
  #define ERR_VERSION_NOT_FOUND      -5   // 找不到 HTTP 版本号
  #define ERR_POST_NO_CONTENT_LEN    -6   // POST 请求缺失 Content-Length 头部
  #define ERR_POST_INVALID_LEN       -7   // Content-Length 的值不合法
  #define ERR_BODY_NOT_FOUND         -8   // 找不到 HTTP 请求体 (未找到 \r\n\r\n)
  #define ERR_BODY_INCOMPLETE        -9   // 请求体数据不完整 (实际接收长度小于 Content-Length)
  
  #define HPROTO_TYPE_TEXT  1   // 普通文件
  #define HPROTO_TYPE_JSON  2   // JSON文件
  
  /* http协议解析 */
  /* 请求头结构 */
  typedef struct {
      /* 请求行 */
      char method[10];  // 请求类型，get / post
      char url[256];    // 资源的原始路径
      char path[128];   // 请求的文件名
  
      /* 请求头（POST专属） */
      int  length;      // 正文长度
  
      /* 请求的正文 */
      char *body;       // 正文内容
  } HProto_request_t;
  
  /* 响应头结构 */
  typedef struct {
      int  status_code;       // 状态码：如 200, 404, 500
      char status_msg[32];    // 状态描述
  
      char content_type[64];  // 返回给浏览器的格式：如 "application/json; charset=utf-8"
      
      char *body;             // 准备写回给浏览器的正文数据（如 HTML 或 JSON 字符串）
      int   body_len;         // 正文的实际长度
  } HProto_response_t;
  
  /**
   * @brief 创建请求头
   * 
   * @return HProto_request_t* 成功,返回请求头;失败,返回NULL 
   */
  HProto_request_t *HProto_createReq();       
  
  /**
   * @brief 销毁请求头
   * 
   * @param req 请求头结构体
   */
  void HProto_freeReq(HProto_request_t *req);
  
  /**
   * @brief 创建响应头
   * 
   * @return HProto_response_t* 成功,返回响应头;失败,返回NULL 
   */
  HProto_response_t *HProto_createRes();
  
  /**
   * @brief 销毁响应头
   * 
   * @param res 响应头结构体
   */
  void HProto_freeRes(HProto_response_t *res);
  
  /**
   * @brief 解析客户端请求数据包
   * 
   * @param task 任务结构体
   * @param req 请求头结构体，内部存放解析的数据
   * @param recv_len 接收的数据长度
   * @return int 成功,返回0;失败,返回<0（头文件上方查看具体对应的错误）
   */
  int HProto_parseReq(struct Epoll_task_s *task, int recv_len);
  
  /**
   * @brief 构造响应头结构体的头部
   * 
   * @param res 响应头结构体的头部
   * @param ret_code 解析请求头的错误码
   * @param type 文件类型
   */
  void HProto_resHead(HProto_response_t *res, int ret_code, int type);
  #endif
  ```
  
  ```c
  #ifndef __EPOLL_H__
  #define __EPOLL_H__
  
  #include <stdint.h>
  
  #include "http_protocol.h"
  #include "openssl/ssl.h"
  
  /* epoll 相关的处理 */
  
  typedef int (*fun_t)(void *arg);
  
  /* 任务结构体 */
  struct Epoll_task_s{
      int 	 			fd;			    // 该任务操作的IO对象对应文件描述符
  	int      			epfd;		    // 该任务最终靠epoll对象进行 ADD DEL
  	SSL                *ssl;			// 该任务绑定的SSL对象
  	SSL_CTX            *ctx;			// 该任务绑定的SSL_CTX对象
  	uint8_t            *data;			// 该任务维护的缓存区首地址
  	int      			len;			// 该任务维护的缓存区的长度
  	int      			pos;			// 该任务维护的缓存区的当前索引号
  	HProto_request_t   *req;			// 该任务维护的请求头
  	HProto_response_t  *res;			// 该任务维护的响应头
  	fun_t               handler;		// 该任务一旦触发，应该执行哪个函数 
  };
  
  /**
   * @brief 初始化epoll文件描述符
   * 
   * @return int 成功,返回 非负fd ;失败,返回 -1
   */
  int Epoll_init();
  
  /**
   * @brief 将fd添加到epoll的树结构中（上树操作）
   * 
   * @param task fd对应的任务体
   * @param events 对应的数据
   * @return int 成功,返回 0 ;失败,返回 -1
   */
  int Epoll_add(struct Epoll_task_s *task,uint32_t events);
  
  /**
   * @brief 将fd从epoll的树结构中删除（下树操作）
   * 
   * @param task fd对应的任务体
   * @return int 成功,返回 0 ;失败,返回 -1
   */
  int Epoll_del(struct Epoll_task_s *task);
  
  /**
   * @brief 将fd设置成非阻塞模式，监听fd不需要设置
   * 
   * @param fd 需要设置的普通fd
   */
  void Epoll_setNonblocked(int fd);
  
  /**
   * @brief 修改fd对应的epoll属性
   * 
   * @param task 任务结构体
   * @param events 修改的属性
   */
  void Epoll_mod(struct Epoll_task_s *task, uint32_t events);
  
  #endif
  ```
  
  问题描述：：展开 `http_protocol.h` $\rightarrow$ 去展开 `epoll.h` $\rightarrow$ 又回过头展开 `http_protocol.h`…… 从而陷入死循环，最终触发了你看到的编译报错。
  
  解决：如果一个头文件只需要知道某个结构体的**名字和它是个指针**（比如 `struct Epoll_task_s *task`），**根本不需要 `#include` 它的头文件**。你可以通过前置声明（Forward Declaration）来告诉编译器这个结构体的存在。
  
  ```c
  #ifndef __HTTP_PROTOCOL_H__
  #define __HTTP_PROTOCOL_H__
  
  #include <stdint.h>
  // ❌ 删掉这行：#include "epoll.h"
  
  // ... 保持你的宏定义不变 ...
  // ... 保持 HProto_request_t 和 HProto_response_t 结构体不变 ...
  
  // 💡 关键：前置声明。告诉编译器 struct Epoll_task_s 是一个结构体类型
  struct Epoll_task_s; 
  
  // ... 保持前面的函数声明不变 ...
  
  /**
   * @brief 解析客户端请求数据包
   */
  int HProto_parseReq(struct Epoll_task_s *task, int recv_len); // 此时编译器看到指针就不会报错了
  
  void HProto_resHead(HProto_response_t *res, int ret_code, int type);
  
  #endif
  ```
  
  