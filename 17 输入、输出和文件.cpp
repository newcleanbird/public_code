/*
17 输入和输出和文件
{
    1.c++输入和输出概述
    2.使用cout进行输出
    3.使用cin进行输入
    4.文件输入和输出
    5.内核格式化
}
*/

/*
17.1 c++输入和输出概述
*/

/*
17.2 使用cout进行输出

17.2.1 重载的<<运算符
    插入运算符(<<)被重置，使之能够识别c++所有的基本类型:
    {
        unsigned char;
        signed char;
        char;
        short;
        unsigned short;
        int;
        unsigned int;
        long;
        unsigned long;
        long long; (c++11)
        unsigned long long;
        float;
        double;
        long double;
    }
    对于上述每种数据类型，ostream类都提供了 operator<<()函数的定义
    函数返回一个指向ostream对象的引用，使得可以将输出连接起来：
    
    1.输出和指针
    ostream还提供了部分指针的类型的插入运算符函数：
    {
        const signed char*;
        const unsighed char*;
        const char*;
        void *;
    }
    C++使用指向存储位置的指针来表示字符串，指针的形式可以是:char数组名、显式的char指针 或 引用括起的字符串。
    方法使用字符串中的"终止空字符"来确定何时停止显式字符。
    {
        char name[20] = "Dudly Diddlemore";
        char * pn = "Violet D`Amore";
        cout << "Hello!";
        cout << name;
        cout << pn;
    }
    对于其他类型的指针，c++需要转换为 (void*)来打印地址的数值表示。即使用强制类型转换，将其转换为其他类型：
    {
        int eggs = 12;
        char * amount = "dozen"; 
        cout << &eggs << endl;              // 输出普通变量的地址
        cout << amount << endl;             // 输出字符串 "dozen"
        cout << &amount << endl;            // 输出指针amount的地址，并非字符串的地址(指针指向的地址)
        cout << (void *)amount << endl;     // 强制类型转换，显式字符串的地址
    }

    2.拼接输出
    插入运算符: << 返回值类型都是 ostream & 原型格式如下:
    Ostream & operator<<(type);
    运算符函数的返回值为调用运算符的对象，因此可以插入 拼接输出：
    cout << "China " << "will " << "gerat " << "great " << "again!" << endl;

17.2.2 其他ostream 方法
    类成员函数 put(); write(); 前者显式字符，后者显式字符串
    1.put() 
    {
        作用：显式一个字符(char)
        原型：
            ostream &  put(char);
        可以拼接输出：
            cout.put('I').put('t');
            cout.put(65); 将int类型的65 转化为char值，显式ASCII码为65的字符。
            cout.put(65.1); 将double类型的65.3转化为char值(65)，显式ASCII为65的值。
    }
    2.write()
    {
        作用：显示一个字符串(const char_type* s)
        模板原型：
            basic_ostream<charT, traits>& write(const char_type* e, streamsize n);
            第一个参数提高了字符串的地址，第二个参数指出要显示多少个字符。
        可以拼接输出：
            cout.write(state2, i) << endl;
        write()不会在遇到空字符时自动停止打印字符，知识打印指定数目的字符，即使超出了字符串的边界。
        write()还可以用于数值数据，将数字的地址转化强制转换为 char *，然后传递给它：
            long val = 560031841;
            cout.write( (char *) &val, sizeof (long));
            560031841作为4个独立的字节被传输，输出设备把每个字节作为ASCII码进行解释。
    }
    这不会将数字转换为相应的字符，而是传输内存中存储的位表示：

17.2.3 刷新缓冲区
    刷新缓冲区的条件：
    1.当缓冲区满时，将刷新(flush)缓冲区，把内容发送出去，并清空缓冲区，以存储新的数据。通常以512字节或其整数倍。
    2.将换行符发送到缓冲区后，将刷新缓冲区。
    3.使用控制符：flush(刷新缓冲区)；endl(刷新缓冲区，并插入一个换行符)；
    {
        cout << "Hello" << flush;
        cout << "Wait!" << endl;
        flush(cout); // 控制符也是函数,对插入运算符<<进行了重载
    }

17.2.4 用cout进行格式化
1.修改显示时使用的计数系统
    1.派生关系；
        ostream类 <-- ios类 <-- ios_base类
    2.ios_base类：
    ios_base类存储了描述状态的信息：
        一个类成员中某些位决定了使用的计数系统
        另一个成员决定了字符宽度
    通过控制符(manipulator)，可以控制整数时使用的计数系统
    通过使用ios_base的成员函数，可以控制字符宽度和小数位数。
    3.控制符调整显示的进制   二进制(B:Bonary)
    dec:十进制(Decimal system)
    hex:十六进制(H:Hexadecimal)
    oct:八进制(O:Octal number system)
    使用：
        cout << dec;切换为十进制
        cout << hex;切换为十六进制
        cout << oct;切换为八进制
2.调整字段宽度
    成员函数widyh()
    {
        int width();        // 返回字段宽度的当前设置
        int width(int i);   // 设置字段宽度为i,并将原宽度返回
    }
    width()方法只影响将显示的下一个项目，然后字段将恢复默认值。
    width是成员函数，必须用对象调用：
    {
        cout.width(12);
        cout << 12;
    }
    c++永远不会截断数据，如果试图在宽度为2的字段中打印一个7位值，c++将增宽字段，以容纳该数据。
    c++ 的原则：显示所有的数据比工整更重要。
    C++视内容重于形式
    默认右对齐
    c++默认用空格填充

3.填充字符
    默认填充字符位空格
    修改填充字符：成员函数：fill()
    cout.fill('*'); // 将填充字符改为星号；
    填充修改一直有效，直到再次修改

4.设置浮点数的显示精度
    浮点数精度取决于输出默认。
    默认模式：显示总位数
    定点模式：小数点后的位数
    科学模式：小数点后的位数

    成员函数precision()可以设置精度：
    cout.precision(2);

5.打印末尾的0和小数点
    ios_base类提供了一个setf()函数(用于set标记)，能够控制多种格式化特性。
    cout.setf(ios_base::showpoint); // 显示末尾的小数点，如果长度足够还将显示0 如：2.00000
    showpoint是ios_base类声明中定义的类级静态常量。
    因此在成员函数定义外使用时，需要加上作用域运算符(::)

6.再谈 setf()
    ios_base类有一个受保护的数据成员(控制格式化的各个方面，比如计数系统、是否显示末尾的0等)，打开一个标记称为设置标记(或位)，1开启，0关闭。
    位标记是编程开关。
    setf()函数有两个原型：
    1.fmtflags setf(fmtflags);
        fmtflags 是 bitmask 类型的typedef名。用于存储格式标记，在ios_base类中定义。
        该setf()版本是设置单个控制的格式信息
        {
            常量：                  含义：
            ios_base::boolalpha     输入和输出bool值，可以为true 或 flase
            ios_base::showbase      对于输出，使用c++基数前缀
            ios_base::showpoint     显示末尾的小数点
            ios_base::uppercase     对于16进制输出，使用大写字母，E表示法
            ios_base::showpos       在正数前面加上+
        }
        {
            使用示例：
            cout.setf(ios_base::uppercase); // 设置位16进制的输出
        }
        bitmask类型是一种用来存储各个位值的类型，它可以是整型、枚举，也可以是STL bitset容器。
        主要思想：每一位都是可以单独访问的，都有自己的定义。iostream使用bitmask来存储状态信息。
    2.fmtflags setf(fmtflags , fmtflags);
        setf()原型接受两个参数，并返回以前的设置：
        函数的重载格式用于设置由多位控制的格式选项。
        第一个参数包含所需要设置的fmtflags值。第二个参数指出要清除第一个参数中的哪些位。清除位(clearing the bit)
        {
            第一个参数：            第二个参数：                含义
            ios_base::dec           ios_base::basefield         基数10
            ios_base::oct           同上                        基数8
            ios_base::hex           同上                        基数16

            ios_base::fixed         ios_base::floatfield        定点计数法
            ios_base::scientific    同上                        科学计数法

            ios_base::left          ios_base::adjustfield       左对齐
            ios_base::right                                     右对齐
            ios_base::internal                                  符号或基数前缀左对齐、值右对齐
        }
        定点表示法：123.4   c:%f
        科学表示法：1.23e04 c:%e
            特征：
                精度指的是小数位数，而不是总位数
                显示末尾的是0
        {
            左对齐：
            ios_base::fmtflags old = cout.setf(ios::left, ios::adjustfield);
            恢复以前的设置：
            cout.setf(old, ios::adjustfield);
        }
    3.unsetf() 用于消除setf()的效果
    原型： 
        void unsetf(fmtflags mask);
        mask是位模式，mask中所有的位都设置位1，将使得对应的位被复原。
        即setf()将位设置为1，unsetf()设置为0
        {
            没有专门指示浮点数默认显示模式的标记：
            1.仅当只有定点位被设置时使用定点表示法；
            2.仅当只有科学位被设置时使用科学表示法
            3.如没有位被设置或两位都被设置时，将使用默认模式
        }
        {
            启用默认模式：
            cout.setf(0, ios_base::floatfield);
            或
            cout.unsetf(ios_base::floatfield);
        }
7.标准控制符
使用setf()不是进行格式化的、对用户最友好的方法，c++提供了多个控制符，能够调用setf()
{
    控制符：                    调用：
    boolalpha       setf(ios_base::boolalpha)
    noboolalpha     unset(ios_base::noboolalpha)
    showbase        setf()
}


*/      

/*
17.3 使用cin进行输入

*/

/*
17.4 文件输入和输出

*/

/*
17.5 内核格式化

*/