/*
12 类和动态内存分配
{
    1.动态内存和类
    2.改进后的string类
    3.再构造函数中使用new应注意的事项
    4.有关返回对象的说明
    5.使用指向对象的指针
    6.复习各种技术：重载<<运算符、转换函数、其构造函数使用new的类
    7.队列模拟
}
*/

/*
12.1 动态内存和类
c++让程序在运行时而不是编译时决定内存分配。
c++使用new 和 delete来动态控制内存

12.1.1 复习示例和静态类成员
1.静态类成员：
static int num_strings;
无论创建了多少个对象，都只有一个静态类变量副本，即所有成员共享一个静态成员。
2.将静态变量初始化为零
int StringBad::num_strings = 0;
不能在类声明中初始化静态成员变量，因为类声明描述了如何分配内存，但并不分配内存。可以使用这种格式来创建对象从而分配和初始化内存。
对于静态类对象，可以在类声明以外使用单独的语句进行初始化，因为静态类成员是单独存储的，而不是对象的组成部分。
初始化在方法文件中。
如果静态成员是const整数或者枚举型，则可以在类声明中初始化。
3.str成员指向new分配的内存。当StringBad对象过期时，str指针也将过期，但str指向的内存仍被分配，因此需要使用delete将其释放。
在构造函数中使用new来分配内存，必须在析构函数中使用delete将其释放。如果使用new[]分配内存，则必须用delete[]释放。

12.2.1 特殊成员函数
StringBad类的问题是由特殊成员函数引起的。这些成员函数时自动定义的，就stringBad而言，这些函数的行为与类设计不符。c++自动提供了下面这些成员函数。
1.默认构造函数
2.默认析构函数
3.复制构造函数
4.赋值运算符
5.地址运算符
更准确的说，编译器将自动生成上述最后三个函数的定义--如果程序使用对象的方法要求这么做。当你将一个对象赋值给另一个对象，编译器将自动提供赋值运算符的定义。
c++提供了另外两个特殊成员函数：移动构造函数，移动赋值运算符。18章

1.默认构造函数
如果没有提供任何构造函数，编译器将自动创建默认构造函数。
Klunk::Klunk() { }
也就是说，编译器会提供一个不接受任何参数也不执行任何操作的构造函数。（默认的默认构造函数），因为创建对象时，总会调用构造函数：
Klunk lunk;
默认构造函数使得lunk类似于一个常规的自动变量，它的值在初始化时是未知的。
如果定义了构造函数，c++不会定义默认构造函数，如果希望在创建对象时，不显式的对它进行初始化，则必须显式定义默认构造函数。这种构造函数没有参数，但可以设定特定的值。
Klunk::Klunk()
{
    klunk_ct = 0;
}
带参数的构造函数也可以是默认构造函数，只要所有 参数都有默认值。
Klunk类包含下列内敛构造函数：
Kluck(int n = 0) { klunk_ct = n; }
但只能有一个默认构造函数：
Klunk() { klunk_ct = 0; }
Klunk(int n = 0) { klunk_ct = 0; }
只能有一个，因为具有二义性。
Klunk kar(10);
Klunk bus;
第二个声明既与构造函数1(没有参数)匹配，也与构造函数(使用默认参数0)匹配。

2.复制构造函数
赋值构造函数用于将一个对象复制到新创建的对象中。也就是说它用于初始化过程中（包括按值传递参数），而不是常规的复制过程中。
类的复制构造函数原型如下：
Class_name(const Class_name &);
它接受一个指向类的常量作为参数：
StringBad(const StingBad &);
对于复制构造函数，需要知道何时调用和有何功能。

2.1 何时调用复制构造函数
新建一个对象并将其初始化为同类现有对象时，复制构造函数将被调用。
将新对象显式的初始化为现有对象。
以下四种情况都会调用复制构造函数：
StringBad ditto(motto);
StringBad metoo = motto; 使用复制构造函数直接创建metoo和also，也可能生成一个临时对象然后将临时对象的内容复制给metto和also，这取决于具体实现。
StringBad also = StringBaad(motto); 同上
StringBad * pStringBad = new StringBad(motto); 使用motto初始化一个匿名对象，并将新对象的地址赋值给pstring指针。
每当程序生成了对象副本时，编译器都将使用复制构造函数。
当函数按值传递对象或函数返回对象时，都将使用复制构造函数。
由于按值传递对象将调用复制构造函数，因此应该按引用传递对象。

2.2 默认的复制构造函数的功能
默认的复制构造函数逐个复制非静态成员，成员复制也称为浅复制，复制的是对象的值。
StringBad sailor = sports;
等效于：(无法通过编译，因为私有成员无法访问)
String sailor;
sailor.str = sports.str;
saolpr.len = sports.len;
如果成员本身就是类成员对象，则将使用这个类的复制构造函数来复制成员对象。静态成员不受影响，因为它本身属于整个类，而不是各个对象。

12.1.3 回到StringBad:复制构造函数的哪里出了问题。
1.析构函数比构造函数使用多两次
程序使用默认的复制构造函数另外创建了两个对象。初始化callme2()的形参。还将被用来将对象sailor创建了两个对象。
提供一个对计数进行更新的显式复制构造函数。
2.字符串内容出现乱码：
隐式构造函数时按值复制的。
3.定义一个显式复制构造函数以解决问题
解决类设计中的这种问题是进行深度复制。也就是说，复制构造函数应当复制字符串并将副本的地址赋给str成员，而不仅仅是复制字符串地址。
这样每个对象都有自己的字符串，而不是引用另一个对象的字符串。
调用析构函数时都将释放不同的字符串，而不会去试图释放已经被释放的字符串。
StringBad::StringBad(const StringBad & st)
{
    num_strings++;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    cout << num_strings << ":\"" << str << "\" object created\n";
}
必须定义复制构造函数的原因在于，一些类成员是使用new初始化的、指向数据的指针，而不是数据本身。
深度复制：定义一个复制构造函数，以复制指向的数据。
浅复制：只是复制指针值，不会摄入挖掘以复制指针引用的结构。

12.1.4 Stringbad的其他问题：赋值运算符
自动为类重载赋值运算符实现的：
Class_name & Class_name::operator=(const Class_name &)
它接受并返回一个指向类对象的引用。例如，StringBad类的赋值运算符的原型如下：
StringBad & StringBad::operator=(const StringBad &)
1.赋值运算符的功能以及何时使用它
将已有的对象赋给另一个对象时，将使用重载的赋值运算符：
StringBad headlie1("Celery Stalks at Midnight");
...
StringBad knotl
knot = headline1;
初始化对象时，并不一定都会使用赋值运算符：
StringBad metoo = knot;
这里，metoo是一个新创建的对象，被初始化为knot的值，因此使用复制构造函数。
然而，正如前面指出的，实现时也可能分两步类处理这条语句：使用构造函数创建一个临时对象，然后通过赋值给将临时对象的值复制到新对象中。
初始化总是会调用复制构造函数，而使用=运算符时也允许调用复制运算符。
与复制构造函数类似，赋值运算符的隐式实现也对成员逐个复制。如果成员本身就是类对象，则程序将使用为这个定义的赋值运算符类复制该成员，但静态数据对象不受影响。
2. 复制到问题出现在哪里
数据受损，这也是成员复制的问题。
3.解决赋值的问题
对于默认赋值运算符不合适而导致的问题，结局办法是提供赋值运算符定义。（进行深度复制）
(1)由于目标对象可能引用了以前分配的数据。应使用delete [] 删除这些数据。
(2)函数应当避免将对象赋值给自身，否则给对象重新赋值前，释放内存操作可能删除对象的内容。
(3)函数返回一个指向调用对象的引用。
通过返回一个对象，函数可以像常规赋值操作那样，连续进行赋值，即如果S0,S1和S2都是StringBad对象，则可以编写代码：
S0=S1=S2；
使用函数表示法：
S0.operator=(s1.opeartor=(S2));
因此，S1.operator=(S2)的返回值是函数S0.operator=()的参数。
因为返回值是一个指向StringBad对象的引用，因此参数类型是正确的。
为StringBad编写赋值运算符：
StringBad & StringBad::operator=(const StringBad & st)
{
    if(this == &st)
    {
        return *this;
    }
    delete [] str;
    len = st.len;
    str = new[len + 1];
    std::strcpy(str, st.str);
    return *this;
}

12.2 改进后的String类
仅用作示例，标准String类的内容丰富的多。
int length() const { return len; }                              // 返回字符串的长度
friend bool operator<(const String &st, const String &st2);     // 对字符串进行比较
friend bool operator>(const String &st, const String &st2);     // 同上
friend bool operator==(const String &st, const String &st2);    // 同上
friend operator>>(istream & is, String & st);                   // 提供了简单的输入
char & operator[] (int i);                                      // 以数组表示法访问字符串中各个字符的功能
const char & operator[] (int i) const;                          // 同上
static int HowMany();                                           // 补充静态类成员num_string

12.2.1 修订后的默认构造函数
String::String()
{
    len = 0;
    str = new char[1];
    str[0] = '\0';
}
str = new char[1]; // 与类析构函数兼容
str = new char;    // 与类析构函数不兼容
析构函数中：
delete [] str;
delete [] 与 new [] 初始化的指针和空指针都兼容。
str = new char[1];
str[0] = '\0';
可修改为：
str = 0;
对于以其他方法初始化的指针，使用delete []时结果时不确定的。

C++11空指针
C++98 字面值0表示：1.数字值0 2.空指针
程序员使用：(void *)0 表示空指针（内部不一定是0），NULL表示空指针的C语言宏
C++11 使用新关键字：nullptr，用于表示空指针。
str = nullptr;

12.2.2 比较成员函数
实现字符串比较函数，第一个字符串在第二个字符串之前，机器排序顺序靠前的小，则返回ture。
最简单的方法就是使用标准strcmp()函数，如果按照字母顺序，第一个参数位于第二个参数之前，则该函数返回一个负值；如果相同则返回0;如果第一个参数位于第二个参数之后则返回一个正值。
bool operator<(const String &st1, const String &st2)
{
    if (std::strcmp(st1.str, st2.str) <0) // 第一个参数位于第二个参数之前
        return true;
    else
        return false;
}
因为内置的>运算符返回的是一个布尔值，所以可以将代码进一步简化：
bool operator<(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}

同样，可以按照下列的方式来编写两个比较函数：
bool operator>(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) > 0);
    或者 return st2 < st1;
}
bool operator==(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) == 0);
}

12.2.3 使用中括号表示法访问字符
c风格字符串：
char city[40] = "America";
cout << city[0] << endl; // 输出为A
c++中，两个中括号组成一个运算发--中括号运算符，可以使用方法operator[]来重组该运算符。
通常二元运算符位于两个操作数之间，例如 1+2
中括号运算符，第一个运算符位于第一个中括号的前面，另一个操作数位于两个中括号之间。
因此city[0]中，city是第一个操作数，0是第二个操作数。
e.g.
{
    String opera("The Magic Flute");
    对于表达式opera[4],C++将查找名称和特征标与此方法相同的方法：
    String::Operator[](int i);
    如果找到匹配的原型，编译器将翻译为：
    opera.operator[](4);
    下面是该方法的简单实现：
    char & String::operator[](int i)
    {
        return str[i];
    }
    有了上述定义后，语句：
    cout << opera[4];
    被翻译为：
    cout << opera.operator[](4);
    返回值为opera.str[4](字符M)。由此，公有方法可以访问私有数据。
    将返回类型设置为char &，则可以给特定元素赋值。
    String means = ("might");
    means[0] = 'r';
    第二条语句被转换为一个重载运算符函数调用：
    means.operator[](0) = 'r';
    这里将r赋值给方法的返回值，而函数返回的是指向means.str的引用，因此上述代码等同于：
    means.str[0] = 'r';
    代码的最后一行访问的是私有数据，但由于operator[]()是类的一个方法，因此能够修改数组的内容。
    最终的结果是“might”被修改为"right"。
    如果是const String answer("futile");
    则无法修改，因为answer是常量，重载时c++将区分常量和非常量函数的特征标，因此可以提供另一个仅供const String对象使用的operator[]()版本：
    const char & String::operator[](int i) const
    {
        return str[i];
    }
}

12.2.4 静态类成员函数
可以将函数声明为静态的(函数声明必须带static，如果函数定义是独立的，则其中不能包含关键字static)
首先不能通过对象调用静态成员函数；实际上，静态成员函数不能使用this指针。
如果静态成员函数实在公有部分声明的，则可以使用类名和作用域解析运算符调用它。
e.g.
{
    给String类添加一个名为HowMany()的静态成员函数，方法是在类声明中添加如下的原型/定义：
    static int HowMany() {return num_strings;}
    调用格式如下：
    int count = String::HowMany();
}
静态成员函数不与任何对象相关联，因此只能使用静态数据成员。

12.2.5 进一步重载赋值运算符
{
    string name;
    char temp[40];
    cin.getline(temp, 40);
    name = temp;
}
1.程序使用构造函数String( const char *)来创建一个临时String对象，其中temp中的字符串副本。
2.String & String::operator=( const String &)函数将临时对象中的信息复制到name对象中。
3.程序调用析构函数~String()删除临时对象。
为提高处理效率，重载赋值运算符。直接使用常规字符串，不用创建和删除临时对象。
String & String::operator=(const char * s)
{
    delete [] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}
一般来说，必须释放str指向的内存并为新字符串分配足够的内存。

*/



