// 默认参数

#include<iostream>
using namespace std;

char * left(const char * str, int n = 1);   // 函数原型指定了默认值，默认值从右向左添加

int main(){
    
}

char * left(const char * str, int n) // 函数定义不需要添加默认值
{
    char * p = new char[n+1];
    return p;
}