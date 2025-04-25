# C++ CMake Hello World 项目

这是一个简单的C++ CMake项目示例，用于演示如何设置和运行一个基本的C++项目。

## 项目结构

```
.
├── CMakeLists.txt         # CMake配置文件
├── src/                   # 源代码目录
│   └── main.cpp           # 主源文件
├── .vscode/               # VS Code配置目录
│   ├── launch.json        # 调试配置
│   └── tasks.json         # 任务配置
└── README.md              # 本文件
```

## 功能描述

这个项目只有一个功能：打印"Hello, World!"到控制台。

## 构建与运行

### 前提条件

- 已安装CMake (推荐3.10或更高版本)
- 已安装C++编译器 (如GCC, Clang或MSVC)
- 如果使用VS Code，建议安装C/C++和CMake Tools扩展

### 使用CMake手动构建

1. 创建build目录：
   ```bash
   mkdir build
   cd build
   ```

2. 配置并构建项目：
   ```bash
   cmake ..
   cmake --build .
   ```

3. 运行可执行文件：
   ```bash
   ./hello_world
   ```

### 使用VS Code

1. 在VS Code中打开项目文件夹
2. 按F5开始调试，或使用终端运行任务来构建项目

## 如何修改

如果要修改输出消息，编辑`src/main.cpp`文件中的字符串内容。 