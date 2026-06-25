## String类

- 特点：

	- 由final修饰，不能被继承

- 底层原理

	- 不可变的字符序列
		- 字符序列（CharSequence），String类 是实现 CharSequence接口
		- 不可变，String类内部是通过`private final byte[] value;` 指向字符串常量的，final修饰，指向不能改变。String对象一旦有改变的操作，本质上是赋值到一个新的String对象中，再返回
		- 底层是 字符数组value ，在jdk9之后改成字节数组

- 常用API

	- | 方法名                                                       | 方法作用                                                     |
		| ------------------------------------------------------------ | ------------------------------------------------------------ |
		| `charAt(int index)`                                          | 返回字符串指定索引位置的字符                                 |
		| `compareTo(String anotherString)`                            | 按字典顺序比较两个字符串，基于第一个不同字符的 ASCII 值差值；内容相同时返回长度差 |
		| `compareToIgnoreCase(String str)`                            | 按字典顺序比较两个字符串，**忽略大小写**                     |
		| `concat(String str)`                                         | 将指定字符串拼接到该字符串末尾                               |
		| `contains(CharSequence s)`                                   | 判断字符串是否包含指定的字符序列，**区分大小写**             |
		| `endsWith(String suffix)`                                    | 判断字符串是否以指定后缀结尾                                 |
		| `equals(Object anObject)`                                    | 比较两个字符串内容是否**完全相同**                           |
		| `equalsIgnoreCase(String anotherString)`                     | 比较两个字符串内容是否相同，**忽略大小写**                   |
		| `getBytes()`                                                 | 使用平台默认编码，将字符串编码为字节数组                     |
		| `getBytes(String charsetName)`                               | 使用指定编码，将字符串编码为字节数组                         |
		| `getChars(int srcBegin, int srcEnd, char[] dst, int dstBegin)` | 将字符从此字符串复制到目标字符数组                           |
		| `indexOf(int ch)` / `indexOf(String str)`                    | 返回指定字符 / 子字符串**第一次出现**的索引位置              |
		| `isEmpty()`                                                  | 判断字符串是否为空（长度为 0）                               |
		| `lastIndexOf(int ch)` / `lastIndexOf(String str)`            | 返回指定字符 / 子字符串**最后一次出现**的索引位置            |
		| `length()`                                                   | 返回字符串的长度                                             |
		| `repeat(int count)`                                          | 将当前字符串重复拼接指定次数                                 |
		| `replace(char oldChar, char newChar)`                        | 将字符串中所有旧字符替换为新字符                             |
		| `replaceAll(String regex, String replacement)`               | 使用正则表达式匹配并替换字符串                               |
		| `split(String regex)`                                        | 使用正则表达式拆分字符串，返回字符串数组                     |
		| `startsWith(String prefix)`                                  | 判断字符串是否以指定前缀开头                                 |
		| `substring(int beginIndex, int endIndex)`                    | 截取字符串，范围 `[begin, end)`，包含开头不包含结尾          |
		| `toCharArray()`                                              | 将字符串转换为新的字符数组                                   |
		| `toLowerCase()`                                              | 将字符串中的所有字符转为小写                                 |
		| `toUpperCase()`                                              | 将字符串中的所有字符转为大写                                 |
		| `trim()`                                                     | 去除字符串**开头和结尾**的空白字符                           |
		| `valueOf(基本数据类型/Object)`                               | 静态方法，将其他数据类型转换为字符串                         |

## StringBuffer类

- 可变字符序列（会修改指向）

