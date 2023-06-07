/*
13 类继承
{
    1.一个简单的基类：
        派生一个类、构造函数：访问权限的考虑、使用派生类、派生类和基类之间的特殊关系
    2.继承：is-a 关系
    3.多态公有继承
    4.静态联编和动态联编
    5.访问控制：protected
    6.抽象基类
    7.继承和动态内存分配
    8.类设计回顾
}
*/ 

/*
13.1 一个简单的基类
一个类派生出另一个类时，原始类叫基类，继承类称为派生类。
为说明继承，首先需要一个基类。
{
    // tabtenn0.h -- a table-tennis base class
    ifndef TABTENN0_H_
    #define TABTENN0_H_
    #include <string>
    using std::string;
    // simple base class
    class TableTennisPlayer
    {
    private:
        string firstname;
        string lastname;
        bool hasTable;
    public:
        TableTennisPlayer (const string & fn = "none", const string & ln = "none", bool ht = false);
        void Name() const;
        bool HasTable() const { return hasTable; };
        void ResetTable(bool v) { hasTable = v; };
    };
    #endif
}

{
    //tabtenn0.cpp -- simple base-class methods
    #include "tabtenn0.h"
    #include <iostream>

    TableTennisPlayer::TableTennisPlayer (const string & fn, 
        const string & ln, bool ht) : firstname(fn),
	        lastname(ln), hasTable(ht) {}
    
    void TableTennisPlayer::Name() const
    {
    std::cout << lastname << ", " << firstname;
    }
}
TableTennisPlayer 类记录会员的名字，以及是否有球桌。
首先这个类使用标准string类来存储名称，相比于使用字符，更方便，安全，灵活。
其次构造函数使用了成员初始化列表语法，但也可以像如下操作：
{
    TableTeenisPlayer::TableTennisPlayer (const string & fn, const string & ln, bool ht)
    {
        firstname = fn;
        lastname = ln;
        hasTable = ht;
    }
}
这将首先为firstname调用String的默认构造函数，再调用string的赋值运算符将firstname设置为fn，但初始化列表语法可减少一个步骤，它直接使用string的复制构造函数将firstname初始化为fn。
但初始化列表可减少一个步骤，它直接使用string类的复制构造函数将firstname初始化为fn。

13.1.1 派生一个类
// 从TableTennisPlayer派生一个RatedPlayer类
{
    class RatedPlayer : public TableTennisPlayer
    {
        ...
    };
}
冒号指出RatedPlayer类的基类是TableTennisPlayer。
public TableTennisPlayer：表面公有基类，这被称为公有派生。
派生类对象包含基类对象。
使用公有派生，基类的公有成员将成为派生类的公有成员，基类的私有部分也成为派生类的一部分。
但只能通过基类的公有和保护方法访问。
{
    RatedPlayer对象将具有以下特征：
    1.派生类对象存储了基类的数据成员。(派生类继承了基类的实现)
    2，派生类对象可以使用基类的方法。(派生类及乘客基类的接口)
}
{
    需要在继承特征中添加：
    1.派生类需要自己的构造函数
    2.派生类可以根据需要添加额外的数据成员和成员函数。
}

13.1.2 构造函数：访问权限的考虑
派生类不能直接访问基类的私有成员，而必须通过基类的公有方法来访问私有的基类成员。
具体的说，派生类构造函数必须使用基类构造函数。
创建派生类对象时，首先创建基类对象。从概念上说，这意味着基类对象应当在程序进入派生类构造函数之前被创建。C++使用成员初始化列表语法来完成这种工作。
{
    RatedPlayer::RatedPlayer(unsigned int r, const string & fn, const string &ln, bool ht) : TableTennisPlayer(fn, ln, ht)
    {
        rating = r;
    }
    TableTennisPlayer(fn, ln, ht)是成员初始哈列表。它是可执行代码，调用TableTennisPlayer类的构造函数。
    假如，程序包含: TableTennisPlayer(fn, ln, ht)的声明
    RealPlayer构造函数将把实参"Mallory" "Duck" true赋给形参fn,In,ht，然后将这些参数作为实参传递给TableTennisPlayer构造函数。
    后者将创建一个嵌套TableTennisPlayer对象，并将数据"Mallory" "Duck" true存储在该对象里。
    然后程序进入RealPlayer构造函数体，完成RealPlayer对象的创建，并将参数r的值（1140)赋给rating成员。
}

{
    有关派生类构造函数要点如下：
    1.首先创建基类对象。
    2.派生类构造函数应通过成员初始化列表将基类信息传递给基类构造函数。
    3.派生类构造函数应初始化派生类新增的数据成员。
    4.派生类构造函数总是调用一个基类构造函数，可以使用初始化列表语法指明要使用的基类构造函数，否则将使用默认的基类构造函数。
}
先创建基类，再创建派生类。先调用基类构造函数，再调用派生类构造函数。派生类对象过期时，程序将首先调用派生类析构函数，再调用基类析构函数。

{
    成员初始化列表：派生类构造函数可以使用初始化列表将值传递给基类构造函数：
    derived::derived(typel x, typel y) : base(x,y)
    {
        ...
    }
    derived是派生类，base是基类，x 和 y 是基类构造函数使用的变量。

}

13.1.3 使用派生类
要使用派生类，程序必须能够访问基类声明。
可以把两种类的声明放在同一个文件夹里，也可以放在独立的文件夹里。
{
    // tabtenn1.h -- a table-tennis base class
    #ifndef TABTENN1_H_
    #define TABTENN1_H_
    #include <string>
    using std::string;
    // simple base class
    class TableTennisPlayer
    {
    private:
        string firstname;
        string lastname;
        bool hasTable;
    public:
        TableTennisPlayer (const string & fn = "none", const string & ln = "none", bool ht = false);
        void Name() const;
        bool HasTable() const { return hasTable; };
        void ResetTable(bool v) { hasTable = v; };
    };

    / simple derived class
    class RatedPlayer : public TableTennisPlayer
    {
    private:
        unsigned int rating;
    public:
        RatedPlayer (unsigned int r = 0, const string & fn = "none", const string & ln = "none", bool ht = false);
        RatedPlayer(unsigned int r, const TableTennisPlayer & tp);
        unsigned int Rating() const { return rating; }
        void ResetRating (unsigned int r) {rating = r;}
    };

    #endif
}    


{
    //tabtenn1.cpp -- simple base-class methods
    #include "tabtenn1.h"
    #include <iostream>

    TableTennisPlayer::TableTennisPlayer (const string & fn, const string & ln, bool ht) : firstname(fn), lastname(ln), hasTable(ht) {}
    
    void TableTennisPlayer::Name() const
    {
        std::cout << lastname << ", " << firstname;
    }

    // RatedPlayer methods
    RatedPlayer::RatedPlayer(unsigned int r, const string & fn,
        const string & ln, bool ht) : TableTennisPlayer(fn, ln, ht)
    {
        rating = r;
    }

    RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer & tp) : TableTennisPlayer(tp), rating(r)
    {

    }
    创建了TableTennisPlayer类和RatedPlayer类的对象。
}

{
    // usett1.cpp -- using base class and derived class
    #include <iostream>
    #include "tabtenn1.h"

    int main ( void )
    {
        using std::cout;
        using std::endl;
        TableTennisPlayer player1("Tara", "Boomdea", false);
        RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
        rplayer1.Name();          // derived object uses base method
        if (rplayer1.HasTable())
            cout << ": has a table.\n";
        else
            cout << ": hasn't a table.\n";
        player1.Name();           // base object uses base method
        if (player1.HasTable())
            cout << ": has a table";
        else
            cout << ": hasn't a table.\n";
        cout << "Name: ";
        rplayer1.Name();
        cout << "; Rating: " << rplayer1.Rating() << endl;
    // initialize RatedPlayer using TableTennisPlayer object
        RatedPlayer rplayer2(1212, player1);
        cout << "Name: ";
        rplayer2.Name();
        cout << "; Rating: " << rplayer2.Rating() << endl;
        // std::cin.get();
        return 0;
    }
}


13.1.4 派生类和基类之间的特殊关系
1.派生类能够使用基类的方法，条件是方法不是私有的。
RatePlayer rplayer1(1140, "Mallory", "Duck", true);
rplayer.Name();
2.基类指针可以在不进行显式类型转换的情况下指向派生类对象；
TableTennisPlayer & rt = rplayer;
3.基类引用可以不进行显式类型转换的情况下引用派生类对象
TableTennisPlayer * pt = &rplayer;
C++要求引用和指针类型与赋给的类型匹配，但这一规则对继承是例外。
*/

