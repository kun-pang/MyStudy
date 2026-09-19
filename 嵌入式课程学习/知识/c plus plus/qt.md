qt学习的相关技能：QML、QSS、qt串口编程、网络编程、网络游戏、配置文件、画图、OpenCV、OpenGL



Qt是一个跨平台（跨操作系统平台 + 跨硬件平台）的C++图形用户界面应用程序框架

Qt 的跨平台主要是通过 **平台抽象层（Platform Abstraction Layer, QPA）** 和 **源码级跨平台（源代码 + 针对各平台的编译器/SDK 编译）**。

Qt的下载和安装：国内代理安装（中科大）https://mirrors.ustc.edu.cn/ 找到`qtproject`，点击`help`

​	下载下载器，使用命令行打开下载器，同时添加镜像源

`.\qt-unified-windows-x86-online.exe --mirror https://mirrors.ustc.edu.cn/qtproject`



​	注册账户，可以需要装MinGW + MSVC x86的SDK，在build Tools目录下是编译器（如果没有编译器，需要安装），安装编辑工具`Qt Creator`



# QtCreator —— 官方的idea工具

Qt的安装目录说明：

```bash
|-- 6.5.3			# SDK包
  |-- mingw_64		
  |-- msvc2019_64
  |-- sha1s.txt
|-- components.xml
|-- dist
  |-- installer-changelog
|-- Docs		# 帮助手册
  |-- Qt-6.5.3
|-- Examples	# 官方案例
  |-- Qt-6.5.3
|-- InstallationLog.txt
|-- installer.dat
|-- installerResources
  |-- qt.license.thirdparty
  |-- qt.qt6.653
  |-- qt.qt6.653.doc
  |-- qt.qt6.653.examples
  |-- qt.qt6.653.win64_mingw
  |-- qt.qt6.653.win64_msvc2019_64
  |-- qt.tools.maintenance
  |-- qt.tools.qtcreator
  |-- qt.tools.qtcreator_gui
  |-- qt.tools.qtcreator_gui.telemetry
  |-- qt.tools.vcredist_msvc2019_x86
  |-- qt.tools.vcredist_msvc2022_x64
  |-- qt.tools.win64_mingw900
|-- licenseInfo.txt
|-- Licenses
  |-- LICENSE
  |-- LICENSE.FDL
|-- MaintenanceTool.dat
|-- MaintenanceTool.exe			# Qt的维护工具 —— 卸载、添加组件
|-- MaintenanceTool.ini
|-- network.xml
|-- Tools		# qt编译好的工具
  |-- mingw1120_64 # c++编译器
  |-- QtCreator	# Qt的编辑器
  |-- sdktool
|-- vcredist
  |-- vc14.50.35719_VC_redist.x64.exe
  |-- vc14.50.35719_VC_redist.x86.exe
```



使用自己的编译器方式：【编辑 -> 偏好设置（Preferences） /  主页面的首选项】-> 构建套件





## 程序构建

Getting Started Programming with Qt Widgets （入门的官方项目）

| **选项名称**                      | **主要技术 / 语言** | **是否包含图形界面 (GUI)** | **核心特点与功能说明**                                       | **适用场景**                                                 |
| --------------------------------- | ------------------- | -------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **Qt Widgets Application**        | C++ / Qt Widgets    | **是**（传统窗口控件）     | 基于传统的 `QWidget` 框架，使用 C++ 进行界面与逻辑开发。提供丰富的原生控件（如按钮、文本框、表格等），开发速度快，适合传统桌面软件。 | 传统的桌面端上位机、工具软件、办公软件、桌面管理系统。       |
| **Qt Console Application**        | C++ / Qt Core       | **否**（纯命令行程序）     | 包含基本 `main.cpp` 的命令行程序，不带任何 GUI 界面。但可以使用 Qt 的非图形核心模块（如 `QCoreApplication`、事件循环、信号与槽、网络通信 `QNetworkAccessManager` 等）。 | 后台服务程序、命令行工具、网络抓取脚本、算法验证或学习 Qt 纯逻辑功能。 |
| **Qt Quick Application**          | C++ + QML / Quick   | **是**（现代化流畅 UI）    | 基于 `QML`（声明式语言）和 `Qt Quick` 渲染引擎。支持高级动画、GPU 加速、炫酷特效，非常适合跨平台和移动端开发，界面与 C++ 业务逻辑天然分离。 | 移动端 App（Android/iOS）、嵌入式设备 UI（如车载屏、智能家居屏）、现代化炫酷桌面软件。 |
| **Qt Quick Application (compat)** | C++ + QML (兼容版)  | **是**（针对旧版兼容）     | `compat` 即 **compatibility（兼容性）**。用于在较新版本的 Qt Creator 中创建向下兼容旧版 Qt（如 Qt 5 或早期的 Qt Quick 语法/构建配置）的项目结构。 | 需要兼容旧版本 Qt 库或需要移植旧版 QML 代码的项目。          |

