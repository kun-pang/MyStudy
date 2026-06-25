[TOC]

## [CMake的使用](https://www.runoob.com/cmake/cmake-tutorial.html)

- CMake：项目管理工具。当项目中有很多文件需要编译时，通过CMake进行快速的gcc编译

- CMake的管理文件都叫做`CMakeLists.txt`

- ```cmake
	# ==============================================
	# 一、基础配置（必须写在最前面）
	# ==============================================
	# 指定 CMake 最低版本
	cmake_minimum_required(VERSION 3.20)
	
	# 定义项目名 + 使用语言（CXX=C++）
	project(MyProject CXX)
	
	# 指定 C++ 标准（现代推荐写法）
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)
	
	# ==============================================
	# 二、生成可执行文件
	# ==============================================
	# 语法：add_executable(可执行文件名 源文件...)
	# 等价 g++ a.cpp b.cpp -o 可执行文件
	add_executable(MyExecutable main.cpp other_file.cpp)
	
	# ==============================================
	# 三、生成库文件（静态库 .a / 动态库 .so）
	# ==============================================
	# 1. 生成静态库（STATIC）
	# 等价：g++ -c lib.cpp -> ar rcs libxxx.a
	add_library(MyLibrary STATIC library.cpp)
	
	# 2. 生成动态库（SHARED）
	# 等价：g++ -fPIC -c -> g++ -shared
	# add_library(MyLibrary SHARED library.cpp)
	
	# ==============================================
	# 四、头文件路径（重要）
	# ==============================================
	# 全局添加头文件路径（适合简单项目，复杂项目推荐使用 target_include_directories）
	# 等价：-I./include
	include_directories(${PROJECT_SOURCE_DIR}/include)
	
	# 给指定目标设置头文件路径（更规范、推荐的现代写法）
	target_include_directories(MyLibrary
	    PUBLIC  ${PROJECT_SOURCE_DIR}/public     # 对外公开头文件
	    PRIVATE ${PROJECT_SOURCE_DIR}/private    # 内部私有头文件
	)
	
	# ==============================================
	# 五、链接库（可执行文件 ← 依赖库）
	# ==============================================
	# 等价 g++ ... -L -lMyLibrary
	target_link_libraries(MyExecutable PRIVATE MyLibrary)
	
	# ==============================================
	# 六、自动化编译选项
	# ==============================================
	# 开启调试信息 + 常用警告
	target_compile_options(MyExecutable PRIVATE -Wall -Wextra -g)
	
	# 如果需要开启 Address Sanitizer（内存错误检测）
	# target_compile_options(MyExecutable PRIVATE -fsanitize=address)
	# target_link_options(MyExecutable PRIVATE -fsanitize=address)
	
	# 打印日志（STATUS=普通提示 FATAL_ERROR=报错停止）
	message(STATUS "CMake 配置完成，开始编译...")
	
	# ==============================================
	# 七、多目录工程（子文件夹 CMake）
	# ==============================================
	# 进入 lib 目录，执行里面的 CMakeLists.txt
	# add_subdirectory(lib)
	
	# ==============================================
	# 八、安装规则（make install）
	# ==============================================
	install(TARGETS MyLibrary MyExecutable
	    RUNTIME DESTINATION bin          # 可执行文件安装到 bin
	    LIBRARY DESTINATION lib          # 动态库安装到 lib
	    ARCHIVE DESTINATION lib/static   # 静态库安装到 lib/static
	    INCLUDES DESTINATION include     # 头文件安装到 include
	)
	
	# ==============================================
	# 九、系统判断（跨平台必备）
	# ==============================================
	if(WIN32)
	    message(STATUS "当前系统：Windows")
	elseif(UNIX)
	    message(STATUS "当前系统：Linux / macOS")
	endif()
	
	# ==============================================
	# 十、自动查找第三方库（如 Boost、OpenCV、Qt 等）
	# ==============================================
	# find_package(Boost REQUIRED)
	# target_link_libraries(MyExecutable PRIVATE Boost::boost)
	
	# ==============================================
	# 十一、编译后自动执行命令（复制文件/打印提示）
	# ==============================================
	# add_custom_command(
	#     TARGET MyExecutable
	#     POST_BUILD
	#     COMMAND ${CMAKE_COMMAND} -E copy
	#         ${CMAKE_SOURCE_DIR}/some_file.txt
	#         ${CMAKE_BINARY_DIR}/
	#     COMMENT "复制文件到构建目录"
	#     VERBATIM
	# )
	
	# ==============================================
	# 🚀 编译命令（固定两步，记死！）
	# ==============================================
	# 1. 创建 build 目录（防止源码污染）
	# mkdir build && cd build
	#
	# 2. 生成构建文件
	# cmake ..          # 或者 cmake -G "Ninja" ..
	#
	# 3. 开始编译
	# cmake --build . --config Release
	#    或
	# make -j4
	```
	
