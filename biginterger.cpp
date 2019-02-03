#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
// 大数高精度运算
struct BigInteger
{
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;
    BigInteger(long long num = 0)
    {
        *this = num;
    }
    BigInteger operator=(long long num)
    {
        s.clear();
        do
        {
            // num的后八位
            s.push_back(num % BASE);
            // 把num的后八位删除
            num /= BASE;
        } while (num > 0);
        // 返回对象本身
        return *this;
    }
    BigInteger operator=(const string &str) // 传引用避免不必要的复制
    {
        s.clear();
        int x;
        // 若有32位，分成(32-1)/8+1=4块；
        // 若有31位，分成(31-1)/8+1=4块；
        // 若有33位，分成(33-1)/8+1=5块，所有情况通吃，好技巧。
        // 共有几块
        int len = (str.length() - 1) / WIDTH + 1; // 分块技巧
        for (int i = 0; i < len; i++)
        {
            // 由start 和 end 取每八位
            int end = str.length() - i * WIDTH; // 分块技巧
            int start = max(0, end - WIDTH);
            // substr()获得字符串s中 从第 位开始的长度为  的字符串
            // 默认时的长度为从开始位置到尾
            // c_str() 以 char* 形式传回 string 内含字符串
            // 如果一个函数要求char*参数，可以使用c_str()方法：
            // string s = "Hello World!";
            // printf("%s", s.c_str()); //输出 "Hello World!"c_str() 以 char* 形式传回 string 内含字符串
            // sscanf()从一个c字符串中读进与指定格式相符的数据.
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return *this;
    }
    BigInteger operator+(const BigInteger &b) const
    {
        // 新声明一个实例用来存结果
        BigInteger result;
        result.s.clear();
        for (int i = 0, g = 0;; i++)
        {
            if (g == 0 && i >= s.size() && i >= b.s.size())
                break;
            int x = g;
            // x = a.s[i]
            if (i < s.size())
                x += s[i];
            // x = a.s[i] + b.s[i]
            if (i < b.s.size())
                x += b.s[i];
            result.s.push_back(x % BASE);
            g = x / BASE;
        }
        return result;
    }
    BigInteger operator+=(const BigInteger &b)
    {
        *this = *this + b;
        return *this;
    }
ostream &operator<<(ostream &out, const BigInteger &x)
{
    // 跳过可能不足八位的那个
    out << x.s.back();
    for (int i = x.s.size() - 2; i >= 0; i--)
    {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]);
        for (int j = 0; j < strlen(buf); j++)
        {
            out << buf[j];
        }
    }
    return out;
}
istream &operator>>(istream &in, BigInteger &x)
{
    string s;
    if (!(in >> s))
    {
        return in;
    }
    x = s;
    return in;
}
int main()
{
    BigInteger a, b;
    a = "10000000000000000000000000000000000000000";
    cin >> b;
    // a += b;
    // cout << a << endl;
    cout << a << endl;
    system("pause");
    return 0;
}
