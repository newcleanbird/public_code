// 8.2 引用变量（reference_variable）
// 引用变量是一种复合类型，相当于给已定义的变量取别名。主要用于函数的形参，函数将使用的是原始数据。

#include<iostream>
using namespace std;

void swapr(int & a, int & b); // 按引用传递
void swapp(int * p, int * q); // 按指针传递
void swapv(int a , int b);    // 按值传递

int main(){
    // （1）创建引用变量,引用变量修改的是原始数据，变量和引用变量的地址相同
    int rats = 100;
    int & rodents = rats;
    cout << "rats=" << rats << endl;
    cout << "rodents=" << rodents << endl;
    rodents++;
    cout << "rats=" << rats << endl;
    cout << "rodents=" << rodents << endl;

    // （2）等效于const指针
    // int & rodents = rats;   // 引用变量
    // int * const pr = &rats; // const指针
    
    // （3）函数按引用传递（重要）
    int wallet1 = 100;
    int wallet2 = 200;
    cout << "wallet1 = " << wallet1 << endl;
    cout << "wallet2 = " << wallet2 << endl;

    cout << "按引用传递交换数据：" << endl;
    swapr(wallet1, wallet2);
    cout << "wallet1 = " << wallet1 << endl;
    cout << "wallet2 = " << wallet2 << endl;

    cout << "按指针传递交换数据：" << endl;
    swapp(&wallet1, &wallet2);
    cout << "wallet1 = " << wallet1 << endl;
    cout << "wallet2 = " << wallet2 << endl;

    cout << "按值传递交换数据：" << endl;
    swapv(wallet1, wallet2);
    cout << "wallet1 = " << wallet1 << endl;
    cout << "wallet2 = " << wallet2 << endl;
    // 结论：按"引用传递"和按"指针传递"都使用的是"原始数据"，"按值传递"的是"副本"。

    // （4）使用const int & wallent1，函数中无法修改wallet1的值，相当于按值传递，但速度不同。
    
    /*
    选择依据：
        传递的是基本数值类型：使用按值传递
        数据量较大时：使用按引用传递
    */

    /*
    临时变量、引用参数和const
    如果实参和引用参数不匹配，c++会生成临时变量。仅当参数为const引用时。
    1.参数的类型正确，但不是左值。
    2.参数的类型不正确，但可以转换为正确的类型。

    左值：左值参数是可被引用的数据对象，例如：变量、数据元素、结构成员、引用和解除引用的指针（解除引用意味着从该指针指向的某个内存位置访问该值。）
    非左值：字面常量（用括号括起的字符串除外，他们由地址表示），包含多项的表达式。

    尽可能使用const 
    1.避免编程中的数据修改
    2.使得函数可以处理const和非const实参，否则只能接受非const数据
    3.使用const引用使函数能够正确生成并使用临时变量。
    */

    // 引用用于结构（主要使用途径）
    struct free_throws
    {
        string name;
        int made;
        int attempts;
        float percent;
    };

    void set_pc(free_throws & ft);          // 函数原型
    void set_pc(const free_throws & ft);    // 不希望函数修改传入的结构

    // 将引用用于类对象，将类对象传递给函数
    string versional(const string & s1, const string & s2);

    /*
    使用引用参数的情况：
    1.修改调用函数中的数据对象
    2.通过传递引用而不是整个数据对象，可以提高程序的运行速度。（尤其是数据较大时）引用参数实际上是基于指针的代码的另一个接口。
    */

    /*
    总结：
    使用传递的值而不作修改的函数：
    1.数据对象很小，如内置数据类型或小型结构，则按值传递。
    2.如果数据对象是数组，则使用指针，这是唯一的选择，并且将指针声明为指向const的指针。
    3.如果数据对象是较大的结构，则使用const指针或const引用，以提高效率。节省复制结构所需的时间和空间。
    4.如果数据对象是类和对象，则使用const引用。传递类对象参数的标准方式是按引用传递。

    对于修改调用函数中数据的函数：
    1.如果数据对象是内置数据类型，则使用指针。
    2.如果数据对象是数组，则只能使用指针。
    3.如果数据对象是结构，则使用引用或指针。
    4.如果数据对象是类对象，则使用引用。
        
    */
    


    system("pause");
    return 0;
}

void swapr(int & a, int & b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;
}

void swapp(int * p, int * q)
{
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

void swapv(int a , int b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;
}