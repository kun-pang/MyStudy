# 环境搭建

宿主机：

- Debian GNU/Linux 13 (trixie)
- 编译器：gcc (Debian 14.2.0-19) 14.2.0
- 交叉编译器：arm-none-linux-gnueabihf-gcc (GNU Toolchain for the A-profile Architecture 9.2-2019.12 (arm-9.10)) 9.2.1 20191025
- make：GNU Make 4.4.1
- 文本编辑器：NVIM v0.12.2
- 代码编辑器：VSCode（Win11环境下，使用SSH链接进行开发）
- uboot：2020_10
- busybox:1.36.1
- Linux内核：4.19.35
- boa：0.94.13
- MobaXterm：v26.3 (Win11环境下)
- 网络查询工具：`netstat` (Linux自带，常见选项`-tuan`)



目标机：

- 野火的ebf-6ull —— ARM Cortex-A7 架构
- 



# BOA

- 嵌入式开源Web服务器
	- BOA：功能简单、代码量少、学习
	- httpd
	- appweb：功能强大、代码量大、一般工程使用。
- **BOA** 指**轻量级的开源 Web 服务器**

- 特点：
	- 单任务/单线程
	- 支持 CGI
	- 资源占用极低



移植BOA服务器：

- 下载源码

- 进行配置
	- 源码在src下面，且没有makefile，需要进行配置生成Makefile
	- 运行configure脚本，自动配置
	- 修改Makefile，使其支持目标机的运行环境
	- 如果需要交叉编译需要修改生成的Makefile，在工具前面添加宏
	
- 使用对应体系结构的编译器，进行编译，生成可执行文 件

- 如果是板子上，需要使用交叉工具链的strip，同时将 -g（调式选项关闭）