- ```cmake
	# 例子
	E:.
	├── CMakeLists.txt          # 顶层
	├── tt.exe
	└── temp/
	    ├── CMakeLists.txt      # 子CMake
	    ├── main.c              # 你的主程序
	    ├── include/            # 头文件公开给外部用
	    │      staticSequentialList.h
	    └── source/             # 源文件
	           staticSequentialList.c
	# CMakeLists.txt 与 tt.exe同级
	# 顶层CMake
	# 声明cmake版本
	cmake_minimum_required(VERSION 3.26)
	
	# 声明项目名称 及 语言
	project(cProject C)
	
	# 说明使用编译器
	set(CMAKE_C_COMPILER clang)
	
	# 编译子CMakeLists.txt文件 ---- 需要添加
	add_subdirectory(temp)
	
	# 声明上级路径变量 ---- 需要更改
	set(MY_PATH "temp")
	
	# 生成可以执行文件
	add_executable(tt ${MY_PATH}/main.c)
	
	# 链接自己的静态库
	target_link_libraries(tt mylib)
	
	# 开启调试信息 以及 地址越界检查 内存泄漏只是退出，越界会有警报
	target_compile_options(tt PRIVATE -fsanitize=address -g -fno-omit-frame-pointer)
	target_link_options(tt PRIVATE -fsanitize=address)
	
	
	# CMakeLists.txt 在tmep/下
	# 子目录 CMake
	# 将要测试的API编写成静态库
	add_library(mylib STATIC
	    source/staticSequentialList.c
	)
	
	# 对外公开mylib这个库
	# ${CMAKE_CURRENT_SOURCE_DIR} = 当前正在解析的 CMakeLists.txt 所在的文件夹路径
	target_include_directories(mylib 
		PUBLIC 
		 ${CMAKE_CURRENT_SOURCE_DIR}/include
	)
	
	# 开启越界检查
	target_compile_options(mylib
	    PUBLIC
	        -fsanitize=address
	        -g
	        -fno-omit-frame-pointer
	)
	
	target_link_options(mylib
	    PUBLIC
	        -fsanitize=address
	)
	
	# 需要下载Ninja  https://github.com/ninja-build/ninja/releases
	# 终端中跳转到当前文件的build目录（创建出来用于存放中间文件的） 使用cmake ..
	# 如果使用clnag的需要 使用 cmake -G Ninja -DCMAKE_MAKE_PROGRAM=E:/ruanJian/ninja/ninja.exe -DCMAKE_C_COMPILER=clang ..构建
	# cmake --build .. 生成可执行文件
	```


## 进阶版

