/*
16 string类 和标准模板库
{
    1.string类
    2.智能指针模板类
    3.标准模板库
    4.泛型编程
    5.函数对象
    6.算法
    7.其他库：vector、valarray、array
}
*/ 

/*
标准C++String类
模板auto_ptr、unique_ptr 和 shared_ptr
标准模板库(STL)
容器类
迭代类
函数对象(functor)
STL算法
模板initializer_list
*/

/*
16.1 String类

16.1.1构造字符串
{
    size_type 是一个依赖于实现的整形，是在头文件string中定义的。
    string类将string::npos定义为字符串的最大长度，通常为unsigned int的最大轴。
    NBTS表示以空字符结束的字符串--传统的C字符串。    
}
{
    构造函数原型：
    string(const cahr * s)          将string对象初始化为s指向的 NBTS
    string(size_type n, char c)     创建一个包含n个元素的string对象，其中每个元素都被初始化为字符c
    string(const string & str)      将一个string对象初始化为string对象 str(复制构造函数)
    string()                        创建一个默认的string对象，长度为0(默认构造函数)
    string(const char * s, size_type n) 将string对象初始化为s指向的NBTS的前n个字符，即使超过了NBTS的结尾。
    template<class Iter> string(Iter begin, Iter end)   将string对象初始化为区间[begin, end]内的字符，其中begin 和 end 就像指针，用于指定位置，范围包括begin,但不包括end。
    string(const string & str, size_type pos = 0, size_type n = npos) 将一个string对象初始化为对象str中位置从pos开始到结尾的字符，或从位置pos开始的n个字符。
    string(string && str) noexcept c+11新增，将一个string对象初始化为string对象str，并可能修改str(移动构造函数)
    string(initializer_list<char> il)   c+11新增，将一个string对象初始化为初始化列表il中的字符。

    // 构造函数 具体使用：
    string one("China");
    string two(20, '$');
    string three(ont);
    string four;
    char alls[] = "all is well that ends well";
    string five(alls, 20);
    string six(all+6, alls + 10);               [begin,end),因此end指向被使用的最后一个位置的后一个位置。
    seven(&five[6], &five[10]);
    eight(four, 7, 16);

    c++11新增构造函数：
    string (string && str)类似于复制构造函数，导致新创建的string为str的副本。不将str视为 const，这些构造函数被称为移动构造函数。
    string (initializer_list<char> il) 可以将列表初始化语法用于string类。
    e.g.:
    string piano_man = {'L', 'I', 'S', 'Z'};


    // 重载运算符：
    cout << onr << endl; << 可以直接打印
    one += "Oops!";
    one += two;     重载+ 可以直接附加string对象、C风格字符串、char值等
    two = "Sorry! That was ";
    two = one;
    two = '?'       重载 = 可以string对象、C风格字符串、char值等赋给string对象
    three[0] = 'p'; 重载[] 可以直接访问string字符中的各个字符
}

16.1.2 string类输入
c风格字符串：
char info[100];          
cin >> info;            // 读取一个字
cin.getline(info, 100); // 读取一列，丢掉\n
cin.get(info, 100);     // 读取一列，留下\n
对于string对象，有两种：
string stuff;
cin >> stuff;           // 读取一个字
getline(cin, stuff);    // 读取一行，丢掉\n
两个版本的getline都有一个可选参数：以确定使用哪个字符来确定输入的边界：
cin.getline(info,100,':');
getline(cin, stuff, ':');
区别为:string 版本的getline将自动调整目标string的大小，使之刚好可以适应输入存储的数据。
函数形式：
cin.operator>>(fname);  // cin类方法
operator>>(cin, lname); // 独立函数


{
    strin版本的getline()从输入中读取字符，将有以下三种情况：
    1.到达文件尾。输入流的eofbit将被设置，fail()和eof()返回true
    2.遇到分界字符(\n)，将把分界字符从输入流中删除，但不存储它。
    3.读取的字符数达到最大允许值(string::npos 和 可供分配内存中较小的一个)，将设置输入流的failbit,方法fail()返回true。
}
{
    输入流有一个统计系统
    eofbit:遇到文件尾
    failbit:检测到输入错误
    badbit:出现无法识别的故障(硬盘故障)
    goodbit:一切顺利
}
string 版本的 >> ：不断读取，直到遇到空白字符停止并跳过空格(丢弃空格)，如果继续调用 >> 则正常输入下一个字符串，直到遇到分界符并将其丢弃。
空白字符：空格、换行符、制表符。即任何将其作为参数来调用isspace()时，该函数返回ture字符。

16.1.3 使用字符串
{
    比较字符串：
    一个对象位于另一个对象前面，视前者为小者。
    数字 < 大写字符 < 小写字母
    string snake1("cobra");
    string snake2("cora1");
    snake1 < snake2;
    snake1 == snake2;
    snake1 != snake2;
}
{
    确定字符串的长度；
    string::npos;       字符串可存储的最大字符数。
    snake1.size();      // 来自STL 
    snake1.length();    // 来自早期string类
}

{
    重载的find()方法：
    size_type find(const string & str, size_type pos = 0)const // 从字符串pos位置开始，查找子字符串(string )str,如果找到返回首次出现的索引，否则返回string::npos。
    size_type find(const char *s, size_type pos = 0)const // 从字符串pos位置开始，查找子字符串(char )s,同上
    size_type find(const char *s, size_type pos, size_type n) //从字符串pos位置开始，查找s的前n个字符组成的子字符串(char )s。同上
    size_type find(char ch, size_type pos = 0)const 从字符串pos位置开始，查找子字符(char )ch,同上。
    还提供了相关的方法： snake1.rfind("hark");
    rfind();            // 最后一次出现的位置
    find_first_of();    // 查找字符串中查找参数首次出现的位置。
    find_last_of();     // 最后一次出现的位置
    find_first_non_of();// 查找一个不包含在参数中的字符 
    find_last_not_of();
}
检测一个字符'h'是否在字符串中：if(snake1.find('h') != string::npos) npos变量是string类的静态成员，值是string对象能存储的最大字符串，索引值从0开始，比最大的索引值大1。
{
    +=运算符能够一个字符附加到字符串中
    badchars += letter;
}
{
    capacity()返回当前分配给字符串的内存块的大小
    reserve()请求内存块的最小长度
}
{
    c_str()返回一个c风格的字符串指针
}

*/

