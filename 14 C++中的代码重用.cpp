/*
14. C++中的代码重用
{
    1.包含对象成员的类
    2.私有继承
    3.多重继承
    4.类模板
}
C++主要目标之一：代码重用。公有继承是这种目标的机制之一。
使用本身是另一个类的对象：包含、组合、层次化
多重继承使得能够使用两个或更多的基类派生出新的类，将基类的功能组合在一起。
类模板：使用模板来创建对特定类型定义的特殊类。
*/

/*
14.1 包含对象成员的类
开发学生类，成员：名字、成绩
名字；使用String类，标准String类，字符数组、char指针、动态内存分配。
考试分数：定长数组、动态内存分配、设计一个使用动态内存分配的类来表示该数组。查找一个标准库中存在的表示这种数据的类；Valarray类

14.1.1 valarray 类
valarray类是由头文件valarray支持的。这个类用于处理数值（或具有特征的类）。支持诸如将数组中所有元素的值相加以及在数组中找出最大和最小的值等操作。
valarray被定义为一个模板类，以能够处理不同的数据类型。
模板类声明对象时，必须指定具体的数据类型。使用valarray类来声明一个对象时，需要在标识符valarray后面加上一对尖括号，并在其中包含所需的数据类型：
valarray<int> q_values;
valarray<double> weights;
类特征意味着要使用valarray类，需要了解它的构造函数和其他类方法。
double gpa[5] = {3.1, 3.5, 3.8, 2.9, 3.3}; // 创建长度为5，并且直接初始化的数组
valarray<double> v1;    // 创建长度为0的数组
valarray<int> v2(8);    // 指定长度为8的数组
valarray<int> v3(10.8); // 
valarray<double> v4(gpa, 4);
也可以使用初始列表：
valarray<int> v5 = {20, 32, 17, 9};

14.1.2 Student类的设计
Student 和 成绩 姓名的关系，不是 is-a 模型，学生不是一组姓名，也不是一组考试，而是 has-a 关系，学生有姓名，也有成绩。
通常用与建立 has-a 关系的c++技术是 组合(包含)，即建立一个包含其他类对象的类。
class Student
{
private:
    string name;    // 使用string类表示姓名
    valarray<double> scores;    // 使用double的valarray模板类表示考试分数
    ...
};

***接口和实现
{
    使用公有继承，类可以继承接口，还有实现(基类的纯虚函数提供接口但不提供实现)。获得接口是 is-a 模型的关系
    使用组合，类可以获得实现，但不能获得接口。不继承接口是 has-a 关系的组成部分。
}
使用 has-a 关系，类对象不能自动获得被包含对象的接口是一件好事。string类通过+预算符重载为将两个字符串串联起来，但将两个student类串联起来没有意义。
但另一方面，被包含的类的接口部分对新类来说可能是有意义的。可能希望使用string类接口中的operator<()方法将student对象按姓名进行排序。
因此可以定义student::operator<()成员函数，在内部使用string::operator<()
{
    // studentc.h -- defining a Student class using containment
    #ifndef STUDENTC_H_
    #define STUDENTC_H_

    #include <iostream>
    #include <string>   
    #include <valarray>
    class Student
    {   
    private:
        typedef std::valarray<double> ArrayDb;  // 定义ArrayDb 为 valarray<double>
        std::string name;       // string表示姓名
        ArrayDb scores;         // ArrayDb表示分数
        std::ostream & arr_out(std::ostream & os) const;    // arr_out：用于分数输出的私有方法
    public:
        Student() : name("Null Student"), scores() {} // 默认构造函数
        explicit Student(const std::string & s) : name(s), scores() {}
        explicit Student(int n) : name("Nully"), scores(n) {}
        Student(const std::string & s, int n)
            : name(s), scores(n) {}
        Student(const std::string & s, const ArrayDb & a)
            : name(s), scores(a) {}
        Student(const char * str, const double * pd, int n)
            : name(str), scores(pd, n) {}
        ~Student() {}
        double Average() const;
        const std::string & Name() const;
        double & operator[](int i);
        double operator[](int i) const;
    // friends
        // input
        friend std::istream & operator>>(std::istream & is,
                                        Student & stu);  // 1 word
        friend std::istream & getline(std::istream & is,
                                    Student & stu);     // 1 line
        // output
        friend std::ostream & operator<<(std::ostream & os,
                                        const Student & stu);
    };

    #endif

}

C++和约束
{
    C++包含让程序员限制程序结构的特性--使用explicit 防止单参数构造函数的隐式转化
    使用const限制方法修改数据等
    根本原因：在编译阶段出现的错误优于在运行阶段出现的错误。
    1.初始化被包含的对象
    构造函数使用成员初始化列表语法初始化name和score成员对象。
    Queue::Queue(int qs) : qsize(qs) {...}
    explicit Student(const std::string & s) : name(s), scores() {}
    构造函数还使用成员初始化列表语法初始化派生对象的基类部分：
    hasDMA::hasMDA(const hasMDA & hs) : baseDMA(hs) {...}
    对于继承的对象，构造函数在成员初始化列表中使用类名来调用特定的基类构造函数。//  如上，baseMDA(hs)
    对于成员对象，构造函数使用成员名进行初始化。 // 如下，name(str)
    Student(const char * str, const double * pd, int n) : name(str), score(pd, n) {}
    初始化列表中，每一项都调用与之匹配的构造函数。name(str)调用的是 string(const char *),因为name()是成员对象，所以使用成员名而不是类名。
    scores(pd,n)调用构造函数ArrayDb(const double *,int)
    如果不使用初始化列表语法，则C++要求在构建对象的其他部分之前，先构建继承对象的所有成员对象。c++将使用成员对象所属类的默认构造函数。
}

{
    初始化顺序
    初始化列表包含多个项目，这些项目被初始化的顺序为它们被声明的顺序，而不是初始化列表中的顺序。
}
2.使用被包含对象的接口
被包含对象的接口不是公有的，但可以在类方法中使用它。借助于被包含对象调用该对象所属类的方法。
double Student::Average() const
{
    if (scores.size() > 0)
    {
        return scores.sum() / scores.size();
    }
    else
    {
        return 0;
    }
}
上述代码定义了可由Student对象调用的方法，该方法内部使用了valarray()的方法size()和sum()，因为scores是一个valarray类对象，所以它可以调用valarray类的成员函数。
因此，想使用其他类方法，则需要添加一个该类的对象作为成员对象。

或者定义友元函数，并加入辅助函数使得编程简洁。也可以访问其他类的成员。


14.2 私有继承
C++还有一种shixian has-a 关系的途径--私有继承。
使用私有继承，基类的公有成员和保护成员都将成为派生类的私有成员。
基类方法将不会成为派生对象公有接口的一部分，但可以在派生类的成员函数中使用它们。
{
    
    使用公有继承，基类的公有方法将成为派生类的公有方法。派生类将继承基类的接口；这是 is-a 关系的一部分。
    使用私有继承，基类的公有方法将成为派生类的私有方法。派生类不继承基类的接口，不完全的继承关系是 has-a 关系的一部分。
    使用私有继承，类将继承实现。
    包含将对象作为一个命名的成员添加到类中，而私有继承将对象作为一个未命名的继承对象添加到类中。
    子对象：表示通过继承或包含添加的对象。
    私有继承提供的特性和包含相同：获得实现，但不获得接口。所以私有继承也能实现 has-a 关系。
}

14.2.1 Student类示例(new version)
私有继承：使用关键字 private(默认也是private)
class Student : private std::string,private std::valarray<double>
{
public:
    ...
};
使用多个基类的继承被称为多重继承(Multiple inheritance, MI)
1.初始化基类组件
隐式地继承组件而不是成员对象将影响代码的编写，因为再也不能使用name和score这两来描述对象了，必须使用公有继承的技术：
Student(const char * str, const double * pd, int n) : name(str), scores(pd, n) {}
对于继承类，新版本的构造函数将使用成员初始化列表语法，它使用类名而不是成员名来标识构造函数：
Student(const char * str, const double * pd, int n) : std::string(str), ArrayDb(pd, n) {}
ArrayDb是std::valarray<double>的别名，成员初始化列表使用std::string(str)，而不是name(str),这是包含和继承的第二个主要区别。
{
    // studenti.h -- defining a Student class using private inheritance
    #ifndef STUDENTC_H_
    #define STUDENTC_H_

    #include <iostream>
    #include <valarray>
    #include <string>   
    class Student : private std::string, private std::valarray<double>
    {   
    private:
        typedef std::valarray<double> ArrayDb;
        // private method for scores output
        std::ostream & arr_out(std::ostream & os) const;
    public:
        Student() : std::string("Null Student"), ArrayDb() {}
        explicit Student(const std::string & s)
                : std::string(s), ArrayDb() {}
        explicit Student(int n) : std::string("Nully"), ArrayDb(n) {}
        Student(const std::string & s, int n)
                : std::string(s), ArrayDb(n) {}
        Student(const std::string & s, const ArrayDb & a)
                : std::string(s), ArrayDb(a) {}
        Student(const char * str, const double * pd, int n)
                : std::string(str), ArrayDb(pd, n) {}
        ~Student() {}
        double Average() const;
        double & operator[](int i);
        double operator[](int i) const;
        const std::string & Name() const;
    // friends
        // input
        friend std::istream & operator>>(std::istream & is,
                                        Student & stu);  // 1 word
        friend std::istream & getline(std::istream & is,
                                    Student & stu);     // 1 line
        // output
        friend std::ostream & operator<<(std::ostream & os,
                                        const Student & stu);
    };

    #endif
}

2.访问基类的方法
使用私有继承时，只能在派生类的方法中使用基类的方法。
double Student::Average() const
{
    if (score.size() > 0)
        return score.sum() / scores.size();
    else 
        return 0;
}
私有继承使得能够使用类名和作用域解析运算符来调用基类的方法：
double Student::Average() const
{
    if (ArrayDb::size() > 0)
        return ArrayDb::sum() / ArrayDb::size();
    else
        return 0;
}
All in all,使用包含时，使用对象名来调用方法；私有继承时，使用类名或者作用域解析运算符来调用方法。

3.访问基类对象
使用作用域解析符可以访问基类的方法，使用强制类型转换可以访问基类。
this指针指向用来调用方法的对象，因此*this为用来调用方法的对象。
为避免调用构造函数创建新的对象，可使用强制类型转换来创建一个引用：
const string & Student::Name() const
{
    return (const string &) *this;
}
上述方法返回一个引用，该引用指向调用该方法的Student对象中继承而来的string对象。

4.访问基类的友元函数
用类名显式的限定函数名不适合于友元函数，因为友元函数不属于类。
可以显示的转换为基类来调用正确的函数。
对于如下的友元函数：
ostream & operator<<(ostream & os, const Student & stu)
{
    os << "scores for " << (const string &) stu << ":\n";
    ...
}
plato是一个Student对象，下面的语句将调用上述函数，stu是指向plato的引用，而os将是指向cout的引用：
cout << plato;
下面的代码：
os << "Scores for" << (const string &) stu << ":\n";
显式的将stu转换为string对象引用，进而调用函数 operator<<(ostream &, const string &)。
引用stu不会自动转化为string引用，在私有继承中，未进行显式类型转换的派生类引用或指针，无法赋值给基类的引用或指针。

14.2.2 使用包含还是私有继承
实现has-a关系，既可以使用私有继承，也可以使用包含。
大多数c++程序倾向于使用包含。
首先，易于理解，类声明中包含表示被包含类的显示命名对象，代码可以根据名称引用这些对象，而使用继承将使关系更抽象。
其次继承容易引起问题，尤其是多个基类继承时。
另外包含能够包括多个同类的子对象。
然后，私有继承所提供的特性更多。类包含保护成员，这样的成员在派生类中是可用的，但在继承层次之外是不可用的。组合不能访问保护成员。

14.2.3 保护继承
保护继承是私有继承的变体。使用关键字 protected:
class Student : protected std::string, protected std::valarray<double> {...};
使用保护继承时，基类的公有成员和保护成员都将成为派生类的保护成员。
基类的接口在派生类中是可用的，在继承层次结构之外是不可用的。
使用私有继承时，第三代类将不能使用基类的接口。
使用保护继承时，基类的公有方法在第二代中变为受保护的，因此第三代可以使用它们。

14.2.4 使用using重新定义访问权限
使用保护派生或私有派生时，基类的公有成员将成为保护成员或私有成员。要让基类方法在派生类外面可用，定义一个使用该基类方法的派生类方法。
假设希望Student类使用valarray类的sum()方法，可以在student类的声明中声明一个sum()方法。
double Student::sum() const
{
    return std::valarray<double>::sum();
}
这样sum()对象便能够调用Student::sum()，后者进而将valarray<double>::sum()方法应用于被包含的valarray对象。
另一种方法是，将函数调用包装在另一个函数中，即使用一个using声明(就像名称空间那样)来指出派生类可以使用特定的基类成员，即采用的是私有派对。
希望通过Student类能够用Valarray的方法min()和max()，可以在studenti.h的公有部分加入using声明：
class Student : private srd::string, private std::valarray<double>
{
    ...
public:
    using std::valarray<double>::min;
    using std::valarray<double>::max;
    ...
};
*/

