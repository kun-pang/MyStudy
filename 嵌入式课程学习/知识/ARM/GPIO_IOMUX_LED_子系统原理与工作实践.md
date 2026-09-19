# GPIO、IOMUX（pinctrl）与 LED 子系统

> 面向 Linux C/C++ / 嵌入式 Linux / 驱动开发学习。  
> 本文重点不只是解释“是什么”，还整理实际工作中最常见的设备树、内核接口、调试方法和开发思路。

---

## 1. 总体认识

在嵌入式 Linux 中，一个最典型的 GPIO 控制 LED 的过程可以理解为：

```text
                         用户空间
                            │
                 ┌──────────┴──────────┐
                 │                     │
             /sys/class/leds       libgpiod/gpiomon
                 │                     │
                 ▼                     ▼
             LED 子系统              GPIO 字符设备
                 │                     │
                 └──────────┬──────────┘
                            │
                            ▼
                      GPIO 子系统
                            │
                            ▼
                    GPIO Controller
                            │
                            ▼
                      SoC GPIO 寄存器
                            │
                            ▼
                         GPIO Pin
                            │
                           LED
```

但在 GPIO 真正工作之前，通常还需要先解决：

```text
                    IOMUX / pinctrl
                           │
                           ▼
                 把物理 Pin 配成 GPIO
                           │
                           ▼
                     GPIO 子系统
                           │
                           ▼
                方向、输入、输出、电平
                           │
                           ▼
                      LED 子系统
```

可以记成一句话：

> **IOMUX 决定 Pin 做什么，GPIO 决定这个 GPIO 怎么工作，LED 子系统决定如何以统一的 LED 设备形式使用它。**

---

# 2. IOMUX / pinctrl 子系统

## 2.1 IOMUX 是什么

SoC 的一个物理引脚往往可以复用成多个功能：

```text
        一个物理 Pin
             │
     ┌───────┼────────┬────────┐
     ▼       ▼        ▼        ▼
    GPIO    UART_TX   SPI_MOSI  PWM
```

例如：

```text
GPIO1_A0
```

可能既可以作为：

```text
GPIO
```

也可以作为：

```text
UART_TX
```

或者：

```text
PWM
```

硬件到底连接到哪个功能，由 SoC 的 pin mux / IOMUX 寄存器决定。

如果软件把某个 Pin 设置成 UART 功能，那么再去把它当普通 GPIO 拉高/拉低，通常就不是你预期的行为。

---

## 2.2 Linux 中为什么叫 pinctrl

Linux 内核通常通过 **pinctrl 子系统**统一管理这部分功能。

可以粗略理解：

```text
SoC 硬件：
    IOMUX / Pin Mux

Linux：
    pinctrl 子系统
         │
         ├── pin configuration
         ├── pin multiplexing
         └── GPIO / 外设功能复用
```

因此在 Linux 驱动开发中，经常会看到：

```text
pinctrl
pinctrl-names
pinctrl-0
pinmux
pinctrl-single
```

不同 SoC 厂商实现不同，但 Linux 上层思想基本一致。

---

# 3. pinctrl 的两个核心概念

## 3.1 pinmux

决定：

> **一个 Pin 被复用成什么功能。**

例如：

```text
PIN_A → GPIO
```

或者：

```text
PIN_A → UART_TX
```

---

## 3.2 pinconf

决定：

> **这个 Pin 的电气/配置属性是什么。**

常见配置包括：

```text
pull-up
pull-down
drive-strength
input-enable
output-enable
slew-rate
open-drain
```

例如：

```text
GPIO 输入按键：

PIN
 ↓
GPIO 功能
 ↓
上拉
 ↓
输入
```

或者：

```text
LED：

PIN
 ↓
GPIO 功能
 ↓
推挽输出
 ↓
默认低电平
```

---

# 4. 设备树中的 pinctrl

实际工作中最常见的用法不是让普通应用程序去配置 IOMUX，而是：

> **通过设备树告诉对应驱动：使用哪组 pinctrl 配置。**

典型结构：

```dts
&pinctrl {
    my_led_pins: my-led-pins {
        pins = "GPIO1_A0";
        function = "gpio";
        bias-pull-up;
        drive-strength = <8>;
    };
};
```

不同平台写法差异非常大。

例如一些 SoC 使用：

```dts
rockchip,pins = <...>;
```

某些平台使用：

```dts
pins = "...";
function = "gpio";
```

某些平台又会采用自己的 pinctrl binding。

所以工作中不能死记某一套 DTS 写法。

最重要的是掌握：

```text
pinctrl 节点
    ↓
定义 Pin
    ↓
定义复用功能
    ↓
定义上下拉/驱动能力等电气属性
    ↓
设备节点引用
```