- 配置boa运行时配置文件

	- 程序的一次编译，能够在多个不同的环境进行运行

	- 在启动时读取配置文件，来告知bos怎么运行

	- boa配置文件放在：`/etc/boa/boa.conf`

		- **修改之前先备份**

		- 在解压目录中有一个参考配置

		- 流程：

			1. 创建配置文件的目录`sudo mkdir /etc/boa`

			2. `sudo cp boa.conf /etc/boa/`

			3. 备份之后，修改配置文件

				```bash
				# Boa v0.94 configuration file
				# File format has not changed from 0.93
				# File format has changed little from 0.92
				# version changes are noted in the comments
				#
				# The Boa configuration file is parsed with a lex/yacc or flex/bison
				# generated parser.  If it reports an error, the line number will be
				# provided; it should be easy to spot.  The syntax of each of these
				# rules is very simple, and they can occur in any order.  Where possible
				# these directives mimic those of NCSA httpd 1.3; I saw no reason to 
				# introduce gratuitous differences.
				
				# $Id: boa.conf,v 1.25 2002/03/22 04:33:09 jnelson Exp $
				
				# The "ServerRoot" is not in this configuration file.  It can be compiled
				# into the server (see defines.h) or specified on the command line with
				# the -c option, for example:
				#
				# boa -c /usr/local/boa
				
				
				# Port: The port Boa runs on.  The default port for http servers is 80.
				# If it is less than 1024, the server must be started as root.
				
				# 端口
				Port 80
				
				# Listen: the Internet address to bind(2) to.  If you leave it out,
				# it takes the behavior before 0.93.17.2, which is to bind to all
				# addresses (INADDR_ANY).  You only get one "Listen" directive,
				# if you want service on multiple IP addresses, you have three choices:
				#    1. Run boa without a "Listen" directive
				#       a. All addresses are treated the same; makes sense if the addresses
				#          are localhost, ppp, and eth0.
				#       b. Use the VirtualHost directive below to point requests to different
				#          files.  Should be good for a very large number of addresses (web
				#          hosting clients).
				#    2. Run one copy of boa per IP address, each has its own configuration
				#       with a "Listen" directive.  No big deal up to a few tens of addresses.
				#       Nice separation between clients.
				# The name you provide gets run through inet_aton(3), so you have to use dotted
				# quad notation.  This configuration is too important to trust some DNS.
				
				# 如果需要限制网段，就设置Listen属性，如果不配置就是任意IP可访问
				#Listen 192.68.0.5
				
				#  User: The name or UID the server should run as.
				# Group: The group name or GID the server should run as.
				
				# 用户名，组
				User siguyuan
				Group siguyuan
				
				# ServerAdmin: The email address where server problems should be sent.
				# Note: this is not currently used, except as an environment variable
				# for CGIs.
				
				#ServerAdmin root@localhost
				
				# ErrorLog: The location of the error log file. If this does not start
				# with /, it is considered relative to the server root.
				# Set to /dev/null if you don't want errors logged.
				# If unset, defaults to /dev/stderr
				
				# 修改错误日志路径
				ErrorLog /home/siguyuan/EBF_6ULL/web_server/boa/error_log
				# Please NOTE: Sending the logs to a pipe ('|'), as shown below,
				#  is somewhat experimental and might fail under heavy load.
				# "Usual libc implementations of printf will stall the whole
				#  process if the receiving end of a pipe stops reading."
				#ErrorLog "|/usr/sbin/cronolog --symlink=/var/log/boa/error_log /var/log/boa/error-%Y%m%d.log"
				
				# AccessLog: The location of the access log file. If this does not
				# start with /, it is considered relative to the server root.
				# Comment out or set to /dev/null (less effective) to disable 
				# Access logging.
				
				# 修改访问日志路径
				# /dev/null内核的空洞文件，设置成/dev/null表示不使用
				AccessLog /home/siguyuan/EBF_6ULL/web_server/boa/access_log
				# Please NOTE: Sending the logs to a pipe ('|'), as shown below,
				#  is somewhat experimental and might fail under heavy load.
				# "Usual libc implementations of printf will stall the whole
				#  process if the receiving end of a pipe stops reading."
				#AccessLog  "|/usr/sbin/cronolog --symlink=/var/log/boa/access_log /var/log/boa/access-%Y%m%d.log"
				
				# UseLocaltime: Logical switch.  Uncomment to use localtime 
				# instead of UTC time
				#UseLocaltime
				
				# VerboseCGILogs: this is just a logical switch.
				#  It simply notes the start and stop times of cgis in the error log
				# Comment out to disable.
				
				#VerboseCGILogs
				
				# ServerName: the name of this server that should be sent back to 
				# clients if different than that returned by gethostname + gethostbyname 
				
				#ServerName www.your.org.here
				
				# VirtualHost: a logical switch.
				# Comment out to disable.
				# Given DocumentRoot /var/www, requests on interface 'A' or IP 'IP-A'
				# become /var/www/IP-A.
				# Example: http://localhost/ becomes /var/www/127.0.0.1
				#
				# Not used until version 0.93.17.2.  This "feature" also breaks commonlog
				# output rules, it prepends the interface number to each access_log line.
				# You are expected to fix that problem with a postprocessing script.
				
				#VirtualHost 
				
				# DocumentRoot: The root directory of the HTML documents.
				# Comment out to disable server non user files.
				
				# 修改web访问的时的根目录，即192.168.50.50/a.html中/a.html展开 => /home/siguyuan/EBF_6ULL/web_server/boa/www/a.hmlt
				DocumentRoot 
				/home/siguyuan/EBF_6ULL/web_server/boa/www
				
				# UserDir: The name of the directory which is appended onto a user's home
				# directory if a ~user request is recieved.
				
				UserDir public_html
				
				# DirectoryIndex: Name of the file to use as a pre-written HTML
				# directory index.  Please MAKE AND USE THESE FILES.  On the
				# fly creation of directory indexes can be _slow_.
				# Comment out to always use DirectoryMaker
				
				DirectoryIndex index.html
				
				# DirectoryMaker: Name of program used to create a directory listing.
				# Comment out to disable directory listings.  If both this and
				# DirectoryIndex are commented out, accessing a directory will give
				# an error (though accessing files in the directory are still ok).
				
				DirectoryMaker /usr/lib/boa/boa_indexer
				
				# DirectoryCache: If DirectoryIndex doesn't exist, and DirectoryMaker
				# has been commented out, the the on-the-fly indexing of Boa can be used
				# to generate indexes of directories. Be warned that the output is 
				# extremely minimal and can cause delays when slow disks are used.
				# Note: The DirectoryCache must be writable by the same user/group that 
				# Boa runs as.
				
				# DirectoryCache /var/spool/boa/dircache
				
				# KeepAliveMax: Number of KeepAlive requests to allow per connection
				# Comment out, or set to 0 to disable keepalive processing
				
				KeepAliveMax 1000
				
				# KeepAliveTimeout: seconds to wait before keepalive connection times out
				
				KeepAliveTimeout 10
				
				# MimeTypes: This is the file that is used to generate mime type pairs
				# and Content-Type fields for boa.
				# Set to /dev/null if you do not want to load a mime types file.
				# Do *not* comment out (better use AddType!)
				
				MimeTypes /etc/mime.types
				
				# DefaultType: MIME type used if the file extension is unknown, or there
				# is no file extension.
				
				DefaultType text/plain
				
				# CGIPath: The value of the $PATH environment variable given to CGI progs.
				
				CGIPath /bin:/usr/bin:/usr/local/bin
				
				# SinglePostLimit: The maximum allowable number of bytes in 
				# a single POST.  Default is normally 1MB.
				
				# AddType: adds types without editing mime.types
				# Example: AddType type extension [extension ...]
				
				# Uncomment the next line if you want .cgi files to execute from anywhere
				#AddType application/x-httpd-cgi cgi
				
				# Redirect, Alias, and ScriptAlias all have the same semantics -- they
				# match the beginning of a request and take appropriate action.  Use
				# Redirect for other servers, Alias for the same server, and ScriptAlias
				# to enable directories for script execution.
				
				# Redirect allows you to tell clients about documents which used to exist in
				# your server's namespace, but do not anymore. This allows you to tell the
				# clients where to look for the relocated document.
				# Example: Redirect /bar http://elsewhere/feh/bar
				
				# Aliases: Aliases one path to another.
				# Example: Alias /path1/bar /path2/foo
				
				Alias /doc /usr/doc
				
				# ScriptAlias: Maps a virtual path to a directory for serving scripts
				# Example: ScriptAlias /htbin/ /www/htbin/
				
				ScriptAlias /cgi-bin/ /usr/lib/cgi-bin/
				
				
				```

			4. 启动boa`sudo ./boa`

			5. 检查是否成功`netstat -tan`，查看有没有`tcp        0      0 0.0.0.0:80 `的条目存在

			6. 运行测试，在网页上使用IP访问www目录下的资源（注意是http）

				访问日志信息`access_log`

				```bash
				siguyuan@debian:~/EBF_6ULL/web_server/boa/www$ cat ../access_log
				10.128.0.1 - - [22/Aug/2026:05:19:06 +0000] "▒" 501 0 "-" "-"
				10.128.0.1 - - [22/Aug/2026:05:19:06 +0000] "l" 501 0 "-" "-"
				10.128.0.1 - - [22/Aug/2026:05:19:06 +0000] "▒" 501 0 "-" "-"
				10.128.0.1 - - [22/Aug/2026:05:19:06 +0000] "l" 501 0 "-" "-"
				10.128.0.1 - - [22/Aug/2026:05:19:22 +0000] "GET /a.html HTTP/1.1" 404 0 "-" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36"
				10.128.0.1 - - [22/Aug/2026:05:19:22 +0000] "GET /favicon.ico HTTP/1.1" 404 0 "http://10.128.0.128/a.html" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36"
				10.128.0.1 - - [22/Aug/2026:05:19:32 +0000] "GET /index.html HTTP/1.1" 200 1462 "-" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36"
				
				```

				错误日志`error_log`：

				```bash
				siguyuan@debian:~/EBF_6ULL/web_server/boa/www$ cat ../error_log
				[22/Aug/2026:03:28:02 +0000] boa.c:194 - unable to bind: Permission denied
				[22/Aug/2026:03:30:54 +0000] boa: server version Boa/0.94.13
				[22/Aug/2026:03:30:54 +0000] boa: server built Aug 22 2026 at 10:23:55.
				[22/Aug/2026:03:30:54 +0000] boa: starting server pid=231419, port 80
				[22/Aug/2026:03:32:03 +0000] caught SIGTERM, starting shutdown
				[22/Aug/2026:03:32:03 +0000] exiting Boa normally (uptime 69 seconds)
				[22/Aug/2026:05:17:27 +0000] boa: server version Boa/0.94.13
				[22/Aug/2026:05:17:27 +0000] boa: server built Aug 22 2026 at 10:23:55.
				[22/Aug/2026:05:17:27 +0000] boa: starting server pid=234807, port 80
				[22/Aug/2026:05:19:06 +0000] malformed request: "▒"
				[22/Aug/2026:05:19:06 +0000] malformed request: "l"
				[22/Aug/2026:05:19:06 +0000] malformed request: "▒"
				[22/Aug/2026:05:19:06 +0000] malformed request: "l"
				# 第一次的失败请求：因为没有a.html文件
				[22/Aug/2026:05:19:22 +0000] request from 10.128.0.1 "GET /a.html HTTP/1.1" ("/home/siguyuan/EBF_6ULL/web_server/boa/www/a.html"): document open: No such file or directory
				[22/Aug/2026:05:19:22 +0000] request from 10.128.0.1 "GET /favicon.ico HTTP/1.1" ("/home/siguyuan/EBF_6ULL/web_server/boa/www/favicon.ico"): document open: No such file or directory
				[22/Aug/2026:05:20:42 +0000] request from 10.128.0.1 "(null)" ("(null)"): connection timed out
				
				```

				



问题：

1. 运行.configure脚本出现报错

  ```bash
  siguyuan@debian:~/EBF_6ULL/web_server/boa/boa-0.94.13/src$ ./configure
  creating cache ./config.cache
  checking for gunzip... /usr/bin/gunzip
  checking for flex... flex
  checking for yywrap in -lfl... no
  checking for bison... bison -y
  checking for gcc... gcc
  checking whether the C compiler (gcc  ) works... no
  configure: error: installation or configuration problem: C compiler cannot create executables.
  
  # 解决：
  # 有gcc版本
  siguyuan@debian:~/EBF_6ULL/web_server/boa/boa-0.94.13/src$ gcc --version
  gcc (Debian 14.2.0-19) 14.2.0
  Copyright (C) 2024 Free Software Foundation, Inc.
  This is free software; see the source for copying conditions.  There is NO
  warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  
  # 1. 检查有没有gcc库
  sudo apt install build-essential bison flex libc6-dev
  
  # 2. 让高版本的GCC放宽语法检查
  # 删除旧的缓存
  rm -f config.cache
  # 传入忽略隐式声明的 CFLAGS 参数重新 configure
  CFLAGS="-Wno-implicit-function-declaration -Wno-implicit-int" ./configure
  
  # 最后还是必须，查看日志cat config.log
  ```

  

