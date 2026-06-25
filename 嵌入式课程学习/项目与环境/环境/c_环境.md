[TOC]

## CLion安装

- 安装 Clion

	- 注意：需要在 **系统变量的 Path** 中添加 GCC 相关的路径（这样才能保证全局都能编译 C 文件）
	- CLion 自带的相关 GCC 路径：`\...\JetBrains\CLion 2023.3.4\bin`（文件类包含 gcc.exe）

- 检验（编写c程序验证）

	- 编写 C 的简单程序，理解   .c 文件  —>  GCC 编译 —>   可执行文件（Windows 上为.exe）

	- 命令行编译：`gcc 文件名.c -o 文件名 `（第二个文件名为可执行文件名，可自定义）

	- ```c
		#include <stdio.h>			// i/o相关的头文件
		#include <stdlib.h>			// 通用工具函数头文件  如：free()、malloc()...
		
		int main()
		{
		    printf("hello word\n");
		    
		    return 0;
		}
		```



## Windows环境下使用Linux中的objdump命令方法

- Windows下想使用这个反汇编指令，需要下载[MSYS2 或者 MinGW64](https://www.mingw-w64.org/downloads/#mingw-w64-builds)

- MSYS2安装

	- 下载之后点击安装程序安装

	- 使用 MSYS2 UCRT64 终端，输入命令，过程中的询问全部按y

	- ```shell
		## 配置下载源（中科大）
		cat > /etc/pacman.conf << 'EOF'
		[options]
		LogFile = /var/log/pacman.log
		GPGDir = /etc/pacman.d/gnupg/
		HookDir = /etc/pacman.d/hooks/
		HoldPkg = pacman glibc msys2-runtime
		CacheDir = /var/cache/pacman/pkg/
		DBPath = /var/lib/pacman/
		RootDir = /
		SigLevel = Never
		
		[ucrt64]
		Server = https://mirrors.ustc.edu.cn/msys2/mingw/ucrt64/
		
		[msys]
		Server = https://mirrors.ustc.edu.cn/msys2/msys/x86_64/
		EOF
		
		rm -rf /var/lib/pacman/sync/*
		pacman -Syyu
		
		
		## 安装工具链
		pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
		```

	- 安装完成之后将  .\msys\ucrt64\bin  添加到环境变量中。(并提供优先级，及将该变量放到其他gcc之前)


## Windows下的内存泄露检测工具

- 使用ASAN库（MSYS2中下载）

- 打开MSYS2 clang64终端

	- ```shell
		tanjun@SiGuYuan MINGW64 /e/project/cProject
		$ nano /etc/pacman.conf
		
		[clang64]
		Server = https://mirrors.ustc.edu.cn/msys2/mingw/clang64/
		
		(ctrl + o 保存 --  回车  --  ctrl + x 退出)
		
		# 强制刷新所有仓库数据库
		tanjun@SiGuYuan CLANG64 /e/project/cProject
		$ pacman -Syy
		
		# 安装所有的库
		tanjun@SiGuYuan CLANG64 /e/project/cProject
		$ pacman -S mingw-w64-clang-x86_64-toolchain
		
		# 写一个越界测试
		cat > test.c << 'EOF'
		#include <stdlib.h>
		int main() {
		    int *p = malloc(4);
		    p[100] = 0; // 堆越界
		    free(p);
		    return 0;
		}
		EOF
		
		# 编译+运行 ASAN
		clang -g -fsanitize=address -o test.exe test.c
		./test.exe
		
		#结果
		=================================================================
		==18408==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x117d3a5a01c0 at pc 0x7ff74ce21490 bp 0x006e8af3fc30 sp 0x006e8af3fc78
		WRITE of size 4 at 0x117d3a5a01c0 thread T0
		    #0 0x7ff74ce2148f in main E:/project/cProject/test.c:4:12
		    #1 0x7ff74ce210fd in __tmainCRTStartup D:/W/B/src/mingw-w64/mingw-w64-crt/crt/crtexe.c:260:11
		    #2 0x7ff74ce213e5 in .l_start D:/W/B/src/mingw-w64/mingw-w64-crt/crt/crtexe.c:129:9
		    #3 0x7ffef2b3e8d6  (C:\WINDOWS\System32\KERNEL32.DLL+0x18002e8d6)
		    #4 0x7ffef37cc40b  (C:\WINDOWS\SYSTEM32\ntdll.dll+0x18008c40b)
		
		0x117d3a5a01c0 is located 396 bytes after 4-byte region [0x117d3a5a0030,0x117d3a5a0034)
		allocated by thread T0 here:
		    #0 0x7ffe2397b7c1 in malloc (E:\ruanJian\msys\clang64\bin\libclang_rt.asan_dynamic-x86_64.dll+0x18004b7c1)
		    #1 0x7ff74ce2144d in main E:/project/cProject/test.c:3:14
		    #2 0x7ff74ce210fd in __tmainCRTStartup D:/W/B/src/mingw-w64/mingw-w64-crt/crt/crtexe.c:260:11
		    #3 0x7ff74ce213e5 in .l_start D:/W/B/src/mingw-w64/mingw-w64-crt/crt/crtexe.c:129:9
		    #4 0x7ffef2b3e8d6  (C:\WINDOWS\System32\KERNEL32.DLL+0x18002e8d6)
		    #5 0x7ffef37cc40b  (C:\WINDOWS\SYSTEM32\ntdll.dll+0x18008c40b)
		
		SUMMARY: AddressSanitizer: heap-buffer-overflow E:/project/cProject/test.c:4:12 in main
		Shadow bytes around the buggy address:
		  0x117d3a59ff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
		  0x117d3a59ff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
		  0x117d3a5a0000: fa fa 00 00 fa fa 04 fa fa fa fa fa fa fa fa fa
		  0x117d3a5a0080: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
		  0x117d3a5a0100: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
		=>0x117d3a5a0180: fa fa fa fa fa fa fa fa[fa]fa fa fa fa fa fa fa
		  0x117d3a5a0200: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
		  0x117d3a5a0280: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
		  0x117d3a5a0300: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
		  0x117d3a5a0380: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
		  0x117d3a5a0400: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
		Shadow byte legend (one shadow byte represents 8 application bytes):
		  Addressable:           00
		  Partially addressable: 01 02 03 04 05 06 07
		  Heap left redzone:       fa
		  Freed heap region:       fd
		  Stack left redzone:      f1
		  Stack mid redzone:       f2
		  Stack right redzone:     f3
		  Stack after return:      f5
		  Stack use after scope:   f8
		  Global redzone:          f9
		  Global init order:       f6
		  Poisoned by user:        f7
		  Container overflow:      fc
		  Array cookie:            ac
		  Intra object redzone:    bb
		  ASan internal:           fe
		  Left alloca redzone:     ca
		  Right alloca redzone:    cb
		==18408==ABORTING
		
		
		# 退出 MSYS2 CLANG64终端
		# 打开 VSCode 设置 → 搜索 terminal.integrated.profiles.windows
		# 输入
		#        "MSYS2 CLANG64": {
		#           "path": "msys的安装路径\\msys\\msys2_shell.cmd",
		#           "args": ["-defterm", "-here", "-no-start", "-clang64"]
		#       }
		# 关闭终端，新建终端
		```

	- ```c++
		{
		    "files.autoSave": "afterDelay",
		    "cmake.configureOnOpen": true,
		    "vscode-edge-devtools.webhint": false,
		    "KeilAssistant.MDK.Uv4Path": "E:\\qianRuShi\\Keil_v5\\UV4\\UV4.exe",
		    "KeilAssistant.C51.Uv4Path": "\"E:\\qianRuShi\\Keil_v5\\UV4\\UV4.exe\"",
		    "files.autoGuessEncoding": true,
		    "github.copilot.editor.enableAutoCompletions": true,
		    "fittencode.languagePreference.displayPreference": "zh-cn",
		    "fittencode.languagePreference.commentPreference": "zh-cn",
		    "workbench.colorTheme": "Default Light+",
		    "workbench.preferredDarkColorTheme": "Default Light+",
		    "workbench.preferredHighContrColorTheme": "Default Light+",
		    "claudeCode.preferredLocation": "panel",
		    "terminal.integrated.profiles.windows": {
		        "MSYS2 CLANG64": {
		            "path": "E:\\ruanJian\\msys\\msys2_shell.cmd",
		            "args": ["-defterm", "-here", "-no-start", "-clang64"]
		        },
		        "PowerShell": {
		            "source": "PowerShell",
		            "icon": "terminal-powershell"
		        },
		        "Command Prompt": {
		            "path": [
		                "${env:windir}\\Sysnative\\cmd.exe",
		                "${env:windir}\\System32\\cmd.exe"
		            ],
		            "args": [],
		            "icon": "terminal-cmd"
		        },
		        "Git Bash": {
		            "source": "Git Bash",
		            "icon": "terminal-git-bash"
		        }
		    },
		    "terminal.integrated.defaultProfile.windows": "MSYS2 CLANG64"
		}
		```

	- ```shell
		# 方法2：使用vs code的终端
		# 把 CLANG64 的 bin 目录加入当前 PowerShell 环境 PATH
		$env:PATH = "E:\ruanJian\msys\clang64\bin;$env:PATH"
		# 然后就可以直接运行
		```

	- 使用

		- ```c
			// 后续的gcc命令换成了clang g++换成了clang++
			// -fsanitize=address 开启ASAN内存泄漏检测 -g 开启调式
			// 如果有内存泄漏，会出现提示，没有则正常输出
			// 例如：
			#include <stdio.h>
			#include <stdlib.h>
			
			int main() {
			    int *p = malloc(4);   // 只申请 4 字节
			    p[100] = 123;        // 故意越界访问！！！
			
			    printf("%p\n", p);
			    printf("%p\n", p);
			    printf("%p\n", p);
			
			    free(p);
			    return 0;
			}
			
			// 现象
			/*
			tanjun@SiGuYuan CLANG64 /e/project/cProject
			$ clang -g -fsanitize=address -o tt tt.c
			
			tanjun@SiGuYuan CLANG64 /e/project/cProject
			$ ./tt.exe
			=================================================================
			==14868==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x125235ca01c0 at pc 0x7ff7ddc11490 bp 0x00c8c92ffb10 sp 0x00c8c92ffb58
			WRITE of size 4 at 0x125235ca01c0 thread T0
			    #0 0x7ff7ddc1148f in main E:/project/cProject/tt.c:6:12
			    #1 0x7ff7ddc110fd in __tmainCRTStartup D:/W/B/src/mingw-w64/mingw-w64-crt/crt/crtexe.c:260:11
			    #2 0x7ff7ddc113e5 in .l_start D:/W/B/src/mingw-w64/mingw-w64-crt/crt/crtexe.c:129:9
			    #3 0x7ffef2b3e8d6  (C:\WINDOWS\System32\KERNEL32.DLL+0x18002e8d6)
			    #4 0x7ffef37cc40b  (C:\WINDOWS\SYSTEM32\ntdll.dll+0x18008c40b)
			
			0x125235ca01c0 is located 396 bytes after 4-byte region [0x125235ca0030,0x125235ca0034)
			allocated by thread T0 here:
			    #0 0x7ffe223ab7c1 in malloc (E:\ruanJian\msys\clang64\bin\libclang_rt.asan_dynamic-x86_64.dll+0x18004b7c1)
			    #1 0x7ff7ddc1144d in main E:/project/cProject/tt.c:5:14
			    #2 0x7ff7ddc110fd in __tmainCRTStartup D:/W/B/src/mingw-w64/mingw-w64-crt/crt/crtexe.c:260:11
			    #3 0x7ff7ddc113e5 in .l_start D:/W/B/src/mingw-w64/mingw-w64-crt/crt/crtexe.c:129:9
			    #4 0x7ffef2b3e8d6  (C:\WINDOWS\System32\KERNEL32.DLL+0x18002e8d6)
			    #5 0x7ffef37cc40b  (C:\WINDOWS\SYSTEM32\ntdll.dll+0x18008c40b)
			
			SUMMARY: AddressSanitizer: heap-buffer-overflow E:/project/cProject/tt.c:6:12 in main
			Shadow bytes around the buggy address:
			  0x125235c9ff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
			  0x125235c9ff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
			  0x125235ca0000: fa fa 00 00 fa fa 04 fa fa fa fa fa fa fa fa fa
			  0x125235ca0080: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
			  0x125235ca0100: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
			=>0x125235ca0180: fa fa fa fa fa fa fa fa[fa]fa fa fa fa fa fa fa
			  0x125235ca0200: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
			  0x125235ca0280: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
			  0x125235ca0300: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
			  0x125235ca0380: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
			  0x125235ca0400: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
			Shadow byte legend (one shadow byte represents 8 application bytes):
			  Addressable:           00
			  Partially addressable: 01 02 03 04 05 06 07
			  Heap left redzone:       fa
			  Freed heap region:       fd
			  Stack left redzone:      f1
			  Stack mid redzone:       f2
			  Stack right redzone:     f3
			  Stack after return:      f5
			  Stack use after scope:   f8
			  Global redzone:          f9
			  Global init order:       f6
			  Poisoned by user:        f7
			  Container overflow:      fc
			  Array cookie:            ac
			  Intra object redzone:    bb
			  ASan internal:           fe
			  Left alloca redzone:     ca
			  Right alloca redzone:    cb
			==14868==ABORTING
			*/
			```

		- 