---

# 5. pinctrl 在驱动中的使用

驱动通常不直接去操作 SoC 的 IOMUX 寄存器，而是通过 pinctrl 框架获取 pinctrl state。

典型代码：

```c
struct pinctrl *p;
struct pinctrl_state *default_state;

p = devm_pinctrl_get(dev);
if (IS_ERR(p))
    return PTR_ERR(p);

default_state = pinctrl_lookup_state(p, PINCTRL_STATE_DEFAULT);
if (IS_ERR(default_state))
    return PTR_ERR(default_state);

ret = pinctrl_select_state(p, default_state);
if (ret)
    return ret;
```

更常见的设备树 + 驱动思路：

```text
DTS
 │
 ├── default state
 ├── sleep state
 └── 其他 state
       │
       ▼
     驱动
       │
       ├── probe()
       │    └── 选择 default
       │
       └── suspend()
            └── 选择 sleep
```

---

# 6. 常见 pinctrl state

最常见：

```text
default
sleep
```

例如：

```dts
pinctrl-names = "default", "sleep";
pinctrl-0 = <&mydev_default>;
pinctrl-1 = <&mydev_sleep>;
```

驱动正常工作：

```text
pinctrl_select_state(dev, default_state);
```

系统休眠：

```text
pinctrl_select_state(dev, sleep_state);
```

---

# 7. GPIO 子系统

## 7.1 GPIO 是什么

GPIO：

```text
General Purpose Input/Output
```

即：

> 通用输入输出。

它最基本的功能就是：

```text
输入：

外部信号
   ↓
 GPIO
   ↓
CPU 读取 0 / 1
```

和：

```text
输出：

CPU
 ↓
GPIO
 ↓
输出 0 / 1
 ↓
外部设备
```

---

# 8. GPIO 的核心能力

一个 GPIO 通常涉及以下几个概念：

```text
方向
 ├── input
 └── output

电平
 ├── low
 └── high

中断
 ├── rising edge
 ├── falling edge
 └── both edge

电气属性
 ├── pull-up
 ├── pull-down
 ├── drive strength
 └── open-drain
```

---

# 9. Linux GPIO 的基本分层

Linux GPIO 大致可以理解为：

```text
GPIO Consumer
   │
   │ 例如 LED / 按键 / 驱动
   ▼
GPIO API
   │
   ▼
gpiolib
   │
   ▼
GPIO Controller Driver
   │
   ▼
SoC GPIO Controller
   │
   ▼
硬件寄存器
```

其中：

```text
gpiolib
```

是 Linux 内核 GPIO 框架的重要组成部分。

---

# 10. GPIO 在现代 Linux 中的推荐接口

Linux GPIO 接口经历过发展。

需要特别注意：

> **旧的 sysfs GPIO 接口现在属于历史接口，新开发一般不应依赖它。**

现代 Linux 用户空间更推荐：

```text
/dev/gpiochipN
```

配合：

```text
libgpiod
```

进行 GPIO 操作。

内核驱动中则推荐使用：

```text
descriptor-based GPIO API
```

也就是：

```text
struct gpio_desc *
```

而不是旧式的整数 GPIO 编号 API。

---

# 11. 内核中常见 GPIO 接口

## 11.1 devm_gpiod_get()

设备驱动中非常常见：

```c
struct gpio_desc *gpio;

gpio = devm_gpiod_get(dev, "led", GPIOD_OUT_LOW);
if (IS_ERR(gpio))
    return PTR_ERR(gpio);
```

含义：

```text
led
 ↓
从设备树获取 GPIO
 ↓
申请 GPIO
 ↓
配置成输出
 ↓
初始值 LOW
```

---

## 11.2 devm_gpiod_get_optional()

如果设备上的 GPIO 并不是必须存在，可以：

```c
gpio = devm_gpiod_get_optional(dev, "enable", GPIOD_OUT_LOW);
if (IS_ERR(gpio))
    return PTR_ERR(gpio);
```

---

# 12. GPIO 输出

常见接口：

```c
gpiod_set_value(gpio, 1);
gpiod_set_value(gpio, 0);
```

表示：

```text
输出高电平
输出低电平
```

代码：

```c
gpiod_set_value(gpio, 1);

msleep(100);

gpiod_set_value(gpio, 0);
```

---

## 12.1 带 can sleep 的 GPIO

某些 GPIO 控制器访问 GPIO 时可能睡眠。

这种 GPIO 应使用：

```c
gpiod_set_value_cansleep()
```

例如：

```c
gpiod_set_value_cansleep(gpio, 1);
```

读取：

