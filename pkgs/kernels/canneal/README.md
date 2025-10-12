# Canneal (Serial Variant)

This directory contains the standalone version of the PARSEC *canneal* kernel. All
PARSEC-specific configuration files and packaged input archives have been removed so
that you can work directly with the source in `src/`.

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
原 PARSEC 发行版在 `pkgs/kernels/canneal/inputs/` 下提供多个数据集（`*.tar`），本精简
版本已移除这些归档。若需要更大的测试用例，可从官方 PARSEC 3.0 发行包中解压相应
数据集，或按照网表格式自行生成。网表文件格式如下：

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

