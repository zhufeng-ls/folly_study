#include "folly/logging/xlog.h"
#include "folly/Conv.h"

using namespace folly;

int main() {
     // To format as text and append to a string, use toAppend.
     fbstring str;
     toAppend(2.5, &str);
     CHECK_EQ(str, "2.5");

     XLOG(INFO) << "str: " << str;
 
     // Multiple arguments are okay, too. Just put the pointer to string at the end.
     toAppend(" is ", 2, " point ", 5, &str);
     CHECK_EQ(str, "2.5 is 2 point 5");

     XLOG(INFO) << "str: " << str;
      
     // You don't need to use fbstring (although it's much faster for conversions and in general).
     std::string stdStr;
     toAppend("Pi is about ", 22.0 / 7, &stdStr);

     XLOG(INFO) << "stdStr: " << stdStr;


     // In general, just use to<TargetType>(sourceValue). It returns its result by value.
     stdStr = to<std::string>("Variadic ", "arguments also accepted.");

     XLOG(INFO) << "stdStr: " << stdStr;

 
     // to<fbstring> is 2.5x faster than to<std::string> for typical workloads.
     str = to<fbstring>("Variadic ", "arguments also accepted.");

     XLOG(INFO) << "str: " << str;
}