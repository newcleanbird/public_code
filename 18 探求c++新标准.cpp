/*
18 探求c++新标准
{
    1.复习c++11新功能
    2.移动语义和右值引用
    3.新的类功能
    4.Lambda函数
    5.包装器
    6.可变参数模板
    7.c++11其他新增功能
    8.语言变化
    9.接下来的工作
}
*/

/*
18.1 复习前面的C++11功能

18.11 新类型
    long long:64位 整型
    unsigned long long:64位无符号整型
    char16_t:16位字节
    char32_t:16位字节
    “原始字符串”：(Raw String Literals)
    {
        将反斜杠视为文字字符,在原始字符串中，字符表示的就是它自己，而无需使用 "\" 转义，
        例如，"\n" 不表示换行符，而是表示两个常规字符："\" 和 "n"，这时使用 "\n" 将不再输出换行符。
        原始字符串使用 "( 和 )" 作为定界符，并使用 R 来标识原始字符串：
        cout << R"(hello)";
    }

18.1.2 统一的初始化
    初始化列表；
        c++11扩大了大括号括起的列表的使用范围，使其可以用于所有的内置类型和用户定义的类型(即类对象)。
        使用初始化列表时，可添加等号(=)，也可以不添加：
        int x = {5};
        double y {2.75};
        short quar[5] {4, 5, 2, 76, 1};
        列表初始化也可以用于new表达式中：
        int * ar = new int [5];
        创建对象时，也可以使用大括号(不是圆括号)来调用构造函数：
        class Stump
        {
        private:
            int roots;
            double weight;
        public:
            Stump(int r, double w) : roots(r), weight(w) {}
        };
        Stump s1(3, 15.6);
        tump s2{5, 32};

    1.缩窄
        禁止数值赋给无法存储它的数值变量。
        禁止进行类型转换，将值存储到比它“窄的”变量中。
        允许将一个窄的类型转换为一个更宽的类型，即在范围内均可以转换。
    2.std::initializer_list 
        作用：对象中的元素永远是const常量值，我们无法改变initializer_list对象中的元素的值
        C++11提供了模板类initializer_list，可将其用作构造函数的参数，如果类有接受initializer_list作为参数的构造函数，则初始化列表语法就只能用于该构造函数。
        列表中的元素必须是同一种类型或可转换为同一种类型。
        STL容器提供了将initializer_list作为参数的构造函数：
            vector<int> a1(10); 有10个默认值的元素
            vector<int> a2{10}; (initializer_list)有一个值为10的元素
            vector<int> a3{4,6,1}; 三个元素分别是4、6、1
        将initializer_list用做常规函数的参数：
            double sum (std::initializer_list<double> il)
            {
                double tot = 0;
                for (auto p = il.begin(); p != il.end(); P++)
                {
                    total += p;
                }
                return tot;
            }
18.1.3
    1.auto
        关键字auto是一个存储说明符，c++11将其用于自动类型推断。
        要求进行显式初始化，让编译器能够将变量的类型设置为初始值的类型；
            auto maton = 112; // int
            auto pt = &maton // int *
            double fm(double, int);
            auto pf = fm; // double (*) (double, int)
        还常用于简化模板声明：
        for (std::initializer_list<double>::iterator p = il.begin(); p != il.end(); p++)
        替换为：
        for (auto p = il.begin(); p != il.end(); P++)
    2.decltype
    关键字decltype将变量的类型声明为表达式指定的类型，让 y 的类型与x相同，其中x是一个表达式：
    decltype(x) y;
    {
        double x;
        int n;
        decltype(x*n) q;    q类型与(x*n)相同，为double
        decltype(&x) pd;    pd类型与&x相同，即为double *
    }
    这在定义模板时非常好用，只有等待模板类被实例化时才能确定类型：
    template<typename T, typename U)
    void ef(T t, U u)
    {
        decltype(T*U) tu;
        ...
    }
    decltype的工作原理比auto更复杂，根据使用的表达式，指定的类型可以为引用和const
    {
        int j = 3;
        int &k = j;
        const int &n = j;    
        decltype(n) il;     // const int &
        decltype(j) i2;     // int
        decltype((j)) i3;   // int &
        decltype(k + 1) i4; // k+1 为k引用的值+1,因此结果为int
    }

    3.返回类型后置 配合 decltype指定返回类型
    C++11新增函数声明方法：在函数名和参数列表后指定返回类型：
    double f1(double, int);         // 传统声明方法
    auto f2(double, int) -> double; // 新增后置返回类型声明方法
    可以配合decltype来指定模板的函数返回类型：
    template<typename T, typename U)
    auto eff(T t, U u) -> decltype(T*U)
    {
        ...
    }

    4.模板别名：using=
    使用"typedef"创建别名，为冗长或复杂的标识符：
    typedef std::vector<std::string>::iterator itType;
    "using"C++11为其提供了新的创建方法：
    using itType = std::vector<std::string>::iterator;
    新语法用于模板部分具体化，但typedef不能：
        template<Typename T>
            using arr12 = std::vector<T, 12>;
    上述语句具体化模板array<T,int>，将参数int设置为12:
    {
        std::array<double, 12> al;
        std::array<std::string, 12> a2;
        可将它们替换为如下声明：
        arr12<double> a1;
        arr12<std::string> a2;
    }    

    5.nullptr
    增加新关键字用于表示空指针，指针类型不能转换为整数类型。
    特别的增加nullptr == 0 为 true，但不能用于赋值。

18.1.4 智能指针
    auto_ptr:C++11已摒弃
    unique_ptr:
    shared_ptr:
    weak_ptr:

    新增的智能指针都能与STL容器和移动语义协同工作。

18.1.5 异常规范方面的修改
    以前C++提供语法，可用于指出函数可能引发哪些异常：
    void f501(int) throw(bad_dog); 抛出bad_dog异常
    void f733(long long) throw(); 不抛出异常
    社区经验表明，异常规范效果没有预期好，因此摒弃了异常规范：
    指出函数不会引发异常有一定的价值，因此添加了关键字: noexcept
    void f875(short, short) noexcept; // 不抛出异常

18.1.6 作用域内枚举
    传统枚举：1.不能同名 2.可能不能移植，不同的实现，底层类型不同。
    enum Old1 {yes, no, maybe};  // 传统枚举
    enum class New1 {never, sometimes, often, always};  // 新形式
    enum struct New2 {never, lever, sever};             // 新形式
    枚举要求显式限定，以免引发冲突。引用特定的枚举时，需要使用New1::never 和 New2::never

18.1.7 对类的修改：
    1.显式转换运算符：
    C++很早支持对象自动转换，但因此可能产生问题。
    关键字：explicit，禁止单参数构造函数导致的自动转换
    {
        class Plebe
        {
            Pleba(int);             允许自动转换
            explicit Plebe(double); 禁止转换
            ...
        };
        plebe a, b;
        a = 5;      // 通过赋值引发--隐式转换(implicit conversion) 调用(call) Plebe(5)
        b = 0.5;    // 不允许
        b = Plebe(0.5); // 调用构造函数--explicit conversion 显式转换
    }
    C++11扩展了 explicit 的方法，使得可以对转换函数做类似的处理：
    {
        类型转换
        在c++中可以用operator Type()的形式定义类型转换函数，将类对象转换为Type类型
        class A
        {
        public:
            mutable int var;
            void setVar(int a)
            {
                var = a;
            }
            operator int()//将类A对象隐式转化为int类型
            {
                return var;
            }
        };
        
        int main()
        {
            A func;
            func.setVar(10);
            std::cout << func << std::endl;//实际上调用的是func.operator int()这个函数
            return 0;
        }
        output
        10
    }

    {
        class Plebe
        {
            // 转换函数：
            operator int() const;
            explicit operator double() const; // 限制了double 不能隐式转换
            ...
        };
        ...
        Plebe a, b;
        int n = a; // 试图将对象 a 转化为 int整型，通过调用转换函数完成
        double x = b;   // 试图将 b 转换为 double，但double()被限制不能隐式转换，因此不允许
        x = double(b);  // 显式转换double(),允许
    }

    2.类内成员初始化
    C++11 允许进行类内成员初始化：
    {
        class Session{
            // 默认是private:
            int mem1 = 10;
            double eme2 {1966.64};
            short mem3;
        public:
            Session() {}
            Session(short s) : mem3(s) {}
            Session(int n, double d, short s) : mem1(n), mem2(d), mem3(s) {}
        }
    }
    可使用等号、大括号版本的初始化，但不能使用原括号的初始化。其结果与对应的构造函数提供成员初始化列表，并指定的mem1和meme2的值相同：
    如果构造函数再成员初始化列表中提供了相应的值，这些默认值将被覆盖，因此第三个构造函数覆盖了类内成员初始化。

18.1.8 模板和STL方面的修改
    1.基于范围的for循环
    {
        double prices[5] = {4.99, 10.99, 6.87, 7.99, 8.49};
        for(double x : prices)
            std::cout << x << std::endl;
    }
    // auto 配合 for
    {
        for(auto x : prices)
            std::cout << x << std::endl;
    }
    // 如果要修改参数，则使用引用类型：
    {
        std::vector<int> vi(6);
        for(auto & x : vi)
            x = std::rand();
    }
    
    2.新的STL容器
    forword_list:单向链表,比双向链表list相比，更简单、占用存储空间更经济。
    unordered_map:
    unordered_multimap:
    unordered_set:
    unordered_multiset:
    C++还新增了模板array，要实例化这种模板，可指定元素类型和固定的元素数：(更贴近于普通的数组)
        std::array<int,360> ar; // ar[360];
        不能使用修改长度的函数；
        也有begin() end()
    3.新的STL方法：
    新增新的STL方法：
        cbegin():指向第一个元素，将元素视为const
        cend():指向最后一个的后面，将元素视为const
    类似还有：
        crbegin():const rbegin()
        crend():const rend()
    {
        构造函数：      A a(3);
        复制构造函数：  A b = a; // 对象名 = 对象名,本质就是复制/拷贝     新建对象初始化
        赋值运算符：    b = a;已有对象间赋值
        移动构造函数：  
        移动赋值运算符：
    }

    4.valarray升级
    valarray独立于STL开发，目前也支持begin() end()

    5.摒弃export
    C++98新增了关键字export，旨在提供一种途径，让程序员能够将模板定义放在接口文件和实现文化中
    接口文件：包含原型和模板声明
    实现文化：包含模板函数和方法的定义

    6.尖括号
    避免与运算符>>混淆，C++要求在声明嵌套模板时使用空格将尖括号分开：
    std::vector<std::list<int> > vl;
    c++11不再要求这样做：
    std::vector<std::list<int>> vl;

18.1.9 右值引用
    1.传统的C++引用(现在称为左值引用)使得标识符关联到左值。
    左值是一个表示数据的表达式(如变量名或接触引用的指针)，程序可获得其地址。
    最初左值可出现在赋值语句的左边，但修饰符const的出现使得可以声明这样的标识符，即不能给它赋值，但可获得其地址；
    {
        int n;              // 定义一个默认值的int
        int * pt = new int; // 定义一个指针，指向new int,动态创建的一个数(大小随机)
        const int b= 101;   // 定义const int，不能赋值给b，但可以获取b的地址
        int & rn = n;       // n的引用rn    
        int & rt = *pt;     // pt接触引用，即为指向的动态申请的int,rt为其引用
        const int & rb = b; // const int &，不能通过引用rb，修改b的值
    }
    2.c++11新增右值引用，使用&&表示的。右值引用可关联到右值
        右值：即可出现在赋值表达式右边，但不能对其引用地址运算符的值。
            包括字面常量(c风格字符串除外，表示地址)、表达式(x+y)、返回值的函数(返回的不是引用)：
            {
                int x = 10;
                int y = 23;
                int && r1 = 13;
                int && r2 = x + y; // 关联的是x+y的结果，修改x/y也不变
                double && r3 = std::sqrt(2.0); 2.0的平方根
            }
            将右值 关联到右值引用导致该右值被存储到特定的位置，且可以获得该位置的地址。
            通过将数据与特定的地址关联，使得可以通过右值引用来访问该数据。
*/