/*
12.3 在构造函数中使用new时应注意的事项
使用new初始化对象的指针成员时，必须特别小心，具体的说，应该这样做：
{
    如果在构造函数中使用new初始化对象的指针成员，则应在析构函数中使用delete;
    new 和 delete 必须相互兼容，new 对应 delete, new [] 对应 delete [];
    如果有多个析构函数，则必须以相同的方式使用new，要么都带中括号，要么都不带。只有一个析构函数，所有构造函数必须和析构函数兼容。
    可以在一个构造函数中使用new初始化指针，而在另一个构造函数中将指针初始化为空。
}

1.应定义一个复制构造函数，通过深度复制将一个对象“初始化”为另一个对象。
e.g.
{
    String::String(const String & st)
    {
        num_Strings++;
        len = str.len;
        str = new char [len + 1];
        std::strcpy(str, st.len);
    }
}
具体的说，复制构造函数应分配足够的空间来存储复制的数据，并复制数据，而不仅仅是数据的地址，另外还应更新所有受影响的静态类成员。

2.应当定义一个赋值类运算符，通过深度复制将一个对象“复制”给另一个对象。
e.g.
{
    String & String ::operator=(const String & st) 
    {
        if (this == &st)
            return *this;
        delete [] str;
        len = st.str;
        str = new char [len + 1];
        std::strcpy(str, st.str);
        return *this;
    }
}
具体的说，该方法应当完成这些操作：检查自我赋值的情况，释放成员指针以前指向的内存。复制这些数据而不仅仅是数据的地址，并返回一个指向调用对象的引用。

12.3.1 应该和不应该
String::String(const String & st)
{
    len = st.len;
    str = new char [len + 1];
    std::strcpy(str, st.str);
}

String::~String()
{
    delete [] str;
}

12.3.2 包含类成员的类和逐成员复制
假设类成员的类型为String类或标准String类：
class Magazine
{
private:
    String title;
    String publisher;
};

*/