- 常用API

	- 

	- | 方法                                                         | 说明                                                         |
		| ------------------------------------------------------------ | ------------------------------------------------------------ |
		| `append(各种类型)`                                           | 将任意类型数据转为字符串后追加到当前字符序列末尾。           |
		| `capacity()`                                                 | 返回当前缓冲区的容量（不是字符长度，初始默认16）。           |
		| `charAt(int index)`                                          | 返回指定索引位置的字符。                                     |
		| `delete(int start, int end)`                                 | 删除 `[start, end)` 范围内的字符，在原对象上修改。           |
		| `deleteCharAt(int index)`                                    | 删除指定索引处的单个字符。                                   |
		| `getChars(int srcBegin, int srcEnd, char[] dst, int dstBegin)` | 将 `[srcBegin, srcEnd)` 范围内的字符复制到目标字符数组中。   |
		| `indexOf(String str)`                                        | 返回子串第一次出现的索引，找不到返回 -1。                    |
		| `insert(int offset, 各种类型)`                               | 在指定偏移位置插入数据，后续字符自动后移。                   |
		| `lastIndexOf(String str)`                                    | 返回子串最后一次出现的索引。                                 |
		| `length()`                                                   | 返回当前字符序列的长度（实际字符个数）。                     |
		| `reverse()`                                                  | 将字符序列反转（原地修改）。                                 |
		| `setCharAt(int index, char ch)`                              | 替换指定索引处的字符。                                       |
		| `substring(int start, int end)`                              | 截取 `[start, end)` 范围的子串，返回 `String`，原 `StringBuffer` 不变。 |

## StringBuilder类

- 可变字符序列
- 常见API（同上）

StringBuffer 和 StringBuilder

- 相似
	- 都是继承于AbstractStringBuilder
	- 都是final修饰，不能被继承
	- 都是可变的字符序列（内部的指向数据的数组可以改变 指向）
- 区别
	- 在StringBuffer的很多方法中，有**synchronized（线程安全）关键字修饰**，某一时刻只会有一个线程执行
	- StringBuffer：安全，但是性能低
	- StringBuilder：不安全，但是性能高（需要放到安全的环境下使用）

## 日期类型

### 组织关系

- ```mermaid
	graph TD
	    %% 顶层父类
	    util_Date["java.util.Date<br/>（日期+时间 父类）"]
	    
	    %% 子类 + 注释
	    sql_Date["java.sql.Date<br/>（年-月-日）"]
	    sql_Time["java.sql.Time<br/>（时-分-秒）"]
	    sql_Timestamp["java.sql.Timestamp<br/>（年-月-日 时-分-秒 纳秒）"]
	    
	    %% 继承关系
	    util_Date --> sql_Date
	    util_Date --> sql_Time
	    util_Date --> sql_Timestamp
	
	    %% 样式美化
	    classDef parent fill:#d1e7ff,stroke:#333,stroke-width:2px
	    classDef child fill:#e6ffed,stroke:#333,stroke-width:2px
	    class util_Date parent
	    class sql_Date,sql_Time,sql_Timestamp child
	    
	    %% 样式美化（区分父类/子类）
	    classDef parentStyle fill:#f9f,stroke:#333,stroke-width:2px
	    classDef childStyle fill:#9f9,stroke:#333,stroke-width:2px
	    
	    class util_Date parentStyle
	    class sql_Date,sql_Time,sql_Timestamp childStyle
	```

### java.util.Date常用API

- 构造器

	- Date()：无参构造器，会给date对象中赋值 当前时间

	- Date(long data)：传入一个 毫秒数（long型—— 从 1970-01-01 00:00:00 GMT 起算）转换成 年月日时分秒（Date型）的形式

	- ```java
		import org.junit.Test;
		
		import java.util.Date;
		@Test
		    public void Test01(){
		        Date date = new Date();
		
		        /* 直接时当前时间 */
		        System.out.println(date);
		    }
		
		    @Test
		    public void Test02(){
		        long datems = System.currentTimeMillis();
		        Date date = new Date(datems);
		
		        /* 将ms 转换成 日期 */
		        System.out.println(date);
		    }
		```

- 方法

	- 

	- | 方法                          | 功能说明                                                     |
		| :---------------------------- | :----------------------------------------------------------- |
		| `after(Date when)`            | 判断当前日期是否在指定日期之后。                             |
		| `before(Date when)`           | 判断当前日期是否在指定日期之前。                             |
		| `compareTo(Date anotherDate)` | 比较两个日期的顺序：返回正数表示当前 > 传入，0 表示相等，负数表示当前 < 传入。 |
		| `equals(Object obj)`          | 判断两个 `Date` 对象是否表示相同的毫秒值（即时间相同）。     |
		| 其余API                       | 已弃用，使用Calendar类代替                                   |