2. 执行make时出现错误

	```bash
	request.c:137:55: error: passing argument 3 of ‘getsockname’ from incompatible pointer type [-Wincompatible-pointer-types]
	  137 |     if (getsockname(fd, (struct sockaddr *) &salocal, &len) != 0) {
	      |                                                       ^~~~
	      |                                                       |
	      |                                                       size_t * {aka long unsigned int *}
	/usr/include/x86_64-linux-gnu/sys/socket.h:117:47: note: expected ‘socklen_t * restrict’ {aka ‘unsigned int * restrict’} but argument is of type ‘size_t *’ {aka ‘long unsigned int *’}
	  117 |                         socklen_t *__restrict __len) __THROW;
	      |                         ~~~~~~~~~~~~~~~~~~~~~~^~~~~
	request.c:171:64: error: passing argument 5 of ‘getsockopt’ from incompatible pointer type [-Wincompatible-pointer-types]
	  171 |             (conn->fd, SOL_SOCKET, SO_SNDBUF, &system_bufsize, &len) == 0
	      |                                                                ^~~~
	      |                                                                |
	      |                                                                size_t * {aka long unsigned int *}
	/usr/include/x86_64-linux-gnu/sys/socket.h:257:46: note: expected ‘socklen_t * restrict’ {aka ‘unsigned int * restrict’} but argument is of type ‘size_t *’ {aka ‘long unsigned int *’}
	  257 |                        socklen_t *__restrict __optlen) __THROW;
	      |                        ~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~
	make: *** [<内置>：request.o] 错误 1
	
	
	# 找到 request.c文件将getsockname(fd, (struct sockaddr *) &salocal, &len)中len的声明将size_t 改为  socklen_t
	
	# 再次make
	util.c: In function ‘get_commonlog_time’:
	util.c:100:39: error: pasting "t" and "->" does not give a valid preprocessing token
	  100 |         time_offset = TIMEZONE_OFFSET(t);
	      |                                       ^
	compat.h:120:30: note: in definition of macro ‘TIMEZONE_OFFSET’
	  120 | #define TIMEZONE_OFFSET(foo) foo##->tm_gmtoff
	      |                              ^~~
	make: *** [<内置>：util.o] 错误 1
	
	# 找到compat.h中#define TIMEZONE_OFFSET(foo) foo##->tm_gmtoff定义改为 foo->tm_gmtoff
	# 如果 ## 拼接的结果不是一个有效的单 Token（valid preprocessing token），则程序是未定义的（Undefined Behavior），编译器必须报错。
	# 拼接后t->不属于下面任何一种有效单token
	
	
	# 再次make
	gcc  -o boa y.tab.o lex.yy.o alias.o boa.o buffer.o cgi.o cgi_header.o config.o escape.o get.o hash.o ip.o log.o mmap_cache.o pipe.o queue.o read.o request.o response.o select.o signals.o util.o sublog.o timestamp.o -g
	/usr/bin/ld: log.o:(.bss+0x8): multiple definition of `error_log_name'; config.o:(.bss+0x88): first defined here
	/usr/bin/ld: log.o:(.bss+0x10): multiple definition of `access_log_name'; config.o:(.bss+0x90): first defined here
	/usr/bin/ld: log.o:(.bss+0x18): multiple definition of `cgi_log_name'; config.o:(.bss+0x98): first defined here
	collect2: error: ld returned 1 exit status
	make: *** [Makefile:43：boa] 错误 1
	
	# 符号表多重定义在log.c 中error_log_name 、access_log_name、cgi_log_name声明前面添加extern
	```

	- 【新版GCC的标准】有效的单 Token（拼接后形成的字符串）：
		- 标识符：用于变量名、函数名、结构体名、宏名等。只能由 **字母、数字、下划线** 组成，且**不能以数字开头**。
		- 预处理数字：包括整数、浮点数、十六进制等。以数字开头，后面可以跟数字、字母、小数点等。
		- 运算符与标点符号：必须是 C 语言词法库里**现成存在**的运算符。
		- 字符/字符串字面量：用单引号或双引号包裹的内容
		- 单个非空白字符：不属于上述分类的单个特殊字符（如 `@`、`$` 等，通常由编译器扩展处理）。



---

# 动态网页和静态网页，以及CGI技术

![](../../img/new_219_%E9%A1%B9%E7%9B%AE1.png)



静态网页：html文件本身在服务器中存在。

动态网页：一切页面和数据都是由程序产生的。

CGI：CGI是一种标准。Web服务器 与 程序（多种语言，如：c、C++、java）动态生成数据 之间的通用网关接口。



如何将程序让BOA服务器接收动态请求时，知道程序在哪里？

1、 先创建生成动态数据的程序。

2、配置/etc/boa/boa.conf，找到ScriptAlias变量，并在后面添加路径信息（请求的虚拟路径和服务器的目录关系）。

> [!CAUTION]
>
> ​	CGIPath变量：并非 CGI 程序的存放路径，而是赋给 CGI 进程的环境变量 `PATH`，用于确保 CGI 脚本能正确找到并执行系统命令（如：`ls`、`cat`）。

```bash
# boa.conf

# CGIPath: The value of the $PATH environment variable given to CGI progs.

# 这个是CGI执行时的环境变量
CGIPath /bin:/usr/bin:/usr/local/bin

# ScriptAlias: Maps a virtual path to a directory for serving scripts
# Example: ScriptAlias /htbin/ /www/htbin/

# 需要修改。这个是请求的虚拟路径 与 实际目录的映射关系
# 记得最后加上/，表示目录
ScriptAlias /cgi-bin/ /home/siguyuan/EBF_6ULL/web_server/boa/www/cgi/

# http://10.128.0.128/cgi-bin/a
# 服务器会自动去/home/siguyuan/EBF_6ULL/web_server/boa/www/cgi下找同名的程序执行
```

3、记得重启服务先`ps aux` 找boa进程号，杀死`kill -9 boa进程号`，重启`sudo ./boa`





简单的shell脚本测试

```bash
#!/bin/bash

date "+%Y-%m-%d %H:%M:%S"

echo "=================="

# 1. 计算瞬时 CPU 使用率（采样 1 秒）
eval $(awk '/^cpu /{print "prev_idle="$5"; prev_total="$2+$3+$4+$5+$6+$7+$8}' /proc/stat)
sleep 1
eval $(awk '/^cpu /{print "idle="$5"; total="$2+$3+$4+$5+$6+$7+$8}' /proc/stat)
diff_idle=$((idle - prev_idle))
diff_total=$((total - prev_total))
cpu_usage=$(awk "BEGIN {printf \"%.1f%%\", (1 - $diff_idle / $diff_total) * 100}")

# 2. 读取并计算已用内存（从 /proc/meminfo）
mem_info=$(awk '/MemTotal/{t=$2} /MemAvailable/{a=$2} END {printf "%.2f GB / %.2f GB (%.1f%%)", (t-a)/1024/1024, t/1024/1024, (t-a)/t*100}' /proc/meminfo)

# 3. 读取并转换系统运行时间（从 /proc/uptime）
uptime_info=$(awk '{
    d=int($1/86400); h=int(($1%86400)/3600); m=int(($1%3600)/60); s=int($1%60);
    if (d>0) printf "%d天 ", d;
    printf "%d小时%d分%d秒", h, m, s
}' /proc/uptime)

# 4. 格式化输出
echo "CPU使用率：${cpu_usage}"
echo "使用内存：${mem_info}"
echo "系统运行时间：${uptime_info}"

```

错误：

​	直接在网页中访问`http://10.128.0.128/cgi-bin/test`。