/*
13.2 继承：is-a 关系
C++有三种继承关系：公有继承、保护继承 和 私有继承。
公有继承：建立一种 is-a 关系，即派生类对象也是一个基类对象，可以对基类对象执行的任何操作也可以对派生类对象执行。is-a-kind-of(是一种)关系
保护继承：
私有继承：

*/

/*
13.3 多态公有继承
希望同一个方法在基类和派生类中的行为是不同的。方法的行为取决于调用该方法的对象。这种行为称为多态，具有多种形态，即同一个方法的行为随上下文而异。
{
    1.在派生类中重新定义基类的方法
    2.使用虚方法
}
13.3.1 开发Brass类和BrassPlus类
见书P401
*/

/*
13.4 静态联编和动态联编
函数名联编：将源代码中的函数调用解释为执行特定的函数代码块。
静态联编(早期联编)：在编译过程中进行联编
动态联编(晚期联编)：能够在程序运行时选择正确的虚方法的代码

13.4.1 指针和引用类型的兼容性
在C++中，动态联编和引用调用方法相关，由继承控制的。
公有继承建立is-a关系的一种方法是如何处理指向对象的指针和引用。
{
    C++不允许将一种类型的地址赋给另一种类型的指针。
    也不允许一种类型的引用指向另一种类型。
    指向基类的指针或引用可以引用派生类对象，而不必进行显示转换
}
基类--派生类--派生类，向上(向左)、向下(向右)
{
    向上强制转换：基类指针或引用指向派生类对象。
    将派生类引用或指针转换为基类引用或指针被称为向上强制转换。这使得公有继承不需要进行显式类型转换。
    该规则是is-a关系的一部分。BrassPlus对象都是Brass对象，因为它继承了Brass对象所有的数据成员和成员函数。
    所以，可以对Brass对象执行的任何操作，都是用于BrassPlus对象。
    向上强制转换是传递的。也就是说，从Brassplus派生出的BrassPlusPlus类，Brass指针或引用可以引用Brass对象、BrassPlus对象、BrassPlusPlus对象。
}
{
    向下强制转换：派生类指针或引用指向基类对象。
    向下强制转换：将基类指针或引用转换为派生类指针或引用。
    如果不适用显式类型转换，则向下强制类型转化是不被允许的。
}
隐式向上强制转换使基类指针或引用可以指向基类对象或派生类对象，因此需要动态联编。C++使用虚函数来满足这种需求。

13.4.2 虚成员函数和动态联编
{
    BrassPlus ophelia;
    Brass * bp;
    bp = &ophelia; // 基类指针指向派生类(将派生类转化为基类指针指向)，即向上强制转换。
    bp ->ViewAcct; // 如果在基类中没有将ViewAcct()声明为虚的，则调用Brass::ViewAcct()
    编译器对非虚方法使用静态联编。
    然而如果在基类中将ViewAcct()声明为虚的，则bp->ViewAcct将调用BrassPlus::ViewAcct()。
    编译器对虚方法使用动态联编。
}
{
    为什么默认为静态联编，为什么有两种联编：
    1.使用静态联编效率更高。C++的指导原则之一是，不要为不使用的特性付出代价。
    2.指出不需要重新定义某个函数，仅将那些期望重新定义的方法设置为虚。
    3.如果要在派生类中重新定义基类的方法，则将它设置为虚方法。
}

{
    虚函数的工作原理：
    1.编译器给每个对象添加一个隐藏成员，隐藏成员中保存了一个指向函数地址数组的指针。这种数组被称为虚函数表，存储了为类对象进行声明的虚函数的地址。
    2.派生类对象将包含一个指向独立地址表的指针，如果派生类提供了虚函数的新定义，则该虚函数表将保存新函数的地址。如果定义了新的虚函数，也将地址添加到Vtbl。
    3.调用虚函数时程序将查看存储在对象中的Vtbl地址，然后转向相应的函数地址标。
    {
        1.每个对象都将增大，增大量为存储地址的空间。
        2.对于每个类，编译器都将创建一项额外的操作，即到表中查找地址。
        3.对于每个函数调用，都需要执行一项额外的操作，即到表中查找地址。
    }
}

13.4.3 有关虚函数的注意事项。
1.在基类方法的声明中使用关键字：virtual 使该方法在基类以及所有的派生类(包括从派生类中派生的新类)，都是虚的。
2.如果使用指向对象的引用或指针来调用虚函数，程序将使用为对象类型定义的方法，而不使用为引用或指针类型定义的方法，这称为动态联编或晚期联编。基类指针或引用可以指向派生类对象。
3.如果定义的类将被用作基类，则应将那些要在派生类中重新定义的类方法声明为虚的。
对于虚方法：
1.构造函数：
构造函数不能是虚函数。创建派生类对象时，将调用派生类构造函数，然后派生类构造函数将使用基类的一个构造函数。派生类不继承基类构造函数，声明为虚无意义。

2.析构函数：
析构函数应当是虚函数，除非类不用做基类。
e.g.
{
    Employee 是基类，Singer是派生类。当Singer对象过期时，必须使用~Singer()析构函数来释放内存。
    Employee * pe = new singer;
    ...
    delete pe;
    如果使用默认的静态联编，delete语句将调用~Employee()函数，这将释放由Singer对象中的Employee部分指向的内存，但不会释放新的类成员指向的内存。
    但如果析构函数是虚函数，则上述代码先调用~Singer析构函数释放由Singer组件指向的内存。
    这意味着，即使基类不需要显式构造函数提供服务，也不应依赖于默认构造函数，而应提供虚析构函数，即使它不执行任何操作：
    Virtual ~BaseClass() {}
}
给类定义一个虚析构函数并非错误，即使这个类不做基类，只会影响效率。
通常给基类提供一个虚析构函数，即使他并不需要析构函数。

3. 友元
友元不能是虚函数，因为友元不是类成员，只有类成员才能是虚函数。

4.没有重新定义
如果派生类没有重新定义函数，将使用该函数的基类版本。如果派生类位于派生链中，则将使用最新的虚函数版本，例外的情况是基类版本是隐藏的。

5.重新定义将隐藏方法
重新定义继承的方法并不是重载， 如果重新定义派生类中的函数，将不只是使用相同的函数参数列表覆盖基类声明，无论参数列表是否相同
该操作将隐藏所有的同名基类方法。
经验规则：
    1.如果重新定义继承的方法，应确保与原来的原型完全相同，但如果返回类型是基类引用或指针，则可以修改为指向派生类的引用或指针，该特性称为返回类别协变。
    2.如果基类声明被重载了，则应在派生类中重新定义所有的基类版本。如果只定义一个，则其他会被隐藏，因此有几个就要重新定义几个。

*/


