#include <iostream>
#include <folly/dynamic.h>
#include <folly/json.h>

// 实际使用的不需要保存动态类型，多创建几个变量就行，至于转 json，完全可以被 nlohmann/json 代替
int main() {
    // 创建各种类型的dynamic对象
    folly::dynamic nullValue = nullptr;
    folly::dynamic boolValue = true;
    folly::dynamic intValue = 123;
    folly::dynamic doubleValue = 3.14;
    folly::dynamic stringValue = "Hello, Folly!";

    // 创建数组
    folly::dynamic array = folly::dynamic::array;
    array.push_back(1);
    array.push_back("two");
    array.push_back(3.0);
    array.push_back(true);

    // 创建对象（类似于Map或Dictionary）
    folly::dynamic object = folly::dynamic::object;
    object["name"] = "Folly";
    object["version"] = 2.0;
    object["features"] = folly::dynamic::array("dynamic", "futures", "concurrency");
    object["isAwesome"] = true;

    // 打印对象
    std::cout << "原始对象: " << folly::toJson(object) << std::endl;

    // 访问对象属性
    std::cout << "名称: " << object["name"].asString() << std::endl;
    std::cout << "版本: " << object["version"].asDouble() << std::endl;
    
    // 修改对象
    object["version"] = 2.1;
    object["newFeature"] = "memory";
    
    // 遍历数组
    std::cout << "特性: ";
    for (const auto& feature : object["features"]) {
        std::cout << feature.asString() << " ";
    }
    std::cout << std::endl;

    // 检查键是否存在
    if (object.count("isAwesome")) {
        std::cout << "Folly是否很棒? " << (object["isAwesome"].asBool() ? "是!" : "否") << std::endl;
    }

    // 转换成JSON字符串
    std::string jsonStr = folly::toJson(object);
    std::cout << "JSON字符串: " << jsonStr << std::endl;

    // 从JSON字符串解析
    folly::dynamic parsedObj = folly::parseJson(jsonStr);
    std::cout << "解析后的对象: " << folly::toPrettyJson(parsedObj) << std::endl;

    // 动态类型检查
    std::cout << "'name'的类型是: ";
    switch (parsedObj["name"].type()) {
        case folly::dynamic::Type::NULLT: std::cout << "null"; break;
        case folly::dynamic::Type::ARRAY: std::cout << "array"; break;
        case folly::dynamic::Type::BOOL: std::cout << "bool"; break;
        case folly::dynamic::Type::DOUBLE: std::cout << "double"; break;
        case folly::dynamic::Type::INT64: std::cout << "int64"; break;
        case folly::dynamic::Type::OBJECT: std::cout << "object"; break;
        case folly::dynamic::Type::STRING: std::cout << "string"; break;
    }
    std::cout << std::endl;

    // 错误处理示例
    try {
        // 尝试访问不存在的键
        auto nonExistent = object["nonExistent"];
        std::cout << "这不会打印，因为会抛出异常" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }

    return 0;
}