### Calendar（日历）

- Calendar 没有 public的构造器，只能通过getInstance() 获取对象

- 常用API

	- 

	- | 方法                          | 作用            | 核心功能                     |
		| ----------------------------- | --------------- | ---------------------------- |
		| `calendar.get(Calendar.字段)` | 获取时间分量    | 获取年、月、日、时、分、秒等 |
		| `calendar.setTime(Date date)` | Date → Calendar | 把日期对象设置到日历中       |
		| `calendar.getTime()`          | Calendar → Date | 把日历对象转成日期对象       |
		| `calendar.getTimeInMillis()`  | 获取毫秒时间戳  | 获取当前时间的毫秒级时间戳   |

### 日期格式化

- ```mermaid
	graph TD
	    %% 顶层抽象父类
	    Format["java.text.Format<br/>（格式化抽象父类）"]
	    
	    %% 一级子类
	    DateFormat["java.text.DateFormat<br/>（日期格式化抽象类）"]
	    NumberFormat["java.text.NumberFormat<br/>（数字格式化抽象类）"]
	    
	    %% 二级子类（DateFormat 的实现类）
	    SimpleDateFormat["java.text.SimpleDateFormat<br/>（自定义日期格式化实现类）"]
	    
	    %% 继承关系
	    Format --> DateFormat
	    Format --> NumberFormat
	    DateFormat --> SimpleDateFormat
	    
	    %% 样式美化（区分层级）
	    classDef topStyle fill:#f8d7da,stroke:#721c24,stroke-width:2px,rx:8
	    classDef midStyle fill:#d1e7dd,stroke:#0f5132,stroke-width:2px,rx:8
	    classDef bottomStyle fill:#cff4fc,stroke:#084298,stroke-width:2px,rx:8
	    
	    class Format topStyle
	    class DateFormat,NumberFormat midStyle
	    class SimpleDateFormat bottomStyle
	```

- DateFormat常用API

	- 

	- | 方法                | 作用           | 转换方向          | 关键注意点                 |
		| ------------------- | -------------- | ----------------- | -------------------------- |
		| `format(Date date)` | **日期格式化** | `Date` → `字符串` | 把时间转成你想要的文字格式 |
		| `parse(String str)` | **字符串解析** | `字符串` → `Date` | 把文字时间转回日期对象     |

	- ```java
		@Test
		public void Test01(){
		/* format() 格式化日期 将日期 格式化成 字符串  */
		DateFormat dateFormat = new SimpleDateFormat("yyyy - MM - DD"); /* DateFormat是抽象类，需要指向子类 */
		 
		Date date = new Date();
		 
		String str = dateFormat.format(date); /* 具体格式通过有参构造器传入 */
		System.out.println(str);
		 }
		
		@Test
		 public void Test02() throws ParseException {
		     /* parse() 格式化字符串 将字符串转换成日期  */
		     String str = "2026-7-10";
		     DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-DD"); /* DateFormat是抽象类，需要指向子类 */
		     Date date;
		 
		 date = dateFormat.parse(str); /* 其字符串格式必须和有参构造中的格式相同，且需要抛出异常 */
		 System.out.println(date);
		 }
		```

	- NumberFormat：主要是对数字进行格式化（默认格式化成货币类型）

## JDK8新提供的3类日期API

1. 本地日期时间：LocalDate、LocalTime、LocalDateTime

	- 

	- | 类型              | 作用                   | 默认格式              | 核心方法                                              |
		| ----------------- | ---------------------- | --------------------- | ----------------------------------------------------- |
		| **LocalDate**     | 表示**日期**（年月日） | `yyyy-MM-dd`          | **now()**：获取当前日期 <br>**of()**：自定义日期      |
		| **LocalTime**     | 表示**时间**（时分秒） | `HH:mm:ss`            | **now()**：获取当前时间,<br>**of()**：自定义时间      |
		| **LocalDateTime** | 表示**日期 + 时间**    | `yyyy-MM-dd HH:mm:ss` | **now()**：获取当前日期时间<br>of()**：自定义日期时间 |

