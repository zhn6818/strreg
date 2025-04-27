#include <iostream>
#include <regex>
#include <string>
#include <vector>

// 前向声明
void generatePermutations(const std::vector<std::string> &fragments,
                          std::vector<std::vector<std::string>> &result);

/**
 * @brief 使用正则表达式验证11位字符串
 * 规则：
 * - 总长度必须是11位
 * - 前两位是年份（可通过参数指定，默认为"25"）
 * - 第3位只能是4、5、6、7、9
 * - 第4位只能是0、1、2
 * - 第9位只能是1、2、3、4、5
 * - 第10位只能是0、1、2
 *
 * @param str 需要验证的字符串
 * @param year 指定的年份，默认为"25"
 * @return 如果字符串符合规则返回true，否则返回false
 */
bool validateString(const std::string &str, const std::string &year = "25") {
  if (year.length() != 2) {
    std::cerr << "错误：年份必须是两位数字" << std::endl;
    return false;
  }

  // 构建正则表达式
  // ^ 表示开始，$ 表示结束
  // 使用传入的year参数替代前两位
  // [45679] 表示第3位只能是4、5、6、7或9
  // [012] 表示第4位只能是0、1或2
  // .{4} 表示第5-8位可以是任意字符
  // [12345] 表示第9位只能是1、2、3、4或5
  // [012] 表示第10位只能是0、1或2
  // . 表示第11位可以是任意字符
  std::string pattern_str = "^" + year + "[45679][012].{4}[12345][012].$";
  std::regex pattern(pattern_str);

  return std::regex_match(str, pattern);
}

/**
 * @brief 使用正则表达式验证8位字符串
 * 规则：
 * - 总长度必须是8位
 * - 前两位是年份（可通过参数指定，默认为"25"）
 * - 第3位只能是4、5、6、7、9
 * - 第4位只能是0、1、2
 * - 第5-8位可以是任意字符
 *
 * @param str 需要验证的字符串
 * @param year 指定的年份，默认为"25"
 * @return 如果字符串符合规则返回true，否则返回false
 */
bool validateString8(const std::string &str, const std::string &year = "25") {
  if (year.length() != 2) {
    std::cerr << "错误：年份必须是两位数字" << std::endl;
    return false;
  }

  // 如果字符串长度不是8位，直接返回false
  if (str.length() != 8) {
    return false;
  }

  // 构建正则表达式
  // ^ 表示开始，$ 表示结束
  // 使用传入的year参数替代前两位
  // [45679] 表示第3位只能是4、5、6、7或9
  // [012] 表示第4位只能是0、1或2
  // .{4} 表示第5-8位可以是任意字符
  std::string pattern_str = "^" + year + "[45679][012].{4}$";
  std::regex pattern(pattern_str);

  return std::regex_match(str, pattern);
}

/**
 * @brief 从输入字符串中提取符合规则的11位或8位子字符串
 * 优先提取符合11位规则的字符串，如果没有符合11位规则的，则尝试提取符合8位规则的
 *
 * @param input 输入字符串
 * @param year 指定的年份，默认为"25"
 * @return 符合规则的子字符串，如果没有符合的子字符串则返回"null"
 */
std::string extractValidString(const std::string &input,
                               const std::string &year = "25") {
  if (year.length() != 2) {
    std::cerr << "错误：年份必须是两位数字" << std::endl;
    return "null";
  }

  // 首先尝试提取符合11位规则的字符串

  // 如果字符串长度小于11位，尝试8位规则
  if (input.length() < 11) {
    // 如果长度等于8位，则直接验证
    if (input.length() == 8) {
      return validateString8(input, year) ? input : "null";
    }
    // 如果长度大于8位但小于11位，尝试提取8位子串
    else if (input.length() > 8) {
      // 提取所有可能的8位子串并验证
      for (size_t i = 0; i <= input.length() - 8; ++i) {
        std::string substr = input.substr(i, 8);
        if (substr.substr(0, 2) == year && validateString8(substr, year)) {
          return substr;
        }
      }
    }
    // 如果什么都没找到，返回"null"
    return "null";
  }

  // 如果字符串长度等于11位，则直接验证整个字符串
  if (input.length() == 11) {
    if (validateString(input, year)) {
      return input;
    }
    // 如果11位字符串不符合规则，尝试提取8位子串
    for (size_t i = 0; i <= input.length() - 8; ++i) {
      std::string substr = input.substr(i, 8);
      if (substr.substr(0, 2) == year && validateString8(substr, year)) {
        return substr;
      }
    }
    return "null";
  }

  // 如果字符串长度大于11位，则先尝试查找符合11位条件的子串
  // 遍历所有可能的11位子串并验证
  for (size_t i = 0; i <= input.length() - 11; ++i) {
    std::string substr = input.substr(i, 11);
    // 检查子串的前两位是否匹配指定的年份
    if (substr.substr(0, 2) == year) {
      // 验证完整的子串
      if (validateString(substr, year)) {
        return substr;
      }
    }
  }

  // 如果没有找到符合11位规则的子串，尝试查找符合8位规则的子串
  for (size_t i = 0; i <= input.length() - 8; ++i) {
    std::string substr = input.substr(i, 8);
    // 检查子串的前两位是否匹配指定的年份
    if (substr.substr(0, 2) == year) {
      // 验证8位子串
      if (validateString8(substr, year)) {
        return substr;
      }
    }
  }

  return "null";
}

