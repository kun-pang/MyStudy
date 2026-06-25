[TOC]



## Windows的中文输入，无法退格、回车

- 原因：SSH 终端窗口**抢占了键盘焦点**，输入法的候选框按键（空格、数字、退格）都直接发给了 Debian，绕过了输入法的选词逻辑。

- 解决方式1：在任意地方打好中文 → 复制 → 终端里右键粘贴

- 解决方式2：在 Debian 里安装 **fcitx + 中文输入法**，让输入法运行在 Linux （但这需要图形界面（X11），纯 SSH 终端下**无法实现**）

	- ```shell
		sudo apt install fcitx fcitx-pinyin
		```



## SSH终端无法显示中文

- 原因：Debian不支持中文

- 解决方式：添加中文包

	- 第一步：检查 Debian 的 locale

		- ```bash
			locale
			```

		- 看输出里有没有 `zh_CN.UTF-8`，如果没有：

		- ```bash
			sudo apt install locales
			sudo dpkg-reconfigure locales
			# 在列表里选择 zh_CN.UTF-8
			```

	- 第二步：设置环境变量

		- ```bash
			export LANG=zh_CN.UTF-8
			export LC_ALL=zh_CN.UTF-8
			```

		- 写入 `~/.bashrc` 让它永久生效：

		- ```bash
			echo 'export LANG=zh_CN.UTF-8' >> ~/.bashrc
			echo 'export LC_ALL=zh_CN.UTF-8' >> ~/.bashrc
			source ~/.bashrc
			```

	- 第三步：MobaXterm 设置 UTF-8

		- 在 MobaXterm 里：
			- Settings → Configuration → Terminal → **Default character set → UTF-8**