/*
12.4 有关返回对象的说明
可以返回：1.指向对象的引用 2.指向对象的const引用 3.const对象
12.4.1 返回指向const对象的引用
旨在提高效率，函数返回(调用对象的方法或将对象作为参数)，传递给他的对象，可以通过返回引用来提高效率。
e.g.
{
    Vector force(50, 60);
    Vector force(10, 70);
    Vector max;
    max = Max(forcr1, force2);
}
// version1
{
    Vector Max(const Vector & V1,const Vector & V2)
    {
        if (v1.magval() > v2.magval())
            return v1;
        else
            return v2;
    }
}
// version2
{
    const Vector & Max(const Vector & V1,const Vector & V2)
    {
        if (v1.magval() > v2.magval())
            return v1;
        else
            return v2;
    }
}
返回对象调用复制构造函数，而返回引用不会。
第二个版本的工作更少，效率高。
其次，引用指向的对象应该在调用函数执行时存在。
V1和V2都是const类型，因此返回也应该为const。

12.4.2 返回指向非 const对象的引用
两种常见的返回非const对象的引用为：重载赋值运算符，cout一起使用的<<运算符。前者提高效率，后者必须这样操作。
opeartor=()的返回值用于连续赋值：
String s1("Good stuff");
String s2,s3;
s3 = s2 = s1;
Operator<<()的返回值用于串联输出：
String s1("Good stuff");
cout << s1 << "is coming";
上述代码中，cont的返回类值成为一个用于显式字符串的对象。因此返回类型必须为ostream &。如果返回ostream 则要调用ostream的构造函数，而它没有公有的构造函数。

12.4.3 返回对象
如果返回的对象是被调用函数中的局部变量，则不应返回引用。函数调用完毕时，局部对象会调用析构函数。引用指向的局部对象将不存在。
{
    Vector force(50, 60);
    Vector force(10, 70);
    Vector net；
    net = force1 + force2;
}
返回的不是force1也不是foece2，因此返回值不能是指向在调用函数中已经存在的对象的引用。计算和结果被存储在一个新对象中，该函数应该返回实际的Vector类。
{
    Vector Vector::operator+(const Vector & b) const
    {
        return Vector(x + b.x, y + b.y);
    }
}
函数调用创建一个方法能够访问的对象，返回语句引发的对复制构造函数的隐式调用创建一个调用程序能够访问的对象。

12.4.4 返回 const对象
前面的Vecotr::operator+()有一个奇异的属性：
net = force1 + force2;
然后这种定义也允许：
force1 + force2 = net;
cout << (force1 + force2 = net).magval() << endl;
之所以可行，是因为复制构造函数将创建一个临时对象来表示返回值，因此force1 + force2 的结果是一个临时对象。
语句1中，该临时对象被赋给net，在语句2中，net被赋给临时对象。
如果担心这种行为被滥用，可以将返回类型声明为const Vector。
总之，方法和函数如果要返回局部对象，则应该返回对象，而不是指向对象的引用。这种情况下，将使用复制构造函数来生成返回的对象。
如果方法或函数要返回一个没有公有复制构造函数的类（ostream），则必须返回一个指向这种对象的引用。
有些方法可以返回对象也可以返回对象的引用，这种情况下首先返回引用，效率高。

*/

