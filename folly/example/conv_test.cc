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

     // nan to double
     // 表示一个无效的或未定义的数值结果。比如0除以0或者对负数开平方这样的操作会导致NaN。
     str = "nan"; // "NaN", "NAN", etc.
     double d = to<double>(str);
     if (std::isnan(d)) {
       // string was a valid representation of the double value NaN
       XLOG(INFO) << "is nan!";
     }

     // inf to double
     // 代表无穷大，分为正无穷（+Inf）和负无穷（-Inf）。当计算结果超出double能表示的最大值时，比如1.0除以0.0，就会得到正无穷；而-1.0除以0.0得到负无穷。
     str = "inf"; // "Inf", "INF", "infinity", "Infinity", etc.
     d = to<double>(str);
     if (std::isinf(d)) {
       XLOG(INFO) << "is inf!";
     }

     // StringPiece 测试
     fbstring s = " 1234 angels on a pin";
     StringPiece pc(s);
     auto x = to<int>(&pc);
     assert(x == 1234);
     assert(pc == " angels on a pin");

     // fbstring to int

     fbstring s1 = " 1234 angels on a pin";
     auto x1 = to<int>(s1);
     CHECK_EQ(x1, 1234);
     // CHECK_EQ(s1, " 1234 angels on a pin");

     // to<fbstring> is 2.5x faster than to<std::string> for typical workloads.
     str = to<fbstring>("Variadic ", "arguments also accepted.");

     XLOG(INFO) << "str: " << str;
}