// 函数重载
#include<iostream>
using namespace std;

int main(){
    // 函数特征标--参数列表（参数数目、参数类型、参数的排列顺序）
    void print(const char * str, int width);
    void print(double d, int width);
    void print(long d, int width);
    void print(int d, int width);
    void print(const char * str);
    // （1）函数重载：函数特征标不同
    // 类型引用和类型本真视为同一个特征标
    long  gronk(int n, float m);
    // double gronk(int n, float m); // 无法重载仅按返回类型区分的函数
    // 特征标而不是函数类型使得函数重载

    // （2）重载“引用参数”
    void stove(double & r1);        // r1与可修改的左值参数匹配
    void stove(const double & r2);  // const引用左值参数r2与可修改的左值参数、const左值参数、右值参数匹配
    void stove(double && r3);       // 右值引用参数r3与左值匹配
    // 函数将调用最匹配的版本
    double x = 55.5;
    const double y = 32.0;
    stove(x);       // r1
    stove(y);       // r2
    stove(x+y);     // r3

    /*
    (3)何时使用函数重载
    仅当函数基本上执行相同的任务，但使用不同形式的数据时，才使用函数重载。
    优先考虑使用默认参数，当数据形式不用时再使用函数重载
    */

}
    

