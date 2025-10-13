# Canneal (Serial Variant)

This directory contains the standalone version of the PARSEC *canneal* kernel. The
build no longer relies on PARSEC-specific configuration files, so you can work
directly with the source in `src/` while still having access to the original
packaged inputs under `inputs/`.

## 构建
```bash
cd pkgs/kernels/canneal/src
make
```

生成的可执行文件位于同一目录下，名称为 `canneal`。

## 运行
`canneal` 需要一个网表（netlist）文本文件作为输入。我们提供了一个最小示例
`src/example.net`，可用于验证程序是否能正确运行：

```bash
./canneal 1 1000 2000 example.net 50
```

参数含义如下：

- `1` —— 线程数，串行版本必须为 1。
- `1000` —— 每个温度步骤尝试的交换次数 (`swaps_per_temp`)，数值越大搜索越充分。
- `2000` —— 初始温度 (`start_temp`)，越高表示接受较差解的概率越大。
- `example.net` —— 网表文件路径。
- `50` —— （可选）温度下降的最大步数；如果省略，程序会一直运行到自适应退出条件满足。

### 使用自定义输入
原 PARSEC 发行版在 `pkgs/kernels/canneal/inputs/` 下提供多个数据集（`*.tar`），例如
`input_test.tar`、`input_simdev.tar`。如果需要更大的测试用例，可直接解压这些归档，
或按照下述格式自行生成网表文件。网表文件格式如下：

```
<逻辑块数量> <max_x> <max_y>
<节点名称> <类型ID> <扇入名称1> <扇入名称2> ... END
...
```

- 第一行给出逻辑块数量以及芯片平面大小（`max_x * max_y` 必须 **严格大于** 逻辑块数量）。
- 随后的每一行描述一个逻辑块：名称、类型编号（当前实现忽略）、若干扇入节点的名称，
  以 `END` 结束。

## 随机数与可复现性
程序内部使用 `Rng`（简化的梅森旋转算法）生成伪随机数，并从固定种子序列初始化，
因此在给定相同输入参数时运行结果是可复现的。

## 相关源码
- `src/main.cpp` —— 命令行解析与程序入口。
- `src/annealer_thread.cpp` —— 核心模拟退火循环，主要的耗时热点。
- `src/netlist.cpp` —— 解析网表并维护元件之间的连接关系。

### 优化 `annealer_thread::Run()` 时的参考文件
`annealer_thread::Run()` 位于 `src/annealer_thread.cpp`，文件顶部已经包含了优化该函数
时常用到的头文件：

- `annealer_thread.h` —— 声明 `annealer_thread` 类、成员变量与 `Run()` 的接口。
- `annealer_types.h` —— 定义 `move_decision_t`、`routing_cost_t` 等枚举和类型别名。
- `location_t.h` —— 提供网表元件位置 (`location_t`) 的数据结构与访问封装。
- `netlist_elem.h` —— 声明 `netlist_elem` 类，包含 `swap_cost`、`present_loc` 等 `Run()` 调用的成员。
- `rng.h` —— 提供 `Rng` 随机数生成器，`Run()` 用它来执行退火中的随机选择。

同一源文件中还实现了 `accept_move`、`calculate_delta_routing_cost` 和 `keep_going` 三个辅助函数：

- `accept_move` 依据 Metropolis 准则决定当前交换是否接受；
- `calculate_delta_routing_cost` 通过 `netlist_elem::swap_cost` 评估交换的成本变化；
- `keep_going` 根据迭代次数或收敛条件判断退火过程是否继续。

调优 `Run()` 时通常需要配合查看这些辅助函数与其头文件定义，便于理解数据结构和状态更新的来龙去脉。