​	出现`502 Bad Gateway `，表示：一般5开头是服务器问题，cgi程序需要在开头添加响应格式`echo -e "Content-Type: text/html; charset=utf-8\r\n"`。

> [!CAUTION]
>
> ​	如果解释器使用的`#!/bin/sh`，不用添加`-e`，因为自动进行字符转义。如果使用的是`#!/bin/bash`，就需要显示开启转义`-e`



----

# 网站工作流程

在浏览器中使用F12（检查） -> 检查网络`network`

网站渲染流程：

​	1、URL地址`http://10.128.0.10/a.html`

​	2、向服务器发起请求 `/a.html`请求

​	3、服务器解析`http://10.128.0.10/a.html`。

​	4、根据解析调用正常的程序或者流程，返回资源

​	5、浏览器根据资源内容，进行逐行样式的解析渲染 ，以及向别服务器发送新的请求（如：图片使用外部的网络图片）。



---

# 前后端分离

动态页面 $\rightarrow$  动态数据加载：

由程序产生的页面 $\rightarrow$  将样式 与 数据 进行 分离【前后端分离，一份程序能支持多个平台的显示】



数据以JSON格式传输到前端（键值对）

前端页面主要由 HTML【骨架】 + CSS【装饰】 +Javascript【功能】

 

HTTP协议（应用层）：

- 请求协议（头） —— ASCII码

	- ```http
		POST /v1/users HTTP/1.1
		Host: api.example.com
		User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
		Content-Type: application/json; charset=utf-8
		Content-Length: 48
		Accept: application/json, text/plain, */*
		Accept-Language: zh-CN,zh;q=0.9,en;q=0.8
		Accept-Encoding: gzip, deflate, br
		Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkXVCJ9...
		Cache-Control: no-cache
		Connection: keep-alive
		
		请求方法 URL 协议版本 \r\n
		请求头部（格式: 字段:值 \r\n)
		\r\n
		请求内容
		
		```

	- 注意：\r\n数量和空格

- 响应协议（头）—— ASCII码

	- ```http
		HTTP/1.1 200 OK
		Date: Sat, 29 Aug 2026 10:12:49 GMT
		Server: nginx/1.24.0
		Content-Type: application/json; charset=utf-8
		Content-Length: 154
		Connection: keep-alive
		Cache-Control: no-cache, no-store, must-revalidate
		Access-Control-Allow-Origin: *
		Set-Cookie: session_id=xyz12345; Path=/; Secure; HttpOnly; SameSite=Lax
		Strict-Transport-Security: max-age=31536000; includeSubDomains
		
		协议版本 状态码 状态值 \r\n
		响应头部（格式: 字段:值 \r\n)
		\r\n
		响应内容 
		```

	- ```text
		状态码：
		2xx：成功
		3xx: 不确定（重定向、不需要响应、有缓存）
		4xx: 请求非法（请求有问题）
		5xx: 服务器有问题
		```

- 重定向（302）：被请求的资源 临时被移动到了新的 URL，客户端还继续使用原 URL 发起以后的请求，服务器返回302并告知新的地址。

	- 服务器使用`Location: 新URL`，返回新的地址



---

# Bootstrap框架（前端）

- 主流前端框架：React 、Vue.js、Angular 、Next.js、Astro、Nuxt、Svelte / SvelteKit、SolidJS / SolidStart、Qwik

- 本次使用老牌的前端框架Bootstrap

- Bootstrap特点 —— 响应式前端（栅格式前端）：

	- 根据设备尺寸大小，网页自适应

- 框架样式已经确定，可以直接使用

- 下载内容（网络好的可以使用在线的方式）：

	- 根据官方的例子，发现需要 样式库bootstrap.min.css、功能库jquery-3.3.1.min.js（注：slim为精简版，不支持ajax）、popper.min.js、bootstrap.min.js

	- ```html
		<!doctype html>
		<html lang="en">
		  <head>
		    <!-- Required meta tags -->
		    <meta charset="utf-8">
		    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
		
		    <!-- Bootstrap CSS -->
		    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.1.3/dist/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
		
		    <title>Hello, world!</title>
		  </head>
		  <body>
		    <h1>Hello, world!</h1>
		
		    <!-- Optional JavaScript -->
		    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
		    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
		    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.14.3/dist/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
		    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.1.3/dist/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
		  </body>
		</html>
		```

	- 解压，选择部分内容放到项目中

		- `bootstrap.min.css`拷贝到项目`css`目录中
		- `bootstrap.min.js`拷贝到项目的`js`目录中

	- 其余两个文件，可以采用src提供的网址，跳转过去，复制 或者 另存为

	- 项目的目录构成

		- ```bash
			.
			└── ./www
			    ├── ./www/css
			    │   └── ./www/css/bootstrap.min.css
			    ├── ./www/index.html
			    └── ./www/js
			        ├── ./www/js/bootstrap.min.js
			        ├── ./www/js/jquery-3.3.1.min.js
			        └── ./www/js/popper.min.js
			```

- 在www下创建一个index.html，里面添加上面官方例子中必要的字段

	- ```html
		<!DOCTYPE html>
		<html lang="zh">
		<head>
		    <meta charset="utf-8">
		    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
		    <title>我的E家</title>
		    <link rel="stylesheet" href="css/bootstrap.min.css">
		    <script src="js/jquery-3.3.1.min.js"></script>
		    <script src="js/popper.min.js"></script>
		    <script src="js/bootstrap.min.js"></script>
		</head>
		<body>
		    <h1>测试</h1>
		</body>
		</html>
		```

	- 如果你是在项目部署在虚拟机上，且虚拟机上只有终端界面，可以在vscode中使用 **Remote - SSH** 配合 **Live Server 扩展**，直接用本地电脑（Windows/Mac）的浏览器实时预览和热重载修改。



实际的显示查看官方的教程或者例子，看到好看的复制到自己的项目中。bootstrap的基本用法：`<html标签 class="使用的bootstrap库名" data-toggle="bootstrap提供的动作库" >`

---

# AJAX

**传统模式（无 Ajax）**： 用户在网页上每做一次操作（例如点个赞、提交一行表单、翻页），浏览器都必须向服务器发送一个全新的 HTTP 请求。服务器处理完后，返回一整张完整的 HTML 页面，浏览器清空当前页面并重新加载渲染。

- **缺点**：页面会频繁出现白屏、闪烁，用户的输入状态和滚动位置会丢失，体验极差。

**Ajax 模式**： 允许 JavaScript 在后台默默地向服务器发送 HTTP 请求，只获取需要更新的数据（如 JSON/XML），然后通过 DOM 操作**局部更新**网页的某一部分，而不需要刷新整个页面。



AJAX（Asynchronous JavaScript and XML），是异步个JavaScript搭XML技术。服务器与AJAX对象（底层是：JS引擎）进行信息交流，AJAX对象再与浏览器信息交流



回调函数：“我先把函数注册在这里，你先去干别的，等到特定时刻（比如事件发生或异步任务完成）你再来调用它。