```cmake
# ==============================================
# 一、基础配置（必须写在最前面）
# ==============================================
# 指定 CMake 最低版本（进阶项目推荐使用更高版本）
cmake_minimum_required(VERSION 3.22)

# 定义项目名 + 使用语言 + 版本信息
project(MyProject VERSION 1.0.0 LANGUAGES CXX)

# 指定 C++ 标准（现代推荐写法）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==============================================
# 二、生成可执行文件
# ==============================================
# 语法：add_executable(可执行文件名 源文件...)
# 等价 g++ a.cpp b.cpp -o 可执行文件
add_executable(MyExecutable main.cpp other_file.cpp)

# ==============================================
# 三、生成库文件（静态库 .a / 动态库 .so）
# ==============================================
# 1. 生成静态库（STATIC）
# 等价：g++ -c lib.cpp -> ar rcs libxxx.a
add_library(MyLibrary STATIC library.cpp)

# 2. 生成动态库（SHARED）
# 等价：g++ -fPIC -c -> g++ -shared
# add_library(MyLibrary SHARED library.cpp)

# ==============================================
# 四、头文件路径（重要）
# ==============================================
# 全局添加头文件路径（适合简单项目）
# 等价：-I./include
include_directories(${PROJECT_SOURCE_DIR}/include)

# 给指定目标设置头文件路径（更规范、推荐的现代写法）
target_include_directories(MyLibrary
    PUBLIC  ${PROJECT_SOURCE_DIR}/public      # 对外公开头文件
    PRIVATE ${PROJECT_SOURCE_DIR}/private     # 内部私有头文件
)

# ==============================================
# 五、链接库（可执行文件 ← 依赖库）
# ==============================================
# 等价 g++ ... -L -lMyLibrary
# 使用 PRIVATE / PUBLIC / INTERFACE 是现代最佳实践
target_link_libraries(MyExecutable PRIVATE MyLibrary)

# ==============================================
# 六、自动化编译选项与生成器表达式（进阶）
# ==============================================
# 为特定目标添加编译选项
target_compile_options(MyExecutable PRIVATE
    -Wall -Wextra -Wpedantic
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O3>
)

# 如果需要开启 Address Sanitizer（内存错误检测）
# target_compile_options(MyExecutable PRIVATE -fsanitize=address)
# target_link_options(MyExecutable PRIVATE -fsanitize=address)

# 打印日志（STATUS=普通提示 FATAL_ERROR=报错停止）
message(STATUS "CMake 配置完成，项目版本 ${PROJECT_VERSION} ...")

# ==============================================
# 七、多目录工程（子文件夹 CMake）
# ==============================================
# 进入子目录，执行里面的 CMakeLists.txt
# add_subdirectory(lib)
# add_subdirectory(tests)

# ==============================================
# 八、安装规则（make install / cmake --install .）
# ==============================================
install(TARGETS MyLibrary MyExecutable
    EXPORT MyProjectTargets
    RUNTIME DESTINATION bin                  # 可执行文件安装到 bin
    LIBRARY DESTINATION lib                  # 动态库安装到 lib
    ARCHIVE DESTINATION lib/static           # 静态库安装到 lib/static
    INCLUDES DESTINATION include             # 头文件安装到 include
)

# 导出目标供其他项目使用（进阶）
install(EXPORT MyProjectTargets
    FILE MyProjectTargets.cmake
    NAMESPACE MyProject::
    DESTINATION lib/cmake/MyProject
)

# ==============================================
# 九、系统判断与平台相关配置（跨平台必备）
# ==============================================
if(WIN32)
    message(STATUS "当前系统：Windows")
    # add_definitions(-DWIN32_LEAN_AND_MEAN)
elseif(UNIX)
    message(STATUS "当前系统：Linux / macOS")
    if(APPLE)
        message(STATUS "当前系统：macOS")
    endif()
endif()

# ==============================================
# 十、选项开关（进阶：让用户可配置功能）
# ==============================================
option(BUILD_TESTS "是否构建单元测试" ON)
option(ENABLE_SANITIZER "是否启用 Address Sanitizer" OFF)

if(BUILD_TESTS)
    message(STATUS "单元测试已启用")
    # add_subdirectory(tests)
endif()

# ==============================================
# 十一、自动查找第三方库（Qt、Boost、OpenCV 等）
# ==============================================
# 示例：查找 Qt6（如果你需要 Qt 项目）
# find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
# target_link_libraries(MyExecutable PRIVATE Qt6::Core Qt6::Widgets)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

# find_package(Boost REQUIRED)
# target_link_libraries(MyExecutable PRIVATE Boost::boost)

# ==============================================
# 十二、编译后自动执行命令（进阶）
# ==============================================
# add_custom_command(
#     TARGET MyExecutable
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#         ${CMAKE_SOURCE_DIR}/config.ini
#         ${CMAKE_BINARY_DIR}/
#     COMMENT "复制配置文件到构建目录"
#     VERBATIM
# )

# ==============================================
# 🚀 编译命令（推荐使用 CMakePresets.json 进阶方式）
# ==============================================
# 基础命令：
# mkdir build && cd build
# cmake .. 
# cmake --build . --config Release
#
# 进阶推荐（CMake 3.19+）：
# cmake --preset=debug     # 使用预设配置
# cmake --build --preset=debug
```

