/*
11 使用类
{
    1.运算符重载
    2.计算时间--一个运算符重载示例
    3.友元
    4.重载运算符--作为成员函数还是非成员函数
    5.再谈重载：一个矢量类
    6.类的自动转换和强制类型转换
}
*/

/*
11.1 运算符重载--一种形式的c++多态
C++根据操作数的数目和类型来决定采用哪种操作。
允许将运算符重载扩展到用户定义的类型。
隐藏了内部机理，强调了实质。
重载运算符要使用被称为运算符函数的特殊函数形式。
operatorop(argument-list)

11.2 添加加法运算符
operator+()
eg:
    头文件：
    Time operator+(const Time & t) const;
    方法文件：
    Time Time::operator+(const Time & t) const;
    {
        Time sum;
        sum.minutes = minutes + t.minutes;
        sum.hours = hours + t.times + sum.minutes / 60;
        sum.minutes %= 60;
        return sum;
    }
调用：
1.函数表示法：可以像调用sum()那样调用operator+()方法；
total = coding.operactor+(fixing);
2.运算符表示法：
total = coding + fixing; 运算符左边的是调用对象，右边是参数被传递的对象。

11.2.2 重载限制
重载的运算符不必是成员函数，但必须有一个操作数 是用户定义的类型。
1.重载后的运算符必须有一个操作数是用户定义的类型。防止用户为标准类型重载运算符。
2.使用运算符时不能违反运算符原来的句法规则。例如：不能把求模运算符(%)重载成使用一个操作数。
3.不能修改运算符的运算优先级。
4.不能创建新运算符。
5.不能重载下面的运算符：
sizeof：sizeof运算符
.：成员运算符
.*：成员指针运算符
::：作用域运算符
?:：条件运算符
typeid：一个RTTI运算符
const_cast:强制类型转换运算符
dynamic_cast:强制类型转换运算符
reinterpret_cast:强制类型转换运算符
static_cast:强制类型转换运算符
6.大多数运算符可以通过成员或非成员函数进行重载，但下面的运算符只能通过成员函数进行重载
=：赋值运算符
()：函数调用运算符
[]：下标运算符
->：通过指针访问类成员的运算符
注意：
不要将*重载为交换两个Time对象的数据成员。                                                              

11.2.3  其他重载运算符
Time operator-(const Time & t) const;
Time operator*(double n) const;
*/

/*
11.3 友元
C++控制对类对象私有部分的访问。公有类方法提供唯一的访问途径。
友元函数：
友元类：
友元成员函数：
通过让函数成为类的友元，可以赋予该函数与类的成员函数相同的访问权限。
非成员函数：使用的所有制(包括对象)都是显式参数。
A = 2.75 * B；
A = operator*(double m, const Time & t);
非成员函数不能直接访问类的私有数据。
但特殊的非成员函数--友元函数可以访问类的私有数据。

11.3.1 创建友元
1.将其放在类声明中，并在原型声明前加上friend：
friend Time operator*(double m, const Time & t);
2.编写函数定义，并且不要使用friend
Time operator*(double m, const Time & t)
{
    Time result;
    long totalminutes = t.hours * m * 60 + minutes * m;
    result.hours = totalminutes / 60;
    result.minutes = totalminutes % 60;
    return result;
}
有了上述声明和定义后：
A = 2.75 * B；
将转化为：
A = operator*(2.75, B);
总之：类的友元函数时非成员函数，其访问权限与成员函数相同。

11.3.2 常用的友元：重载<<运算符
1.<<的第一种版本
目的：想直接使用语句 cout << trip;
如果使用一个Time成员函数来重载<<，Time对象将是第一个操作数，因此格式为：
trip << cout;
所以考虑用友元函数，重载运算符：
void operator<<(ostream & os, const Time & t)
{
    os << t.hours << " hours, " << t.minutes << " minutes";
}
这样可以使用下面的语句：
cout << trip;

2.<<的第二个重载版本
第一种版本可以实现：
cout << trip;
但不能实现：
cout << "Trip time: " << trip << " (Tuesday)\n";
<<运算符要求左边是一个ostream对象，ostream类将operator<<()函数实现返回为一个指向ostream对象的引用。
具体的说是它返回一个指向调用对象(这里是cout)的引用。
可以对友元函数使用类似的方法，对1进行修改。
ostream & operator<<(ostream & os, const Time & t)
{
    os << t.hours << " hours, " << t.minutes << " minutes";
    return os;
}
注意：返回类型为ostream &,意味着函数返回ostream对象的引用。

*/

/*
11.4 重载运算符：作为成员函数还是非成员函数
成员函数：直接访问类的私有成员。
非成员函数是友元函数，这样才能直接访问类的私有成员。
例如：
Time operator+(const Time & t) const;
freand Time operator+(const Time & t1, const Time & t2);
成员函数版本：一个操作数通过this指针隐式的传递，另一个参数作为函数参数显式传递
友元函数版本：两个操作数都通过函数参数显式传递
编译器将下面的语句：
T1 = T2 + T3;
转化为下面两个之一：
T1 = T2.operator+(t3);
T1 = operator+(T2, T3);
只能选择上述之一，不能同时选择两个。
对于某些运算符而言，成员函数是唯一合法的选择，其他情况下，两者没有太大的区别。
有时根据类设计，非成员函数的版本可能更好。

*/