```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ajax测试 —— 菜鸟教程</title>
    <script>
        function loadXMLDoc() {         // 按钮点击函数 —— 加载内容
            var xmlhttp;
            xmlhttp = new XMLHttpRequest();     // new出一个ajax对象

            xmlhttp.onreadystatechange = function () {      // 注册一个函数（回调函数）
                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {     // 比对状态和状态码是否正确
                    document.getElementById("myDiv").innerHTML = xmlhttp.responseText;      // 获取资源修改html内容
                }
            }
            xmlhttp.open("GET", "/ajax_demo.txt", true);                // 请求的资源   
            // 如果 HTML 文件在 Web 服务器的根（资源）目录下使用了软链接，
            // 那么该 HTML 引用的资源文件（CSS、JS、图片等）也必须放置在 Web 根目录下（或同样在 Web 根目录下为资源建立软链接）；
            // 注意使用绝对路径时：
            // 使用相对路径跨目录引用时，可以利用 .. 退回上一级目录（例如 ../app/style.css）；
            // 但如果写成以 / 开头的绝对路径（如 /app/style.css），浏览器会将 / 解析为 Web 服务器的根目录，
            // 导致服务器最终拼接出假的本地路径（例如 /www/app/style.css）而报 404 错误。
            xmlhttp.send();                                             // 发送请求
        }
    </script>
</head>

<body>
    <div id="myDiv">
        <h2>使用 AJAX 修改该文本内容</h2>
    </div>
    
    <button type="button" onclick="loadXMLDoc()">修改内容</button>      
</body>

</html>
```



---

# JQuery的ajax

```htm
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>jquery的ajax</title>
    <!-- 引入时，不能写内容 slim不支持ajax -->
    <script src="js/jquery-3.3.1.min.js"></script>     
</head>
<body>
    <div id="myDiv">
        <h2>使用 JQuery的 AJAX 修改该文本内容</h2>
    </div>
    
    <button type="button" id="btn">修改内容</button>    
    
    <!-- JQuery语法格式要求，在文件最后写 -->
    <script>
    	// $表示jquery的全局变量
        $(document).ready(function(){       // 表示当 DOM 树加载渲染完毕（网页结构准备就绪）的那一刻，注册一个匿名函数
            $("#btn").click(function(){      // 找到id为btn的标签，注册一个点击函数
                $.ajax({                    // 使用ajax对象
                    url: "/ajax_demo.txt",
                    async: true,            // 开启异步，发送完，不等待响应，先处理其他事情，接收到响应后执行处理函数
                    success: function(result){    // 成功，将响应结果，放到替换的标签中
                        $("#myDiv").html(result);
                    }  
                });
            });
        });
    </script>
</body>
</html>
```



---

# JSON

是**轻量、解析速度快、天生契合主流语言编程结构** 的优势，成功替代了 XML。

是一种键值对的字符串格式。



使用Jquery框架，实现ajax获取json格式

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>jquery获取json数据</title>
    <!-- 引入时，不能写内容 slim不支持ajax -->
    <script src="js/jquery-3.3.1.min.js"></script>     
</head>
<body>
    <div id="myDiv">
        <h2>使用 JQuery的 JSON 数据</h2>
    </div>
    
    <button type="button" id="btn">JSON数据</button>    
    
    <!-- JQuery语法格式要求，在文件最后写 -->
    <script>
        $(document).ready(function(){       
            $("#btn").click(function(){      
                $.getJSON("/json_test.json", function(date){        // 使用封装的getJSON使用ajax获取JSON数据
                    console.log(date);          // 打印到浏览器控制台
                    var aa = "<p>这是数据1：" + date[0].a1 + " 这是数据2：" + date[0].a2 + "</p>";     // 字符串拼接
                    $("#myDiv").html(aa);
                });
            });
        });
    </script>
</body>
</html>
```





动态刷新

```html
<!DOCTYPE html>
<html lang="zh">

    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <title>我的E家</title>
        <link rel="stylesheet" href="css/bootstrap.min.css">
        <script src="js/jquery-3.3.1.min.js"></script>
        <script src="js/popper.min.js"></script>
        <script src="js/bootstrap.min.js"></script>
    </head>

    <body>

        <!-- 顶部导航栏 -->
        <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
            <div class="container-fluid">
                <!-- 品牌名称 -->
                <a class="navbar-brand" href="#">我的E家</a>

                <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav">
                    <span class="navbar-toggler-icon"></span>
                </button>

                <div class="collapse navbar-collapse" id="navbarNav">
                    <!-- 左侧导航菜单 -->
                    <ul class="navbar-nav mr-auto mb-2 mb-lg-0">
                        <li class="nav-item active">
                            <a class="nav-link" href="#">智能客厅</a>
                        </li>
                        <li class="nav-item">
                            <a class="nav-link" href="#">智能厨房</a>
                        </li>
                    </ul>

                    <!-- 右侧注册登录 -->
                    <ul class="navbar-nav ml-auto">
                        <li class="nav-item">
                            <a class="nav-link" href="#">注册</a>
                        </li>
                        <li class="nav-item">
                            <a class="nav-link" href="#">登录</a>
                        </li>
                    </ul>
                </div>
            </div>
        </nav>

        <!-- 主体内容区域 -->
        <div class="container mt-5">
            <!-- 标题 -->
            <h2 class="text-center mb-5">我的智能客厅</h2>

            <!-- 下载列表表格 -->
            <table class="table table-borderless text-center " id="t1">
                <thead class="border-bottom">
                    <tr>
                        <th scope="col">序号</th>
                        <th scope="col">任务名称</th>
                        <th scope="col">任务大小</th>
                        <th scope="col">下载速度</th>
                        <th scope="col">下载进度</th>
                        <th scope="col">下载组状态</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <th scope="row">1</th>
                        <td>复仇者联盟4</td>
                        <td>3.21GB</td>
                        <td>3.12MB/s</td>
                        <td>57.87%</td>
                        <td>下载中</td>
                    </tr>
                </tbody>
            </table>
        </div>

        <script>
            $(document).ready(function () {
                // 假设 API 一次性返回全部数据（这里以 10 条为例）
                var allData = [];
                var currentIndex = 0; // 当前展示的页码索引（0 表示前5条，1 表示后5条）
                var pageSize = 5;      // 每页显示 5 条

                // 动态渲染数据的函数
                function renderTableData(dataList) {
                    var $tbody = $("#t1 tbody");
                    $tbody.empty(); // 清空当前表格

                    $.each(dataList, function (index, item) {
                        var row = "<tr>" +
                            "<td>" + item.序号 + "</td>" +
                            "<td>" + item.任务名称 + "</td>" +
                            "<td>" + item.任务大小 + "</td>" +
                            "<td>" + item.下载速度 + "</td>" +
                            "<td>" + item.下载进度 + "</td>" +
                            "<td>" + item.下载组状态 + "</td>" +
                            "</tr>";
                        $tbody.append(row);
                    });
                }

                // 切换并显示下一组数据
                function showNextPage() {
                    if (allData.length === 0) return;

                    // 计算切片位置
                    var start = currentIndex * pageSize;
                    var end = start + pageSize;
                    var pageData = allData.slice(start, end);

                    // 渲染当前 5 条数据
                    renderTableData(pageData);

                    // 更新索引，循环切换（0 -> 1 -> 0 ...）
                    currentIndex = (start + pageSize >= allData.length) ? 0 : currentIndex + 1;
                }

                // 获取 JSON 并启动定时轮播
                function initData() {
                    $.getJSON("/index_data.json", function (data) {
                        allData = data; // 保存全部数据
                        showNextPage(); // 立即显示第一组（1-5条）

                        // 每隔 5 秒切换显示下一组（6-10条）
                        setInterval(showNextPage, 5000);
                    });
                }

                initData();
            });
        </script>
    </body>

</html>
```

数据：

```json

