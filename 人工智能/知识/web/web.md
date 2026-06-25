[TOC]

javaWeb学习过程

web基础

​	客户端：html、css、js、jQuery

​	服务端：servlet、jsp

​	写项目：为高级铺垫 layui、servlet包装

​	vue框架

web进阶

​	框架：ssm框架

​	 Spring Boot：引入ai

## http协议

- http协议：tcp/ip的应用层
- http协议特点
	- 请求（通过域名解析出ip地址，通过ip地址向服务器的80端口程序 发送请求 遵守协议http）  —— 响应（服务器80端口上运行的程序 将客户端请求的页面源代码返回给客户端浏览器，使用浏览器进行渲染 需要遵循一定规范）
		- 该规范（客户端技术 —— 客户端执行）
			- 内容（结构）——html
			- 美化——css
			- 动作行为——js
	- 明文传输  衍生出https（有一个安全层）
	- 无状态协议
- https默认使用443端口，http默认使用80端口

## html

html

- 超文本 标记（给浏览器看） 语言

- html5是移动端开发的使用

- 表单

	- ```html
		<!--每个控件都需要name属性，以便服务端获取数据-->
		<body>
		    <form action="服务器地址" method="get/post">
		        文本框:<input type="text"> <br>
		        密码框:<input type="password"> <br>
		        单选:男<input type="radio" name="sex">女<input type="radio" name="sex"><br>
		        复选:男<input type="checkbox" name="sex">女<input type="checkbox" name="sex"><br>
		        下拉列表:<select>
		        	<option>1</option>
		        	<option>2</option>
		        </select>
		        隐藏域：<input type="hidden" value="123"><br>
		        文本域：<textarea></textarea> <br>
		        文件上传<input type="file"> <br>
		        <input type="button" value="普通按钮">
		        <input type="submit" value="提交按钮">
		        <input type="rest" value="重置按钮">
		        
		    </form>
		          
		</body>
		```

### iframe

#### frame(同级不能有body标签)

```html
<!-- main.html -->
<!DOCTYPE html>
<html lang="en">
<body>
    <ul>
        <li>管理系统</li>
        <ul>
            <a href="add.html" target="mainFrame"><li>添加</li></a>
            <a href="query.html" target="mainFrame"><li>查询</li></a>
        </ul>
    </ul>
</body>
</html>

<!-- top.html -->
<!DOCTYPE html>
<html lang="en">
<body>
    <h1>你好</h1>
</body>
</html>

<!-- left.html -->
<!DOCTYPE html>
<html lang="en">
<body>
    <ul>
        <li>管理系统</li>
        <ul>
            <a href="add.html" target="mainFrame"><li>添加</li></a>
            <a href="query.html" target="mainFrame"><li>查询</li></a>
        </ul>
    </ul>
</body>
</html>

<!-- add.html -->
<!DOCTYPE html>
<html lang="en">
<body>
    <h1>添加</h1>
</body>
</html>

<!-- query.html -->
<!DOCTYPE html>
<html lang="en">
<body>
    <h1>查询</h1>
</body>
</html>
```



```powershell
# 文件结构
E:.
    add.html
    left.html
    main.html
    query.html
    top.html
```

![frame效果图](../../img/JavaWeb%20--%20frame%E6%95%88%E6%9E%9C.png)

## CSS

css

- 使用方式
	- 内部：`<style> 标签{属性:具体样式} </style>`
	- 外部：`<linke href="css文件地址" type="text/css" rel="stylesheet">` 外部需要.css文件
	- 内联：`<标签 style="属性:具体样式">`
- 基本常识
	- 注释：`/**/ 或者 //`
	- 长度单位：px：像素   em：倍（默认14px）
- 选择器（常用）
	- 部分的选择器
		- id选择器：标签上使用id属性，css中使用 #id 访问
		- 元素选择器： css直接使用div
		- 类选择器：标签使用class属性，css中使用 .类名 访问