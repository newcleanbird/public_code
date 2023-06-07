#include<iostream>
using namespace std;

int main(){
    // 标准cout cin
    int temp ;
    cin >> temp;
    cout << "temp:" << temp <<endl;
    cout << "helloworld!" << endl;
    cout.setf(ios::boolalpha); // 设置一个标记，命令cout显示false和true

    // 键盘 io输入
    char ch;
    int count = 0;
    cin.get(ch);
    while (ch != '#') // 设置哨兵字符 #,遇到则结束输入
    {
        cout << ch;
        count ++ ;
        cin.get(ch);
    }
    
    // 文件输入（繁杂版）
    char ch;
    int count = 0;
    cin.get(ch);
    while (cin.fail() == false) // while (!cin.fail())     如果遇到EOF,则cin.fail()将返回true,中止输入。
    // while (cin) // 更具有一般性，并且可以检测磁盘故障等其他原因
    {
        cout << ch;
        ++count;
        cin.get(ch);
    }
    cin.clear(); // 清理EOF标记，否则无法继续输入。

    // 精简版
    while (cin.get(ch))
    {
        cout.put(ch); 
    };

    // 怀旧版
    int ch;
    ch = cin.get();
    while(ch != EOF)
    {
        cout.put(ch);
        ++count;
        ch = cin.get();
    }

    // 读取数字的循环
    int Max = 5;
    int golf[Max];
    for (int i = 0; i < Max; i++)
    {
        while (!(cin >> golf[i]))
        {
            cin.clear();
            while (cin.get() != '\n')
            {
                continue;
            }
            cout << "please enter a number: ";
        }
    }

    system("pause");
    return 0;
}