```c
value = gpiod_get_value_cansleep(gpio);
```

因此工作中经常可以看到：

```c
gpiod_set_value()
```

和：

```c
gpiod_set_value_cansleep()
```

两套接口。

---

# 13. GPIO 输入

获取输入值：

```c
int value;

value = gpiod_get_value(gpio);
```

或者：

```c
value = gpiod_get_value_cansleep(gpio);
```

例如按键：

```text
按键
 ↓
GPIO Input
 ↓
读取电平
 ↓
判断 0 / 1
```

---

# 14. GPIO 方向

如果不在申请阶段直接指定方向，也可以：

```c
gpiod_direction_input(gpio);
```

或者：

```c
gpiod_direction_output(gpio, 0);
```

但实际工作中更推荐在获取 GPIO 时就表达初始方向：

```c
devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
```

这种写法更清晰。

---

# 15. GPIO 中断

GPIO 经常用来接：

```text
按键
传感器中断
触摸中断
设备 ready 信号
```

一个典型流程：

```text
GPIO
 ↓
gpio_to_irq / gpiod_to_irq
 ↓
request_irq
 ↓
中断处理函数
```

例如：

```c
int irq;

irq = gpiod_to_irq(gpio);
if (irq < 0)
    return irq;

ret = devm_request_irq(dev,
                       irq,
                       my_irq_handler,
                       IRQF_TRIGGER_FALLING,
                       "my_gpio_irq",
                       data);
```

---

# 16. GPIO 与设备树

现代驱动经常采用 GPIO descriptor + device tree。

例如：

```dts
leds {
    compatible = "gpio-leds";

    status_led {
        label = "status";
        gpios = <&gpio1 3 GPIO_ACTIVE_LOW>;
        default-state = "off";
    };
};
```

这里：

```text
gpios = <...>
```

告诉驱动：

> 这个 LED 对应哪个 GPIO，以及 GPIO 的有效电平。

---

# 17. GPIO_ACTIVE_HIGH / GPIO_ACTIVE_LOW

这是工作中非常重要的概念。

例如 LED 原理图：

```text
GPIO ---- LED ---- GND
```

那么：

```text
GPIO = 1
```

LED 亮。

这是：

```text
GPIO_ACTIVE_HIGH
```

但如果硬件是：

```text
VCC ---- LED ---- GPIO
```

可能变成：

```text
GPIO = 0
```

LED 亮。

此时：

```text
GPIO_ACTIVE_LOW
```

所以：

> **“GPIO 电平”和“设备逻辑上的开/关”不是一回事。**

这也是为什么设备树中推荐正确描述：

```dts
GPIO_ACTIVE_LOW
```

这样驱动可以按照“逻辑值”工作，而不用到处手工写反逻辑。

---

# 18. LED 子系统

## 18.1 为什么还需要 LED 子系统？

假设不同厂商都有：

```text
status LED
power LED
activity LED
```

如果每个驱动自己定义：

```text
ioctl
/proc
sysfs
```

会非常不统一。

Linux 因此提供统一的：

```text
LED Class
```

用户空间最终可以看到：

```text
/sys/class/leds/
```

例如：

```text
/sys/class/leds/status/
```

---

# 19. LED 子系统的核心思想

应用层不需要关心：

```text
GPIO 是哪个编号
GPIO 控制器是哪一个
寄存器地址是多少
SoC 是什么型号
```

它只需要关心：

```text
LED
```

例如：

```bash
echo 1 > /sys/class/leds/status/brightness
```

或者：

```bash
echo 0 > /sys/class/leds/status/brightness
```

---

# 20. LED 子系统的常见目录

例如：

```text
/sys/class/leds/status/
```

可能包含：

```text
brightness
max_brightness
trigger
```

查看：

```bash
ls /sys/class/leds/status/
```

---

# 21. brightness

最常用：

```bash
cat /sys/class/leds/status/brightness
```

设置：

```bash
echo 1 > /sys/class/leds/status/brightness
```

关闭：

```bash
echo 0 > /sys/class/leds/status/brightness
```

对于普通 GPIO LED：

```text
brightness
   ↓
LED class
   ↓
gpio-leds driver
   ↓
GPIO
   ↓
Pin
   ↓
LED
```

---

# 22. trigger

LED 子系统一个非常实用的功能是：

```text
trigger
```

它允许 LED 根据系统事件自动闪烁。

例如：

```bash
cat /sys/class/leds/status/trigger
```

可能看到：

```text
none timer heartbeat mmc0 ...
```

不同内核、配置和驱动可用 trigger 不同。

例如：

```bash
echo heartbeat > /sys/class/leds/status/trigger
```

LED 可以按照 heartbeat trigger 工作。

