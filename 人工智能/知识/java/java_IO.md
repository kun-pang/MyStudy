## 基本的概念

- 运行场景：与 多线程 + 网络  =》 实现底层通信（使用Netty框架）
- 分类：
	1. BIO：阻塞IO
	2. **NIO**：新IO （不好用）     ———封装成——>   ==Netty（网络通信框架）==
	3. AIO：异步IO
- 流：数据交换的  管道
	- 理解：水渠（IO流），从一个地方（源）——水（数据）——>  另一个地方（目标）。
	- 分类
		- 按照处理单位
			1. 字节流
			2. 字符流
		- 按流向（站在程序的角度来理解输入输出）
			1. 输入流（程序读取）
			2. 输出流（程序写入）
		- 按功能
			1. 处理流（过滤流），包装其他流，没有和数据源直接接触
			2. 节点流，与数据源相接触

## 常用流

- 字节流：
	- 输入：xxxInputStream
	- 输出：xxxOutputStream
- 字符流：
	- 输入：xxxReader
	- 输出：xxxWriter

### 文件相关的流

- 

- | 流分类     | 流类名                                                       | 方法                                 | 输入参数               | 返回值 | 功能说明                                | 适用范围                                       |
	| ---------- | ------------------------------------------------------------ | ------------------------------------ | ---------------------- | ------ | --------------------------------------- | ---------------------------------------------- |
	| 字节输入流 | FileInputStream                                              | read()                               | 无                     | int    | 每次读取**1 个字节**，读到末尾返回 -1   | 可处理**一切文件**（文本、图片、音频、视频等） |
	|            |                                                              | read(byte[] buff)                    | byte [] 缓冲数组       | int    | 每次读满数组，返回实际读取长度，-1 结束 | 同上                                           |
	|            |                                                              | close()                              | 无                     | void   | 关闭输入流                              | 同上                                           |
	| 字节输出流 | FileOutputStream（构造函数的第二个参数是覆盖模式(false) 或者 追加模式(true)） | write(byte[] b, int off, int len)    | 字节数组、起始位、长度 | void   | 按有效长度写入字节数据                  | 可处理**一切文件**                             |
	|            |                                                              | flush()                              | 无                     | void   | 刷新缓冲区，强制写出                    | 同上                                           |
	|            |                                                              | close()                              | 无                     | void   | 关闭输出流                              | 同上                                           |
	| 字符输入流 | FileReader                                                   | read()                               | 无                     | int    | 每次读取**1 个字符**，末尾返回 -1       | 只能处理**纯文本文件**                         |
	|            |                                                              | read(char[] cbuf)                    | char [] 字符数组       | int    | 批量读取字符，返回实际读取长度          | 同上                                           |
	|            |                                                              | close()                              | 无                     | void   | 关闭字符输入流                          | 同上                                           |
	| 字符输出流 | FileWriter（构造函数的第二个参数是覆盖模式(false) 或者 追加模式(true)） | write(char[] cbuf, int off, int len) | 字符数组、起始位、长度 | void   | 按有效长度写入字符，默认为覆盖模式      | 只能处理**纯文本文件**                         |
	|            |                                                              | flush()                              | 无                     | void   | 刷新缓冲区                              | 同上                                           |
	|            |                                                              | close()                              | 无                     | void   | 关闭字符输出流                          | 同上                                           |

### 字节流和字符流相互转换的流（属于处理流）

- `InputStreamReader`，将输入字节流  转换成  输入字符流
- `OutputStreamWriter`，将 输出字节流  转换成   输出字符流

### 自带存储介质的流

| 流分类         | 流类名                | 方法              | 输入参数         | 返回值 | 功能说明                       |
| -------------- | --------------------- | ----------------- | ---------------- | ------ | ------------------------------ |
| 字节数组输入流 | ByteArrayInputStream  | read()            | 无               | int    | 读取**1 个字节**，末尾返回 - 1 |
|                |                       | read(byte[] buff) | byte [] 缓冲数组 | int    | 批量读取字节，返回实际长度     |
|                |                       | close()           | 无               | void   | 关闭流（无实际效果）           |
| 字节数组输出流 | ByteArrayOutputStream | write(byte[] b)   | byte [] 字节数组 | void   | 将字节数组写入内存缓冲区       |
|                |                       | toByteArray()     | 无               | byte[] | 获取流中存储的字节数组         |
|                |                       | close()           | 无               | void   | 关闭流（无实际效果）           |
| 字符数组输入流 | CharArrayReader       | read()            | 无               | int    | 读取**1 个字符**，末尾返回 - 1 |
|                |                       | read(char[] cbuf) | char [] 字符数组 | int    | 批量读取字符，返回实际长度     |
|                |                       | close()           | 无               | void   | 关闭流                         |
| 字符数组输出流 | CharArrayWriter       | write(int c)      | int 字符值       | void   | 写入单个字符到内存数组         |
|                |                       | toCharArray()     | 无               | char[] | 获取流中存储的字符数组         |
|                |                       | close()           | 无               | void   | 关闭流（无实际效果）           |