[
  {
    "序号": 1,
    "任务名称": "Ubuntu_24.04_LTS_Desktop_x64.iso",
    "任务大小": "4.8 GB",
    "下载速度": "12.5 MB/s",
    "下载进度": "85%",
    "下载组状态": "下载中"
  },
  {
    "序号": 2,
    "任务名称": "VSCodeUserSetup-x64-1.92.0.exe",
    "任务大小": "95.4 MB",
    "下载速度": "0 B/s",
    "下载进度": "100%",
    "下载组状态": "已完成"
  },
  {
    "序号": 3,
    "任务名称": "CentOS-Stream-9-latest-x86_64-dvd1.iso",
    "任务大小": "9.2 GB",
    "下载速度": "0 B/s",
    "下载进度": "32%",
    "下载组状态": "已暂停"
  },
  {
    "序号": 4,
    "任务名称": "Node.js_v20.16.0_Documentation.pdf",
    "任务大小": "18.6 MB",
    "下载速度": "2.1 MB/s",
    "下载进度": "60%",
    "下载组状态": "下载中"
  },
  {
    "序号": 5,
    "任务名称": "DockerDesktopInstaller.exe",
    "任务大小": "584.0 MB",
    "下载速度": "0 B/s",
    "下载进度": "12%",
    "下载组状态": "网络异常"
  },
 {
    "序号": 6,
    "任务名称": "Python-3.12.5-amd64.exe",
    "任务大小": "25.2 MB",
    "下载速度": "5.4 MB/s",
    "下载进度": "92%",
    "下载组状态": "下载中"
  },
  {
    "序号": 7,
    "任务名称": "MySQL_Community_Server_8.0.39.zip",
    "任务大小": "420.8 MB",
    "下载速度": "0 B/s",
    "下载进度": "45%",
    "下载组状态": "等待中"
  },
  {
    "序号": 8,
    "任务名称": "Debian_12.6.0_netinst.iso",
    "任务大小": "628.0 MB",
    "下载速度": "0 B/s",
    "下载进度": "100%",
    "下载组状态": "已完成"
  },
  {
    "序号": 9,
    "任务名称": "JDK-21_windows-x64_bin.msi",
    "任务大小": "165.3 MB",
    "下载速度": "1.8 MB/s",
    "下载进度": "38%",
    "下载组状态": "下载中"
  },
  {
    "序号": 10,
    "任务名称": "Android_Studio_2024.1.1_installer.exe",
    "任务大小": "1.1 GB",
    "下载速度": "0 B/s",
    "下载进度": "0%",
    "下载组状态": "任务暂停"
  }
]

```



---

# cJSON

用于第三库解析和生成JSON数据

```c
#include <stdio.h>
#include "cJSON.h"

int main(){
    /* 产生一个cJSON指针 */
    cJSON *root = cJSON_CreateObject();     // 本质是一棵树,且申请在堆区
    if(!root){
        fprintf(stderr, "cJSON_CreateObject\n");
        goto enderr;
    }

    /* 添加数据 —— 键值对 */
    cJSON *value = cJSON_CreateString("aaa"); 
    if(!value){
        fprintf(stderr, "cJSON_CreateString\n");
        goto enderr;
    }
    cJSON_AddItemReferenceToObject(root, "a1", value);       // 添加一个a1: "aaa"

    /* 生成能打印的字符串 */
    char *str = cJSON_Print(root);
    if (str == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
        cJSON_free(str);
        cJSON_Delete(root);
        return -1;
    }
    printf("%s\n", str);

    cJSON_free(str);        // 释放堆区上的空间
enderr:
    cJSON_Delete(root);
    return 0;
}

```



数据动态产生

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cJSON.h"

char *getStr(){
    char *str = NULL;       // 变量放开头，防止-o2优化下，认为有goto导致后面变量不能初始化的警告
    cJSON *value = NULL;

    /* 产生一个cJSON指针 */
    cJSON *root = cJSON_CreateObject();     // 本质是一棵树,且申请在堆区
    if(!root){
        fprintf(stderr, "cJSON_CreateObject\n");
        goto enderr;
    }

    /* 增加随机数 */
    srand(time(NULL));
    double temp = (double)(rand() % 30 + 10);

    /* 添加数据 —— 键值对 */
    value = cJSON_CreateNumber(temp); 
    if(!value){
        fprintf(stderr, "cJSON_CreateString\n");
        goto enderr;
    }
    cJSON_AddItemToObject(root, "temp", value);       // 添加一个温度

    /* 生成能打印的字符串 */
    str = cJSON_Print(root);
    if (str == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }
enderr:
    cJSON_Delete(root);
    return str;
}


int main(){
    char *str = NULL;
    str = getStr();
    printf("Content-Type: application/json; charset=utf-8\r\n\r\n");
    printf("%s", str);

    cJSON_free(str);
    return 0;
}
```

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>jquery获取json数据</title>
    <!-- 引入时，不能写内容 slim不支持ajax -->
    <script src="js/jquery-3.3.1.min.js"></script>
</head>

<body>
    <div id="myDiv">
        <h2>使用 JQuery的 JSON 数据</h2>
    </div>

    <button type="button" id="btn">JSON数据</button>

    <!-- JQuery语法格式要求，在文件最后写 -->
    <script>
        $(document).ready(function () {
            $("#btn").click(function () {
                $.getJSON("/cgi-bin/cgi_ajax", function (date) {        // 使这里的路径使用的是boa配置文件里boa自己认定的cgi目录名
                    console.log(date);          // 打印到浏览器控制台
                    var aa = "<p>温度:" + date.temp + "</p>";     // 字符串拼接
                    $("#myDiv").html(aa);
                }).fail(function (jqXHR, textStatus, errorThrown) {
                    // 如果后端返回的不是标准 JSON，或者路径不对，会走这里
                    console.error("请求失败：", textStatus, errorThrown);
                    console.log("服务器返回的原始响应内容：", jqXHR.responseText);
                });
            });
        });
    </script>
</body>

</html>
```



---

# 如何获取web传递的数据（GET 和 POST）

需要读取web提交的form表单 或者 json方式

form表单get请求方式：通过url传递 数据：`?键=值`

```html
<!DOCTYPE html>
<html lang="zh">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>form表单</title>
    <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="js/jquery-3.3.1.min.js"></script>
    <script src="js/popper.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
</head>

<body>
<form action="/cgi-bin/test_form" method="get">
    <!-- lavbel的for属性表示：绑定组件的id，点击标签也会跳到输入框 -->
     <!-- input name表示用于后端接收数据以及控制表单行为 -->
    <label for="u_name"> 用户名： <input type="text" id="u_name" name="user_name"></label>
    <br>
    <label for="u_pwd"> 密码： <input type="password" id="u_pwd" name="user_pwd"></label>
    <br>
    <!-- submit:触发表单提交 -->
    <input type="submit" value="注册">
</form>
</body>

</html>
```



```txt
GET http://10.128.0.128/cgi-bin/test_from?user_name=1&user_pwd=1 
```



form表单post请求方式：通过TCP报文传递

```html
<!DOCTYPE html>
<html lang="zh">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>form表单</title>
    <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="js/jquery-3.3.1.min.js"></script>
    <script src="js/popper.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
</head>

<body>
<form action="/cgi-bin/test_form" method="post">
    <!-- lavbel的for属性表示：绑定组件的id，点击标签也会跳到输入框 -->
     <!-- input name表示用于后端接收数据以及控制表单行为 -->
    <label for="u_name"> 用户名： <input type="text" id="u_name" name="user_name"></label>
    <br>
    <label for="u_pwd"> 密码： <input type="password" id="u_pwd" name="user_pwd"></label>
    <br>
    <!-- submit:触发表单提交 -->
    <input type="submit" value="注册">
</form>
</body>