/*
13.5 访问控制：protected
protected:在类外只能用公有类成员来访问protected部分中的类成员。
private 和 protected 区别只有在基类派生的类中才能体现出来。
派生类的成员可以直接访问基类的保护成员，但不能直接访问基类的私有成员。
对于外部来说，保护成员和私有成员类似，但对于派生类来说，保护成员和公有成员类似。

最好对类数据成员采用私有访问控制，不要使用保护访问控制。
同时通过基类方法使派生类能够访问基类数据。

*/

/*
13.6 抽象基类
从Ellipse和Circle中抽象出它们的共性，将这些共性放到一个ABC中，然后从该ABC派生出Circle和Ellipse类。 
使用基类指针数组同时管理Circe和Ellipse对象。(即可以使用多态方法)
C++通过纯虚函数(puer virtual function)提供未实现的函数。纯虚函数声明的结尾处 = 0。
注意：当类声明中包含纯虚函数时，则不能创建该类的对象。
这里的理念是，包含纯虚函数的类只能用作基类。
要成为ABC，必须包含至少一个纯虚函数。
e.g.
{
    可以将原型声明为虚的：
    void Move(int nx, ny) = 0;
    这将使得基类成为抽象的，在函数实现文件中提供方法的定义：
    void BaseEllipse::Move(int nx, ny) {x = nx, y = ny;}
    总之在原型中使用 = 0，指出类是一个抽象基类，在类中可以不定义该函数。
}
使用这些类的成员可以创建Circle和Ellipse类，但不能创建BaseEllipse类。
总之ABC描述的是至少使用一个纯虚函数的接口，ABC派生出的类将根据派生类的具体特征，使用常规虚函数来实现这种接口。

13.6.1 应用ABC概念
首先定义一个名为AcctABC 的 ABC，这个类包含Brass 和 BrassPlus类共有的所有方法和数据成员。
而那些在Barss 和 BrassPlus 中行为不同的方法应被声明为虚函数。
至少应有一个虚函数是纯虚函数，这样才能使AcctABC成为抽象类。

13.11 头文件声明了AcctABC类(ABC)、Brass类 和 BrassPlus类(两者都是具体类)。
为帮助派生类访问基类数据,AcctABC提供了一些保护方法，派生类方法可以调用这些方法，但他们并不是派生类对象的公有接口的组成部分。
AcctABC还提供了一个保护成员函数，用于处理格式化(以前是使用非成员函数处理的)。
Acct还有两个纯虚函数，所以它确实是抽象类。
{
    // acctabc.h  -- bank account classes
    #ifndef ACCTABC_H_
    #define ACCTABC_H_
    #include <iostream>
    #include <string>

    // Abstract Base Class
    class AcctABC
    {
    private:
        std::string fullName;   全名
        long acctNum;           账户账号
        double balance;         
    protected:
        struct Formatting 
        {
            std::ios_base::fmtflags flag;
            std::streamsize pr;
        };
        const std::string & FullName() const {return fullName;}
        long AcctNum() const {return acctNum;}
        Formatting SetFormat() const;
        void Restore(Formatting & f) const;
    public: 
        AcctABC(const std::string & s = "Nullbody", long an = -1,
                    double bal = 0.0);
        void Deposit(double amt) ;
        virtual void Withdraw(double amt) = 0; // pure virtual function
        double Balance() const {return balance;};
        virtual void ViewAcct() const = 0;     // pure virtual function
        virtual ~AcctABC() {}
    };

    // Brass Account Class
    class Brass :public AcctABC
    {
    public:
        Brass(const std::string & s = "Nullbody", long an = -1,
            double bal = 0.0) : AcctABC(s, an, bal) { }
        virtual void Withdraw(double amt);
        virtual void ViewAcct() const;
        virtual ~Brass() {}
    };

    //Brass Plus Account Class
    class BrassPlus : public AcctABC
    {
    private:
        double maxLoan;
        double rate;
        double owesBank;
    public:
        BrassPlus(const std::string & s = "Nullbody", long an = -1,
                double bal = 0.0, double ml = 500,
                double r = 0.10);
        BrassPlus(const Brass & ba, double ml = 500, double r = 0.1);
        virtual void ViewAcct()const;
        virtual void Withdraw(double amt);
        void ResetMax(double m) { maxLoan = m; }
        void ResetRate(double r) { rate = r; };
        void ResetOwes() { owesBank = 0; }
    };

    #endif
   
}


13.6.2 ABC理念
设计ABC之前，首先应开发一个模型--指出编程问题所需的类以及它们之间相互关系。
学院派思维认为，如果要设计类继承层次，则只能将那些不会被用作基类的类设计成具体的类。(派生类都是具体类，基类都是抽象基类)
可以将ABC当作一种必须实施的接口。ABC要求具体派生类覆盖其纯虚函数--迫使派生类遵循ABC设置的接口规则。

*/