### 带缓冲区的流（属于处理流）

| 流分类         | 流类名               | 方法                              | 输入参数               | 返回值 | 功能说明                                      |
| -------------- | -------------------- | --------------------------------- | ---------------------- | ------ | --------------------------------------------- |
| 字节缓冲输入流 | BufferedInputStream  | read()                            | 无                     | int    | 与 **FileInputStream** 的 read () 相同        |
|                |                      | read(byte[] buff)                 | byte [] 缓冲数组       | int    | 与 **FileInputStream** 的 read (byte []) 相同 |
|                |                      | close()                           | 无                     | void   | 与 **FileInputStream** 的 close () 相同       |
| 字节缓冲输出流 | BufferedOutputStream | write(byte[] b,int off,int len)   | 字节数组、起始位、长度 | void   | 与 **FileOutputStream** 的 write 相同         |
|                |                      | flush()                           | 无                     | void   | 与 **FileOutputStream** 的 flush () 相同      |
|                |                      | close()                           | 无                     | void   | 与 **FileOutputStream** 的 close () 相同      |
| 字符缓冲输入流 | BufferedReader       | read()                            | 无                     | int    | 与 **FileReader** 的 read () 相同             |
|                |                      | read(char[] cbuf)                 | char [] 字符数组       | int    | 与 **FileReader** 的 read (char []) 相同      |
|                |                      | **readLine()**                    | 无                     | String | 独有：一次读取一行文本，读完返回 null         |
|                |                      | close()                           | 无                     | void   | 与 **FileReader** 的 close () 相同            |
| 字符缓冲输出流 | BufferedWriter       | write(String str,int off,int len) | 字符串、起始位、长度   | void   | 与 **FileWriter** 的 write 相同               |
|                |                      | flush()                           | 无                     | void   | 与 **FileWriter** 的 flush () 相同            |
|                |                      | **newLine()**                     | 无                     | void   | 独有：写入跨平台换行符                        |
|                |                      | close()                           | 无                     | void   | 与 **FileWriter** 的 close () 相同            |

### 数据相关的流

| 流分类     | 流类名           | 方法                 | 功能说明                   |
| ---------- | ---------------- | -------------------- | -------------------------- |
| 数据输出流 | DataOutputStream | writeUTF(String str) | 按 UTF 格式写入字符串      |
|            |                  | writeChar(int c)     | 写入一个字符（2 字节）     |
| 数据输入流 | DataInputStream  | readUTF()            | 读取 writeUTF 写入的字符串 |
|            |                  | readChar()           | 读取一个字符（2 字节）     |



### 打印相关的流

| 流类型     | 类名        | 常用方法       | 说明                                  |
| ---------- | ----------- | -------------- | ------------------------------------- |
| 字节打印流 | PrintStream | println (内容) | 输出并自动换行，可输出到文件 / 控制台 |
| 字符打印流 | PrintWriter | println (内容) | 输出并自动换行，常用于控制台输出      |



## 序列化和反序列化

- 作用：将 对象 永久存储起来  或者 网络的传输对象信息（需要将对象 转换成 字节流）
- 序列化： 对象  ——>  字节流  (（将对象写入文件)
- 反序列化：字节流 ——> 对象

### jdk中序列化和反序列化的流(缺点：效率低)

- 相关的流

	- 属于处理流

	- | 流分类     | 类名               | 核心方法                | 作用                          |
		| ---------- | ------------------ | ----------------------- | ----------------------------- |
		| 序列化流   | ObjectOutputStream | writeObject(Object obj) | 将对象写入流（对象 → 字节）   |
		| 反序列化流 | ObjectInputStream  | readObject()            | 从流中读取对象（字节 → 对象） |

	- 注意：

		- 序列化某个对象，这个对象所在的类 必须实现 Serializable这个接口（标记接口，没有需要实现的方法）， 才能序列化
		- 如果某个属性不需要序列化，需要让 transient关键字修饰该属性。static修饰的，也不能序列化
		- serialVersionUID   保证序列化 和 反序列化时，这个类还是同一个类

	- ```java
		package demo.day06;
		
		import org.junit.Test;
		
		import java.io.*;
		
		public class TestSerialize {
		    /* 序列化相关的流 */
		    @Test
		    public void test01() throws Exception{
		        /* 序列化 对象->字节流 */
		        FileOutputStream fos = new FileOutputStream("aa/bb/senrialize.txt");
		        ObjectOutputStream oos = new ObjectOutputStream(fos);
		        Student s = new Student();
		        s.setId(1010);
		        s.setName("aaa");
		        s.setAgr(20);
		        s.setFlag1(false);
		        s.setFlag2(false);
		
		        oos.writeObject(s);
		    }
		
		    @Test
		    public void test02() throws Exception{
		        /* 序列化 对象->字节流 */
		        FileInputStream fis = new FileInputStream("aa/bb/senrialize.txt");
		        ObjectInputStream ois = new ObjectInputStream(fis);
		
		        Student s =  (Student) ois.readObject();
		        System.out.println(s);
		    }
		
		
		}
		
		class Student implements Serializable {  /* 序列化的前提是必须实现Serializable接口（标记接口——没有需要实现的方法） */
		    private final static long serialVersionUID = 1L; /* 保证序列化 和 反序列化时，还是同一个类。如果不加这个，反序列时，类稍微变动都会导致生成的serialVersionUID不一样，从而出现InvalidClassException */
		    private Integer id;
		    private String name;
		    private Integer agr;
		    private static boolean flag1 = true;
		    private transient boolean flag2 = true; /* transient修饰，该变量不会被序列化。 static修饰的变量也不会被序列化 */
		
		    public Integer getId() {
		        return id;
		    }
		
		    public void setId(Integer id) {
		        this.id = id;
		    }
		
		    public Integer getAgr() {
		        return agr;
		    }
		
		    public void setAgr(Integer agr) {
		        this.agr = agr;
		    }
		
		    public String getName() {
		        return name;
		    }
		
		    public void setName(String name) {
		        this.name = name;
		    }
		
		    public boolean isFlag1() {
		        return flag1;
		    }
		
		    public void setFlag1(boolean flag1) {
		        this.flag1 = flag1;
		    }
		
		    public boolean isFlag2() {
		        return flag2;
		    }
		
		    public void setFlag2(boolean flag2) {
		        this.flag2 = flag2;
		    }
		
		    @Override
		    public String toString() {
		        return "["+ this.id + ","
		                + this.name + ","
		                + this.agr + ","
		                + flag1 + ","
		                + this.flag2
		                + "]";
		    }
		}
		```