---

# 23. 常见 LED trigger 思路

常见用途：

```text
heartbeat
    ↓
系统运行状态

timer
    ↓
定时闪烁

mmc / disk activity
    ↓
存储访问指示

netdev
    ↓
网络状态/网络流量指示
```

实际项目里，如果只是简单控制 GPIO LED，通常：

```text
gpio-leds
```

已经足够。

---

# 24. gpio-leds

Linux 自带非常常见的：

```text
gpio-leds
```

它用于：

> 使用 GPIO 控制普通 LED。

设备树典型形式：

```dts
leds {
    compatible = "gpio-leds";

    led_status: status {
        label = "status";
        gpios = <&gpio1 3 GPIO_ACTIVE_LOW>;
        default-state = "off";
    };
};
```

系统启动后，可能出现：

```text
/sys/class/leds/status/
```

---

# 25. gpio-leds 的启动状态

常见属性：

```dts
default-state = "off";
```

也可能是：

```dts
default-state = "on";
```

某些平台/驱动还支持与保留状态等相关配置，实际使用要查看当前内核对应 binding 文档。

---

# 26. 三个子系统如何协同工作

假设：

```text
LED 接在 GPIO1_A3
```

完整链路可以理解为：

```text
             Device Tree
                  │
        ┌─────────┴─────────┐
        │                   │
     pinctrl            gpio-leds
        │                   │
        ▼                   ▼
   Pin 配成 GPIO        获取 GPIO
        │                   │
        └─────────┬─────────┘
                  ▼
            GPIO 子系统
                  │
                  ▼
          GPIO Controller
                  │
                  ▼
             SoC Register
                  │
                  ▼
                 Pin
                  │
                  ▼
                 LED
```

---

# 27. 实际工作中的完整开发流程

下面是比较重要的部分。

遇到一个：

> “开发板上的 LED 不亮”

实际不要一上来就写驱动。

推荐按下面步骤排查。

---

## 27.1 第一步：看原理图

先确认：

```text
LED 接到了哪个 Pin？
```

例如：

```text
LED0 → GPIO1_A3
```

还需要确认：

```text
LED 是高电平亮还是低电平亮？
```

---

## 27.2 第二步：确认 IOMUX

检查设备树 pinctrl：

```text
GPIO1_A3
```

是否确实配置成：

```text
GPIO
```

而不是：

```text
UART
SPI
PWM
```

---

## 27.3 第三步：确认 GPIO 属性

确认：

```text
input/output
pull-up/pull-down
drive strength
active high/low
```

---

## 27.4 第四步：确认设备树节点

例如：

```dts
leds {
    compatible = "gpio-leds";

    status_led {
        label = "status";
        gpios = <&gpio1 3 GPIO_ACTIVE_LOW>;
        default-state = "off";
    };
};
```

---

## 27.5 第五步：确认驱动是否 probe

查看：

```bash
dmesg | grep -i led
```

或者：

```bash
dmesg | grep -i gpio
```

---

## 27.6 第六步：确认 LED class

查看：

```bash
ls /sys/class/leds/
```

如果看到：

```text
status
```

说明 LED class 设备已经注册。

---

## 27.7 第七步：手动控制

例如：

```bash
echo 1 > /sys/class/leds/status/brightness
```

然后观察 LED。

再：

```bash
echo 0 > /sys/class/leds/status/brightness
```

---

# 28. 用户空间 GPIO：libgpiod

对于现代 Linux 用户空间 GPIO 控制，推荐使用：

```text
libgpiod
```

核心对象：

```text
/dev/gpiochip0
/dev/gpiochip1
...
```

查看：

```bash
gpiodetect
```

查看 GPIO line：

```bash
gpioinfo
```

控制输出：

```bash
gpioset
```

读取输入：

```bash
gpioget
```

监控边沿：

```bash
gpiomon
```

注意：

> `gpioset/gpioget/gpioinfo/gpiodetect` 的具体命令参数会随 libgpiod 版本存在差异，工作中应以目标系统安装的版本帮助信息为准。

例如：

```bash
gpioset --help
gpiodetect --help
gpioinfo --help
```

---

# 29. 为什么不推荐新的项目继续使用旧 sysfs GPIO

旧方式常见：

```text
/sys/class/gpio/
```

例如：

```bash
echo 23 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio23/direction
echo 1 > /sys/class/gpio/gpio23/value
```

这种方式历史上非常常见。

但是现代 Linux GPIO 开发推荐：

```text
内核驱动：
    gpiod API

用户空间：
    /dev/gpiochip*
    libgpiod
```

因此学习旧 sysfs 方法时要知道它是什么，但不要把它作为新项目的主要接口。

