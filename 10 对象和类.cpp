/*
第十章 对象和类
{
    1.过程性编程和面向对象编程
    2.抽象和类
    3.类的构造和析构函数
    4.this指针
    5.对象数组
    6.类作用域
    7.抽象数据类型
}

10.1 过程性编程和面向对象编程
过程性编程主要考虑遵循的步骤，考虑如何表示这些数据。
面向对象编程首先考虑数据，不仅考虑如何表示数据，而且要考虑如何使用数据。初始化，更新，报告。
从用户的角度考虑对象，描述对象所需的数据，以及描述用户与数据交互所需的操作。完成接口的描述后，确定如何实现接口和数据存储。最后使用新的设计方案完创建程序。

10.2 抽象和类
10.2.1 类型
用户可以根据需要自定义类型，区别于内置类型（char int）。

10.2.2 类
类是一种将抽象转化为用户定义类型的c++工具，将数据表示和操纵数据的方法合成一个整洁的包。
类规范由两个部分组成：
1.类声明：以数据成员的方式描述数据部分，以成员函数（被称为方法）的方式描述公有接口。
2.类方法定义:描述如何实现类成员函数。
类提供了类的蓝图，方法定义提供了细节。
接口（类定义）放在头文件中，实现（类方法的代码）放在源代码文件中。

举例:Stock类
class Stock
{
private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot() {total_val = shares * share_val; }
public:
    void acquire(const std::string & co, long n, double pr);
    void buy(long mun, double price);
    void sell(long num, double price);
    void updata(double price);
    void show();
};

声明Shock类型的变量--称为对象和实例。
存储的数据以类数据成员的形式出现，成员函数可以就地定义，也可以用原型表示（如其他成员函数）。
其他成员函数的完整定义包含在实现文件中，但对于描述函数接口而言，原型足够了。

10.2.1 访问控制
private和public是新的，它们描述了对类成员的访问控制。
使用类对象的程序可以直接访问公有部分，但只能通过公有成员函数（或友元函数）来访问对象的私有成员。
例如要修改Stock类的shares成员，只能通过Stock的成员函数。
公有成员函数是程序和对象的私有成员之间的桥梁，提供了对象和程序之间的接口。防止程序直接访问数据被称为数据隐藏还可以使用关键字protected。
类设计尽可能将公有接口与实现细节公开，公有接口表示设计的抽象组件。将实现细节放在一起并将它们与抽象分开称为封装。
数据隐藏（将数据放在类的私有部分中）是一种封装，将实现的细节隐藏在私有部分中。封装的另一个例子是，将类函数定义和类声明放在不同的文件中。

10.2.2 控制对成员的访问：公有还是私有
数据项通常放在私有部分，组成类接口的成员函数放在公有部分。可以把成员函数放在私有部分中，不能直接从程序中调用这种函数，但公有方法却可以使用它们。
通常，程序员使用私有成员函数来处理不属于公有接口的实现细节。

10.2.3 实现类成员函数
为那些由类声明中的原型表示的成员函数提供代码。成员函数与常规函数定义非常相似，它们有函数头和函数体，也可以有返回类型和参数。
（1）定义成员函数时，使用作用域解析运算符（::）来标识函数所属的类；
（2）类方法可以访问类的private组件。
1.首先成员函数的函数头使用作用域运算符解析（::）类指出函数所属的类。
void Stock::updata(double price)
作用域解析运算符确定了方法定义对应的类的身份，标识符updata()具有类作用域(class scope)。Stock 类的其他成员函数不必使用作用域解析运算符，就可以使用updata()方法。
2.方法可以访问类的私有成员。
3.内联函数：
其定位位于类声明中的函数都将自动成为内联函数。类声明常将短小的成员函数作为内联函数。
可以在类声明之外定义成员函数，并使其称为内联函数。使用关键字inline限定符：
class Stock
{
private:
    ...
    void set_tot();
public:
    ...
};

inline void Stock::set_tot()
{
    total_val = shares * share_val;
}
内联函数特性：在每个使用它们的文件中都对其进行定义，确保内联定义对 多文件程序中的所有文件都是可用的，最简便的方法：将内联定义放在定义类的头文件中。
在类声明中定义方法等同于用原型替换方法定义，然后在类声明后将定义改为内联函数。
4.方法使用哪个对象
(1)创建对象:
Stock kate,joe;
(2)使用对象的成员函数：
kate.show();
joe.show();
调用成员函数被称为：发送消息

10.2.4 使用类
(1)创建对象
Stock fluffy_the_cat;
(2)使用成员函数
fluffy_the_cat.caquire("NanoSmart", 20, 12.50);
fluffy_the_cat.show();
oop程序员常依照客户/服务器的模型来讨论程序设计。客户是使用类的程序，类声明（包括类方法）构成了服务器，他是程序可以使用的资源。
客户只能通过以公有方法定义的接口使用服务器，客户的唯一职责是了解接口。
服务器的责任是确保服务器根据该接口可靠并准确的执行。只能修改类设计的实现细节，不能修改端口。

10.2.5 修改实现
数字的格式不一致，使用方法setf();
std.cout.setf(std::ios_base::fixed, std::ios_base::floatfield);设置了cout对象的一个标记，命令cout使用定点表示法。
std.cout.precision(3);显示三位小数
*/

