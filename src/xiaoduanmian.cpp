/**
 * @file xiaoduanmian.cpp
 * @brief 使用正则表达式验证字符串格式和提取满足条件的子字符串
 * 规则：
 * 1. 前两位是年份（默认为"25"，可由外部传入）
 * 2. 第3位只能是4、5、6、7、9
 * 3. 第4位只能是0、1、2
 * 4. 第9位只能是A、B、C、D、E、F、G
 */

#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

/**
 * @brief 使用正则表达式验证字符串是否符合特定格式
 * @param str 需要验证的字符串
 * @param year 指定的年份，默认为"25"
 * @return 如果字符串符合规则返回true，否则返回false
 */
bool validateString(const std::string &str, const std::string &year = "25") {
  // 检查字符串长度是否为10
  if (str.length() != 10) {
    return false;
  }

  // 构建正则表达式模式
  // 前两位是指定年份，第3位是[45679]，第4位是[012]，第9位是[A-G]
  std::string pattern = "^" + year + "[45679][012]....[A-G].$";

  // 创建正则表达式对象
  std::regex regex_pattern(pattern);

  // 使用正则表达式匹配字符串
  return std::regex_match(str, regex_pattern);
}

/**
 * @brief 从输入字符串中提取符合规则的子字符串
 * @param input 输入字符串
 * @param year 指定的年份，默认为"25"
 * @return 符合规则的子字符串列表，如果没有符合的则返回空列表
 */
std::vector<std::string> extractValidStrings(const std::string &input,
                                             const std::string &year = "25") {
  std::vector<std::string> results;

  // 如果输入字符串长度小于10位，直接返回空列表
  if (input.length() < 10) {
    return results;
  }

  // 构建正则表达式模式，用于搜索符合条件的子串
  std::string pattern = year + "[45679][012]....[A-G].";
  std::regex regex_pattern(pattern);

  // 在输入字符串中搜索所有匹配项
  std::sregex_iterator it(input.begin(), input.end(), regex_pattern);
  std::sregex_iterator end;

  // 将每个匹配项添加到结果列表
  while (it != end) {
    results.push_back(it->str());
    ++it;
  }

  return results;
}

/**
 * @brief 递归函数，生成所有可能的字符串片段组合
 * @param fragments 字符串片段数组
 * @param current 当前组合的字符串
 * @param index 当前处理的片段索引
 * @param results 存储所有组合结果的数组
 */
void generateCombinations(const std::vector<std::string> &fragments,
                          std::string current, size_t index,
                          std::vector<std::string> &results) {
  // 将当前组合添加到结果中
  if (!current.empty()) {
    results.push_back(current);
  }

  // 已经处理完所有片段，返回
  if (index >= fragments.size()) {
    return;
  }

  // 递归生成组合：选择当前片段
  generateCombinations(fragments, current + fragments[index], index + 1,
                       results);

  // 递归生成组合：不选择当前片段
  generateCombinations(fragments, current, index + 1, results);
}

/**
 * @brief 从字符串片段数组中提取满足正则表达式的字符串
 * @param fragments 字符串片段数组
 * @param year 指定的年份，默认为"25"
 * @return 符合规则的字符串列表
 */
std::vector<std::string>
extractFromFragments(const std::vector<std::string> &fragments,
                     const std::string &year = "25") {
  std::vector<std::string> results;

  // 如果没有片段，直接返回空结果
  if (fragments.empty()) {
    return results;
  }

  // 生成所有可能的片段排列
  std::vector<std::string> allPermutations = fragments;
  std::sort(allPermutations.begin(), allPermutations.end());

  std::vector<std::string> validResults;

  // 对每种排列生成所有可能的组合
  do {
    // 生成这个排列的所有组合
    std::vector<std::string> combinations;
    generateCombinations(allPermutations, "", 0, combinations);

    // 检查每个组合是否包含符合要求的子串
    for (const auto &combination : combinations) {
      // 从组合中提取符合要求的子串
      std::vector<std::string> extracted =
          extractValidStrings(combination, year);

      // 将符合要求的子串添加到结果中
      validResults.insert(validResults.end(), extracted.begin(),
                          extracted.end());
    }

  } while (
      std::next_permutation(allPermutations.begin(), allPermutations.end()));

  // 去除重复的结果
  std::sort(validResults.begin(), validResults.end());
  validResults.erase(std::unique(validResults.begin(), validResults.end()),
                     validResults.end());

  return validResults;
}