/*
16.2 智能指针模板类
为了解决，常规指针被释放时，指向的存储空间没有被释放的问题。（忘记使用delete，程序异常中止等等）
智能指针：
auto_ptr:       c++98加入，c++11摒弃
unique_ptr:
share_ptr:

16.2.1 使用智能指针
1.#include<memory>
2.
{
    普通指针：
    double * pd = new double;
    *pd = 25.5;
    智能指针：
    auto_ptr<double> pd(new double)
    *pd = 25.5;
}
{
    三种智能指针：
    auto_ptr<string> ps(new string);
    unique_ptr<double> pdu(new double);
    shared_ptr<string> pss(new string);
}

16.2.2 有关智能指针的注意事项：
错误使用 auto_ptr 有可能导致问题，当两个auto_ptr指向同一个对象时，将会试图删除这个对象两次。
{
    1.定义赋值运算符，进行深度复制、
    2.建立所有权的概念。对于特定的对象，只能有一个智能指针才能拥有它。当赋值时，将转让所有权。auto_ptr 和 unique_ptr 的策略。
    3.创建智能更高的指针，跟踪引用特定的对象的智能指针数。称为引用计数。赋值时+1，指着过期时-1，只有当最后一个指针过期时才调用delete。share_ptr的策略。
}

16.2.3 unque_ptr 为何优于 auto_ptr
程序试图将一个 unique_ptr赋给另一个时：
1.源unique_ptr是个临时右值，编译器允许。
2.unique_ptr将存在一段时间，编译器将禁止
{
    unique_ptr<string> pu1(new string "Hello!");
    unique_ptr<string> pu2;
    pu2 = pu1; // 不允许
    unique_Ptr<string> pu3;
    pu3 = unique_ptr<string> (new string "Yo!"); // 允许,将一个临时(没有名称)的unique_ptr字符串智能指针赋给pu3
}
{
    std::move()；使得能够将一个unique_ptr赋给另一个
    unique_ptr<string> ps1,ps2;
    ps1 = demo("Uniquely special");
    ps2 = move(ps1);
    ps1 = demo(" and more");
    unique_ptr 使用了c++11的移动构造函数 和 右值引用 来区分安全和不安全。
}
3.unique_ptr 有一个可用于数组的变体
{
    auto_ptr 使用 delete ,不用delete[],因此只能与new一起用，不能与 new[]一起用。shared_ptr也是
    unique_ptr 有使用 new[] 和 new 的两个版本：
    std::unique_ptr<double []>pda(new double(5)); 
}

16.2.4 选择智能指针
使用shared_ptr:
1.指针数组，使用一些辅助指针来标识特定的元素，最大值和最小值。
2.两个对象包含都指向第三个对象的指针；
3.STL容器包含指针。
*/

