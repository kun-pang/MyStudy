## MVC架构思想

- **MVC分层**（项目目录 —— 加粗的字体为必须层）：	

	- **展示层（ui界面）** 
		- ui
			- frame  —— 存放界面代码
			- listener —— 存放监听动作
	- **业务层（处理业务，将数据处理之后返回给另外两层）**
		- service —— 存放业务接口 和 impl中的业务实现
			- impl —— 放业务实现类
			- 业务接口
	- **数据访问层（与数据库、文件数据进行直接交流的，只是获取数据）**
		- dao ——— 存放dao接口 和 impl中的dao实现
			- impl —— 存放dao实现
			- dao接口
	- images —— 存放图片素材
	- model  —— 存放model相关
	- pojo —— 存放类，数据库中几张表，就至少有几个类
	- utils —— 存放重复出现的代码段
		- 常量类：存放全局的字符常量、普通常量
		- 其他工具类
	- Dto —— 存放输入组件的信息类，数据传输对象（表单、查询条件）
	- clinet ——存放测试代码 或者 程序入口 ，比如测试其他类是否到达预期

- ```powershell
	com.XXX
	  - images             // 图片资源
	  - ui                 // 视图层 View
	    - frame            // 所有窗体
	    - listener         // 监听器（Controller）
	  - dto                // 数据传输对象（表单、查询条件）
	  - service            // 业务层
	    - EmpService.java  // 接口
	    - impl
	      - EmpServiceImpl.java // 接口实现
	  - dao                // 数据访问层
	    - EmpDao.java     // dao接口
	    - impl
	      - EmpDaoImpl.java // dao实现
	  - pojo               // 数据库实体类（Emp、Dept）
	  - util               // 工具类（JDBCUtil、DateUtil等）
	  - constant           // 常量类
	  - test               // 测试类
	  - Main.java          // 程序入口
	```

- 


## 面向对象的设计原则

1. 单一职责原则

	- 一个类 / 一个方法，只干一类事情 / 一件事，并且只因为一件事而修改。

2. OCP原则（开闭原则）

	- open close principle ， 对扩展开放（要加新功能，**新增代码**就行），对修改关闭（原来能运行的老代码**尽量不改**）。

	- ```java
		/* 例如 */
		/* 违背ocp */
		class Pay {
		    void pay(String type) {
		        if ("wx".equals(type)) {
		            System.out.println("微信支付");
		        } else if ("ali".equals(type)) {
		            System.out.println("支付宝");
		        }
		        // 以后加银联、云闪付……都要改这里
		    }
		}
		
		/* 符合ocp */
		// 统一接口
		interface Payment {
		    void pay();
		}
		
		// 微信支付
		class WxPay implements Payment {
		    public void pay() { System.out.println("微信"); }
		}
		
		// 支付宝
		class AliPay implements Payment {
		    public void pay() { System.out.println("支付宝"); }
		}
		```

3. 依赖倒置

	- 面向接口 或者 父类编程时，  使用父类引用（接口）  指向子类对象（接口实现）。
	  - `父类 aa = new 子类();` `接口 bb = new 接口实现类;

4. 接口隔离原则

	- 接口应该小而专（一个接口不应该装太多方法）