创建项目流程：文件 -> new project -> Application -> Qt Widgets Application ->设置项目路径，勾选设置项目默认路径 -> 构建系统选择，工程管理器（前期选择qmake，后期以及工作选择Cmake） ->  选择语言 -> 构建套件选择，选择编译器和build目录路径 -> 汇总，是否添加git 。

​	`.user`文件，可以删除，是当前机器的信息。

​	`.pro`文件，qmake的管理文件

qmake配置文件（现在不常用）：

| **配置选项**      | **核心作用**                                        | **常见可选值 / 赋值语法**                                    | **语法示例**                                | **说明与适用场景**                                           |
| ----------------- | --------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------- | ------------------------------------------------------------ |
| **`QT`**          | 指定项目需要引用的 Qt 官方模块                      | `core`, `gui`, `widgets`, `network`, `sql`, `serialport` 等  | `QT += widgets network`                     | 默认包含 `core` 和 `gui`。若开发桌面界面程序需添加 `widgets`；若使用网络模块需添加 `network`。 |
| **`TARGET`**      | 指定最终生成的编译产物名称（可执行程序或库）        | 自定义字符串                                                 | `TARGET = my_app`                           | 编译后在 Windows 下会生成 `my_app.exe`，Linux 下生成 `my_app`。若未设置，默认使用 `.pro` 文件同名。 |
| **`TEMPLATE`**    | 指定项目的生成模板（项目类型）                      | `app`（应用程序，默认） `lib`（动态库/静态库） `subdirs`（多工程管理） | `TEMPLATE = app`                            | 决定构建结果是生成可执行文件，还是 `.so`/`.dll` 动态库，或是用作多子工程的管理总目录。 |
| **`CONFIG`**      | 指定项目编译和链接的全局配置参数                    | `debug`, `release`, `c++11`, `c++17`, `plugin`, `console` 等 | `CONFIG += c++17 debug`                     | 用于控制 C++ 语言标准、构建类型（Debug/Release），或启用控制台打印支持（如 `CONFIG += console`）。 |
| **`SOURCES`**     | 指定参与编译的 C/C++ 源文件列表                     | 源码文件名路径                                               | `SOURCES += main.cpp \` `    widget.cpp`    | 包含项目中所有 `.cpp` 或 `.c` 实现文件。多行连接可使用反斜杠 `\`。 |
| **`HEADERS`**     | 指定项目引用的头文件列表（触发 moc 预处理）         | 头文件路径                                                   | `HEADERS += widget.h \` `    network_mgr.h` | 声明项目所需的 `.h` 文件。Qt 会自动为其中包含 `Q_OBJECT` 宏的类生成 `moc_xxx.cpp` 代码。 |
| **`FORMS`**       | 指定项目使用的 Qt Designer 界面文件（`.ui`）        | `.ui` 文件路径                                               | `FORMS += mainwindow.ui`                    | `qmake` 会自动调用 `uic` 工具将 `.ui` 文件编译转换为 `ui_mainwindow.h` C++ 头文件。 |
| **`RESOURCES`**   | 指定项目嵌入的 Qt 资源配置文件（`.qrc`）            | `.qrc` 文件路径                                              | `RESOURCES += res.qrc`                      | `qmake` 会自动调用 `rcc` 将图片、样式表等资源打包编译进最终的二进制程序中。 |
| **`INCLUDEPATH`** | 添加头文件搜索路径（等效于 GCC 的 `-I`）            | 目录路径                                                     | `INCLUDEPATH += $$PWD/include`              | 告诉编译器头文件查找的附加目录。`$$PWD` 表示当前 `.pro` 文件所在的物理路径。 |
| **`LIBS`**        | 指定链接外部库文件路径和库名（等效于 `-L` 和 `-l`） | `-L<路径> -l<库名>`                                          | `LIBS += -L$$PWD/libs -lopencv_core`        | 用于链接第三方 `.a` / `.so` / `.lib` 库。`-L` 指定库目录，`-l` 指定剥离前缀/后缀后的库名称。 |
| **`DEFINES`**     | 添加全局 C/C++ 预处理器宏定义（等效于 `-D`）        | 宏定义字符串                                                 | `DEFINES += USE_DRV_V2`                     | 在代码中可通过 `#ifdef USE_DRV_V2` 进行条件编译，常用于区分平台或版本。 |
| **`DESTDIR`**     | 指定编译生成的二进制目标文件的输出目录              | 相对路径或绝对路径                                           | `DESTDIR = $$PWD/bin`                       | 将编译出的 `.exe` 或可执行文件统一输出到指定文件夹，方便项目目录整理。 |