---

# 30. GPIO 与字符设备

现代用户空间 GPIO 接口背后的思路可以理解为：

```text
应用程序
    │
    ▼
libgpiod
    │
    ▼
/dev/gpiochipN
    │
    ▼
GPIO character device API
    │
    ▼
内核 gpiolib
    │
    ▼
GPIO Controller
```

这样相比旧 sysfs 模型，更适合：

```text
多个 GPIO
GPIO 配置
事件监听
边沿检测
进程间使用
现代 GPIO 管理
```

---

# 31. GPIO 驱动中推荐的资源管理方式

工作中常见：

```c
devm_gpiod_get()
```

这里的：

```text
devm_
```

代表设备资源管理。

驱动 probe：

```c
gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
```

驱动卸载时：

```text
不需要自己手工释放
```

因为 device-managed resource 会随着设备生命周期自动释放。

---

# 32. GPIO 命名与设备树

这是实际写驱动时特别重要的一点。

例如驱动：

```c
devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
```

那么设备树一般对应：

```dts
reset-gpios = <...>;
```

如果：

```c
devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
```

则一般对应：

```dts
enable-gpios = <...>;
```

所以可以建立：

```text
驱动：

"reset"

        ↓

设备树：

reset-gpios
```

这就是 GPIO descriptor 的典型连接方式。

---

# 33. GPIO 描述符为什么比 GPIO number 更好

旧式代码经常看到：

```c
int gpio;
```

现代接口更多使用：

```c
struct gpio_desc *desc;
```

原因之一是：

```text
GPIO number
```

只是一个全局编号概念，容易让驱动和硬件细节耦合。

而：

```text
gpio_desc
```

更接近：

> “这个设备当前获得的这个 GPIO 资源”。

所以现代驱动一般尽量采用 descriptor API。

---

# 34. GPIO 常见 API 速查

## 获取 GPIO

```c
devm_gpiod_get()
devm_gpiod_get_optional()
gpiod_get()
```

## 输出

```c
gpiod_set_value()
gpiod_set_value_cansleep()
```

## 输入

```c
gpiod_get_value()
gpiod_get_value_cansleep()
```

## 方向

```c
gpiod_direction_input()
gpiod_direction_output()
```

## 中断

```c
gpiod_to_irq()
```

## 释放

如果不是 devm：

```c
gpiod_put()
```

---

# 35. pinctrl 常用接口速查

典型：

```c
devm_pinctrl_get()
pinctrl_lookup_state()
pinctrl_select_state()
pinctrl_put()
```

常见流程：

```c
p = devm_pinctrl_get(dev);

state = pinctrl_lookup_state(
    p,
    PINCTRL_STATE_DEFAULT
);

pinctrl_select_state(
    p,
    state
);
```

---

# 36. LED 驱动开发中的两个方向

Linux LED 相关开发大致可以分为两类。

## 第一类：GPIO LED

例如：

```text
普通状态灯
电源灯
网口灯
指示灯
```

常用：

```text
gpio-leds
```

---

## 第二类：专用 LED 控制器

例如硬件本身就是：

```text
LED Controller
RGB LED Controller
PWM LED Controller
```

这时不一定直接通过 GPIO 控制。

可能是：

```text
LED
 ↓
PWM
 ↓
LED class
```

或者：

```text
LED
 ↓
专用 LED Controller
 ↓
I2C/SPI
 ↓
SoC
```

但上层仍然可以使用 LED class 的统一思想。

---

# 37. GPIO、PWM、LED 不要混为一谈

例如：

```text
普通 GPIO LED
```

只能很好地实现：

```text
亮
灭
```

而：

```text
PWM LED
```

可以进一步控制：

```text
亮度
```

所以：

```text
GPIO
    └── 适合数字开关控制

PWM
    └── 适合占空比控制

LED 子系统
    └── 给用户提供统一 LED 抽象
```

---

# 38. 常见工作场景

## 场景 1：控制状态灯

需求：

```text
系统启动
    ↓
LED 常亮

系统异常
    ↓
LED 快速闪烁

系统正常
    ↓
LED 心跳闪烁
```

实现思路：

```text
gpio-leds
   +
trigger
```

优先考虑是否已经有现成 LED trigger，而不是自己重复实现闪烁线程。

---

# 39. 场景 2：GPIO 控制硬件 Reset

例如：

```text
SoC GPIO
   │
   ▼
RESET_N
   │
   ▼
Camera / Sensor
```

设备树：

```dts
reset-gpios = <&gpio1 5 GPIO_ACTIVE_LOW>;
```

驱动：