/*
16.3 标准模板类
STL 提供了一组表示：容器、迭代器、函数对象、算法 的模板。
1.能够构造各种容器(数组、队列、链表)
2.执行各种操作(搜索，排序，随机排列)
{
    容器：与数组类似的单元，存储若干个值。容器是同质的，存储的值的类型要相同。
    迭代器：遍历容器的对象，能够与遍历数组的指针类似，是广义指针。
    函数对象；类似于函数的对象，可以是类对象 或 函数指针(包括函数名，因为函数名被用作指针)
    算法：完成特定的任务（数组排序，列表查找特定值）
}
STL不是面向对象，而是泛型编程。

16.3.1 模板类 vector
矢量(vector)对应数组，而不是数学矢量。
计算矢量存储了一组可随机访问的值。
{
    1.创建vector对象
    vector<int> ratings(5);
    vector<double> scores(n); // 可以使用动态内存分配。
    2.将一个vector对象赋值给另一个
    3.使用[]来访问vector元素
}
{
    分配器：
    与string类相似，各种STL容器模板都接受一个可选的模板参数，该参数指定使用哪个分配器对象来管理内存。
    template <class T, class Allocator = allocator<T> >
        class vector {...}
    如果省略该模板，则容器模板将默认使用allocator<类>。 这个类使用new 和 delete
}

16.3.2 可对矢量执行的操作：
1.所有的STL容器都提供了一些基本方法：
{
    size():返回容器中元素数目
    swap():交换两个容器的内容
    begin():返回一个指向容器第一个元素的迭代器
    end():返回一个表示超过容器尾的迭代器
}

2.迭代器:
{
    迭代器：广义指针，可以是指针，也可以是一个可对其执行类似指针的操作--接触引用 和 递增 的对象。
    通过将指针广义化为迭代器，让stl能够为各种不同的容器类(包括那些简单指针无法处理的类)提供统一的接口。
    每个容器都定义了一个合适的迭代器，该迭代器的类型是一个名为 iterator 的 typedef，其作用域为整个类。
}

3.迭代器的使用：
{
    为vecto 的 double 类型规范声明一个迭代器：
    vector<double>::iterator pd;
    假设scores 是一个 vector<double>的对象：
    vector<double> scores;
    则可以使用迭代器pd执行这样的操作：
    pd = scores.begin();
    *pd = 22.3;
    ++pd;
}
C++11 自动类型推断：
{
    vector<double>::iterator pd = scores.begin();
    可以改为：
    auto pd = scores.begin();
}
超过结尾
{
    超过结尾(past-the-end)，是一种迭代器，指向容器最后一个元素的下一个元素。
    类似于指向c类型字符串后面的空字符，超过结尾是一个指向元素的指针(迭代器)。
    end()成员函数标识超过结尾的位置。
    begin() 和 end() 指向区间的起始处 和 区间中止处的后一个位置。
    显式容器的内容：遍历+打印
    for(pd = scores.begin(); pd != socres.end(); pd++)
    {
        cout << *pd << endl;
    }
}
vector模板类的方法：
{
    push_back() 将元素添加到矢量末尾；      scores.push_back(temp);
    erase()     删除矢量种给定区间的元素：  scores.erase(scores.begin(), scores.begin() + 2) 删除第一个和第二个元素,第一个(下标0)到第三个之前(下标2)，[0,2)即前两个 0，1
    insert()    参数(新元素插入位置（本身迭代器指示插入位置），迭代器左区间，迭代器右区间) 区间为另一个容器对象
    old_v.insert(old_v.begin(), new_v.begin() + 1, new_v.end()); // 插入到开头
    old_v.insert(old_v.end(), new_v.begin() + 1, new_v.end());   // 插入到末尾
}
STL文档使用[p1,p2)表示从p1 到 p2(不包括p2)的区间，区间[begin(), end()]将包括集合所有内容
区间[itl,it2)由迭代器 it1 和 it2 指定，范围为it1 到 it2(不包括it2)。

16.3.3 对矢量的可执行的其他操作：
STL从更广泛的角度定义了非成员函数来执行：搜素、排序、随机排序等
即不是为每个容器定义find()函数，而是定义了一个适用于所有容器类的非成员函数find()
vector的成员函数swap() 比非成员函数swap()高，但非成员函数能交换两个不同类型的容器内容。
{
    三个有代表性的 STL 函数：
    for_each():接受三个函数：前两个定义容器中区间的迭代器，指向函数的指针(一个函数对象)。函数将被指向的函数应用于容器区间中的各个元素。被指向的函数不能修改容器元素的值。
    {
        可以用for_each()代替不修改值的for循环：
        vector<Review>::iterator pr;
        for (pr = books.begin(); pr != books.end(); pr++)
            ShowReview(*pr);
        提换为：
        for_each(books.begin(), books.end(), ShowReview);
        可避免显式的使用迭代器变量。
    }
    random_shuffle():接受两个指定区间的迭代器参数，随机排列该区间中的元素。该函数要求容器类能随机访问。
    sort():容器支持随机访问。
    {
        版本1：接受两个定义区间的迭代器参数，并使用为存储在容器中的类型元素定义的<运算符，对区间中的元素进行操作。
        vectoe<intt> coolstuff;
        ...
        sort(coolstuff.begin(), coolstuff.end());
        版本2：前两个是区间，第三个是要使用的函数的指针(函数对象)
        bool WorseThan(const Review & r1, const Review & r2)
        {
            if (r1.rating < r2.rating)
                return true;
            else
                return false;
        }
        sort(books.begin(), books.end(), WorseThan); // 函数名就是函数指针(函数对象)
    } 
}

16.3.4 基于范围的for循环(c++11)
基于范围的for循环是为用于STL设计的。
double prices[5] = {4.99, 10.99, 6.87, 7.99, 8.49};
for(double x: prices)
    cout << x << std::endl;
括号内声明一个与存储对象相同的变量，然后指出容器的名称，接下循环体将遍历整个容器元素。
{
    for_each(books.begin(), books.end(), ShowReview);
    等价于：
    for(auto x : books) ShowReview();
    根据book的类型(vector<Review>)，编译器将自动推断x的类型为Review，而循环体依次将books中的每个Review传递给ShowReview()
}
基于范围的for循环可以修改容器的内容，指定一个引用参数。
void InflateReview(Review &r) {r.rating++;}
可使用如下循环对books的每个元素执行该函数：
for (auto & x : books) InflateReview(x);
*/