/*
13.7 继承和动态内存分配
13.7.1 派生类不使用new 
基类使用了动态内存分配：
声明中包含了构造函数使用new时需要的特殊方法：析构函数、复制构造函数和重载赋值运算符。
是否需要为lackDMA类定义显式析构函数、复制构造函数、赋值运算符呢？ 不需要
1.如果没有定义析构函数，编译器将定义一个不执行任何操作的默认析构函数。派生类的默认析构函数：执行自身代码后调用基类析构函数。默认构造函数是够用的。
2.默认构造函数执行成员复制，对于动态内存分配是不合适的，但对新的lacksDMA成员来说是合适的。只需考虑继承的baseDMA成员。复制类成员或继承的类组件时，使用该类的复制构造函数完成。
lackDMA类的默认复制构造函数使用显式baseDMA复制构造函数来复制lacksMDA对象的baseDMA部分。
3.赋值也是如此。类的默认赋值运算符将自动使用基类的赋值运算符来对基类组件进行赋值。

13.7.2 派生类使用new
{
    class hasDMA : public baseDMA
    {
    private:
        char * style; //  使用new
    public:
    ...
    };
}
必须为派生类定义显式析构函数、复制构造函数、赋值运算符。
1.派生类析构函数自动调用基类的析构函数，故其自身的职责是对派生类构造函数执行工作的进行清理。
{
    hasMDA析构函数必须释放指针style管理的内存，并依赖于baseDMA的析构函数来释放指针label管理的内存。
    baseDMA::~baseDMA()
    {

        delete [] label;
    }

    hasDMA::~hasDMA()
    {
        delete [] style;
    }
}
2.复制构造函数：
BaseDMA复制构造函数遵循char数组的常规模式，使用strlen()来获悉c风格字符串空间、分配足够的空间内存(字符数加上存储空字符所需的1字节)并使用函数strcpy()将原始字符串复制到目的地：
baseDMA::baseDMA(const baseDMA & rs)
{
    label = new char[std::strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = rs.rating;
}
hasDMA复制构造函数只能访问hasDMA数据，因此必须调用baseDMA复制构造函数来处理共享的baseDMA数据。
hasDMA::hasDMA(const hasDMA & hs) : baseDMA(hs)
{
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(strcpy, hs.style);
}
需要注意的是，baseDMA复制构造函数将使用hasDMA参数的baseDMA部分来构造新对象的baseDMA部分。
3.赋值运算符
baseDMA赋值运算符遵循如下常规模式：
{
    baseMDA & baseMDA::operator=(const baseMDA & rs)
    {
        if (this == &rs)
            return 0;
        delete [] label;
        label = new char[std::strlen(rs.label) + 1];
        std::strcpy(label, rs.label);
        rating = rs.rating;
        return *this;
    } 
}
hasDMA使用动态内存分配，需要一个显式赋值运算符。作为hasDMA方法，能直接访问hasDMA数据，派生类的显式赋值运算符必须负责所有继承的baseDMA基类对象的赋值，通过显式调用基类赋值运算符完成。
{
    hasDMA & hasDMA::operator=(const hasDMA & hs)
    {
        if (this == &hs)
            return *this;
        baseDMA::operator=(hs);
        delete [] style;
        style = new char[std::strlen(hs.style) + 1];
        std::strcpy(style, hs.style);
        return *this;
    }
}

总之，当基类和派生类都使用动态内存分配时，派生类的析构函数、复制构造函数、赋值运算符都必须使用相应的基类方法来处理基类元素。
析构函数：自动完成
构造函数：通过在初始化列表中调用基类的复制构造函数完成，如果不这样，则自动调用基类的默认构造函数
赋值运算符：通过作用域解析运算符显式的调用基类的赋值运算符。

13.7.3 使用动态的内存分配和友元的继承，
*/