## 装饰设计模式

- 被装饰类 和 装饰类 实现相同的接口

- 装饰类中应该持有被装饰类实现的这个接口的引用

- Coffee.java

	- ```java
		/* 咖啡接口 */
		public interface Coffee {
		    public Double getRetail(); /* 零售价格 */
		    public String getMessage(); /* 消息 */
		}
		
		```

- BlackCoffee.java

	- ```java
		/* 黑咖啡实现 -- 被装饰类 */
		public class BlackCoffee implements Coffee {
		
		    @Override
		    public Double getRetail() {
		        return 2.0; /* 2元1杯 */
		    }
		
		    @Override
		    public String getMessage() {
		        return "这是黑咖啡";
		    }
		}
		
		```

- Americano.java

	- ```java
		/* 美式咖啡 -- 被装饰类 */
		public class Americano implements Coffee {
		    @Override
		    public Double getRetail() {
		        return 3.0;
		    }
		
		    @Override
		    public String getMessage() {
		        return "这是美式咖啡";
		    }
		}
		```

- CoffeeDecorator.java

	- ```java
		/* 咖啡的抽象装饰类 */
		/* 装饰类(CoffeeDecorator) 和 被装饰类(BlackCoffee、Americano) 需要实现相同接口Coffee */
		public abstract class CoffeeDecorator implements Coffee{
		    private Coffee coffee; /* 装饰类(CoffeeDecorator)中应该持有被装饰类实现的这个接口的引用(Coffee) */
		
		    public CoffeeDecorator(Coffee coffee){
		        this.coffee = coffee;
		    }
		
		    @Override
		    public String getMessage() {
		        return coffee.getMessage(); /* 调用传入的实体对象 */
		    }
		
		    @Override
		    public Double getRetail() {
		        return coffee.getRetail();
		    }
		}
		```

- MilkCoffeeDecorator.java

	- ```java
		/* 装饰类 -- 牛奶 */
		public class MilkCoffeeDecorator extends CoffeeDecorator{
		    public MilkCoffeeDecorator(Coffee coffee){
		        super(coffee);
		    }
		
		    @Override
		    public String getMessage() {
		        return super.getMessage() + "牛奶";
		    }
		
		    @Override
		    public Double getRetail() {
		        return super.getRetail() + 1.0;
		    }
		}
		```

- SugarCoffeeDecorator.java

	- ```java
		/* 装饰类 -- 糖 */
		public class SugarCoffeeDecorator extends CoffeeDecorator{
		    public SugarCoffeeDecorator(Coffee coffee){
		        super(coffee);
		    }
		
		    @Override
		    public String getMessage() {
		        return super.getMessage() + "糖";
		    }
		
		    @Override
		    public Double getRetail() {
		        return super.getRetail() + 0.5;
		    }
		}
		```

- ```java
	public class TestDecorator {
	
	    public static void main(String[] args) {
	        Coffee coffee = new BlackCoffee(); /* 点了一杯黑咖啡 */
	        System.out.println(coffee.getMessage() + "," + coffee.getRetail() + "元");
	
	        /* 使用装饰 加糖 */
	        MilkCoffeeDecorator milkCoffee = new MilkCoffeeDecorator(coffee);
	        System.out.println(milkCoffee.getMessage() + "," + milkCoffee.getRetail() + "元");
	    }
	}
	```

