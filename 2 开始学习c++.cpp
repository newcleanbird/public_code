/*
2 开始学习c++
    创建c++程序
    C++程序的一般格式
    #include 编译指令
    main()函数
    使用cout 对象进行输出
    在C++程序中加入注释
    何时以及如何使用endl;
    声明和使用变量
    使用cin对象进行输入
    定义和使用简单函数
*/


#include<bits/stdc++.h> // 编译指令 预处理器操作，在源代码被编译前，替换或添加文本 // 头文化(header file) 包含文件(include file)

using namespace std;    // 名称空间

void simon(int);

int main(){             // 函数头(function heading) // 以下为函数定义(function definition)
// int main(void)       // 变体，指出函数不接受任何参数
// void main()          // 省略返回语句
    simon(10);
    return 0;           // 返回语句(return statement)
}

void simon(int n)
{   
    for(int i = 0; i < n; i++)
    cout << "hello simon" << endl;
}