/*
16.4 泛型编程
STL是一种泛型编程。
    面向对象关注的是编程的数据
    泛型编程关注的是算法。
    共同特点是，抽象和创建可重用的代码。
泛型编程旨在编写独立于数据类型的代码。

16.4.1 迭代器
模板使得算法独立于存储的数据类型。                                  提供了通用的数据类型表示。
迭代器使得算法独立于使用的容器类型，并且独立于容器本身的数据结构。    遍历容器中的值的通用表示。

每个容器类都定义了相应的迭代器类型。迭代器可能是指针、对象等。不管实现是什么，都提供所需的操作。
每个容器都有一个超尾标记，当迭代器增加到超越容器最后一个值后，这个值将被赋给迭代器。
每个容器都有begin() end()
    begin():指向容器第一个元素的迭代器
    end():指向容器超尾位置的迭代器。

16.4.2 迭代器类型
STL定义了5种迭代器类型：输入迭代器、输出迭代器、正向迭代器、双向迭代器、随机访问迭代器
    1.输入迭代器：容器输入到程序    被程序用来读取容器中的信息。
    输入迭代器接触引用(*)：使程序能够读取容器中的值，但不一定能让程序修改值。
    需要输入迭代器的算法将不会修改容器中的值。
    输入迭代器是单向的，可以递增，不能倒退。

    2.输出迭代器：程序输出到容器    将信息从容器传输到迭代器。即程序的输出就是容器的输入。
    输出迭代器接触引用(*)：让程序修改容器值，但不能读取。

    3.正向迭代器：
    只能使用++遍历，总是按相同的顺序遍历一系列值。
    既可以使得能够读取和修改数据，也可以使得只读取数据。

    4.双向迭代器：
    具有正向迭代器的所有特征，同时支持两种递减运算符(前缀++i,后缀i--).

    5.随机访问迭代器：
    有些算法需要直接跳转到容器中的任何一个位置，即随机访问，需要随即迭代器。
    具有双向迭代器的所有特征，同时添加了支持随机访问的操作 和 用于对元素进行排序的关系运算符。

16.4.3 迭代器层次结构
输入迭代器、输出迭代器 -> 正向迭代器 -> 双向迭代器 -> 随机访问迭代器
每个迭代器都定义了一个类级typedef名称--iterator
vector<int>类的迭代器类型：vector<int>::iterator


16.4.4 概念、改进和模型
概念：正向迭代器是一系列要求，而不是类型。STL文献使用"概念"来描述一系列要求。
改进：概念可以具有类似继承的关系。如：双向迭代器继承了正向迭代器的功能。但不能将c++继承机制用于迭代器。有些STL使用"改进"来表示这种"概念"上的继承。
模型：概念的具体实现称为 "模型"。
1.将指针用作迭代器
    迭代是广义指针，指针满足所有的迭代器要求。
    迭代器是STL算法的接口，而指针是迭代器，因此STL算法可以使用指针来对基于指针的非STL容器进行操作。
    例如：可以将STL算法用于数组。
    STL sort()函数：接受指向容器第一个元素的迭代器和指向超尾的迭代器作为参数。
    {
        const int SIZE = 100;
        double Receipts[SIZE];
        sort(Receipts, Receipts + SIZE);
    }

STL提供了一些预定义迭代器。
    1.copy():可以将数据从一个容器复制到另一个容器，算法是以迭代器方式实现的。
    {
        int casts[10] = {6, 7, 2, 4, 11, 8, 7, 10, 5};
        vector<int> dice[10];
        copy(casts, casts + 10, dice.begin()); // 前两个参数指定范围[a, b),a最好是输入迭代器，b最好是输出迭代器。
    }
    copy()函数将覆盖目标函数中已有的数据，同时目标容器必须足够大，以便能够容纳被复制的元素。
    不能使用copy()将数据放到空矢量中。

    2.假设要将信息复制到显示器上。如果有一个表示输出流的迭代器，则可以使用copy()。
    STL提供了ostream_iterator模板。该模板是速出迭代器的一个模型，也是一个适配器。
    可以将一些其他接口转换为STL使用的接口。
    通过包含头文件 #include<iterator>来创建这种迭代器：
    {
        #include<iterator>
        ...
        ostream_itreator<int, char> out_iter(cont,  " ");
    }
    out_iter现在是一个接口，能够让你使用cout来显式信息。
    第一个模板参数(int)指出了被发送给输出流的数据类型。
    第二个模板参数(char)指出了输出流使用的字符类型(另一个可能参数值为 wchar_t)
    构造函数第一个参数(cout)指出了要使用的输出流，也可以是用于文件输出的流(17)。
    构造函数第二个参数(" ")指出了发送给输出流的每个数据项后面显式的分隔符。
    {
        使用迭代器：
        *out_iter++ = 15;
        对于常规指针，这意味着将15赋给指针指向的位置，然后指针+1。
        对于ostream_itreator，意味着将15和空格组成的字符串发送到cout管理的输出流中，并未下一个输出操作做好了准备。

        可以将copy()用于迭代器：
        copy(dice.begin(), dice.end(), out_iter);
        这意味着可以将dice容器的整个区间复制到输出流中，即显示容器的内容。
        
        也可以不创建命名的容器，直接构建一个匿名迭代器：
        copy(dice.begin(), dice.end(), ostream_iterator<int, char>(cout, " "));

        iterator还定义了一个istream_iterator模板，使istream输入可作为迭代器接口。它是一个输入迭代器概念的模型，可以使用两个istream_iterator对象来定义copy()的输入范围。
        copy(istream_iterator<int, char)(cin), istream_iterator<int, char>(), dice.begin());
        与ostream_itreator相同，istream_iterator也有两个参数。第一个参数指出了要读取的数据类型，第二个参数指出输入流使用的字符类型。
        使用构造函数参数cin意味着由cin管理的输入流，省略构造函数参数表示输入失败，因此上述代码从输入流中读取，直到文件结尾、类型不匹配、出现其他错误故障为止。
    }

2.其他有用的迭代器
1.reverse_iterator
对reverse_iterator执行递增会导致其递减
{
    反向显式内容：
    copy(dice.rbegin(), dice.rend(), out_iter);
    rbegin()、rend(),返回的类型是reverse_iterator
}
反向指针有特殊补偿，*rp将在*rp的当前值之前对迭代器进行接触引用。
rp指向位置6，*rp将是位置5的值。

2.3.4：三种迭代器通过将复制转换为插入，解决了插入而不是覆盖已有的内容的问题。
2.back_insert_iterator:将元素插入到容器尾部
3.front_insert_interator:将元素插入到容器的前端
4.insert_iterator:将元素插入到insert_iterator构造函数的参数指定的位置前面。

限制：
    back_insert_iterator 只允许在尾部快速插入的容器(指的是时间固定的算法)，如：vector
    front_insert_interator 允许在起始位置做时间固定的插入的容器类型。vector不满足，但queue满足
    insert_insert_iterator 没有这些限制，因此可以把信息插入到矢量的前端。

这些迭代器将容器类型作为模板参数，将实际的容器标识符作为构造函数参数。
    要为名为dice 的 vector<int>容器创建一个 back_insert_iterator
    back_insert_iterator<vector<int> > back_iter(dice);
必须声明容器类型的原因是，迭代器必须使用合适的容器方法。


16.4.5 容器种类
STL具有"容器概念"，"容器类型"。
    概念是具有名称(容器、序列容器、关联容器等)的通用类别
    容器类型是可用于创建具体容器对象的模板。
    11个容器类型分别是：
        deque、list、queue、priority_queue、stack、vector、map、multimap、set、multiset、bitset
    c++11 新增容器：
        forward_list、unordered_map、unordered_multimap、unordered_set 和 unordered_multiset，且不将bitset视为容器，而是独立的类别。

1.容器概念
容器概念：指定了所有STL容器都必须满足的一系列要求。
容器是存储其他对象的对象。类型必须是可复制构造的和可赋值的。只要类没有将复制构造函数和赋值运算符声明为私有或可保护的。

2.c++11 新增的容器要求：
复制构造和复制赋值以及移动构造和移动赋值的差别：
复制操作保留源对象，而移动操作可修改源对象，还可能转让所有权，而不做任何复制。
如果源对象是临时的，移动操作的效率将高于常规复制。

3.序列
包括：deque forward_list list queue priority_queue stack vector
数组和链表也都是序列

序列概念增加了迭代器至少是正向迭代器的要求，保证了元素将按照特定顺序排列，不会在两次迭代之间发生变化。
还要求元素按照严格的线性顺序排列，即存在第一个元素，最后一个元素，除第一个元素和最后一个元素外，每个元素前后都有一个元素。

    1.vector 数组

    2.deque 双端队列

    3.list 双向列表

    4.forward_list 单链表

    5.queue 队列

    6.priority_queue 优先队列

    7.stack 栈

    8.array 非容器，没有定义调整容器大小的操作， 如push() insert()，但很多STL算法适用于array对象。

16.4.6 关联容器


*/

/*
16.5 函数对象
16.5.1 函数符概念

16.5.2 预定义的函数符

16.5.3 自适应函数符和函数适配器

*/

/*
16.6 算法
16.6.1 算法组

16.6.2 预定义的函数符

16.6.3 STL 和 String类

16.6.4 函数和容器方法

16.4.5 使用STL
*/

/*
16.7 其他库


*/