2. 日期/时间间隔：Period和Duration

	- 

	- | 工具类       | 用途                   | 搭配类                    | 核心方法                   | 获取差值                                                     |
		| ------------ | ---------------------- | ------------------------- | -------------------------- | ------------------------------------------------------------ |
		| **Period**   | 计算**两个日期**的间隔 | LocalDate                 | `Period.between(早, 晚)`   | `getYears()`<br>`getMonths()`<br>`getDays()`<br>`toTotalMonths()` |
		| **Duration** | 计算**两个时间**的间隔 | LocalTime / LocalDateTime | `Duration.between(早, 晚)` | `toDays()`<br>`toHours()`<br>`toMinutes()`<br>`getSeconds()`<br>`toMillis()` |

3. DateTimeFormatter：日期时间格式化

	- ```java
		public void test01(){
		         /* DateTimeFormatter 对日期和时间同时格式化 */
		         LocalDateTime localDateTime = LocalDateTime.now();
		 
		         DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
		 
		         String str = dateTimeFormatter.format(localDateTime);
		         System.out.println(str);
		     }
		```

## 基本数据类型包装类

- 存在自动装箱 以及 自动拆箱； 包装类缓存问题

- 

- | 基本数据类型 | 对应包装类 | 常用 API（静态方法居多）                                     |
	| ------------ | ---------- | ------------------------------------------------------------ |
	| byte         | Byte       | `parseByte(String)`<br>`valueOf(String/byte)`<br>`byteValue()` |
	| short        | Short      | `parseShort(String)`<br>`valueOf(String/short)`<br/>`shortValue()` |
	| char         | Character  | `isDigit(char)`<br/>`isLetter(char)`<br/>`isUpperCase(char)`<br/>`toLowerCase(char)` |
	| int          | Integer    | `parseInt(String)`<br/>`valueOf(String/int)`<br/>`intValue()`<br/>`MAX_VALUE`/`MIN_VALUE` |
	| long         | Long       | `parseLong(String)`<br/>`valueOf(String/long)`<br/>`longValue()` |
	| float        | Float      | `parseFloat(String)`<br/>`valueOf(String/float)`<br/>`floatValue()` |
	| double       | Double     | `parseDouble(String)`<br/>`valueOf(String/double)`<br/>`doubleValue()` |

	- ```java
		public void test01(){
		        /* 自动装箱 */
		        /* 将下面语句自动变成 Integer i = new Integer(10) */
		        Integer i = 10; /* 10 为 int型 */
		
		        /* 自动拆箱 */
		        /* 将下面语句自动变成 int i1 = i.intValue() */
		        int i1 = i;
		
		        /* Integer转换成各个类型 类型Value() */
		        double d = i.doubleValue();
		        long l = i.longValue();
		
		        System.out.println(i);
		        System.out.println(i1);
		        System.out.println(l);
		        System.out.println(d);
		
		    }
		
		public void test02(){
		        /* 包装类缓冲问题 */
		        /* 包装类 存在缓存池（存储常用的数字） 大小为-128~127 超过以后就会去堆区开辟空间 */
		        /* 只要在缓存池的大小范围内，无论多少对象，指向同一块缓存区域 */
		        Integer a = 128;
		        Integer a1 = 128;
		        Integer b = 127;
		        Integer b1 = 127;
		        Integer c = -129;
		        Integer c1 = -129;
		        Integer d = -128;
		        Integer d1 = -128;
		
		        System.out.println( a == a1);
		        System.out.println( b == b1);
		        System.out.println( c == c1);
		        System.out.println( d == d1);
		}
		```

## Math类（数学工具类），方法都是静态方法

- | 静态方法               | 作用           |
	| ---------------------- | -------------- |
	| double floor(double a) | 对小数向下取整 |
	| double ceil(double a)  | 对小数向上取整 |

## Random类

- | 方法                   | 作用                        |
	| ---------------------- | --------------------------- |
	| int nextInt(int bound) | 随机生成[0,bound - 1)的数字 |
	| next数据类型()         | 其他类型的随机数格式        |

## File类