/**
 * @brief 从多个字符串片段中找出满足正则表达式规则的11位或8位字符串
 * 优先查找符合11位规则的字符串，如果没有则尝试查找符合8位规则的字符串
 *
 * @param fragments 字符串片段数组
 * @param year 指定的年份，默认为"25"
 * @return 符合规则的字符串，如果没有符合的字符串则返回"null"
 */
std::string findValidFromFragments(const std::vector<std::string> &fragments,
                                   const std::string &year = "25") {
  if (year.length() != 2) {
    std::cerr << "错误：年份必须是两位数字" << std::endl;
    return "null";
  }

  // 首先将所有片段合并成一个完整字符串
  std::string combined = "";
  for (const auto &fragment : fragments) {
    combined += fragment;
  }

  // 使用extractValidString函数从合并后的字符串中提取有效子串
  std::string result = extractValidString(combined, year);
  if (result != "null") {
    return result;
  }

  // 尝试不同的片段组合顺序
  // 这里使用一个简单的方法：从每个可能的起始片段开始，尝试所有可能的组合
  for (size_t start = 0; start < fragments.size(); ++start) {
    combined = fragments[start];

    // 创建一个临时数组，包含除起始片段外的所有片段
    std::vector<std::string> remainingFragments;
    for (size_t i = 0; i < fragments.size(); ++i) {
      if (i != start) {
        remainingFragments.push_back(fragments[i]);
      }
    }

    // 递归尝试所有可能的排列组合
    std::vector<std::vector<std::string>> permutations;
    generatePermutations(remainingFragments, permutations);

    for (const auto &perm : permutations) {
      std::string testString = combined;
      for (const auto &frag : perm) {
        testString += frag;
      }

      // 检查当前组合是否包含有效字符串
      std::string validResult = extractValidString(testString, year);
      if (validResult != "null") {
        return validResult;
      }
    }
  }

  return "null";
}

/**
 * @brief 生成所有可能的排列组合
 *
 * @param fragments 字符串片段数组
 * @param result 结果数组，包含所有可能的排列组合
 */
void generatePermutations(const std::vector<std::string> &fragments,
                          std::vector<std::vector<std::string>> &result) {
  // 如果只有一个元素，直接返回该元素组成的排列
  if (fragments.size() <= 1) {
    result.push_back(fragments);
    return;
  }

  // 对于每个可能的第一个元素，生成剩余元素的所有排列
  for (size_t i = 0; i < fragments.size(); ++i) {
    // 创建一个不包含当前元素的新片段数组
    std::vector<std::string> remaining;
    for (size_t j = 0; j < fragments.size(); ++j) {
      if (j != i) {
        remaining.push_back(fragments[j]);
      }
    }

    // 递归生成剩余元素的所有排列
    std::vector<std::vector<std::string>> subPermutations;
    generatePermutations(remaining, subPermutations);

    // 将当前元素添加到每个子排列的开头
    for (const auto &perm : subPermutations) {
      std::vector<std::string> newPerm;
      newPerm.push_back(fragments[i]);
      newPerm.insert(newPerm.end(), perm.begin(), perm.end());
      result.push_back(newPerm);
    }
  }
}

/**
 * @brief 简化版的从字符串片段中查找有效字符串函数
 * 此版本不尝试所有排列组合，只考虑片段的线性组合
 * 优先查找符合11位规则的字符串，如果没有则尝试查找符合8位规则的字符串
 *
 * @param fragments 字符串片段数组
 * @param year 指定的年份，默认为"25"
 * @return 符合规则的字符串，如果没有符合的字符串则返回"null"
 */
std::string
findValidFromFragmentsSimple(const std::vector<std::string> &fragments,
                             const std::string &year = "25") {
  if (year.length() != 2) {
    std::cerr << "错误：年份必须是两位数字" << std::endl;
    return "null";
  }

  // 首先将所有片段合并成一个完整字符串
  std::string combined = "";
  for (const auto &fragment : fragments) {
    combined += fragment;
  }

  // 使用extractValidString函数从合并后的字符串中提取有效子串
  return extractValidString(combined, year);
}

/**
 * @brief 主函数 - 测试正则表达式验证方法
 * @return 程序退出状态码
 */