</html>
```

```txt
POST http://10.128.0.128/cgi-bin/test_form 
```

 

web服务器与CGI模块的数据传递通过环境变量传递，防止有些语言不支持进程间通信。CGI有规范的环境变量要求

| 变量                       | 描述                                                         |
| -------------------------- | ------------------------------------------------------------ |
| `AUTH_TYPE`                | 用于保护 servlet 的认证方案的名称。 例如， `BASIC`， `SSL`或 `null` (如果 servlet 未受保护)。 |
| `CONTENT_LENGTH`           | 通过输入流变为可用的请求主体的长度（以字节为单位），或 `-1`（如果长度未知）。 对于 HTTP servlet，返回的值与 CGI 变量 `CONTENT_LENGTH` 的值相同。 |
| `CONTENT_TYPE`             | 请求的主体的 MIME 类型，或 NULL（如果类型未知）。 对于 HTTP servlet，返回的值与 CGI 变量 `CONTENT_TYPE` 的值相同。 |
| `GATEWAY_INTERFACE`        | 服务器用于与脚本进行通信的 CGI 规范的修订版。 它是“`CGI/1.1`”。 |
| `HTTP_ACCEPT`              | 如果所使用方案是 HTTP，那么名称以“HTTP_”开头的变量将包含来自请求头的值。 `HTTP_ACCEPT` 指定了您的浏览器所支持的内容类型。 例如，`text/xml`。 |
| `HTTP_ACCEPT_CHARSET`      | 字符首选项信息。 用于指示客户机的首选字符集（如果有）。 例如，`utf-8;q=0.5`。 |
| `HTTP_ACCEPT_ENCODING`     | 定义可对返回到客户机的内容执行的编码类型。 例如，`compress;q=0.5`。 |
| `HTTP_ACCEPT_LANGUAGE`     | 用于定义希望以何种语言来接收内容。 例如，`en;q=0.5`。 如果未返回任何内容，那么将不指示任何语言首选项。 |
| `HTTP_FORWARDED`           | 如果请求经过转发，那么将显示代理服务器的地址和所经端口。     |
| `HTTP_HOST`                | 指定所请求资源的因特网主机和端口号。 对于所有 HTTP/1.1 请求为必需变量。 |
| `HTTP_PROXY_AUTHORIZATION` | 由客户机用于向要求认证的代理识别自身（或其用户）。           |
| `HTTP_USER_AGENT`          | 客户机用于发送请求的浏览器的类型和版本。 例如，`Mozilla/1.5`。 |
| `PATH_INFO`                | 可以选择包含来自调用脚本的 HTTP 请求的额外路径信息，从而指定路径由 CGI 脚本进行解释。 PATH_INFO 将识别要由 CGI 脚本返回的资源或子资源，并来源于位于脚本名称之后及任何查询数据之前的 URI 路径部分。 |
| `PATH_TRANSLATED`          | 将脚本的虚拟路径图到用于调用脚本的物理路径。 此操作通过采用请求 URI 的任何 PATH_INFO 组件并执行任何适当的从虚拟到物理转换而完成。 |
| `QUERY_STRING`             | 包含在路径后的请求 URL 中的查询字符串。                      |
| `REMOTE_ADDR`              | 返回发送请求的客户机的 IP 地址。 对于 HTTP servlet，返回的值与 CGI 变量 `REMOTE_ADDR` 的值相同。 |
| `REMOTE_HOST`              | 发送请求的客户机的标准名称，或该客户机的 IP 地址（如果无法确定名称）。 对于 HTTP servlet，返回的值与 CGI 变量 `REMOTE_HOST` 的值相同。 |
| `REMOTE_USER`              | 如果用户已通过认证，将返回进行此请求的用户的登录信息，或者返回 NULL（如果用户未经认证）。 |
| `REQUEST_METHOD`           | 返回进行请求时所使用的 HTTP 方法的名称。 例如，`GET`、`POST` 或 `PUT`。 |
| `SCRIPT_NAME`              | 返回 HTTP 请求第一行中的 URL 中从协议名称到查询字符串的部分。 |
| `SERVER_NAME`              | 返回收到请求的服务器的主机名称。 对于 HTTP servlet，返回的值与 CGI 变量 `SERVER_NAME` 的值相同。 |
| `SERVER_PORT`              | 返回收到此请求的端口号。 对于 HTTP servlet，返回的值与 CGI 变量 SERVER_PORT 的值相同。 |
| `SERVER_PROTOCOL`          | 将按以下格式返回请求所使用的协议的名称和版本：`protocol/majorVersion.minorVersion`。 例如，`HTTP/1.1`。 对于 HTTP servlet，返回的值与 CGI 变量 `SERVER_PROTOCOL` 的值相同。 |
| `SERVER_SOFTWARE`          | 返回正在运行 servlet 的 servlet 容器的名称和版本。           |
| `HTTP_COOKIE`              | HTTP cookie 字符串。                                         |
| `WEBTOP_USER`              | 已登录用户的用户名。                                         |
| `NCHOME`                   | `NCHOME` 环境变量。                                          |



c原生的方式获取get数据

```c
#include <stdio.h>
#include <stdlib.h>

int main(){
    /* 获取cgi环境变量 */
    printf("Content-Type: text/html; charset=utf-8\r\n\r\n");
    char *ret = NULL;
    ret = getenv("REQUEST_METHOD");     // REQUEST_METHOD: 获取请求方式 get post
    if(!ret){
        fprintf(stderr, "REQUEST_METHOD get error\n");
        return -1;
    }

    printf("<h2> 请求方式： %s</h2>\n", ret);

    ret = getenv("QUERY_STRING");
     if(!ret){
        fprintf(stderr, "QUERY_STRING get error\n");
        return -1;
    }
    printf("<h2> get请求数据： %s</h2>\n", ret);

    return 0;
}

// 注意对的html文件中的form标签的method选择的请求方式
```





c原生的方式获取post数据

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *ret = NULL;  // 请求方式
  char *data = NULL; // 请求数据
  int falg = 0;      // 默认get请求，1为post请求
  /* 获取cgi环境变量 */
  printf("Content-Type: text/html; charset=utf-8\r\n\r\n");
  ret = getenv("REQUEST_METHOD"); // REQUEST_METHOD: 获取请求方式 get post
  if (!ret) {
    fprintf(stderr, "REQUEST_METHOD get error\n");
    return -1;
  }

  if (strncmp(ret, "GET", 3) == 0) {
    data = getenv("QUERY_STRING");
    if (!data) {
      fprintf(stderr, "QUERY_STRING get error\n");
      return -1;
    }
  } else if (strncmp(ret, "POST", 4) == 0) {
    falg = 1;

    /* post请求，先获取请求数据长度 */
    char *num_str = getenv("CONTENT_LENGTH");

    /* 转换数字 */
    char *end = NULL;
    errno = 0;
    long val = strtol(num_str, &end, 10);
    if (errno == ERANGE) {
      perror("数值溢出\n");
      return -1;
    }
    // 检查是否解析到了非数字字符
    else if (end == num_str) {
      printf("未找到有效数字！\n");
      return -1;
    } 

    /* 获取请求数据 —— 从标准输入中获取 */
    data = (char *)malloc(sizeof(char) * (val + 1));
    if(!data){ return -1; }
    memset(data, 0, sizeof(char) * (val + 1));

    int i = 0;
    for(i = 0; i < val; ++i){
        data[i] = fgetc(stdin);
    }

    data[i] = '\0';  // 补齐字符串

  } else {
    printf("<h1> form表单请求方式未知 </h1>");
  }

  printf("<h2> 请求方式： %s</h2>\n", ret);
  printf("<h2> 请求数据： %s</h2>\n", data);

  if(falg){
    free(data);
  }

  return 0;
}
```

