#include<iostream>
#include<ctime>

using namespace std;

#define Byte char; //所有Byte都替换为char
typedef char byte; // byte是char的别名。 比#define 更好

int main(){
    // 标准for
    for (int i = 0; i <= 10; i++) 
    {
        cout  << i << endl;
    }

    // while
    char name[] = "china";
    int i = 0;
    while(name[i])
    {
        cout << name[i] << endl;
        i++;
    }

    // do while 
    int n;
    do
    {
        cin >> n;
    }while(n<7);

    // 基于范围的for循环
    double prices[5] = {4.99, 10.99, 6.87, 7.99, 8.49};
    for (double x : prices)
    {
        cout << x << endl;
    }
    // 需要修改变量
    for(double &x : prices)
    {
        x = x*0.8;
        cout << x << endl;
    }

    // 直接初始化列表
    for (int x : {3,5,2,8,6})
    {
        cout << x << " ";
    }
    cout << endl;

    // ?
    int a = 1,b = 2;
    int c = a > b ? a : b; 

    char  choice;
    cin >> choice;
    switch (choice)
    {
        case 'a' : cout << "\a\n";
                 break;
        case 'b' : cout << choice;
                 break;
        default : cout << "try again" << endl;
    }

    enum {red, orange, yellow, green, blue, violet, indigo}; // 0~6

    int code;
    cin >> code;
    while (code >= red && code <= indigo)
    {
        switch(code)
        {
            case red    : cout << "red"; break;
            case orange : cout << "orange"; break;
            case yellow : cout << "yellow"; break;
            case green  : cout << "green"; break;
            case blue   : cout << "blue"; break;
            case violet : cout << "violet"; break;
            case indigo : cout << "indigo"; break;
        }
        cout << "Enter color code 0 ~ 6";
        cin >> code;
    }

    // goto 直接跳转到标记处

    goto pairs;
    pairs: cout << "succeed" << endl;

    system("pause");
    return 0;
}