```c
reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
if (IS_ERR(reset))
    return PTR_ERR(reset);

gpiod_set_value_cansleep(reset, 0);
msleep(10);
gpiod_set_value_cansleep(reset, 1);
```

这里实际上就是：

```text
GPIO 子系统
```

而不一定需要：

```text
LED 子系统
```

---

# 40. 场景 3：GPIO 控制 Enable

例如：

```text
GPIO
 ↓
EN
 ↓
Sensor Power Enable
```

设备树：

```dts
enable-gpios = <&gpio2 1 GPIO_ACTIVE_HIGH>;
```

驱动：

```c
enable = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
```

启动：

```c
gpiod_set_value_cansleep(enable, 1);
```

---

# 41. 场景 4：GPIO 接按键

硬件：

```text
Button
  │
  ▼
GPIO
```

工作流程：

```text
按下
 ↓
GPIO 电平变化
 ↓
IRQ
 ↓
中断处理
 ↓
input 子系统
 ↓
用户空间
```

注意：

> 如果设备是一个真正的用户输入按键，更常见的完整设计是 GPIO + IRQ + input 子系统，而不是应用程序一直轮询 GPIO。

---

# 42. 场景 5：GPIO 接外部中断设备

例如：

```text
Camera
Sensor
触摸控制器
IMU
```

都可能提供：

```text
INT
```

连接到：

```text
GPIO
```

Linux 中常见：

```text
GPIO Controller
      ↓
IRQ
      ↓
设备驱动
```

然后在中断服务程序中尽量少做工作，把耗时处理放到：

```text
workqueue
threaded IRQ
tasklet（旧代码中较常见）
```

等合适的下半部机制中。

---

# 43. 三个子系统的区别

| 子系统 | 核心问题 | 典型对象 | 常见设备树内容 |
|---|---|---|---|
| IOMUX / pinctrl | Pin 做什么、怎么配置 | pinctrl state | pinctrl-0 / pinctrl-names |
| GPIO | 输入输出、读写、电平、中断 | gpio_desc | xxx-gpios |
| LED | LED 统一抽象、亮度、trigger | LED class device | compatible = "gpio-leds" 等 |

---

# 44. 实际工作中最容易出错的地方

## 44.1 只检查 GPIO，不检查 IOMUX

错误思路：

```text
LED 不亮
↓
怀疑 GPIO 代码
```

实际上可能是：

```text
Pin 仍然复用成 UART
```

所以第一检查：

```text
Pinmux
```

---

## 44.2 忽略 ACTIVE_LOW

例如：

```dts
GPIO_ACTIVE_LOW
```

那么：

```text
逻辑 1
```

不一定意味着：

```text
物理电平 1
```

这是排查 LED、Reset、Enable 时非常常见的问题。

---

## 44.3 用错 GPIO API

例如某个 GPIO 可能睡眠，却在不能睡眠的上下文里使用：

```c
gpiod_set_value_cansleep()
```

要根据 GPIO controller 和执行上下文正确选择接口。

---

## 44.4 直接依赖 GPIO 编号

尽量不要写：

```c
gpio = 123;
```

然后整个驱动都依赖这个数字。

推荐：

```text
设备树提供 GPIO
        ↓
gpiod descriptor
        ↓
驱动使用
```

这样更容易移植。

---

## 44.5 把“LED 框架”和“GPIO”认为是一层东西

实际上：

```text
GPIO
```

是底层硬件控制资源。

而：

```text
LED class
```

是更高层的设备抽象。

可以有：

```text
LED → GPIO
```

也可以有：

```text
LED → PWM
```

甚至：

```text
LED → 专用控制器
```

---

# 45. 调试时推荐的排查顺序

遇到 GPIO/LED 问题，可以按这个顺序：

```text
① 看原理图
      ↓
② 确认 Pin
      ↓
③ 检查 IOMUX / pinctrl
      ↓
④ 检查 GPIO active level
      ↓
⑤ 检查 DTS GPIO 描述
      ↓
⑥ 检查驱动 probe
      ↓
⑦ 检查 /dev/gpiochip*
      ↓
⑧ 检查 /sys/class/leds/
      ↓
⑨ 手动控制
      ↓
⑩ 最后再深入看寄存器
```

---

# 46. 常用调试命令

## LED

```bash
ls /sys/class/leds/
```

```bash
cat /sys/class/leds/status/brightness
```

```bash
cat /sys/class/leds/status/trigger
```

```bash
echo 1 > /sys/class/leds/status/brightness
```

---

## GPIO

现代系统：

```bash
gpiodetect
```

```bash
gpioinfo
```

```bash
gpioget --help
```

```bash
gpioset --help
```

```bash
gpiomon --help
```

---