```html
<!DOCTYPE html>
<html lang="zh">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>form表单</title>
    <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="js/jquery-3.3.1.min.js"></script>
    <script src="js/popper.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
</head>

<body>
<form action="/cgi-bin/test_form2" method="post">
    <!-- lavbel的for属性表示：绑定组件的id，点击标签也会跳到输入框 -->
     <!-- input name表示用于后端接收数据以及控制表单行为 -->
    <label for="u_name"> 用户名： <input type="text" id="u_name" name="user_name"></label>
    <br>
    <label for="u_pwd"> 密码： <input type="password" id="u_pwd" name="user_pwd"></label>
    <br>
    <!-- submit:触发表单提交 -->
    <input type="submit" value="注册">
</form>
</body>

</html>
```



引入第三方库cgic

​	cgic的实现思想：cgic中有main，先处理web服务器的数据，然后调用cgic预留的cgiMain接口，将数据发现自己的程序。现在我需要实现cgiMain，即数据处理

​	注意cgic库主要针对form表单，不能解析JSON数据格式

```c
#include "cgic.h"
#include <stdio.h>
#include <stdlib.h>

int cgiMain() {

  /* 获取请求方式 */
  char *ret = getenv("REQUEST_METHOD");
  if (!ret) {
    fprintf(stderr, "REQUEST_METHOD get error\n");
    return -1;
  }

  /* 利用cgic库获取解析好的数据 */
  char name[16] = {0};
  char pew[16] = {0};
  cgiHeaderContentType("text/html; charset=utf-8");                 // 响应内容
  cgiFormStringNoNewlines("user_name", name, 16);                 // 获取用户名
  cgiFormStringNoNewlines("user_pwd", pew, 16);                   // 获取用户名

  fprintf(cgiOut, "<b> 请求方式：%s, 用户名 - 密码: %s - %s </b>", ret, name,
          pew);
  return 0;
}
```



---

# 案例介绍 —— 基于web服务的机房温度监控系统



## 结构框图

![](../../img/new_222_%E9%A1%B9%E7%9B%AE%E7%9A%84%E7%BB%93%E6%9E%84%E6%A1%86%E5%9B%BE.png)



## 项目代码

项目目录结构
```bash
.
├── ./cJSON.c
├── ./cJSON.h
├── ./sim_catch.c
├── ./task.c
├── ./task.h
└── ./temp_cgi.c
```



```c
// task.h
#ifndef __TASK_H__
#define __TASK_H__

#define NAME_LEN 32
#define MSG_LEN 5

/* 消息结构体的声明 */
struct task_msg_s{
    char    name[NAME_LEN];    // 名字
    double  temp;              // 温度
};

/* 池子思想 —— 管理消息结构体的池 */
struct task_info_s{
    int use;                              // 使用的个数
    struct task_msg_s task_msg[MSG_LEN];  // 消息数组
} ;


/* 共享内存相关 */
#define KEY_1       "/home"
#define KEY_2       10
extern int shm_id;

void* init_shm();
void delete_shm(void *p);

#endif

// task.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "task.h"

int shm_id = 0;

void* init_shm(){
    key_t k1;
    struct task_info_s *table;

    k1 = ftok(KEY_1, KEY_2);
    if(k1 == -1){
        perror("ftok");
        return NULL;
    }

    shm_id = shmget(k1, sizeof(struct task_info_s), IPC_CREAT | 0644);
    if(shm_id == -1){
        perror("shmget");
        return NULL; 
    }

    table = (struct task_info_s *)shmat(shm_id, NULL, 0);
    if(table == (void *)-1){
        perror("table");
        return NULL;
    }
    return table;
}


void delete_shm(void *p){
    shmdt(p);
    shmctl(shm_id,IPC_RMID, NULL);
}
```



```c
// sim_catch.c
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "task.h"

/* 采集端 */
static struct task_info_s *tasks;
static char *t_names[] = {"机房1","机房2", "机房3" };

void get_data(int num){
    tasks->use = num;

    int i = 0;
    /* 随机产生温度 */
    for(i = 0; i < num; ++i){
        tasks->task_msg[i].temp = (double)((rand() % 9000) + 1000) / 100.0;
        snprintf(tasks->task_msg[i].name, NAME_LEN, "%s", t_names[i % 3]);
    }
}

int main(){
    srand(time(NULL));
    tasks = (struct task_info_s *)init_shm();
    if(tasks == NULL){
        fprintf(stderr, "init share memory!\n");
        return -1;
    }

    for(int i = 0; i < 4; ++i){
        get_data(3);
        sleep(1);
    }

    return 0;
}
```



```c
// temp_cgi.c
#include <stdio.h>

#include "cJSON.h"
#include "task.h"

/* 发送端 */

static struct task_info_s *tasks;

void send_json(){
    cJSON *infos;
    cJSON *info;
    char temp[16] = {0};

    cJSON *root = cJSON_CreateObject();
    if(!root){
        goto end1;
    }

    cJSON_AddItemToObject(root, "num", cJSON_CreateNumber(tasks->use));
    
    infos = cJSON_CreateArray();
    if(infos == NULL){
        goto end2;
    }

    cJSON_AddItemToObject(root, "data", infos);

    for(int i = 0; i < tasks->use; ++i){
        info = cJSON_CreateObject();
        if(info == NULL){
            goto end2;
        }

        cJSON_AddItemToArray(infos, info);

        cJSON_AddItemToObject(info, "name", cJSON_CreateString(tasks->task_msg[i].name));
        snprintf(temp, sizeof(temp), "%0.2f", tasks->task_msg[i].temp);
        cJSON_AddItemToObject(info, "temp", cJSON_CreateString(temp));
    }

    char *str = cJSON_Print(root);
    if(!str){
        goto end2;
    }
    printf("%s", str);

    cJSON_free(str);
end2:
   cJSON_Delete(root);
end1:
    return;
}

int main(){
    printf("Content-Type: text/html; charset=utf-8\r\n\r\n");

    tasks = (struct task_info_s *)init_shm();
    if(tasks == NULL){
        fprintf(stderr, "init share memory!\n");
        return -1;
    }

    send_json();

    delete_shm(tasks);
    return 0;
}
```



```html
<!DOCTYPE html>
<html lang="zh">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>温度</title>
    <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="js/jquery-3.3.1.min.js"></script>
    <script src="js/popper.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
</head>

<body>

    <!-- 主体内容区域 -->
    <div class="container mt-5">
        <!-- 下载列表表格 -->
        <table class="table table-borderless text-center " id="t1">
            <thead class="border-bottom">
                <tr>
                    <th scope="col">机房名称</th>
                    <th scope="col">温度</th>
                </tr>
            </thead>
            <tbody>
            </tbody>
        </table>
        <button type="button" id="btn">修改内容</button>
    </div>

    <script>
        $(document).ready(function () {
            var $tbody = $("#t1 tbody");
            $("#btn").click(function () {
                $.getJSON("/cgi-bin/temp_cgi", function (info) {        // 使用封装的getJSON使用ajax获取JSON数据
                    console.log(info);          // 打印到浏览器控制台
                    $tbody.empty();
                    for (let item of info.data) {
                        var row = "<tr>" +
                            "<td>" + item.name + "</td>" +
                            "<td>" + item.temp + "℃" + "</td>" +
                            "</tr>";
                        $tbody.append(row);
                    }
                });
            });
        });
    </script>
</body>

</html>
```