CLI（命令行程序） —— 程序顺序设计，基本都是按照代码顺序先后

GUI（图形行程序） —— 事情分发设计，事件等待-> 事件分发-> 事件处理。Qt提供了这种事件分发框架

​	触发函数：`exec()`

Qt在编译时，可以多进行一次预处理，将ui文件（xml配置文件）转换成.cpp文件

Qt中的官方头文件，一般是大写Q开头



## ui设计器

有些类，是由ui设计器生成。

```c++
// MainWindow等组件/窗口类，有ui配置文件经过 Qt User Interface Compiler生成对应的源文件
/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
```

一般的组件可以通过ui设计器，进行可视化拖拽；也可以手动写

```text
# ui设计界面
		
|					|							 |
|					|		 ui设计可视界面		 |   对象查看器
|		组件		   | ————————————————————----- |-----------
|					|		动作编辑器			 |  熟悉编辑器
|					|							|
```



每个组件都需要一个布局类进行管理，最底层的基类也需要进行布局设计



## Qt简单的代码分析

构建时生成的代码

```c++
// widget.h
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE		// 空的宏 目的是方便人交流，表示被命名空间包含，同时告知编译器，在其他文件有Ui::Widget这个类
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT		// 元对象

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void on_btn_calc_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

```



```c++

#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)		// 列表初始化
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_calc_clicked()
{
    /* 获取输入框的值 */
    double redius = ui->lineEdit_radius->text().toDouble();
    /* 计算 */
    double res = redius * redius * 3.14;
    /* 写回结果文本框 */
    QString s = "结果：%1";
    ui->label_res->setText(s.arg(res));
}


```



