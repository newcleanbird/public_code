// 模板
#include<iostream>
#include<vector>
#include<array>
using namespace std;

int main(){
    vector<int> vi;
    vector<double> vd(5); // 一个名为vd的对象,可以存储5个double。长度可以为变量。
    
    array<int,5> ai; // 创建一个名为ai，可以存储5个int的对象 特点：长度固定、使用栈。
    array<double,5> ad= {1.2,2.1,3.43,4.3,5.9}; // 大小不能是变量，相当于静态数组
    ad.at(1) = 2.44; // .at()检查是否越界，但效率降低。
    
    system("pause");
    return 0;
}
