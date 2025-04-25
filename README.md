# C++ 字符串验证工具

这是一个C++项目，使用正则表达式实现字符串格式验证功能。同时包含了一个简单的Hello World示例程序。

## 项目结构

```
.
├── CMakeLists.txt         # CMake配置文件
├── src/                   # 源代码目录
│   ├── main.cpp           # 主源文件
│   ├── daduanmian.cpp     # 字符串验证功能实现
│   └── xiaoduanmian.cpp   # 简化版字符串验证程序
├── .vscode/               # VS Code配置目录
│   ├── launch.json        # 调试配置
│   └── tasks.json         # 任务配置
└── README.md              # 本文件
```

## 简化版字符串验证程序

项目中包含了一个简化版字符串验证程序，位于`src/xiaoduanmian.cpp`。这个程序使用正则表达式来验证输入的字符串是否符合特定格式。

### 验证规则

1. 前两位是年份（默认为"25"，可由外部传入）
2. 第3位只能是4、5、6、7、9
3. 第4位只能是0、1、2
4. 第9位只能是A、B、C、D、E、F、G

### 使用方法

编译项目后，运行xiaoduanmian可执行文件：

```bash
./xiaoduanmian
```

程序会提示用户输入：
1. 年份（可直接回车使用默认值"25"）
2. 要验证的字符串

然后程序会输出验证结果，告知用户输入的字符串是否符合格式要求。

### 示例

```
字符串格式验证程序
规则：
1. 前两位是年份（默认为"25"，可由外部传入）
2. 第3位只能是4、5、6、7、9
3. 第4位只能是0、1、2
4. 第9位只能是A、B、C、D、E、F、G

请输入年份（直接回车使用默认值"25"）：23
请输入要验证的字符串：2350abcdE123
验证结果：符合格式要求
```

## 功能描述

这个项目实现了三个主要功能：

1. 使用正则表达式验证11位字符串是否符合特定格式
2. 从任意长度的字符串中提取符合特定格式的11位子字符串
3. 从多个字符串片段中找出组合后符合特定格式的11位字符串

### 验证规则

字符串格式规则为：

1. 字符串总长度必须是11位
2. 前两位是年份（可通过参数指定，默认为"25"）
3. 第3位只能是4、5、6、7、9
4. 第4位只能是0、1、2
5. 第9位只能是1、2、3、4、5
6. 第10位只能是0、1、2
7. 第11位无特殊限制

## API参考

### 验证函数

```cpp
/**
 * @brief 使用正则表达式验证11位字符串
 * @param str 需要验证的字符串
 * @param year 指定的年份，默认为"25"
 * @return 如果字符串符合规则返回true，否则返回false
 */
bool validateString(const std::string& str, const std::string& year = "25");
```

#### 使用示例

```cpp
// 使用默认年份"25"验证
std::string testString1 = "25501234102";
bool isValid1 = validateString(testString1);  // 返回 true

// 指定年份"23"验证
std::string testString2 = "23501234102";
bool isValid2 = validateString(testString2, "23");  // 返回 true
```

### 提取函数

```cpp
/**
 * @brief 从输入字符串中提取符合规则的11位子字符串
 * @param input 输入字符串
 * @param year 指定的年份，默认为"25"
 * @return 符合规则的11位子字符串，如果没有符合的子字符串则返回"null"
 */
std::string extractValidString(const std::string& input, const std::string& year = "25");
```

#### 使用示例

```cpp
// 从较长字符串中提取符合条件的子串
std::string longString = "725911203401";
std::string result1 = extractValidString(longString, "72");  // 如果不符合规则，返回 "null"
std::string result2 = extractValidString(longString, "25");  // 如果不包含以"25"开头的符合条件子串，返回 "null"

// 字符串不足11位时
std::string shortString = "1234567890";
std::string result3 = extractValidString(shortString);  // 返回 "null"
```

### 片段组合函数

```cpp
/**
 * @brief 从多个字符串片段中找出满足正则表达式规则的11位字符串
 * @param fragments 字符串片段数组
 * @param year 指定的年份，默认为"25"
 * @return 符合规则的11位字符串，如果没有符合的字符串则返回"null"
 */
std::string findValidFromFragments(const std::vector<std::string>& fragments, const std::string& year = "25");

/**
 * @brief 简化版的从字符串片段中查找有效字符串函数
 * 此版本不尝试所有排列组合，只考虑片段的线性组合
 * @param fragments 字符串片段数组
 * @param year 指定的年份，默认为"25"
 * @return 符合规则的11位字符串，如果没有符合的字符串则返回"null"
 */
std::string findValidFromFragmentsSimple(const std::vector<std::string>& fragments, const std::string& year = "25");
```

#### 使用示例

```cpp
// 从多个字符串片段中找出符合条件的组合
std::vector<std::string> fragments = {"7", "259112", "03", "401"};

// 简化版函数（只检查按输入顺序组合的字符串）
std::string result1 = findValidFromFragmentsSimple(fragments, "72");

// 完整版函数（尝试所有可能的片段排列组合）
std::string result2 = findValidFromFragments(fragments, "72");
```

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
   ./string_validator
   ```

### 使用VS Code

1. 在VS Code中打开项目文件夹
2. 按F5开始调试，或使用终端运行任务来构建项目

## 代码实现细节

### 验证函数实现

正则表达式模式：`^{year}[45679][012].{4}[12345][012].$`

- `^` 表示字符串开始
- `{year}` 是动态替换的年份参数（默认为"25"）
- `[45679]` 表示第3位只能是4、5、6、7或9
- `[012]` 表示第4位只能是0、1或2
- `.{4}` 表示第5-8位可以是任意字符
- `[12345]` 表示第9位只能是1、2、3、4或5
- `[012]` 表示第10位只能是0、1或2
- `.` 表示第11位可以是任意字符
- `$` 表示字符串结束

### 提取函数实现

提取函数处理逻辑：

1. 如果输入字符串长度小于11位，返回"null"
2. 如果输入字符串长度等于11位，使用validateString函数验证，符合则返回原字符串，否则返回"null"
3. 如果输入字符串长度大于11位，尝试提取符合条件的11位子串：
   - 遍历所有可能的11位子串（使用滑动窗口方法）
   - 检查子串的前两位是否匹配指定的年份
   - 对匹配年份的子串使用validateString函数进行完整验证
   - 如果找到符合条件的子串，返回该子串
   - 如果遍历完所有可能的子串都不符合条件，返回"null"

### 片段组合函数实现

片段组合函数有两个版本：

1. **简化版（findValidFromFragmentsSimple）**
   - 按照输入顺序将所有片段合并成一个字符串
   - 使用extractValidString函数从合并后的字符串中提取符合条件的子串
   - 如果找到符合条件的子串，返回该子串，否则返回"null"

2. **完整版（findValidFromFragments）**
   - 先尝试简化版的方法
   - 如果简化版未找到符合条件的子串，则尝试所有可能的片段排列组合
   - 对每种排列组合生成的字符串，使用extractValidString函数提取符合条件的子串
   - 如果找到符合条件的子串，返回该子串
   - 如果尝试所有组合后仍未找到符合条件的子串，返回"null"

## 扩展与优化

1. 如需修改验证规则，只需更改`validateString`和`extractValidString`函数中的正则表达式模式
2. 如需支持更多自定义参数，可以扩展函数参数列表
3. 可以添加批量处理功能，支持从文件读取多个字符串进行验证或提取
4. 可以优化片段组合函数，减少不必要的排列组合尝试 