```c++
// ui_widget.h  Qt工具根据ui文件自动生成的
/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;		// 自己在ui拖拽的组件
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_radius;
    QVBoxLayout *verticalLayout;
    QLabel *label_res;
    QPushButton *btn_calc;
    QPushButton *btn_exit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(340, 399);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_radius = new QLineEdit(Widget);
        lineEdit_radius->setObjectName("lineEdit_radius");

        horizontalLayout->addWidget(lineEdit_radius);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_res = new QLabel(Widget);
        label_res->setObjectName("label_res");

        verticalLayout->addWidget(label_res);

        btn_calc = new QPushButton(Widget);
        btn_calc->setObjectName("btn_calc");

        verticalLayout->addWidget(btn_calc);

        btn_exit = new QPushButton(Widget);
        btn_exit->setObjectName("btn_exit");

        verticalLayout->addWidget(btn_exit);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Widget);	// 翻译，将显示文本进行初始化
        QObject::connect(btn_exit, &QPushButton::clicked, Widget, qOverload<>(&QWidget::close));	// 信号与槽的连接

        QMetaObject::connectSlotsByName(Widget);	// 元对象的静态方法，会自动将界面上的子控件信号与符合 on_控件名_信号名() 规则的特定槽函数进行绑定。on_<objectName>_<signalName>}(...)
    } // setupUi

    void retranslateUi(QWidget *Widget)	// 显示文本初始化
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\345\234\206\347\232\204\345\215\212\345\276\204", nullptr));
        label_res->setText(QCoreApplication::translate("Widget", "\347\273\223\346\236\234\357\274\232", nullptr));
        btn_calc->setText(QCoreApplication::translate("Widget", "\350\256\241\347\256\227", nullptr));
        btn_exit->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

```



Qt中Ui设计器会自动生成ui_widget.h 和 元对象系统自动生成 moc_widget.h。（ui文件本质就是xml文件）

```txt
[ widget.ui ] --------( uic 工具 )-------> [ ui_widget.h ]  ---┐
                                                               ├─> C++ 编译器 ---> 目标文件 (.obj/.o)
[ widget.h  ] --------( moc 工具 )-------> [ moc_widget.h ] ---┤
  (含 Q_OBJECT)                                                │
                                                               │
[ widget.cpp ] ------------------------------------------------┘
```



## RCC文件

QRC文件是RCC子系统。

QRC文件中包含相关的图片资源文件路径，由RCC解析生成cpp文件（里面包含图片的二进制资源），方便程序移植时能正确找到资源。（.qrc本质是xml文件）

```txt
[ images.qrc ]  ---> ( rcc 工具 ) ---> [ qrc_images.cpp ] ---> ( C++ 编译器 ) ---> 嵌入二进制可执行程序 (.exe)
```

- **`images.qrc`**：一个标准的 XML 文本文件，里面通过相对路径记录了图片、图标、样式表等文件的位置。
- **`rcc` (Resource Compiler)**：Qt 的资源编译器。它会读取 `.qrc` 中记录的资源路径，找到原始图片，把图片的字节流转换成巨大的 C++ `unsigned char` 二进制数组，并生成 `qrc_images.cpp`。
- **编译嵌入**：生成的 `.cpp` 文件被直接打进最终的可执行程序中。



优点：

- **消除外部路径依赖**：使用外部文件时，一旦复制到其他电脑缺少了图片文件夹，或者绝对路径发生变化（如 `C:\images\logo.png`），程序就会死图。使用资源系统后，路径统一采用虚拟的前缀路径（如 `:/images/logo.png` 或 `qrc:/images/logo.png`），在任何机器上运行都能保证精准加载。
- **部署单文件化**：无需随程序附带一大堆零散的图片文件夹，防范资源被用户误删。



使用方式：

- **内置编译（内存加载）**：直接打进 `.exe`。优点是部署方便；缺点是如果图片极大（如几百兆），会导致程序包体变大、启动内存增加。
- **外置动态加载（`.rcc` 文件）**：可以使用 `rcc -binary images.qrc -o assets.rcc` 命令把资源打包成独立的 `.rcc` 二进制文件，然后在 C++ 代码中使用 `QResource::registerResource("assets.rcc")` 在运行时动态挂载。这种方式适合大型游戏或软件的 **DLC/皮肤插件包** 更新。



用法：

- 右键项目 -> 添加新文件 -> Qt -> Qt Resource file -> 填写文件名 -> 选择项目
- 在项目目录中创建一个用于存放资源的目录（是磁盘上的项目目录），在Qt的逻辑项目目录中的.qrc中添加虚拟前缀，然后添加对应的资源



## 信号和槽

![](../../img/new_228_qt%E4%BF%A1%E5%8F%B7%E5%92%8C%E6%A7%BD.png)