/*
10.3 类的构造函数和析构函数
创建对象时无法想结构那样直接进行初始化，因为数据部分的访问状态时私有的，程序不能直接访问数据成员。程序只能用过成员函数访问数据成员，因此引出了构造函数。
构造函数没有声明类型

10.3.1 声明和定义构造函数
原型：
Stock::Stock(const string & co, long n = 0, double pr = 0.0);
定义：
Stock::Stock(const string & co, long n, double pr)
{
    company = co;
    if (n < 0)
    {
        std::cerr << "Number of shares can`t be negative: " << company << " shares set to 0.\n";
        shares = 0 ;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
}
上述代码与acquire()相同，但区别在于，函数声明对象时，会自动调用构造函数。

成员名和参数名：
构造函数的参数表示的时赋给类成员的值，不是类成员。因此参数名不能与类成员相同。
1.在数据成员名中使用m_前缀:
class Stock
{
private:
    string m_company;
    long m_shares;
}

2.在数据成员名后使用_后缀:
class Stock
{
private:
    string company_;
    long shares_;
}

10.2.3 使用构造函数
(1)显示的调用构造函数：
Stock food = Stock("World cabbage", 250, 1.25);
隐式调用构造函数：
Stock garment("Ferry Mason", 50, 2.5);

(2)创建类对象(使用new动态分配内存)：
Stock *pstock = new Stock("Electroshock", 20, 2.5);
对象没有名称，但可以通过指针pstock来管理该对象。

(3)注意：
构造函数的使用方式不同于其他类方法，使用对象来调用方法：
stock1.show();
但无法使用对象来调用构造函数，因为在构造函数构造出对象前，对象是不存在的。因此构造函数被用来创建对象，而不能通过对象来调用。

(4)当对象已经存在是，再次调用构造函数
此时不是进行初始化，而是将新值赋给它，让构造函数创建一个新的、临时的对象，然后将内容复制给原对象而实现的。

10.3.3 默认构造函数：
默认构造函数是在未提供显式初始值时，用来创建对象的构造函数。
例如：Stock flully_the_cat;
默认构造函数可能如下：
Stock::Stock() { }
当且仅当没有定义任何构造函数时，编译器才会提供构造函数，为类定义了构造函数后，程序员必须为他提供默认的构造函数：
(1)Stock(const string & co = "Error", int n = 0; double pr = 0.0);
(2)通过函数重载来定义另一个构造函数：一个没有参数的构造函数：
Stock();
例如：
Stock::Stock()
{
    company ="no name";
    share = 0;
    share_val = 0.0;
    total_val = 0.0;
}
使用默认构造函数：
Stock first;
Stock first = Stock();
Stock *prelief = new Stock;

10.3.4 析构函数
用构造函数创建对象后，程序负责追踪该对象，直到其过期，对象过期时，程序自动调用一个特殊的成员函数--析构函数。
析构函数完成清理工作。
1.特性：
(1)析构函数的名称：~Stock()
(2)析构函数也可以没有返回值和声明类型。
(3)析构函数没有参数。
(4)通常不能在代码中显式的调用析构函数。
(4)必须有析构函数，如果程序员没有提供，编译器会自动提供。
2.析构函数的原型：
~Stock();
析构函数不承担任何工作时：
Stock::~Stock()
{
    cout << "Byee, " << company << "~\n";
}

小结：
Stock stock2 = Stock ("Boffo Objects", 2, 2.0);
stock1 = Stock("Nifty Foods", 10, 50.0);
第一个语句是初始化，创建有指定值的对象，可能会创建临时对象。
第二条是赋值，在赋值语句中使用构造函数将导致在赋值前创建一个临时对象。
如果既可以通过初始化，也可以通过赋值来设置对象的值，应采用初始化方法（第一张方法）。

10.3.5 列表初始化
Stock hot_tip = {"Derivarives Plus Plus", 100, 45.0};
Stock jock {"Sport Age Storage, Inc"};
Stock temp {};

10.3.6 const成员函数
保证函数不会修改调用对象。
show()函数没有参数，不能用传统的const引用或指向const的指针来解决问题。它所使用的对象是函数隐式提供的。
show()声明：
void show() const;
show() 定义：
void stock::show() const
只要类方法不修改调用对象，就应将其声明为const。
*/


