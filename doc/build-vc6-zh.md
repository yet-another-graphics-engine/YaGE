# 使用 Visual C++ 6.0 编译 YaGE

**注意**：目前 YaGE 对 Visual C++ 6.0 的支持是**试验性**的。

请尽量**不要**使用连 C99 标准都不支持的 Visual C++ 6。

使用全新的 Visual Studio 2015，享受更舒服的**补全，多标签，有行号**的舒适编辑体验。

## 准备环境

- Visual C++ 6.0 with SP6
- [Windows Media Player 9 SDK](https://www.microsoft.com/en-us/download/details.aspx?id=25243)

## 修改 YaGE 源代码

### `include/yage.h`  

- 去掉所有 C/C++ 注释 (`/* ... */` `// ...`)
- 将文件转为 ANSI 编码（即去掉 UTF-8 BOM）
- 删除 `#define main(...)` 宏

## 生成 Visual C++ 6 工程文件

```
md build-vc6
cd build-vc6
cmake .. -G "Visual Studio 6"
```

## 修改工程文件

打开 `YaGE.dsw` 工程文件，选择菜单 `工程(P) - 设置(O)`（或按 Alt + F7 快捷键）。

点击左边的 `yage`，在右边点击 `C/C++` 选项卡，将 `工程选项(O)` 中最后的 `-Wall -mms-bitfields` 修改为 `/W3 /GX`。

## 编译

选择菜单 `组建(B) - 组建` （或按 F7 快捷键）即可编译生成 `yage.lib` 文件。

## 测试

在 Visual C++ 6.0 环境下不支持生成目标 `yagetest.exe`，即不支持进行测试。