#include<iostream>
#include<string>
using namespace std;

int main(int argc,char *argv[],char *envp[]){
    string s,x;
    char a,b,c;
    while(cin)
    {
        getline(cin,s);
        cout << s << endl;
        if(s == "q")    break;
    }
    // cin >> a >> b >> c;
    // cout << s << endl << x << endl << a << endl <<  b  << endl << c << endl;

    system("pause");
    return 0;
}

// main函数有三个参数，argc、argv和envp，它的标准写法如下：
// int main(int argc,char *argv[],char *envp[])
// ** int argc，存放了命令行参数的个数。
// char argv[]，是个字符串的数组，每个元素都是一个字符指针，指向一个字符串，即命令行中的每一个参数。
// char envp[]，也是一个字符串的数组，这个数组的每一个元素是指向一个环境变量的字符指针。