/*
10.4 this指针
this：指针指向用来调用成员函数的对，是对象的地址。
*this：解除引用运算符*用于指针得到指针指向的值。
const Stock & Stock::topval(const Stock & s) const
{
    if (s.total_val > total_val)
        return s;
    else
        return *this;
}

const Stock & s 的const表示函数不会修改被显式访问的对象
后面的const 表示函数不会修改被隐式访问的对象
前面的const表示返回的是const引用。
*/

/*
10.5 对象数组
声明对象数组：
Stock mystuff[4];
使用构造函数来初始化数组元素：
const int STKS = 4;
Stock stocks[STKS] = {
    Stock("NanoSmart", 12.5, 20),
    Stock("Boffo Objects", 200, 2.0),
    Stock("Monolithic", 130, 3.25),
    Stock("Fleep Enterperiese", 60 ,6.5)
}
如果类包含多个不同的构造函数，则可以对不同的元素使用不同的构造函数：
const int STKS = 10;
Stock stocks[STKS] = {
    Stock("NanoSmart", 12.5, 20),
    Stock(),
    Stock("Fleep Enterperiese", 60 ,6.5)
}
使用Stock(const string & co,long n,double pr) 初始化stock[0] and stock[2]
使用stock()初始化stock[1]
其他7个元素使用默认构造函数进行初始化。
注意：
初始化对象数组的方案实际上是：先使用默认构造函数创建数组元素，然后使用构造函数将创建临时对象，然后将临时对象的内容复制到相应的元素中。
因此要创建类对象数组，必须要有默认构造函数。

*/


/*
10.6 类作用域
在类中定义的名称（如类数据成员名和类成员函数名）的作用域为整个类。作用域为整个类的名称在类内已知，类外不可知。
不同类中可以使用相同名称的类成员名而不会引起冲突。
类作用域意味着不能从外部直接访问类成员，类的公有成员亦是如此。
1.直接成员运算符(.)
2.间接成员运算符(->)
3.作用域解析运算符(::)
class Ik
{
private:
    int fuss;
public:
    Ik(int f = 9) {fuss = f;}
    void ViewIk() const;
};

void Ik::ViewIk() const
{
    cout << fuss << endl;
}

int main()
{
    Ik * pik = new Ik;
    Ik ee = Ik(8);
    ee.ViewIk();    对象.
    pik->ViewIk();  对象指针->
}

10.6.1 作用域为类的常量
使符号常量的作用域为类很有用。
1.声明一个枚举
class Bakery
{
private:
    enum {Months = 12};
    double costs[Months];
}
2.使用关键字static
class Bakery
{
private:
    static const int Months = 12;
    double consts[Months];
}

10.6.2 作用域内枚举
1.使用关键字: class struct
enum class egg {Small, Medium, Large, Jumbo};
enum class t_shirt {Small,Medium, Large, Xlarge};
2.使用：
egg choice = egg::Large;
t_shirt Floyd = t_shirt::Large;

*/

/*
10.7 抽象数据类型
ADT：抽象数据类型，以通用的方式描述数据类型，使用类是一种非常好的方式。
栈：总数从栈顶添加或删除数据，C++使用栈来管理自动变量。
栈存储了多个数据项，使得栈成为一个容器（一个更为通用的抽象）。
1.可创建空栈
2.可将数据项添加到堆顶
3.可从栈顶删除数据项
4.可查看栈是否填满
5.可查看栈是否为空
可将上述描述转化为一个类声明，公有成员提供了表示栈的接口，私有成员负责存储数据。类概念非常适用于ADT方法。
私有部分表明存储数据的方式。

*/