- 文件以及目录处理类——程序 和 磁盘 上的文件或者目录 的中间桥梁

- API

	-  构造器

		- 

		- | 构造器                              | 参数说明                                                     | 作用                                 |
			| ----------------------------------- | ------------------------------------------------------------ | ------------------------------------ |
			| `File(String pathname)`             | 传入 **文件 / 目录 的路径字符串**                            | 根据路径字符串直接创建 File 对象     |
			| `File(String parent, String child)` | **parent：父目录路径****child：子文件名 / 子目录名**         | 拼接父目录 + 子项形成完整路径        |
			| `File(File parent, String child)`   | **parent：父目录的 File 对象****child：子文件名 / 子目录名** | 更安全的拼接，基于 File 对象组合路径 |

	- 方法

		- 

		- | 方法              | 返回值    | 核心作用                                 |
			| ----------------- | --------- | ---------------------------------------- |
			| `mkdir()`         | `boolean` | 创建**单级目录**，父目录必须存在         |
			| `mkdirs()`        | `boolean` | 创建**多级目录**，自动补全不存在的父目录 |
			| `isDirectory()`   | `boolean` | 判断当前 `File` 是否为目录               |
			| `isFile()`        | `boolean` | 判断当前 `File` 是否为文件               |
			| `exists()`        | `boolean` | 判断文件 / 目录是否真实存在              |
			| `listFiles()`     | `File[]`  | 获取当前目录下的所有子文件 / 子目录      |
			| `createNewFile()` | `boolean` | 创建一个新的空文件，文件已存在则失败     |
			| `delete()`        | `boolean` | 删除文件 / 空目录，非空目录无法直接删除  |

## BigDecimal类 (高精度类)

- 运用于 对金钱等数据的处理 （或者 化成最小单位分，使用浮点类型，会出现错误）	

- ```java
	public void test01(){
	      /* 在底层运行小数时，会出现 浮点数精度丢失 / 浮点数运算误差 */
	      double a = 2.0;
	      double b = 1.1;
	      System.out.println(a - b); /* 0.8999999999999999 */
	
	      /* 使用高精度的类 */
	      BigDecimal a1 = new BigDecimal("2.0");
	      BigDecimal b1 = new BigDecimal("1.1");
	      System.out.println(a1.subtract(b1)); /* 0.9 */
	
	      /* 错误使用，无法等到正确的结果 */
	      BigDecimal a2 = new BigDecimal(2.0);
	      BigDecimal b2 = new BigDecimal(1.1);
	      System.out.println(a2.subtract(b2)); /* 0.899999999999999911182158029987476766109466552734375 */
	  }
	```

## 系统相关

- System类

	- 

	- | 静态方法                       | 说明                                                         |
		| ------------------------------ | ------------------------------------------------------------ |
		| long currentTimeMillis()       | 返回当前系统时间距离1970-1-1 0:0:0的毫秒值                   |
		| void exit(int status)          | 退出当前系统                                                 |
		| void gc()                      | 运行垃圾回收器                                               |
		| String getProperty(String key) | 获取某个系统属性 （Key 可以取值 java.version(获取 JDK 版本号)、user.language(获取用户语言)、user.country(获取国家/地区)、file.encoding(文件编码格式)、user.name(当前电脑登录的用户名)、os.version(操作系统版本号)、os.name(操作系统名称)） |

- Runtime类

	- 每个 Java 应用程序都有一个 `Runtime` 类实例，使应用程序能够与其运行的环境相连接。可以通过  `getRuntime` 方法获取当前运行时。  应用程序不能创建自己的 Runtime 类实例。

	- 

	- | 方法                        | 说明                                                         |
		| --------------------------- | ------------------------------------------------------------ |
		| static Runtime getRuntime() | 返回与当前 Java 应用程序相关的运行时对象（静态方法）         |
		| long totalMemory()          | 返回 Java 虚拟机中的内存总量。此方法返回的值可能随时间的推移而变化，这取决于主机环境 |
		| long freeMemory()           | 回 Java 虚拟机（JVM）中的空闲内存量。调用 gc 方法可能导致 freeMemory 返回值的增加 |