/**
 * @brief 主函数 - 程序的入口点
 * @return 返回程序执行的状态码，0表示正常退出
 */
int main() {
  // 欢迎信息
  std::cout << "字符串格式验证程序" << std::endl;
  std::cout << "规则：\n"
            << "1. 前两位是年份（可由外部传入）\n"
            << "2. 第3位只能是4、5、6、7、9\n"
            << "3. 第4位只能是0、1、2\n"
            << "4. 第9位只能是A、B、C、D、E、F、G\n"
            << "5. 字符串总长度必须是10位\n"
            << std::endl;

  // 测试字符串
  std::string testString = "225602445DD";

  std::cout << "测试字符串: " << testString << std::endl << std::endl;

  // 使用年份22进行验证
  std::string year1 = "22";
  bool isValid1 = validateString(testString.substr(0, 10), year1);
  std::cout << "年份 " << year1
            << " 验证结果: " << (isValid1 ? "符合格式要求" : "不符合格式要求")
            << std::endl;

  // 使用年份25进行验证
  std::string year2 = "25";
  bool isValid2 = validateString(testString.substr(0, 10), year2);
  std::cout << "年份 " << year2
            << " 验证结果: " << (isValid2 ? "符合格式要求" : "不符合格式要求")
            << std::endl;

  std::cout << "\n提取符合条件的子字符串：" << std::endl;

  // 从较长的字符串中提取符合条件的子串
  std::string longString = "xxx2250ABCDE32256024FGabcdefgh";

  // 使用年份22提取
  std::vector<std::string> extracted1 = extractValidStrings(longString, "22");
  std::cout << "使用年份 " << year1 << " 提取结果：" << std::endl;
  if (extracted1.empty()) {
    std::cout << "  未找到符合条件的子字符串" << std::endl;
  } else {
    for (const auto &str : extracted1) {
      std::cout << "  " << str << std::endl;
    }
  }

  // 使用年份25提取
  std::vector<std::string> extracted2 = extractValidStrings(longString, "25");
  std::cout << "使用年份 " << year2 << " 提取结果：" << std::endl;
  if (extracted2.empty()) {
    std::cout << "  未找到符合条件的子字符串" << std::endl;
  } else {
    for (const auto &str : extracted2) {
      std::cout << "  " << str << std::endl;
    }
  }

  // 从字符串片段数组中提取符合条件的字符串
  std::cout << "\n从字符串片段中提取符合条件的字符串：" << std::endl;
  std::vector<std::string> fragments = {"225602", "445DD"};

  std::cout << "字符串片段: ";
  for (size_t i = 0; i < fragments.size(); ++i) {
    std::cout << "\"" << fragments[i] << "\"";
    if (i < fragments.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;

  // 使用年份22提取
  std::vector<std::string> fromFragments1 =
      extractFromFragments(fragments, "22");
  std::cout << "使用年份 " << year1 << " 提取结果：" << std::endl;
  if (fromFragments1.empty()) {
    std::cout << "  未找到符合条件的字符串" << std::endl;
  } else {
    for (const auto &str : fromFragments1) {
      std::cout << "  " << str << std::endl;
    }
  }

  // 使用年份25提取
  std::vector<std::string> fromFragments2 =
      extractFromFragments(fragments, "25");
  std::cout << "使用年份 " << year2 << " 提取结果：" << std::endl;
  if (fromFragments2.empty()) {
    std::cout << "  未找到符合条件的字符串" << std::endl;
  } else {
    for (const auto &str : fromFragments2) {
      std::cout << "  " << str << std::endl;
    }
  }

  return 0;
}