/*
类设计回顾 P427
13.8.1 编译器生成的成员函数
1.默认构造函数
{
    下述代码将使用默认构造函数：
    Star rigel;


    
    star pleiades[6];
}
默认构造函数要么没有参数，要么参数都有默认值。如果没有定义任何构造函数，编译器会自动提供默认构造函数，让您能够创建对象。
自动生成的默认构造函数的另一项功能是，调用基类的默认构造函数以及调用本身是对象的成员所属类的默认构造函数。
如果派生类构造函数的成员初始化列表中没有显式调用基类构造函数，则编译器将使用基类的默认构造函数来构造派生类对象的基类部分。(如果基类没有构造函数，则导致编译错误)
如果定义了某种构造函数，编译器将不会定义默认构造函数。如果需要默认构造函数，则必须自己提供。
提供某种构造函数的动机之一是保证对象总能被正确的初始化。如果类包含指针成员，则必须初始化这些成员。因此最好提供一个显式默认构造函数，将所有的类数据成员都初始化为合理的值、

2.复制构造函数
复制构造函数接受其所属的类的对象作为参数。
{
    Star类复制构造函数原型：
    Star(const Star &);
}
{
    下述条件，将使用复制构造函数：
    1.将新对象初始化为一个同类对象。
    2.按值将对象传递给函数
    3.函数按值返回对象。
    4.编译器生成临时对象。
}
如果程序没有使用(显式或隐式)复制构造函数，编译器将提供原型，但不提供函数定义。
否则程序将定义一个执行成员初始化的复制构造函数。也就是说，新对象的每个成员都将被初始化为原始对象相应成员的值。
如果成员为类对象，则初始化该成员时，将使用相应类的复制构造函数。

3.赋值运算符
默认的赋值运算符用于处理同类对象之间的赋值，不要将赋值与初始化混淆。
如果语句创建新的对象，则使用初始化；
如果语句修改已有对象的值，则是赋值：
Star Sirius;
Star alpha = sirius;
Star dogstar;
dogstar = sirius;
默认赋值函数为成员赋值。如果成员为类成员，则默认成员赋值将使用相应类的赋值运算符。
如果需要显式定义复制构造函数，则基于相同的原因，也需要显式定义赋值运算符。
Star类的赋值运算符的原型如下：
Star & Star::operator=(const Star &);
赋值运算符函数返回一个Star对象引用。baseDMA类演示了一个典型的显式赋值运算符函数示例。
编译器不会生成将一种类型赋给另一种类型的赋值运算符。如果希望将字符串赋给Star对象，则方法之一是显式定义下面的运算符：
Star & Star::operator=(const char *) {...}
另一种方法是使用转换函数：（见下一节转换），将字符串转换成Star对象，然后使用将Star赋给Star的赋值函数。第一种方法的运行速度较快，但需要的代码较多。而使用轮转函数可能导致编译器出现混乱。

13.8.2 其他的类方法
1.构造函数：
构造函数不同于其他类方法，因为它创建新的对象。而其他类方法只能被现有的对象调用。这是构造函数不能被继承的原因之一。
继承意味着派生类对象可以使用基类的方法，然而，构造函数在完成其工作之前，对象并不存在。
2.析构函数：
一定要显式定义析构函数来释放类构造函数使用new分配的所有内存，并完成类对象所需的任何特殊的清理工作。
对于基类，即使它不需要析构函数，也应提供一个虚析构函数。
3.转换
使用一个参数就可以调用的构造函数定义了从参数类型到类类型的转换。例如，下述Star类的构造函数原型：
Star(const char *);
Star(const Spectarl &, int member = 1);
将可转换的类型传递给以类为参数的函数时，将调用转换构造函数。
Star north;
north = "polaris";


4.按值传递对象与传递引用

5.返回对象和返回引用

6.使用const


13.8.3 公有继承的考虑因素
1.is-a 关系




*/