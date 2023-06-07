// 数组

#include<iostream>
#include<vector>
#include<array>
using namespace std;

int main()
{
    int list[10] ; // 声明一个int数组
    int cards[4] = {3,6,8,9}; // 初始化一个数组，只有在定义的时候才行

    // 多维数组
    int maxtemp[5][6] =  // 可以看作5行6列二维数组，或者5个带有6个元素的数组。先6后5
    {
        {12,412,14,214,56,341},
        {14,124,535,2667,23,53},
        {124,325,3634,235,25,346},
        {175,748,136,253,77,38},
        {15,674,356,1241,658,324}
    };
    // 赋值
    
    cout << "请输入5行6列行列式\n";
    for (int row = 0; row < 5; row++)
    {
        for(int col = 0; col < 6; col++)
        {
            cin >> maxtemp[row][col];
        }
    } 

    // 打印
    for (int row = 0; row < 5; row++)
    {
        for(int col = 0; col < 6; col++)
        {
            cout << maxtemp[row][col] << "\t";
        }
        cout << endl;

    }

    // 二维数组
    int sum(int (*ar)[4], int size); // ar2是一个指针，给函数sum传递参数（二维数组），
    int sum(int ar2[][4], int size); // 同上
    // ar2[r][c] == *(*(ar2 + r) + c) // 数组等价于指针

    // 模板类 vector
    vector<int> vi;
    vector<double> vd(5); // 一个名为vd的对象,可以存储5个double。长度可以为变量。
    
    // 模板类 array
    array<int,5> ai; // 创建一个名为ai，可以存储5个int的对象 特点：长度固定、使用栈。
    array<double,5> ad= {1.2,2.1,3.43,4.3,5.9}; // 大小不能是变量，相当于静态数组
    ad.at(1) = 2.44; // .at()检查是否越界，但效率降低。
    
    
    system("pause");
    return 0;
}