/*
11.5 再谈重载：一个矢量类
使用运算符和友元的类设计=一个表示矢量的类。
1.大小和方向
2.水平矢量x和垂直矢量y

vector 类 P326

11.5.1 使用状态成员
枚举RECT表示直角坐标模式（默认），POL表示极坐标模式。
这样的成员被成为状态成员(state number)，描述对象所处的状态。

11.5.2 为Vector类重载算术运算符
如果方法通过计算得到了一个新的类对象，则应考虑是否使用构造函数来完成工作。这样不仅可以避免麻烦，还可以保证新对象是按照正确的方式创建的。
1.乘法：
矢量乘以倍数(double)
Vector Vector::operator*(double n) const
{
    return vector(n * x,n * y);
}
倍数乘以矢量
定义:
frend Vevtor operator*(double n,const Vector & a)
{
    return a * n;
}

2.对已重载的运算符进行重载
二元运算符：A - B
一元运算符：-A
对于矢量来说，二者都是有意义的，因此Vector类有这两种操作。
二元运算符：实现减法
原型：
Vector opertor-(const Vector & b) const;
定义：
Vector Vector::opertor-(const Vector & b) const
{
    return Vector(x - b.x, y - b.y);
}
操作数顺序很重要：
diff = v1 - v2;
将被转化为:
diff = v1.operator-(v2);
这意味着从隐式矢量参数减去显式参数传递的矢量，所以应使用x - b.x,而不是b.x - x;
一元运算符：实现反转
Vector operator-() const;
Vector Vector::operator-() const
{
    return Vector(-x, -y);
}
现在operator 有两种版本，它们的特征值不同，即提供了一元和二元版本。
注意：对于只有二元形式的运算符，只能将其重载为二元运算符。如：除法/

11.5.3 对实现的说明：根据情况选则合适的实现，将接口和实现分离。
Vector对象存储了矢量的直角坐标和极坐标，但公有接口并不依赖这一事实。即所有接口都要求能够显式这两种表示，并可以返回各个值。
内部实现可以完全不同，对象可以只存储x和y的分量，而返回矢量长度的 magval()方法可以根据x和y的值来计算出长度，而不是查找对象中存储的这个值。
这种方法改变了实现，但用户接口不变。
将接口和实现分类是oop的目标之一，这种允许对对象进行调整，而无需修改使用这个类的程序中的代码。
存储数据意味着对象将占用更多的内存，每次Vector对象被修改时，都需要更新直角坐标和极坐标，但查找速度较快。
如果程序需要经常访问矢量的两种表示，则这个例子的实现比较合适，如果只是偶尔需要极坐标，则第二种实现更好。
可以在一个程序中使用一种实现，在另一个程序中使用另一个实现。

11.5.4 使用Vector类来模拟随机漫步

*/

/*
11.6 类的自动转换和强制类型转换
内置类型转换：将一个标准类型变量的值赋给另一种标准类型的变量时，如果这两种类型兼容，c++自动将这个值转换为接收变量的类型。
c++语言不自动转换不兼容的类型：
int * p = 10;
但可以强制类型转换：
int & p = (int *) 10; // 虽然不一定有意义
可以将类定义成与基本类型或另一个类相关，使得从一种类型转换为另一种类型是有意义的。
在C++中，接受一个参数的构造函数为将类型与该参数相同的值转换为类提供了蓝图。
因此下面的构造函数用于将double类型的值转换为Stonewt类型：
Stonewt(double lbs);
也就是可以编写如下代码：
Stonewt myCat;
myCat = 19.6;
程序将使用构造函数Stonewt(double)来创建一个临时的Stonewt对象，并将19.6作为初始值。
然后使用逐成员赋值方式将该临时对象内容赋值到myCat中，这一过程称为隐式转换。因为它是自动进行的，并没有强制类型转换。
注意：只有接受一个参数的构造函数才能作为转换函数。或者是第二个参数有默认参数。
关键字 explicit 可以关闭转换特性。
Stonewt myCat; 创建对象
myCat = 19.6; 不允许隐式转换
myCat = Stonewt(19.6); 允许显式强制类型转换。
myCat = (Stonewt)19.6; 旧版本强制类型转换。
总结：
1.将Stonewt对象初始化为double值时。
2.将double值赋给Stonewt对象时。
3.将double值传递给接受Stonewt参数的函数时。
4.返回值被声明为Stonewt的函数试图返回double值时。
5.在上述任意一种情况下，使用可转化为double类型的内置参数时。

11.6.1 转换函数（特殊的c++运算符函数）
可以使用构造函数将数字转换为Stonewt对象。
也可以使用转换函数将Stonewt对象转换为数字。
Stonewt wolfe(285.7);
double host = double (wolft);
double thinker = (double) wolfe;
编译器发现左边是double右边是Stonewt，因此查看是否定义了转换函数，否则输出错误。
创建转换函数：
格式：operator typename();
注意：
1.转换函数必须为类方法。
2.转换函数不能指定返回类型。
3.转换函数不能有参数。
转换为double类型的函数原型如下：
operator double();
要添加将stonewt对象转换为int类型和double类型的函数，需要将下面的原型添加到类声明中：
operator int();
operator double();
类方法文件：
stonewt::operator int() const
{
    return int (poinds + 0.5);
}

stonewt::operator double() const{
    return pounds;
}
转换函数也有其优缺点：隐式转换可能出现意想不到的错误，而且不能被捕获。
因此需要使用explicit关键字，只能用于显式转换。

11.6.2 转换函数和友元函数
实现加法的选择：
1.将下面的函数定义为友元函数，让Stonewt(double)构造函数将double类型的参数转换为Stonewt类型的参数：
operator+(const Stonewt &, const Stonewt &)
2.第二种方法是：将加法运算符重载为一个Stonewt类型的函数：
Stonewt operator+(double x);
friend Stonewt operator+(double x,Stonewt  & s);

*/