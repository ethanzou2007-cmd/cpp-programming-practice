# C++ Programming Practice

6 个独立的 C++ 控制台练习，涵盖输入输出、条件分支、switch 和位运算。每个源文件都有自己的 `main()`，需要分别编译。

## 程序列表

| 文件 | 功能 | 输入 |
| --- | --- | --- |
| `bmi_calculator.cpp` | 计算 BMI，保留两位小数 | 体重 kg、身高 m，均为正数 |
| `plant_water.cpp` | 根据湿度和浇水间隔给出建议 | 湿度 0–100、非负天数 |
| `music_selector.cpp` | 根据天气、心情和时段推荐音乐 | 心情 1–5；时段 M/A/E；天气 S/R |
| `vending.cpp` | 选择饮料、判断金额并计算找零 | 非负金额（分）；商品 A/B/C |
| `energy_saver.cpp` | 按房间占用状态决定设备动作 | 状态值 0–15 |
| `street_light_controller.cpp` | 单灯开关、切换和批量控制 | 菜单 1–6；灯号 0–7；十进制掩码 0–255 |

## 编译与运行

建议使用支持 C++17 的编译器，例如 GCC、Clang 或 Visual Studio。以 Music Selector 为例：

```sh
g++ -std=c++17 -Wall -Wextra music_selector.cpp -o music_selector
./music_selector
```

Windows PowerShell 下可编译为 `music_selector.exe`，然后执行 `./music_selector.exe`。

在 Visual Studio 的开发者命令提示符中：

```bat
cl /std:c++17 /EHsc /W4 music_selector.cpp /Fe:music_selector.exe
music_selector.exe
```

其他程序只需替换文件名。不要把 6 个文件链接成同一个可执行程序。

## Music Selector 规则

按照课程讲义 *C++ Programming Practice M1S2 Conditional Branching and Selection Mechanisms* 的 PDF 第 22–27 页核对；参考资料仅用于核对，不随仓库上传。

先验证输入，再优先判断雨天。字符输入使用大写。

| 天气 | 心情 | 时段 | 推荐 |
| --- | --- | --- | --- |
| R | 任意有效心情 | 任意有效时段 | Relaxing piano music |
| S | 4–5 | M / A | Upbeat pop music |
| S | 4–5 | E | Smooth jazz |
| S | 1–3 | M / A | Acoustic guitar ballads |
| S | 1–3 | E | Ambient electronic music |

讲义文字提到“六种”，但决策分析和示例代码对应上述五种推荐；这里遵循明确的分支规则。原程序把晴天、心情较好、上午或下午的结果写成 Smooth jazz，现已修正。

示例输入 `4 M S` 应输出 `Recommendation: Upbeat pop music`。

## 其他规则与整理说明

- 浇水建议按“湿度 < 20 → 天数 > 5 → 湿度 >= 80 → 正常”的顺序判断。
- 商品 A/B/C 分别为 Water/Juice/Cola，价格为 150/200/250 分。
- 节能器优先级为厨房 → 浴室 → 客厅 → 卧室，每次只执行首个匹配动作；状态 0 进入待机。
- 路灯状态使用 8 位无符号整数。批量掩码先读入整数并检查范围，再转换，避免被当作字符读取。
- 文件名已去除姓名和学号，统一为小写下划线形式；代码统一为 UTF-8、4 空格缩进，并提供 `.clang-format`。
- 增加输入读取失败检查、BMI 正数及数值范围检查、灯号和掩码范围检查。输入错误时以非零状态退出，避免无效位移或读取失败后的循环。

## 验证

6 个程序已使用 MSVC 按 C++17、`/W4 /WX` 编译通过。113 项运行检查通过，覆盖 Music Selector 全部 30 种有效组合、非法输入、浇水阈值、16 种房间状态、售货金额比较、BMI 和路灯位操作。姓名和学号残留检查通过。