## 内核日志

```bash
dmesg | grep -i gpio
```

```bash
dmesg | grep -i pinctrl
```

```bash
dmesg | grep -i led
```

也可以：

```bash
dmesg -w
```

一边操作设备，一边观察内核日志。

---

# 47. 设备树调试思路

当怀疑 DTS 配置有问题时，不要只看源码。

可以先确认：

```text
运行中的设备树
```

例如查看：

```bash
ls /sys/firmware/devicetree/base/
```

对应节点：

```bash
ls /sys/firmware/devicetree/base/leds/
```

进一步查看属性：

```bash
cat /sys/firmware/devicetree/base/leds/status-led/compatible
```

具体路径以实际设备树结构为准。

---

# 48. 驱动开发中的推荐模式

假设自己写一个设备驱动，需要：

```text
GPIO reset
GPIO enable
```

推荐：

```dts
mydevice {
    compatible = "vendor,mydevice";

    reset-gpios = <&gpio1 5 GPIO_ACTIVE_LOW>;
    enable-gpios = <&gpio1 6 GPIO_ACTIVE_HIGH>;
};
```

驱动：

```c
struct gpio_desc *reset_gpio;
struct gpio_desc *enable_gpio;

reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
if (IS_ERR(reset_gpio))
    return PTR_ERR(reset_gpio);

enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
if (IS_ERR(enable_gpio))
    return PTR_ERR(enable_gpio);
```

然后：

```c
gpiod_set_value_cansleep(enable_gpio, 1);

gpiod_set_value_cansleep(reset_gpio, 0);
msleep(10);
gpiod_set_value_cansleep(reset_gpio, 1);
```

这个模式非常值得掌握。

---

# 49. 一个完整的 GPIO LED 例子

## 49.1 设备树

假设：

```text
GPIO1_3
```

连接一个低电平点亮 LED：

```dts
leds {
    compatible = "gpio-leds";

    status_led {
        label = "status";
        gpios = <&gpio1 3 GPIO_ACTIVE_LOW>;
        default-state = "off";
    };
};
```

同时 pinctrl 配置：

```dts
&pinctrl {
    led_pins: led-pins {
        /*
         * 下面是示例写法。
         * 不同 SoC 的具体 binding 不同。
         */
    };
};
```

---

## 49.2 Linux 启动后

检查：

```bash
ls /sys/class/leds/
```

可能出现：

```text
status
```

---

## 49.3 打开 LED

```bash
echo 1 > /sys/class/leds/status/brightness
```

这里的：

```text
1
```

是 LED 的**逻辑亮度值**。

即使硬件是：

```text
ACTIVE_LOW
```

LED 子系统/驱动仍然负责把逻辑状态转换成正确的物理 GPIO 电平。

---

# 50. 从“会用”到“会写驱动”的学习路线

如果你的目标是 Linux C/C++ / 驱动开发，建议按照下面顺序学习：

```text
第一阶段：
GPIO 基础
    ↓
输入 / 输出 / 电平
    ↓
ACTIVE_HIGH / ACTIVE_LOW
```

```text
第二阶段：
设备树
    ↓
xxx-gpios
    ↓
GPIO descriptor
```

```text
第三阶段：
pinctrl
    ↓
pinmux
    ↓
pinconf
    ↓
default / sleep state
```

```text
第四阶段：
LED class
    ↓
gpio-leds
    ↓
brightness
    ↓
trigger
```

```text
第五阶段：
GPIO IRQ
    ↓
按键
    ↓
传感器中断
```

```text
第六阶段：
自己写 platform driver
    ↓
probe()
    ↓
devm_gpiod_get()
    ↓
控制 GPIO
    ↓
处理中断
```

---

# 51. 和 Linux C/C++ 岗位技能的对应关系

这个知识点可以直接映射到 Linux 驱动岗位常见技能：

| 技能 | 对应内容 |
|---|---|
| Linux Device Tree | DTS GPIO / pinctrl |
| Linux GPIO | gpiod API |
| Linux pinctrl | pinmux / pinconf |
| Linux IRQ | GPIO 中断 |
| Linux Driver Model | platform_driver / probe |
| Linux LED | LED class / gpio-leds |
| Linux Debug | dmesg / sysfs / debugfs |
| Embedded Linux | SoC + GPIO + pinmux |
| C 语言 | 内核驱动结构体、指针、资源管理 |
| 并发/同步 | 中断、workqueue、threaded IRQ |
| 硬件基础 | 电平、上拉下拉、驱动能力、有效电平 |

---

# 52. 面试时可以这样理解

### Q：GPIO 和 IOMUX 有什么区别？

答：