## 多层CMake

### 顶层cmake

```cmake
# ==============================================
# 一、基础配置（必须写在最前面）
# ==============================================
cmake_minimum_required(VERSION 3.22)

# 定义项目名称和版本
project(MyProject VERSION 1.2.0 LANGUAGES CXX)

# C++ 标准设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==============================================
# 二、全局选项（建议放在最前面）
# ==============================================
option(BUILD_TESTS "是否构建单元测试" ON)
option(BUILD_EXAMPLES "是否构建示例程序" OFF)
option(BUILD_SHARED_LIBS "是否构建动态库" OFF)

# ==============================================
# 三、主目录可执行文件
# ==============================================
add_executable(MyExecutable main.cpp)

# ==============================================
# 四、多目录结构 —— 使用 add_subdirectory（核心！）
# ==============================================
# 推荐的现代多层 CMake 目录结构：
#
# MyProject/
# ├── CMakeLists.txt                 ← 根 CMakeLists.txt（本文件）
# ├── src/
# │   ├── CMakeLists.txt
# │   └── ...
# ├── lib/
# │   ├── CMakeLists.txt
# │   ├── MyLib/
# │   │   ├── CMakeLists.txt
# │   │   └── ...
# │   └── Utils/
# │       ├── CMakeLists.txt
# │       └── ...
# ├── tests/
# │   └── CMakeLists.txt
# ├── examples/
# │   └── CMakeLists.txt
# └── include/

add_subdirectory(src)
add_subdirectory(lib)
# add_subdirectory(tests)     # 可根据 option 控制是否加入
# add_subdirectory(examples)

# ==============================================
# 五、链接主程序与子目录生成的库
# ==============================================
# 注意：子目录中定义的库名称必须能在这里访问到
target_link_libraries(MyExecutable PRIVATE 
    MyCoreLib
    MyUtils
)

# ==============================================
# 六、头文件路径管理（多目录时推荐写法）
# ==============================================
target_include_directories(MyExecutable PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# ==============================================
# 七、安装规则
# ==============================================
install(TARGETS MyExecutable
    RUNTIME DESTINATION bin
)

# ==============================================
# 八、系统判断
# ==============================================
if(WIN32)
    message(STATUS "当前系统：Windows")
elseif(UNIX)
    message(STATUS "当前系统：Linux / macOS")
    if(APPLE)
        message(STATUS "当前系统：macOS")
    endif()
endif()

message(STATUS "CMake 配置完成，项目版本 ${PROJECT_VERSION}")

# ==============================================
# 🚀 多层 CMake 使用建议与命令
# ==============================================
# 推荐目录结构（大型项目强烈建议这样组织）：
#
# 项目根目录/CMakeLists.txt          ← 只负责统筹
# src/CMakeLists.txt                  ← 放置可执行文件相关
# lib/MyLib/CMakeLists.txt            ← 每个库独立一个文件夹
# tests/CMakeLists.txt
# examples/CMakeLists.txt
```

### 子cmake

```cmake
# src/CMakeLists.txt

add_executable(MyExecutable main.cpp app.cpp)

target_include_directories(MyExecutable PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
)

# 把这个可执行文件“导出”给父目录使用
set_target_properties(MyExecutable 
    PROPERTIES 
        OUTPUT_NAME "myapp"
)
```

```cmake
# lib/MyLib/CMakeLists.txt
add_library(MyCoreLib STATIC 
    src/core.cpp 
    src/helper.cpp
)

target_include_directories(MyCoreLib 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include      # 对外公开
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src          # 内部使用
)

# 如果这个库依赖其他库
target_link_libraries(MyCoreLib PRIVATE MyUtils)
```

```cmake
# lib/Utils/CMakeLists.txt
add_library(MyUtils STATIC utils.cpp)

target_include_directories(MyUtils PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```