int main() {
  // 测试样例 - 使用默认年份"25"
  std::string valid = "25501234102";    // 有效字符串
  std::string invalid1 = "2550123410";  // 长度不够11位
  std::string invalid2 = "25301234102"; // 第3位是3，不符合规则
  std::string invalid3 = "25531234602"; // 第9位是6，不符合规则

  // 测试样例 - 使用指定年份"23"
  std::string valid2 = "23501234102"; // 有效字符串，但年份是"23"

  // 测试提取函数
  std::string longString = "725911203401"; // 给定样例，12位字符串
  std::string longStringResult1 =
      extractValidString(longString, "72"); // 使用"72"作为年份
  std::string longStringResult2 =
      extractValidString(longString, "25"); // 使用默认"25"作为年份

  // 测试用户提供的示例字符串片段
  std::vector<std::string> fragments = {"7", "259112", "03", "401"};

  // 新增测试用例：8位规则测试
  std::string valid8 = "25501234";   // 有效的8位字符串
  std::string invalid8 = "25301234"; // 第3位是3，不符合8位规则
  std::string mixed = "25702212";    // 测试8位与11位混合场景
  std::vector<std::string> fragments2 = {"257022", "12"}; // 新增片段测试

  std::cout << "验证结果（默认年份\"25\"）：" << std::endl;
  std::cout << valid
            << " 是否有效: " << (validateString(valid) ? "有效" : "无效")
            << std::endl;
  std::cout << invalid1
            << " 是否有效: " << (validateString(invalid1) ? "有效" : "无效")
            << std::endl;
  std::cout << invalid2
            << " 是否有效: " << (validateString(invalid2) ? "有效" : "无效")
            << std::endl;
  std::cout << invalid3
            << " 是否有效: " << (validateString(invalid3) ? "有效" : "无效")
            << std::endl;

  std::cout << "\n验证结果（指定年份\"23\"）：" << std::endl;
  std::cout << valid2
            << " 是否有效: " << (validateString(valid2, "23") ? "有效" : "无效")
            << std::endl;
  std::cout << valid
            << " 是否有效: " << (validateString(valid, "23") ? "有效" : "无效")
            << std::endl;

  std::cout << "\n提取函数测试结果：" << std::endl;
  std::cout << "从 \"" << longString << "\" 中提取(年份\"72\")："
            << longStringResult1 << std::endl;
  std::cout << "从 \"" << longString << "\" 中提取(年份\"25\")："
            << longStringResult2 << std::endl;

  // 测试用户提供的示例字符串
  std::string userString = "725911203401";
  std::cout << "\n用户字符串测试结果：" << std::endl;
  std::cout << "字符串：\"" << userString << "\"" << std::endl;
  std::cout << "提取结果(年份\"72\")：" << extractValidString(userString, "72")
            << std::endl;
  std::cout << "提取结果(年份\"25\")：" << extractValidString(userString, "25")
            << std::endl;

  // 测试片段组合函数
  std::cout << "\n字符串片段测试结果：" << std::endl;
  std::cout << "片段: ";
  for (const auto &frag : fragments) {
    std::cout << "\"" << frag << "\" ";
  }
  std::cout << std::endl;

  // 使用简化版函数（不尝试所有排列组合）
  std::string simpleResult72 = findValidFromFragmentsSimple(fragments, "72");
  std::string simpleResult25 = findValidFromFragmentsSimple(fragments, "25");

  std::cout << "简单组合提取结果(年份\"72\")：" << simpleResult72 << std::endl;
  std::cout << "简单组合提取结果(年份\"25\")：" << simpleResult25 << std::endl;

  // 测试8位规则函数
  std::cout << "\n8位验证结果：" << std::endl;
  std::cout << valid8 << " 是否符合8位规则: "
            << (validateString8(valid8) ? "有效" : "无效") << std::endl;
  std::cout << invalid8 << " 是否符合8位规则: "
            << (validateString8(invalid8) ? "有效" : "无效") << std::endl;

  // 测试混合场景
  std::cout << "\n混合测试场景：" << std::endl;
  std::cout << "字符串：\"" << mixed << "\"" << std::endl;
  std::cout << "提取结果(年份\"25\")：" << extractValidString(mixed, "25")
            << std::endl;

  // 测试新增片段组合
  std::cout << "\n新增片段测试结果：" << std::endl;
  std::cout << "片段: ";
  for (const auto &frag : fragments2) {
    std::cout << "\"" << frag << "\" ";
  }
  std::cout << std::endl;

  std::string fragmentResult = findValidFromFragmentsSimple(fragments2, "25");
  std::cout << "简单组合提取结果(年份\"25\")：" << fragmentResult << std::endl;

  std::string fragmentResultFull = findValidFromFragments(fragments2, "25");
  std::cout << "完整组合提取结果(年份\"25\")：" << fragmentResultFull
            << std::endl;

  return 0;
}