> IOMUX 主要负责一个物理 Pin 的功能复用，比如配置成 GPIO、UART 或 SPI；GPIO 子系统负责在 Pin 已经作为 GPIO 使用的情况下，对 GPIO 进行输入输出、电平读取、中断等操作。

---

### Q：为什么 GPIO 配好了还是没反应？

常见原因：

```text
1. pinmux 没切到 GPIO
2. GPIO_ACTIVE_LOW 写反
3. 方向配置错误
4. DTS GPIO 写错
5. GPIO 被其他设备占用
6. 电路本身是开漏/上下拉问题
7. LED 硬件连接方式和软件假设不一致
```

---

### Q：LED 子系统和 GPIO 子系统是什么关系？

答：

> GPIO 是一种底层硬件控制资源，LED 子系统是更高层的设备抽象。普通 GPIO LED 可以通过 gpio-leds 驱动把 GPIO 映射成 Linux LED class 设备，从而让用户空间通过统一接口控制。

---

### Q：现代 Linux 用户空间如何控制 GPIO？

答：

> 新项目通常使用 GPIO character device 接口，即 `/dev/gpiochipN`，配合 `libgpiod`，而不是继续依赖旧的 `/sys/class/gpio` sysfs GPIO 接口。

---

# 53. 最后总结

记住下面这个模型，基本就把三个子系统串起来了：

```text
                    ┌──────────────────────┐
                    │       应用程序       │
                    └──────────┬───────────┘
                               │
                         LED / GPIO API
                               │
              ┌────────────────┴────────────────┐
              │                                 │
              ▼                                 ▼
        LED 子系统                         GPIO 字符设备
              │                                 │
              ▼                                 ▼
       gpio-leds / LED Core                 gpiolib
              │                                 │
              └──────────────┬──────────────────┘
                             ▼
                       GPIO Controller
                             │
                             ▼
                           GPIO
                             │
                             ▼
                            Pin
                             ▲
                             │
                      pinctrl / IOMUX
                             │
                    PinMux + PinConfig
```

一句话记忆：

```text
IOMUX：
这个 Pin 用来干什么？

GPIO：
这个 Pin 作为 GPIO 后，输出/输入什么电平？

LED：
把 GPIO/PWM/专用控制器包装成统一的 LED 设备。
```

---

# 54. 实际项目建议

在你自己的 Linux C/C++ 项目中，建议至少做三个小练习：

## 练习 1：GPIO

完成：

```text
GPIO 输出高低电平
GPIO 输入读取
GPIO 中断
```

重点掌握：

```c
devm_gpiod_get()
gpiod_set_value_cansleep()
gpiod_get_value_cansleep()
gpiod_to_irq()
```

---

## 练习 2：LED

使用：

```text
gpio-leds
```

完成：

```text
常亮
常灭
闪烁
heartbeat trigger
```

理解：

```text
LED class
brightness
trigger
```

---

## 练习 3：IOMUX + GPIO

故意设计一个：

```text
GPIO / UART
```

复用冲突实验。

观察：

```text
pinctrl 配置变化
```

如何影响：

```text
GPIO 是否正常工作
```

这样能真正理解：

```text
PinMux
    ↓
GPIO
    ↓
设备驱动
```

之间的关系。

---

# 55. 速查表

| 需求 | 优先关注 |
|---|---|
| Pin 没反应 | IOMUX / pinctrl |
| GPIO 不工作 | GPIO + pinctrl |
| GPIO 高低电平 | gpiod_set_value* |
| 读取 GPIO | gpiod_get_value* |
| GPIO 中断 | gpiod_to_irq + IRQ |
| 普通状态灯 | gpio-leds |
| LED 开关 | brightness |
| LED 自动闪烁 | trigger |
| 用户空间 GPIO | libgpiod |
| 查看 GPIO 控制器 | gpiodetect |
| 查看 GPIO line | gpioinfo |
| 调试内核 | dmesg |
| 调试设备树 | /sys/firmware/devicetree/base |
| 调试运行时 pin | pinctrl/debugfs（视内核配置而定） |

---

## 56. 版本与平台注意事项

Linux 内核、libgpiod 以及不同 SoC 的 pinctrl binding 都可能存在版本差异。

因此实际工作中遵循：

```text
Linux Kernel 文档
        +
目标 SoC 的 Device Tree Binding
        +
目标板子的原理图
        +
当前系统实际暴露的设备节点
```

不要只照抄其他平台的 GPIO 编号、pinctrl DTS 或命令参数。

尤其需要牢记：

```text
“GPIO 编号”
不等于
“物理 Pin 名称”
不等于
“设备树里的 GPIO specifier”
```

它们属于不同层次的概念。