/*
18.2 移动语义和右值引用
    移动语义的引入是为了解决，多次调用构造函数进行赋值带来的开销。
    类似于计算机中移动文件的情形：实际文件还留在原来的地方，而只修改记录。这种方式称为移动语义。
    移动语义实际上避免了移动原始数据，而只是修改了记录。
    让编译器直到什么时候需要复制，什么时候不需要。这就是右值引用发挥作用的地方。
    {
        可定义两个构造函数：
        1.常规复制构造函数，使用const左值引用作为参数，这个引用关联到左值实参。
            可执行深复制
        2.移动构造函数，使用右值引用作为参数，该引用关联到右值实参。
            只调整记录，在讲所有权转移到新对象的过程中，移动构造函数可能修改其参数，这意味着右值引用参数不应该是const。
    }
18.2.2 一个移动示例
{
    #include<iostream>
    using namespace std;
    
    class Useless
    {
    private:
        int n;
        char * pc;
        static int ct;
        void ShowObject() const; // 禁止函数修改数据
    public:
        Useless();
        explicit Useless(int k);
        Useless(int k, char ch);
        Useless(const Useless & f); 常规构造复制函数
        Useless(Useless && f); // 移动构造函数
        ~Useless(); // 析构函数
        Useless operator+(const Useless & f)const;
        void ShowData() const;
    };

    int Useless::ct = 0;

    Useless:Useless()
    {
        ++ct;
        n = 0;
        pc = nullptr;
        ShowObject();
    }

    Useless::Useless(int k) : n(k)
    {
        ++ct;
        pc = new char[n];
        ShowObject();
    }

    Useless::Useless(int k, char ch) : n(k)
    {
        ++ct;
        pc = new char[n];
        for(int i = 0; i < n; i++)
            pc[i] = ch;
        ShowObject();
    }

    Useless::Useless(const Useless & f) : n(f.n)    // 复制构造函数
    {
        ++ct;
        pc = new char[n];               // 深度复制
        for(int i = 0; i < n; i++)      
            pc[i] = f.pc[i];
        ShowObject();
    }

    Useless::Useless(Useless && f) : n(f.n) 
    {
        ++ct;
        pc = f.pc;
        f.pc = nullptr;
        f.n = 0;
        ShowObject();
    }

    Useless::~Useless()
    {
        ShowObject();
        delete [] pc;
    }

    Useless Useless::operator+(const Useless & f) const
    {
        Useless temp = Useless(n + f.n);
        for(int i = 0; i < n; i++)
            temp.pc[i] = pc[i];
        for(int i = 0; i < temp.n; i++)
            temp.pc[i] = f.pc[i - n];
        return temp;
    }

    void Useless::ShowObject() const
    {
        cout << (void *) pc << endl;
    }

    void Useless::ShowData() const
    {
        if (n == 0)
            cout << "(Object empty)";
        else
            for(int i = 0; i < n; i++)
                cout << pc[i];
        cout << endl;
    }

    int main()
    {
        {
            Useless ont(10, 'x');
            Useless two = one;      // 复制构造函数
            Useless three(20, 'o');
            Useless four (one + three);
            one.ShowData();
            two.ShowData();
            three.ShowData();
            four.ShowData();
        }
    }
}
复制构造函数：
{
    useless::Useless(const Useless & f) : n(f.n)
    {
        ++ct;
        pc = new char[n];
        for(int i = 0; i < n; i++)
            pc[i] = f.pc[i];
    }
    执行深复制，下面的语义将使用复制构造函数：(初始化时调用复制构造函数)
    Useless two = one;
}           

移动构造函数：
{
    Useless::Useless(Useless && f) : n(f.n)
    {
        ++ct;
        pc = f.pc;
        f.pc = nullptr;
        f.n = 0;
    }
    构造函数：
    Useless four (one+three);
    表达式one+three调用Useless::Operator+(),右值引用f将关联到该方法返回的临时对象。
}
18.2.3 移动构造函数解析
    1.右值引用让编译器直到何时可使用移动语义：
    {
        Useless two = one;          // Useless::Useless(const Useless &)
        Useless four (one + three); // Useless:Useless(Useless &&)
        对象one 是左值，与左值引用匹配
        表达式one+three是右值，与右值引用匹配。右值引用让编译器使用移动构造函数来初始化对象four
    }
    2.编写移动构造函数，提供所需的行为
        Useless::Useless(Useless && f)

18.2.4 赋值
    移动语义适用于赋值运算符：
    1.复制赋值运算符
    {
        Useless & Useless::operator=(const Useless & f) // 复制
        {
            if(this == &f)
                return *this;
            delete [] pc;
            n = f.n;
            pc = new char[n];
            for(int i = 0; i < n; i++)
                pc[i] = f.pc[i];
            return *this;
        }
    }
    2.移动赋值运算符
    {
        Useless & Useless::operator=(Useless && f)
        {
            if(this == &f)
                return *this;
            delete [] pc;
            n = f.n;
            pc = f.pc;
            f.n = 0;
            f.pc = nullptr;
            return *this;
        }
    }
    移动赋值运算符删除目标对象中的原始数据，并将源对象的所有权转让给目标，不能让多个指针指向相同的数据。指针设置为nullptr

18.2.5 强制移动
    如果移动构造函数和移动赋值运算符使用右值：
        static_cast<>强制类型转换为 Useless &&
        使用头文件 utility 中声明的 std::move()

总结：右值引用的好处并非是能够编写使用右值引用的代码，而是能够使用右值引用实现移动语义的库代码。
STL类现在都有复制构造函数、移动构造函数、复制赋值运算符、移动赋值运算符

*/

