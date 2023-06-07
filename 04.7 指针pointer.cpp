#include<iostream>
using namespace std;

struct antarctica_years_end
{
    int year;
};

int main()
{
    // 初始化指针
    
    int temp = 20;
    int *pt = &temp;
    /*
    cout << "temp = " << temp << endl;
    cout << "&temp = " << &temp << endl;
    cout << "pt = " << pt << endl;
    cout << "*pt = " << *pt << endl;
    cout << "&pt = " << &pt << endl;
    */
    int *pn = new int; // 使用new来分配内存
    *pn = 30;
    delete pn; // 释放内存*pn指向的内存，但不会删除*pn指针

    
    // 动态数组
    int *psome = new int [10]; // 创建一个包含10个int元素的数组
    delete [] psome; // 释放内存

    //psome ++; // 指针+1，则增加量等于指向类型的字节数
    //psome[1] 和 *(psome+1)等价

    // 指针数组
    antarctica_years_end s01,s02,s03; // 创建结构体
    const antarctica_years_end *arp[3] = {&s01,&s02,&s03};  //创建指针数组
    const antarctica_years_end **ppa = arp; //创建多级指针 指向指针的指针
    
    int age1 = 100;
    const int *pt1 = &age1; // pt 指向一个 const int, 不能修改age的值。

    // const int age2 = 99;
    // int *pt2 = &age2; //不被允许的，不能用非常量指针指向常量数据

    const int age3 = 98;
    const int *pt3 = &age3; // pt不能修改age3的值，但允许pt3指向其他位置

    int age4 = 97;
    int * const pt4 = & age4; // 指针常量，只能使得pt4指向age4，但能修改

    /*
    const int *pt1;  // 非常量数据的常量指针（指针常量），所指向内容为常量，不能修改。
    int const *pt2;  // 非常量数据的常量指针（指针常量），所指向内容为常量，不能修改。同上，const 在*左边，修饰的是常量
    int * const pt3; // 常量数据的非常量指针（常量指针），这种情况下不能对指针本身进行更改操作，如a++是错误的
    const int* const pt4;    // 常量数据的常量指针，指针本身和指向的内容均为常量。   
    */

    system("pause");
    return 0;
}