/*
12.5 使用指向对象的指针
C++程序经常使用指向对象的指针。
程序12.6使用数组索引来跟踪最短的字符串和按字母顺序排在最前面的字符串。
另一种方法是使用指针指向这些类别的开始位置，程序清单12.7使用两个指向String的指针实现了这种方法。
最初，shortes指针指向数组中的第一个对象，每当程序找到比更短的对象时，就重新设置指向新的最短对象。这样first指针跟踪按字幕顺序排在最前面的字符串，
这两个指针并不新建对象，而只是指向已有的对象。因此指针并不需要new来分派内存。
除此以外，12.7还使用一个指针来跟踪新对象：
String * fororate = new String(sayings[choice]);
favorite指向new创建的未命名对象。意味着使用对象saying[choice]来初始化新的String对象，这将调用复制构造函数。
{
    使用new初始化对象:
    如果是Class_name是类，value的类型为type_name：
    Class_name * pclass = new Class_name(value);
    将调用构造函数：
    Class_name(const Type_name &);
}

12.5.1 再谈new 和 delete
构造函数：使用new创建对象的名字字符串分配存储地址
析构函数：使用delete释放内存。
因为字符串是一个字符数组，因此使用delete []
使用new来为整个对象分配内存：
String * favorite = new String(sayings[choice]);
这不是为要存储的字符串分配内存，而是为对象分配内存。
为保存字符串地址的str指针和len成员分配内存。
创建对象将调用构造函数，后者分配用于保存字符串的内存，并将字符串的地址赋给str。
当程序不再需要该对象时，使用delete删除它。对象是单个的，不需要[]。
这只释放用于保存str指针和len成员的空间，并不释放str指向的内存，该任务由析构函数完成。

{
    下列情况，则会调用析构函数：
    1.对象是动态变量，当执行完定义该对象的程序块时，调用该函数的析构函数。
    2.如果对象是静态变量(外部、静态、静态外部或来自名称空间)，则在程序结束时将调用析构函数。
    3.new创建的对象，仅当显式使用delete删除对象时，析构函数才调用。
}

12.5.2 指针和对象小结
使用对象指针，需要注意：
1.使用常规表示法来声明指向对象的指针。
String * glamour;
2.可以将指针初始化为指向已有的对象。
String * first = &sayings[0];
3.可以使用new来初始化指针，这将创建一个新的对象。
String * favorite = new String(sayings[choice]);
4.对类使用new将调用相应的类构造函数来初始化新创建的对象：
String * gleep = new String;
String * glop = new String("my my my ");
String * favorite = new String (sayings[choice]);
5.可以使用->运算符通过指针访问类方法：
if (sayings[i].length() < shortest->length())
5.可以对对象指针应用接触引用运算符(*)来或的对象：
if (sayings[i] < *first)
    first = &saying[i];

12.5.3 再谈定位new运算符
定位new运算符能够让你在分配内存时指定内存位置。
pc1 = new (buffer) JustTesting;
pc2 = new JustTesting("Heap1", 20);
1.在创建第二个对象时，定位new运算符使用一个新对象来覆盖与第一个对象的内存单元。如果类动态为其成员分配内存，将引发问题。
将delete用于pc2 pc4时，将自动调用为pc2 pc4指向的对象调用析构函数。然而将delete[]用于buffer时，不会为其使用定位new运算符创建的对象调用析构函数。
经验：程序员必须负责管用定位new运算符从中使用的缓冲区内存单元。要使用不用的内存单元，程序员需要提供两个位于缓冲区的不同地址，并确保这两个内存单元不重叠。
pc1 = new (buffer) JustTesting;
pc3 = new (buffer + sizeof (JustTesting)) JustTesting("Better Idea", 6);
其中pc3相对于pc1的偏移量为JustTesting对象的大小。
2.如果使用定位new 运算符来为对象分配内存，必须确保其析构函数被调用。
如果确保呢？在堆中创建的对象，可以这样做：
delete pc2;
但不能像下面这样做：
delete pc1;
delete pc3;
原因在于delete可以与常规new运算符配合使用，但不能与定位new运算符配合使用。
指针pc1指向的地址与buffer相同，但buffer是new []初始化的，因此必须使用delete []来释放。
即使buffer 是使用new 而不是new[] 初始化的，delete pc1 也将释放buffer，而不是pc1。

显式的为使用定位new 运算符创建的对象调用析构函数：
{
    pc3->~JustTesting();
    pc1->~JustTesting();
    对与使用定位new运算符创建的对象，应与创建顺序相反的顺序进行删除。晚创建的对象可能依赖于早创建的对象。仅当所有对象都被销毁时，才能释放用于存储这些对象的缓冲区。
}
*/