/*
14.3 多重继承 （MI）
MI描述的是有多个直接继承的类。与单继承一样，公有MI表示的也是 is-a 关系。
必须使用public关键字来限定每一个基类，否则编译器认为是私有派对。
class SingingWaiter : public waiter, Singer {...};
私有MI和保护MI可以表示 has-a 关系。
MI可能会给程序员带来很多新问题：
1.从两个不同的基类继承方式继承同名方法。
2.从两个更多的相关基类哪里继承同一个类的多个实例。

14.3.1 有多少worker
首先从Singer 和 Waiter 公有派生出 SingingWaiter:
class SingingWaiter: public Singer, public Waiter {...}
因为Singer和Waiter都继承了一个Worker的组件，因此SingingWaiter将包含两个Work组件。
正如预期的，这将引发问题。通常可以将派生类对象的地址赋给基类指针，此时将出现二义性：
SingingWaiter ed;
Worker * pw = &ed;
通常，这种赋值将把基类指针设置为派生对象中的基类对象的地址。但ed中包含两个Worker对象，有两个地址可供选择，应使用类型转换来指定对象。
Work * pw1 = (Waiter *) &ed;
Word * pw2 = (Singer *) &ed;
这将使得使用基类指针来引用不用的对象(多态性)复杂性。
C++引用多重继承时，也引入了新技术-虚基类(virtual base class)，使MI(多重继承)成为可能。

1.虚基类
虚基类可以从多个类(它们的基类相同)派生出的对象只继承一个基类对象。
例如：通过在类声明中使用关键字 virtual，可以使 Worker 被用作 Singer 和 Waiter 的虚基类(Virtual 和 public 的次序无关紧要)
class Singer : virtual public Worker {...};
class Waiter : public virtual Worker {...};
然后可以将SingingWaiter 类定义为：
class SingingWaiter : public Singer, public Waiter {...};
现在，SingingWaiter 对象只包含Worker对象的一个副本。
从本质上说，继承的 Singer 和 Waiter 对象共享一个Worker对象，而不是各自引入自己的Worker对象副本。
因为SingingWorker现在只包含一个Worker子对象，所以可以使用多态。
{
    虚基类的“虚”其实和虚函数的“虚”没有明显联系，更像是"关键字重载"。
    使用虚基类需要修改已有的代码--SingingWorkder类添加到Worker集成层次中时，需要在Singer waiter 类中添加关键字virtual
}

2.新的构造函数规则
使用虚基类时，需要对构造函数采用一种新的方法。
{
    对于非虚基类，唯一可以出现在初始化列表中的构造函数使基类构造函数。但这些构造函数需要将信息传递给其基类。
    {
        class A
        {
            int a;
        public:
            A(int n = 0) : a(n) {}
            ...
        };
        class B : public A
        {
            int b;
        public:
            B(int m = 0, int n = 0) : A(n), b(m) {}
            ...
        };
        class C : public C
        {
            int c;
        public:
            C(int q = 0, int m = 0, int n = 0) : B(m, n), c(q) {}
        };
        ...
    }
    C类构造函数传递 m 和 n 调用B类构造函数，B类构造函数传递 n 调用A类构造函数。
}
{
    如果Worker是虚基类，则这种信息自动传递将不起作用。
    SingingWaiter(const Worker & wk, int p = 0, int v = Singer::other) : Waiter(wk,p), Singer(wk,v) {}
    自动传递信息时，将通过两条不同途径(waiter Singer)将wk传递给worker对象。
    为避免这种情况，C++在基类是虚的时，禁止信息通过中间类自动传递给子对象Waiter。
    编译器必须在构造派生对象前构造基类对象组件，因此编译器将使用worker的默认构造函数。
    如果不希望使用默认构造函数来构造虚基类对象，则需要显式的调用所需的基类构造函数。。
    构造函数如下：
    SingingWaiter(const Worker & wk, int p = 0, int v = Singer::other) : Worker(wk), waiter(wk,p), Singer(wk,v) {}
    上述代码将显式调用构造函数worker(const Worker &)。 
    这种调用是合法的，对于虚基类，必须这么做，但对于非虚基类，则是非法的。
}

14.3.2 哪个方法
除了修改类构造函数规则外，MI通常还需要调整其他代码。
多重继承可能导致函数调用的二义性。
可以使用作用域解析运算符来澄清编程者的意图：
SingingWaiter newhire("Elise Hawks", 2005, 6, sopeano);
newhire.Singer::Show();
{
    然而更好的方法是在SingingWaiter中重新定义Show(),并指出要使用哪个Show()。
    如果希望SingingWaiter 使用Singer版本的Show()，则可以这么做：
    void SingingWaiter::Show()
    {
        Singer::Show();
    }
}
对于单继承来说，让派生方法调用基类方法是可行的。

1.混合使用虚基类和非虚基类
当类通过多条虚途径和非虚途径继承某个特定类时，该类将包含一个表示所有虚途径的基类子对象和分别表示各条非虚途径的多个基类子对象。

2.虚基类和支配
使用虚基类将改变C++解析二义性的方式。
使用虚基类规则很简单。如果类从不同的类继承了两个或更多的同名成员(数据或方法)，则使用该成员名时，如果没有用类名进行限定，将导致二义性。
但如果使用的是基虚基类，这样做不一定会导致二义性。如果某个名称优先于其他所有名称，则使用它时，即便不使用限定符，也不会导致二义性。

14.3.3 MI小结
P461


*/

