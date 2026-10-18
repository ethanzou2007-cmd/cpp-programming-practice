# C++ Programming Practice

14 个独立的 C++ 控制台练习，涵盖输入输出、条件分支、循环、位运算、数组和基础数据处理。每个源文件都有自己的 `main()`，需要分别编译。

## 程序列表

### 条件分支与交互

| 文件 | 功能 | 输入 |
| --- | --- | --- |
| `bmi_calculator.cpp` | 计算 BMI，保留两位小数 | 体重 kg、身高 m，均为正数 |
| `plant_water.cpp` | 根据湿度和浇水间隔给出建议 | 湿度 0–100、非负天数 |
| `music_selector.cpp` | 根据天气、心情和时段推荐音乐 | 心情 1–5；时段 M/A/E；天气 S/R |
| `vending.cpp` | 选择饮料、判断金额并计算找零 | 非负金额（分）；商品 A/B/C |

### 位运算

| 文件 | 功能 | 输入 |
| --- | --- | --- |
| `energy_saver.cpp` | 按房间占用状态决定设备动作 | 状态值 0–15 |
| `street_light_controller.cpp` | 单灯开关、切换和批量控制 | 菜单 1–6；灯号 0–7；十进制掩码 0–255 |
| `bit_detective.cpp` | 清除最低位的 1，统计二进制 1 的个数并判断 2 的幂 | 正整数，0 结束；负数重试 |

### 循环搜索与累计

| 文件 | 功能 | 输入 |
| --- | --- | --- |
| `goldbach_conjecture_verification.cpp` | 枚举指定偶数的全部不重复素数对 | 大于 2 的偶数；其他整数重试 |
| `hundred_monks_and_hundred_buns.cpp` | 枚举百僧百馒头问题的全部解 | 无；大僧 3 个、中僧 2 个、小僧每 3 人 1 个，允许人数为 0 |
| `supermarket_checkout_system.cpp` | 累计商品数量、总价、均价并判断优惠券 | 非负价格，至少 1 件商品，0 结算；负价重试 |

### 数组与数据处理

| 文件 | 功能 | 输入 |
| --- | --- | --- |
| `one_hot_encoding_generator.cpp` | 生成 5 类独热编码并统计频数 | 内置 12 个类别标签 |
| `quantitative_trading_backtest_engine.cpp` | 计算 MA5 / MA10，输出交叉买卖信号 | 内置 30 天价格 |
| `signal_smoother.cpp` | 三点移动平均平滑，端点保留原值 | 内置 10 个采样值 |
| `temperature_statistics_tool.cpp` | 日均温、极值、冰点以下小时数及逐小时偏差 | 内置 24 小时温度 |

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

其他程序只需替换文件名。不要把这些文件链接成同一个可执行程序。

在 Visual Studio 开发者命令提示符中，可批量编译并运行测试（需要 Python 3.10 或更新版本）：

```bat
mkdir build
for %f in (*.cpp) do cl /nologo /std:c++17 /EHsc /W4 /WX "%f" /Fo:build\%~nf.obj /Fe:build\%~nf.exe
python tests/verify.py build
```

以上为直接输入命令提示符的写法；保存为 `.bat` 时需把 `%f`、`%~nf` 中的 `%` 改为 `%%`。

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

14 个程序已使用 MSVC 按 C++17、`/W4 /WX` 分别编译通过。`tests/verify.py` 的 259 次程序运行检查全部通过，覆盖原有 6 个程序和本次新增 8 个程序。

- 原有回归检查覆盖 Music Selector 全部 30 种有效组合、非法输入、浇水阈值、16 种房间状态、售货金额比较、BMI 和路灯位操作。
- Bit Detective 对照独立位计数结果，包含 1–64、2 的幂、32 位有符号整数上界，以及负数、0、非法字符、小数、超范围整数和 EOF。
- Goldbach 对照独立筛法结果，逐一验证 4–200 的全部偶数及 1000 的所有素数对；检查非法输入、无效整数重试和 EOF。
- 超市结算检查 200 元上下及等于 200 元、多件累计、首次输入 0、负价、空输入、缺少结算符、非法数字及数值溢出。
- 百僧百馒头对照完整枚举；编码检查全部标签和频数；平滑检查全部 10 行；温度检查全部 24 行、统计值及偏差；均线检查全部 30 天及信号统计。

姓名、学号和邮箱残留检查通过。原有 6 个源文件与更新前公开仓库的 Git blob 哈希一致，未覆盖、未删除。

## 本次新增程序的修正与边界

- **Supermarket Checkout System**：优惠券条件由最后一次输入的 `price` 改为 `total > 200.0`，正好 200 元不送券，保持原作业“超过 200”的含义。统一价格读取循环，避免空购物单除零；拒绝负价并重试；非法、缺失、非有限或溢出输入不会继续累计，也不会卡在循环中。仍按原作业使用 `double` 并以两位小数显示。
- **Temperature Statistics Tool**：偏差输出循环由 `i < n - 1` 改为 `i < n`，完整输出 0–23 时，即全部 24 个小时。
- **Goldbach / Bit Detective**：检查输入读取结果，非法数字、小数、夹杂字符和超范围整数以非零状态退出，EOF 正常结束，避免死循环或使用未初始化值。Goldbach 的试除条件改为 `i <= value / i`，避免 `i * i` 的有符号整数溢出。
- **One Hot Encoding Generator**：写入独热数组前检查标签是否在 `[0, 5)`，避免以后修改数据时出现越界。
- **其他新增程序**：统一 UTF-8、小写 snake_case 文件名及 4 空格排版；保留内置数据、算法和原有思考题。

Goldbach 程序只验证输入偶数，不构成对猜想的证明；试除枚举适合课程练习，大输入可能运行较慢。Quantitative Trading Backtest Engine 保留原文件命名含义，但当前作业只计算均线交叉信号，不包含持仓、手续费、成交或收益回测，也不将当日价格信号解释为可当日无延迟成交。
