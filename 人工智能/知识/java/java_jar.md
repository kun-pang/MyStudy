## Java swing

- JFrame ：窗口类

  - setVisible(true)  ：设置窗口是否可见 位置必须在方法的最后，否则组件不可
  - setSize() : 设置窗口大小
  - setLocationRelativeTo() ： 设置窗口居中（相对位置） null 为居中
  - setTitle(“ ”) ： 设置窗口标题
  - add() ：在窗口中加入组件，这样才会显示
  - setLayout() ：布局管理器 
  	- null为禁用
  	- new FlowLayout(FlowLayout.LEFT) 从左到右的布局
  - setDefaultCloseOperation()：点击窗口上×时，JFrame.EXIT_ON_CLOSE 关闭程序
  - add()：添加组件，先添加的组件在上层，后添加的组件在下层
  - setJMenuBar()：设置菜单条

- JLabel ：标签类

  - setBounds()：设置位置  前两个参数指定位置，后两个参数指定大小
  - setIcon()：放置图片

- JButton：按钮类

  - setBounds() ：设置位置
  - addActionListener() ：添加动作监听器

- ButtonGroup：按钮组类 将两个单选按钮归到一个组中

  - add() 加入组

- JTextF ield：文本输入框类

  - setBounds() ：设置位置

- JPasswordField : 密码输入框类

  - setBounds() ：设置位置
  - isSelected()：是否选中
  - setSelected()：true 初始状态选中

- ImageIcon：图片类

  - getIconWidth()：获取图片的宽
  - getIconHeight()：获取图片的高

- JMenuBar：菜单条类（不需要设置位置、大小）

  - add()：添加菜单

- JMenu：菜单

  - add()：添加菜单项

- JMenuItem：菜单项

  - ```java
    JMenuBar jMenuBar = new JMenuBar();
    String[] menuNames = {"管理","设置","文件"};
    String[][] menusItems = {{"管理1","管理2"},{"设置1","设置2"},{"文件1","文件2"}};
    
    for(int i = 0; i < menuNames.length; i++){
        JMenu jMenu = new JMenu(menuNames[i]);
        jMenuBar.add(jMenu);
        for(int j = 0; j < menusItems[i].length; j++){
            JMenuItem jMenuItem = new JMenuItem(menusItems[i][j]);
            jMenu.add(jMenuItem);
        }
    }
    ```

- JPanel：容器组件

- JSplitPane：分割容器

	- setDividerLocation()：设置分隔线位置

- JScrollPane：可以滑动的容器

- JTable：表格，需要放到JScrollPane中




### 适配器

- 在接口需要实现的方法太多，就需要适配器进行一次处理（空实现），后续的使用哪个方法直接调用适配器进行重写哪个方法
- MouseAdapter()：MouseListener的适配器，里面空实现了MouseListener的方法，后续只用继承一下重写需要的方法进行

## junit

- 测试框架
- 使用步骤
	-  项目中创建 lib 的目录（放别人写好的 jar 包）
	- 将 junit 的 jar 包加入项目
	- 通过 Project Structure-> LIbraries-> 添加 lib 目录
	- 在自己的项目中在写一个用于测试的（public、无返回值的）函数上写@Test，该函数中调用想要测试的函数（一个类只有一个 main()，main 中只能调用一个方法）



## druid

阿里的数据库连接池包



## dbutils

简化数据库增删改查的包



## lombok

在优化类的包（在运行时，自动写一些方法，如get（）set(）方法等）

1、打插件 java -jar lombok.jar选择ide的安装路径（传统方式）
2、引入依赖（JAVA Maven的方式）
   	<dependency>
		<groupId>org.projectlombok</groupId>
		<artifactId>lombok</artifactId>
		<version>1.16.18</version>
		<scope>provided</scope>
	</dependency>
3、使用：
 @Getter/@Setter 生成get /set
 @ToString 生成toString
 @EqualsAndHashCode 生成equals 和 hashcode
 @NonNull
 @NoArgsConstructor：生成无参构造器；
@RequiredArgsConstructor：生成包含final和@NonNull注解的成员变量的构造器；
@AllArgsConstructor：生成全参构造器
@Data：作用于类上，是以下注解的集合：
	@ToString @EqualsAndHashCode @Getter@Setter @RequiredArgsConstructor



## 杂项

- ```java
	//获取当前屏幕的尺寸（宽度和高度）
	Toolkit toolkit = Toolkit.getDefaultToolkit();   // 获取默认的工具包（与平台相关）
	Dimension screenSize = toolkit.getScreenSize();  // 获得屏幕的大小，包含 width 和 height
	```

	