/*
18.3 新的类功能
18.3.1 特殊的成员函数
    原有的4个特殊成员函数：
        默认构造函数
        复制构造函数
        复制赋值运算符
        析构函数
    c++11新增：
        移动构造函数：
        移动赋值运算符：

18.3.2 默认的方法和禁用的方法
    当提供了移动构造函数，则编译器不会自动创建默认的构造函数、复制构造函数、复制赋值构造函数。
    1.使用default显式的声明这些方法的默认版本：
    {
        class Someclass
        {
        public:
            Someclass(SomeClass &&);
            Someclass() = default;
            Someclass(const Someclass &) = default;
            Someclass & operator=(const Someclass &) = default;
            ...
        };
    }
    编译器将创建在您没有提供移动构造函数情况下将自动提供的构造函数。
    关键字default只能用于6个特殊成员函数

    2.关键字delete可用于禁止编译器使用特定方法。
    {
        要禁止对象复制，即禁用复制构造函数和复制赋值运算符：
        class Someclass
        {
        public:
            Someclass() = default;  默认构造：允许
            Someclass(const Someclass &) = delete;  复制构造函数：禁止
            Someclass & operator=(const Someclass &) = delete;  复制赋值运算符：禁止
            Someclass(Someclass &&) = default; 移动构造函数:允许
            Someclass & operator=(Someclass &&) = default;  移动赋值运算符
            Someclass & operator+(const Someclass &) const;
            ...
        };
        要禁止复制构造函数和赋值运算符，可以放在类定义的private部分，但使用delete也能达到这个目的，并且不容易犯错、更容易理解。
    }
    关键字delete可用于任何成员函数

18.3.3 委托构造函数
    类提供了多个构造函数，为了减少工作量，编写重复相同的代码，C++11允许在一个构造函数的定义中使用另一个构造函数。被称为委托
    class Notes{
        int k;
        double x;
        std::string st;
    public:
        Notes();
        Notes(int);
        Notes(int, double);
        Notes(int, double, std::string);
    };
    Notes::Notes(int kk, double xx, std::string stt) : k(kk), x(xx), st(stt) {...}
    Notes::Notes() : Notes(0, 0.01, "AH") {...}         // 默认构造函数，将使用第一个构造函数，并执行其函数体
    Notes::Notes(int kk, double xx) : Notes(kk, xx, "Uh") {...}

18.3.4 继承构造函数
    进一步简化编码工作C++11提供了一种能让派生类能够继承基类构造函数的机制。
    {
        class BS
        {
            int q;
            double w;
        public:
            BS() : q(0), w(0) {}
            BS(int k) : q(k), w(100) {}
            BS(double x) : q(-1), w(x) {}
            B0(int l, double x) : q(k), w(x) {}
            void Show() const {std::cout << q << ", " << w << '\n';}
        };

        class DR : public BS
        {
            short j;
        public:
            using BS::BS;
            DR() : j(-100) {}
            DR(double x) : BS(2*x), j(int(x)) {}
            DR(int i) : j(-2), BS(i, 0.5* i) {}
            void Show() const {std::cout << j << ", "; BS::Show();}
        };
        int main()
        {
            DR o1;
            DR o2(18.81);
            DR o3(10, 1.8);
            ...
        }

        继承的基类构造函数只初始化基类成员，如果还要初始化派生类成员，则应使用成员列表初始化语法。
        DR（int i, int l, double x) : j(i), BS(k,x) {}
    }

18.3.5 管理虚方法：override 和 final
    1.虚说明符override
        指出要覆盖一个虚方法，将其放在参数列表以后，如果声明与基类方法不匹配，则会出现错误。
        {
            virtual void f(char * ch) const override{}
        }
    2.说明符final
        禁止派生类覆盖特定的虚方法
        {
            virtual void f(char ch) const final {...}
        }


*/

/*
18.4 Lambda函数

*/

/*
18.5 包装器

*/