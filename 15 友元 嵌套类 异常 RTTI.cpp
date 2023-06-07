/*
15 友元、异常和其他
{
    1.友元
    2.嵌套类
    3.异常
    4.RTTI
    5.类型转换运算符
}
1.友元类、友元成员函数、嵌套类
2.异常、运行阶段类型识别（RTII）、改进后的类型转换控制
*/

/*
15.1 友元
友元类的所有方法都可以访问原始类的私有成员和保护成员，被赋予从外部访问类的私有部分的权限。提高了公有接口的灵活性。

15.1.1 友元类
遥控器并非电视机，电视机也并非遥控器，因此公有继承的 is-a 关系并不适用。
遥控器并非电视机的一部分，电视机也并非遥控器的一部分，因此 has-a 关系也不适用。
遥控器可以改变电视机的状态，表明应将Romote类作为Tv类的一个友元。
{
    类TV：可以用一组状态成员(描述电视各个方面的变量)
    1.开、关
    2.频道设置
    3.音量设置
    4.有线电视或天线调节模式
    5.TV协调或A/V输入
    friend class Remote; 使Remote 成为友元类
    友元声明可以位于公有、私有或保护部分，其所在的位置无关紧要。
}
{
    // tv.h -- Tv and Remote classes
    #ifndef TV_H_
    #define TV_H_

    class Tv
    {
    public:
        friend class Remote;   // Remote can access Tv private parts
        enum {Off, On};
        enum {MinVal,MaxVal = 20};
        enum {Antenna, Cable};
        enum {TV, DVD};

        Tv(int s = Off, int mc = 125) : state(s), volume(5),
            maxchannel(mc), channel(2), mode(Cable), input(TV) {}
        void onoff() {state = (state == On)? Off : On;}
        bool ison() const {return state == On;}
        bool volup();
        bool voldown();
        void chanup();
        void chandown();
        void set_mode() {mode = (mode == Antenna)? Cable : Antenna;}
        void set_input() {input = (input == TV)? DVD : TV;}
        void settings() const; // display all settings
    private:
        int state;             // on or off
        int volume;            // assumed to be digitized
        int maxchannel;        // maximum number of channels
        int channel;           // current channel setting
        int mode;              // broadcast or cable
        int input;             // TV or DVD
    };

    class Remote
    {
    private:
        int mode;              // controls TV or DVD
    public:
        Remote(int m = Tv::TV) : mode(m) {}
        bool volup(Tv & t) { return t.volup();}
        bool voldown(Tv & t) { return t.voldown();}
        void onoff(Tv & t) { t.onoff(); }
        void chanup(Tv & t) {t.chanup();}
        void chandown(Tv & t) {t.chandown();}
        void set_chan(Tv & t, int c) {t.channel = c;}
        void set_mode(Tv & t) {t.set_mode();}
        void set_input(Tv & t) {t.set_input();}
    };
    #endif
}
{
    // tv.cpp -- methods for the Tv class (Remote methods are inline)
    #include <iostream>
    #include "tv.h"

    bool Tv::volup()
    {
        if (volume < MaxVal)
        {
            volume++;
            return true;
        }
        else
            return false;
    }
    bool Tv::voldown()
    {
        if (volume > MinVal)
        {
            volume--;
            return true;
        }
        else
            return false;
    }

    void Tv::chanup()
    {
        if (channel < maxchannel)
            channel++;
        else
            channel = 1;
    }

    void Tv::chandown()
    {
        if (channel > 1)
            channel--;
        else
            channel = maxchannel;
    }

    void Tv::settings() const
    {
        using std::cout;
        using std::endl;
        cout << "TV is " << (state == Off? "Off" : "On") << endl;
        if (state == On)
        {
            cout << "Volume setting = " << volume << endl;
            cout << "Channel setting = " << channel << endl;
            cout << "Mode = "
                << (mode == Antenna? "antenna" : "cable") << endl;
            cout << "Input = "
                << (input == TV? "TV" : "DVD") << endl;
        }
    }

}
{
    //use_tv.cpp -- using the Tv and Remote classes
    #include <iostream>
    #include "tv.h"

    int main()
    {
        using std::cout;
        Tv s42;
        cout << "Initial settings for 42\" TV:\n";
        s42.settings();
        s42.onoff();
        s42.chanup();
        cout << "\nAdjusted settings for 42\" TV:\n";
        s42.settings();

        Remote grey;

        grey.set_chan(s42, 10);
        grey.volup(s42);
        grey.volup(s42);
        cout << "\n42\" settings after using remote:\n";
        s42.settings();

        Tv s58(Tv::On);
        s58.set_mode();
        grey.set_chan(s58,28);
        cout << "\n58\" settings:\n";
        s58.settings();
        // std::cin.get();
        return 0; 
    }
}

类友元是一种自然用语，用于表示一些关系。
如果不使用某些形式的友元关系，则必须将TV类的私有部分设置为公有的，或者创建一个笨拙的、大型类来包含电视机和遥控器。
这种方法无法反应一个事实：即同一个遥控器可用于多台电视机。

15.1.2 友元成员函数
可以选择仅让特定的类成员成为另一个类的友元，而不必让整个类成为友元，但这样做稍微有些麻烦。必须小心排列各种声明和定义的顺序。
让Roemote::set_chan() 成为Tv类的友元的方法是,在Tv类声明中将其声明为友元：
class Tv
{
    friend void Remote::set_chan(Tv & t, int c);
    ...
};
然而，要使编译器能处理这条语句，它必须知道Remote定义。意味着要将Remote的定义放到Tv的定义前面。
Remote的方法提到了Tv对象，而这意味着Tv定义应当位于Remote定义之前。
避开这种循环依赖的方法是，使用向前声明。
为此，需要在Remote定义前面插入下面的语句：
class Tv;
这样排列次序应如下：
class Tv;
class Remote {...};
class Tv {...};

通过在方法定义中使用关键字inline，使其成为内联方法。

15.1.3 其他友元关系
P494

15.1.4 共同的友元
使用友元的另一种情况是，函数需要访问两个类的私有数据。
可以是一个类的成员，同时是另一个类的友元。
但也可以把它作为两个的友元更为合理。
{
    class Analyzer;
    class Probe
    {
        friend void sync(Analyzer & a, const Probe & p);
        friend void sync(Probe & p, const Analyzer & a);
        ...
    };
    class Analyzer
    {
        friend void sync(Analyzer & a, const Probe & p);
        friend void sync(Probe & p, const Analyzer & a);
        ...
    };
    向前声明，可以使编译器看到Probe的类声明中的友元声明时，知道Analyzer是一种类型。
}

15.2 嵌套类
嵌套类：在另一个类中声明的类。
{
    通过提供新的类作用域来避免名称混乱。包含类的成员函数可以创建和使用被嵌套类的对象，仅当声明位于公有部分，才能在包含类的外面使用嵌套类，必须使用作用域解析运算符。
    
}


*/