/*
12.6 复习各种技术
12.6.1 重载<<运算符
要重新定义<<运算符，以便它可以和cout一起用来显示对象的内容。请定义下面的友元运算符函数
ostream & operator<<(ostream & os, const c_name & obj)
{
    os << ...;
    return os;
}
其中c_name是类名，如果该类提供了能够返回所需内容的公有方法，则可在运算符函数中使用这些函数，这样便不用讲它们设置为友元函数了。

12.6.2 转换函数
要将单个值转换为类类型，需要创建原型如下的类构造函数：
c_name(type_name value);
其中，c_name是类名，type_name是要转换的类型的名称。
要将类转换为其他类型，需要创建原型如下的类成员函数：
operator type_name();
虽然该函数没有其他类型，但应返回所需类型的值。
使用转换函数要小心，可以使用关键字explicit 防止被用于隐式转换。

12.6.3 其构造函数使用new的类
如果类使用new运算符来分配类成员指向的内存，在设计时应加入一些预防措施。
1.对于指向的内存是由new分配的所有类成员，都应在类的析构函数中对其使用delete，该运算符将释放分配的内存。
2.如果析构函数通过对指针类成员使用delete来释放内存，则每个构造函数都应当使用new来初始化指针，或将它设置为空指针。
3.构造函数中要么是有new ,new[]，不能混用。如果构造函数是new []，则析构函数使用delete[]。
4.应定义一个分配内存(而不是将指针指向已有内存)的复制构造函数。这样程序能够将类对象初始化为另一个对象。这种构造函数原型：
className(const clsssName &)
5.应定义一个重载赋值运算符的类成员函数，其函数定义如下(其中c_pointer是c_name的类成员，类型为指向type_name的指针)。
下面的示例假设使用new[]来初始化变量c_pointer;
c_name & c_name::operator=(const c_name & cn)
{
    if (this == & cn)
    {
        return *this;
    }
    delete [] c_pointer;
    c_pointer = new type_name[size];

    ...
    return *this;
}
*/


