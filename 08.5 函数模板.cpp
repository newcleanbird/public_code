// 函数模板
// 允许以泛型方式编程，因此被称为通用编程，模板特性被称为参数化类型。
// 需要多个将同一种算法应用于不同类型的函数，使用模板。

#include<bits/stdc++.h>

using namespace std;

// 模板声明
template <typename AnyType> // 建立一个模板，并将类型命名为AnyType,其中template 和 typename是关键字。 typename = class (c++98之前标准)
void Swap(AnyType &a, AnyType &b);

// 重载模板声明
template <typename AnyType> // 新的模板
void Swap(AnyType *a, AnyType *b, int n);

/*
（2）显示具体化
对于给定的函数名，可以有非模板函数，模板函数和显式具体化模板函数以及他们的重载版本。
显式具体化的原型和定义以 template<>打头，并通过名称来指出类型。
具体化优先于常规模板，非模板函数优先于具体化和常规模板。
*/

struct job
{
    char name[40];
    double salary;
    int floor;
};

template <> void Swap<job>(job &j1, job &j2); // 显示具体化原型

/*
（3）显式实例化
*/
//（1）直接命令编译器创建特定的实例
template void Swap<int>(int, int); // 显式实例化
//（2）在程序中使用函数来创建显式实例化
template <class T>
T Add(T a, T b)
{
    return a+b;
}
int m = 8;
double x = 10.2;
cout << Add<double>(x, m) << endl; 
// 强制为doulbe类型实例化，将参数m转换为double类型。

// 对比显式具体化
template <> void Swap<int>(int &,int &); // 显式具体化
template <> void Swap(int &, int &);     // 显示具体化等价声明



int main(){
    int i = 10;
    int j = 20;
    Swap(i,j); // 生成（int，int）的Swap函数
    // 隐式实例化：函数调用Swap(i,j)导致编译器生成Swap（）的一个实例，使用int类型。

    double x = 21.8;
    double y = 44.5;
    Swap(x,y); // 生成（int，int）的Swap函数
    

    system("pause");
    return 0;
}

// 模板定义
template <typename AnyType>
void Swap(AnyType &a, AnyType &b)
{
    AnyType temp;
    temp = a;
    a = b;
    b = temp;
}

// 重载模板定义
template <typename AnyType>
void Swap(AnyType a[], AnyType b[],int n)
{
    AnyType temp;
    for (int i = 0; i < n; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
    
}

// 显示具体化定义
template <> void Swap<job>(job &j1, job &j2) // 显示具体化
{
    double t1;
    int t2;
    t1 = j1.salary;
    j1.salary = j2.salary;
    j2.salary = t1;
    t2 = j1.floor;
    j1.floor = j2.floor;
    j2.floor = t2;
}