/*
14.4 类模板
继承(公有、私有或保护)和包含并不总是能够满足重用代码的需要。Stack 和 Queue 都是容器类，设计用来存储其他对象或数据类型。
与其编写新的类声明，不如编写一个泛型(即独立于类型的)栈，然后将具体的类型作为参数传递给这个类。
{
    缺点：
    1.每次修改类型都需要编辑头文件
    2.在每个程序中只能使用这种技术生成一种栈，即不能让typedef同时代表两种不同的类型。不能同时定义int栈和string栈。
}
C++模板类为生成通用的类声明提供了一个更好的方法。
模板提供参数化类型，即能够将类型名作为参数传递给接收方来建立类或函数。

14.4.1 定义类模板
模板类：
template <class Type> // 关键字template，说明要定义一个模板，<>尖括号内容相当于函数的参数列表。
关键字class看作是变量的类型名，该变量接受类型作为其值，把Type看作是该变量的名称。
这里使用class 并不说明Type必须是一个类，而只是表面Type是一个通用的类型说明符，在使用模板时，将使用实际的类型替换它。
typename 可以替换 class:
template <typename Type>
可以使用自己的泛型名代替Type,命名规则和其他标识符相同。流行的是T Type，这里用Type。
当模板被调用时，Type将被具体的类型值取代。
模板定义中，可以使用泛型名来标识要存储在栈中的类型。
{
    对于Stack而言，这意味着应将声明中所有的typedef标识符Item替换为Type。
    Item items[MAX];
    应该为：
    Type items[MAX];
    同样可以使用模板成员函数替换原有类的类方法。每个函数头都将以相同的模板声明打头：
    template <class Type>
    同样应使用泛型名Type替换typedef标识符Item。另外，还需将类限定符从Stack::改为Stack<Type>::
    bool Stack::push(consy Item & item)
    {
        ...
    }
    应该为：
    template <class Type>
    bool Stack<Type>::push(const Type & item)
    {
        ...
    }
}
如果在类声明中定义了方法(内联定义)，则可以省略模板前缀和类限定符。
模板的具体实现--实例化 或 具体化
由于模板不是函数，它们不能单独编译。
模板必须与特定的模板实例化请求一起使用。
最简单的方法就是将所有的模板信息放在一个头文件中，并在要使用模板的文件中包含该文件。

14.4.2 使用模板类
必须请求实例化：声明一个类型为模板类的对象，方法是使用所需的具体类型替换泛型名。
{
    Stack<int> kernels;
    Stack<String> colonels;
}
编译器将按 Stack<Type>模板来生成两个独立的类声明和两组独立的类方法。
泛型标识符--Type--称为类型参数(type parameter)，这意味着它们类似于变量，但赋值必须是类型。必须显式提供所需的类型。

14.4.3 深入探讨模板类
可以将内置类型或类对象用作类模板Stack<Type>的类型。
可以创建指针栈，但需要对程序做出巨大修改。
{
    正确使用指针栈：
    让调用程序提供一个指针数组，其中每个指针都指向不同的字符串。
    注意：创建不同指针是调用程序的职责，而不是栈的职责。栈的任务是管理指针，而不是创建指针。
}

14.4.4 数组模板示例和非类型参数
template <class T, int n>
关键字class指出T为类型参数，int 指出n的类型为int。这种参数(指定特殊类型而不是用作泛型)称为非类型或表达式参数。
ArrayTP<double, 12> eggweights;
这将导致编译器定义名为 ArrayTP<double, 12>的类，并创建一个类型为 ArrayTP<double, 12>的eggweight对象。定义类时，编译器将使用double替换T，使用12替换n。
表达式参数有一定的限制：
1.表达式参数可以是整形、枚举、引用或指针。不能是其他符合类型或浮点型。因此double m不合法。但double * rm 合法。
2.模板代码不能修改参数的值，也不能使用参数的地址
3.实例化模板时，用作表达参数的值必须是常量表达式。
与Stack中使用的构造函数方法相比，改变数组大小的方法有一个优点：
构造函数方法使用的是new 和 delete 管理的堆内存，而表达式参数方法使用的是为自动变量维护的内存栈。执行速度更快
表达式参数方法的主要缺点：每种数组大小都将生成自己的模板。
{
    生成两个独立的类声明：
    ArrayTP<double, 12> eggweights;
    ArrayTP<double, 13> donuts;
    生成一个类声明，并将数组大小发给构造函数：
    Stack<int> eggs(12);
    Stack<int> dunkers(13);
}
构造函数方法更通用，数组大小是作为类成员存储在定义中。可以将一种尺寸的数组赋给另一种尺寸的数组，也可以允许创建数组大小可变的类。

14.4.5 模板多功能性
可以将用于常规类的技术用于模板类。模板类可用作基类，也可以用作组件类，还可以用作其他模板的类型参数。
{
    template <typename T>
    class Array
    {
    private:
        T entry;
        ...
    };

    template <typename Type>
    class GrowArray : public Array<Type> {...};

    template <typename Tp>
    class Stack
    {
        Array<Tp> ar;
        ...
    };
}
Array < Stack<int> > asi; // 使用数组模板来构建数组--数组元素是基于栈模板的栈。

1. 递归使用模板
ArrayTP< ArrayTP<int,5>, 10> twodee;
这使得twodee是一个包含10个元素的数组，其中每个元素都是一个包含5个int元素的数组。
与之等价的常规数组声明如下：
int twodee[10][5];
注意：
模板语法中，维的顺序与等价的二维数组相反。

2.使用多个类型参数
模板可以含有多个类型的参数。
希望类可以保存两种值，可以创建pair模板来保存两个不同的值。
{
    // pairs.cpp -- defining and using a Pair template
    #include <iostream>
    #include <string>
    template <class T1, class T2>
    class Pair
    {
    private:
        T1 a;
        T2 b;
    public:
        T1 & first();
        T2 & second();
        T1 first() const { return a; }
        T2 second() const { return b; }
        Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) { }
        Pair() {}
    };

    template<class T1, class T2>
    T1 & Pair<T1,T2>::first()
    {
        return a;
    }
    template<class T1, class T2>
    T2 & Pair<T1,T2>::second()
    {
        return b;
    }

    int main()
    {
        using std::cout;
        using std::endl;
        using std::string;
        Pair<string, int> ratings[4] =
        {
            Pair<string, int>("The Purpled Duck", 5),
            Pair<string, int>("Jaquie's Frisco Al Fresco", 4),
            Pair<string, int>("Cafe Souffle", 5),
            Pair<string, int>("Bertie's Eats", 3)
        };

        int joints = sizeof(ratings) / sizeof (Pair<string, int>);
        cout << "Rating:\t Eatery\n";
        for (int i = 0; i < joints; i++)
            cout << ratings[i].second() << ":\t "
                << ratings[i].first() << endl;
        cout << "Oops! Revised rating:\n";
        ratings[3].first() = "Bertie's Fab Eats";
        ratings[3].second() = 6;
        cout << ratings[3].second() << ":\t "
            << ratings[3].first() << endl;
    // std::cin.get();
    return 0; 
    }
}

3.默认类型模板参数
类模板的另一项新特性是，可以为类型参数提供默认值：
template <class T1, class T2 = int> class Topo {...};
如果省略T2的值，编译器将继续使用int:
Topo<double, double> m1;
Topo<double> m2;
标准模板库经常使用该特征，将默认类型设置为类。
虽然可以为类模板类型参数提供默认值，但不能为函数模板参数提供默认值。
然而可以为非类型参数提供默认值，这对于类模板和函数模板都是适用的。

14.4.6 模板的具体化
类模板和函数模板很类似，可以有隐式实例化、显式实例化和显式具体化，它们统称为具体化。模板以泛型的方式描述类，而具体化是使用具体的类型生成类声明。
1.隐式实例化
截至目前，本章的例子都是隐式实例化，即它们声明一个或多个对象，指出所需要的类型，编译器根据通用模板提供的处方生成具体的类定义。
ArrayTP<int, 100> stuff;
编译器在需要对象前，都不会生成类的隐式实例化：
ArrayTP<double, 30> * pt;
pt = new ArrayTP<double, 30>;
第二条语句导致编译器生类定义，并根据该定义创建一个对象。

2.显式实例化
当使用关键字template 并指出所需要的类型时，编译器将生成类声明(包括方法定义)。声明必须位于模板定义所在的名称空间之中。
下面的声明将ArrayTP<string, 100>声明为一个类：
template class ArrayTP<string, 100>;
在这种情况下，虽然没有创建或提及类对象，编译器也将生成类声明(包括方法定义)。和隐式实例化一样，也将根据通用模板来生成具体化。

3.显式具体化
显示具体胡是特定类型(用于替换模板中的泛型)的定义。
需要在为特殊类型实例化时，对模板进行修改，使其行为不同。这种情况下，可以创建显式具体化：
{
    假设已经为用于表示排序后数组的类(元素在加入时被排序)定义了一个模板：
    template <typaname T>
    class SortedArray
    {
        ...
    };
    假设模板使用>运算符对值进行比较。可以提供一个显式模板具体化，将采用为具体类型定义的模板，而不是为泛型定义的模板。
    当具体化模板和同样模板都与实例化请求匹配时，编译器讲使用具体化版本。
    具体化模定义的格式如下：
    template <> class Classname<specialized-type-name> {...};
    早期的编译器可能只能识别早期的格式：
    class Classname<specialized-type-name> {...};
    要使用新的表示法提供一个专供const char* 类型使用的SortedArray 模板，可以使用类型下面的代码：
    template <> class SortedArray<const char char*>
    {
        ...
    };
    其中的实现代码将使用strcmp()而不是>来比较组值。当请求const char*类型的Sortedrray模板时，编译器将使用上述专用的定义，而不是通用的模板定义。
    SortedArray<int> scores;
    SortedArray<const char *> dates;
}

4.部分具体化
C++还允许使用部分具体化，即部分限制模板的通用性。
例如，可以部分具体化给类型参数之一指定具体的类型：
template <class T1, class T2> class Pair {...};
template <class T1> class Pair<T2, int> {...};
关键字template后面的<>声明的时没有被具体化的类型参数。因此上述的第二个声明将T2具体化为int，但T1保持不变。
如果指定所有的类型，则<>内讲为空，这将导致显式具体化：
template <> class Pair<int, int> {...};
如果有多个模板可供选择，编译器将使用具体化程度最高的模板：
Pair<double double> p1;
Pair<double, int> p2;
Pair<int, int> p3;
也可以通过为指针提供特殊版本来部分具体化现有的模板：
template<class T>
class Feeb {...};
template<class T*>
class Feeb {...};
如果提供的类型不是指针，则编译器会使用通用版本，如果提供的是指针，则编译器会使用指针具体化版本：
Feeb<char> fb1;
Feeb<char *> fb2;
如果没有进行部分具体化，则第二个声明将使用通用模板，将T转换为char * 类型。
如果进行了部分具体化，则第二个声明将使用具体化模板，将T转换为char。
部分具体化使得能够设置各种限制：
template <class T1, class T2, class T3> class Trio{...};
template <class T1, class T2> class Trio<T1, T2, T3> {...};
template <class T1> class Trio<T1, T2*, T3*> {...};
给定上述声明，编译器将作出如下选择：
Trio<int, short, char *> t1;
Trio<int short> t2;
Trio<char, char *,char *> t3;

14.4.7 成员模板
模板可用作结构、类、或模板类的成员。
P475
上述定义将T\V\U用作模板参数。因为参数是嵌套的，因此必须使用如下的语法：
template <typename T>
    template <typename V>
而不能使用下面的语法：
template<typename T, typename V>

14.4.8 将模板用作参数
模板可以包含类型参数(typename T)和非类型参数(int n)，模板可以本身就是模板的参数。
{
    template <template <typename T> class Thing>
    class Creb
}
模板参数是：template <typename T> class Thing
其中：<typename T> class 是类型，Thing 是参数。

可以混合使用模板参数和常规参数：
template <template <template T> class Thing, typename U, typename V>
class Crab
{
private:
    Thing<U> s1;
    Thing<V> s2;
    ...
};
成员s1 s2可储存的数据类型为泛型，而不是用硬编码指定的类型。这要求将程序中nebula的声明修改成下面这样：
Creb<Stack, int, double> nebula;
模板参数T表示一种模板类型，而类型参数U和V你表示非模板类型。

14.4.9 模板类和友元
模板类声明也可以有友元。模板的友元分三类：
1.非模板友元：
2.约束模板友元：
3.非约束模板友元：

1.模板类的非模板友元函数
在模板类中将一个常规函数声明为友元：
template <class T>
class HasFriend
{
public:
    friend void counts();
    ...
};
上述声明使counts()函数成为模板所以实例化的友元。例如，它是hasFriend<int> 和 HasFriend<String>的友元
{
    count()函数不是通过对象调用的(它是友元，不是成员函数)，也没有对象参数。
    1.它可以访问全局对象；
    2.可以使用全局指针访问非全局对象；
    3.可以创建自己的对象；
    4.可以访问独立于对象的模板类的静态数据成员。
}
假设要为友元函数提供模板类参数，必须指明具体化：
template <class T>
class HasFriend
{
    Friend void report(HasFriend<T> &);
    ...
};
为理解上述代码的功能，声明一个特定类型的对象时，将生成的具体化：
HasFriend<int> hf;
编译器将用int替代模板参数T，因此友元的声明格式如下：
class Hadfriend<int>
{
    friend void report(HasFriend<int> &);
    ...
};
带HasFriend<int>参数的report()将成为HasFreind<int>类的友元。
带HasFriend<double>参数的report()将是report()的一个重载版本--它是Hasfriend<double>类的友元。
report()本身并不是模板函数，而只是使用一个模板作参数。这意味着必须要为使用的友元定义显式具体化：
void report(HasFriend<short> &) {...};
void report(HasFriend<int> &) {...};

2.模板类的约束模拟友元函数
使友元函数成为模板，具体地说，为约束模板做准备，要使类的每一个具体化都获得与友元匹配的具体化。这比模板友元复杂点。
{
    1.在类定义前声明每个模板函数：
    template <typename T> void counts();
    template <typename T> void report(T &);
    2.然后在函数中再次将模板声明为友元。这些语句根据类模板参数的类型声明具体化：
    template <typename TT>
    class HasFriendT
    {
        ...
        friend void counts<TT>();
        friend void report<>(HasFriend<TT> &);

    };
    声明中的<>指出这是模板具体化。对于report()，<>可以为空，因为可以从函数参数推断出如下模板类型参数：
    HasFriendT<TT>
    然而也可以这么用：
    report<HasFriendT<TT> >(HasFriendT<TT> &)
    但count()函数没有参数，因此必须使用模板参数语法(<TT>)来指明参数具体化。 TT是HasFriendT类的参数类型。
    同样理解声明的最佳方式也是设想声明一个特定具体化的对象时，它们将变成什么样子。
    假设声明了一个对象：
    HasFriendT<int> squack;
    编译器将用int替换TT，并生成下面的类定义：
    class HasFriendT<int>
    {
    ...
        friend void counts<int>();
        friend void report<>(HasFriendT<int> &);
    };
    基于TT的具体化将变为int,基于HasFriend<TT>的具体化类型将变为HasFriend<int>.
    因此，模板具体化counts<int>()和report<HasFriendT<int> >()将声明为HasFriend<int>类的友元。
    3.程序必须满足第三个要求是：
    为友元提供模板定义。
}

3.模板类的非约束模板友元函数：
通过在类内声明模板，可以创建非约束友元函数，即每个函数具体化都是每个类具体化的友元。
对于非约束友元，友元模板类型参数与模板类类型参数是不同的：
template <typename T>
class ManyFriend
{
    ...
    template <typename C, typename D> friend void show2(C &, D &);
};

14.4.10 模板别名(C++)
如果能为类型指定别名，将很方便，在模板设计中尤其如此。
可使用typedef为模板具体化指定别名：
typedef std::array<double, 12> arrd;
typedef std::array<int, 12> arri;
typedef std::array<std::String, 12> arrst;
arrd gallons;
arri days;
arrst months;
C++提供了一项新的功能--使用模板提供一系列别名，如下所示：
template<typename T>
    using arrtype = std::array<T,12>;
这将arrtype定义为一个模板别名，可使用它来指定类型，如下；
arrtype<double> gallons;
arrtype<int> days;
arrtype<std::string> months;
总之，arrtype<T>表示类型std::array<T,12>
C++11允许语法using =用于模板。
用于非模板时，这种语法与常规typedef等价：
typedef const char * pc1;
using pc2 = const char *;
typedef const int *(*)[10];
using pa2 = const int *(*)[10];
*/


/*
14.5 总结



*/