/*
12.7 队列模拟
队列是一种抽象的数据类型(ADT)。可以存储有序的项目序列。新项目被添加到队尾，并可以删除队首的项目。
栈：后进先出(LIFO:lasi-in,first out)
队列:先进先出(FIFO:first-in,first-out)

12.7.1 队列类
队列的特征：
{
    1.队列存储有序的项目序列
    2.队列能够容纳的项目数有一定的限制
    3.能够创建空队列
    4.能够检查队列是否为空
    5.能够检查队列是否为满
    6.能够在队尾添加项目
    7.能够从队首删除项目
    8.确定队列中的项目数
}
设计类时，需要开发公有接口和私有接口。
1.Queue类的接口
从队列的特征知，Queue类的公有接口如下：
class Queue
{
    enum {Q_size = 10};
private:
public:
    Queue(int qs = Q_size);         // 构造函数：创建一个Q_size大小的队列
    ~Queue();                       // 析构函数
    bool isempty();                 // 检查是否为空
    bool isfull();                  // 检查是否为满
    int queuecount() const;         // 查看队列中的项目总数
    bool enqueue(const Item &item); // 队尾添加项目
    bool dequeue(Item &item);       // 队首删除项目
}

构造函数创建一个空队列。默认情况下，队列最多可以存储10个项目，但是可以用显式初始化参数覆盖该默认值。
Queue line1;
QUeue line2(20);

2.Queue类的实现
使用链表实现，链表由节点序列构成，每一个节点中都包含要保存到链表中的信息以及一个指向下一个节点的指针。数据部分是一个Item类型的值。
struct Node
{
    Item item;              // 数据部分
    strcut Node * next;     // 指向下一个节点的指针
};
通常链表最后一个节点被设置为NULL(或0)，指出后面没有节点了。

class Queue
{
private:
    struct Node{ Item item; strcut Node * next;}
    enum {Q_size = 10;}
    Node * front;
    Node * rear;
    int items;
    const int qsize;
    ...
public:
    ...
};
上述声明使用了C++的一项特性：
在类中嵌套结构或类声明。通过将Node声明放在Queue类中，可以使其作用域为整个类。
Node是这样一种类型：可以使用它来声明类成员，也可以将它作为类方法中的类型名称，但只能在类中使用。
{
    嵌套结构和类
    在类声明中声明的结构、类或枚举被称为是嵌套在类中，其作用域为整个类。
    这种声明不会创建数据对象，而只是指定了可以在类中使用的类型。
    如果是私有部分，则只能在这个类使用被声明的类型。
    如果声明是在公开部分，则可以从类的外部通过作用域解析运算符使用被声明的类型。
    如果Nude是在Queue的公有部分声明，则可以在类外部声明Queue::Nude类型的变量。
}
3. 类方法
类构造函数提供类成员的值，队列最初是空的，因此队首和队尾指针都设置为NULL(0或nullptr)，并将items设置为0.还应将队列的最大长度qsize设置为构造函数参数qs的值。
成员初始化列表：成员初始化列表由逗号分隔的初始化列表组成(前面带冒号)。它位于参数列表的右括号之后，函数体之前。
如果数据成员名称为mdata，并需要将它初始化为val，则初始化器为mdata(val)。
Queue构造函数：
{
    Queue::Queue(int qs) : qsize(qs)
    {
        front = rear = NULL;
        items = 0;
    }
}
通常，初值可以是常量或构造函数的参数列表中的参数，这种方法并不局限于初始化常量可以将Queue构造函数编写如下：
{
    Queue::Queue(int qs) : qsize(qs), front(NULL), rear(NULL), iteam(0)
    {

    }
}
只有构造函数可以使用这种初始化列表语法。对于const成员，必须使用这种语法。另外，对于被声明为引用的类成员，也必须使用这种语法。
{
    class Agency {...};
    class Agent
    {
    private:
        Agency & belong;
        ...    
    };
};
Agent::Agent(Agency & a) : belong(a) {...}
这是因为引用和const类似，只能在被创建时初始化。
使用初始化列表的效率较高。

{
    成员初始化列表的语法：
    如果Classy是一个类，mem1,men2,mem3是这个类的数据成员，则类构造函数可以使用如下的语法来初始化数据成员。：
    {
        Classy::Classy(int n, int m) : mem1(n), mem(0), mem(n*m + 2)
        {
            ...
        }
    }
    这些初始化工作是在对象创建时完成的，此时还未执行括号中的任何代码。
    1.这种格式只能用于构造函数
    2.必须用这种格式来初始化非静态const数据成员
    3.必须用这种格式来初始化引用数据成员。
    成员初始化列表使用的括号方式也可以用于常规初始化：
    int games = 162;
    double talk = 2.71828;
    替换为：
    int games(162);
    double talk(2.71828);
    初始化内置类型就像初始化类对象一样。
}

{
    C++的类内初始化
    C++11允许以更直观的方式进行初始化：
    {
        Class Classy
        {
            int mem1 = 10;
            const int mem2 = 20;
            ...
        };
    }
    这与在构造函数中使用成员初始化列表等价：
    Classy::classy() : men1(10),mem2(20) {...}
}
{
    入队：
    bool Queue::enqueue(const Item & item)
    {
        if (isfull())           // 如果队列已满，则结束
            return false;
        Node * add = new Node;  // 创建一个新节点add，
        add->item = item;       // 放入正确的值，代码将Item值复制到节点的数据部分
        add->next = NULL;       // 将节点的next指针设置为NULL(0或Nullptr)
        items++;                // 项目计数+1
        if (front = NULL)       // 将节点附加到队尾，如果队列为空，必须将front指针设置成指向新节点，只有一个节点，即是队首节点，也是队尾节点。
            front = add;
        else                    // 将当前队尾节点的next指针指向新的队尾节点。
            rear->next = add;
        rear = add;             // 将Queue的成员指针rear设置为指向新节点，使队列可以直接访问最后一个节点。
        return true;
    }
}
{
    删除队首项目(出队)
    bool Queue::dequeue(Item & item)
    {
        if (front == NULL)      // 如果队列为空，则结束
        {
            return false;
        }
        item = front->item;     // 将队列中的第一个项目提供给调用函数。
        item--;                 // 将项目数减一
        Node * temp = front;    // 保存front节点的位置，供以后删除
        front = front->next;    // 让节点出队，将Queue的成员指针front设置为指向下一个节点来完成。该节点的位置由front->next提供。
        delete temp;            // 删除第一个节点
        if(items == 0)          如果列表为空，设置rear为NULL，
        {
            rear = NULL;
        }
        return true;
    }
}
4. 是否需要其他类方法
需要显式析构函数--该函数删除剩余的所有节点。
{
    Queue::~Queue()
    {
        Node * temp;
        while (front != NULL);
        temp = front;
        front = front->next;
        delete temp;
    }
}

*/