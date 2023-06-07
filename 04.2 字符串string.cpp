#include<iostream>
#include<cstring>
#include<string>

using namespace std;

int main(){
    char dog[] = {'a','b','c',' ','e','\0'};    // 带有\0结尾的才是字符串,长度为字符数量+1（空字符也算数量）
    char dog_1[] = "abc e"; // 定义一个字符串       sizeof()是6，strlen()是5 不计算空字符。
    // cout << sizeof(dog) << endl; 
    // cout << strlen(dog) << endl; 

    char a = 'a';    // 字符常量 长度为1
    char a_1[] ="a"; // 字符串常量 长度为2

    char charr[20];
    char charr1[20] = "baoji";
    char charr2[20] = "xian";
    /*
    cin >> charr;        // 一次只能输入一个单词，其余留在输入队列。遇到空格，制表符，换行符就停止并补充\0
    cin.getline(charr1,20);    // 一次读取一行的字符串，最后丢弃换行符 只能读取参数-1 长度的字符        更方便输入
    cin.get(charr2,20).get();        // 一次读取一行字符串，换行符仍在输入序列中,用.get()读取换行符。   更方便检查错误
    cin.clear(); // 恢复输入
    cout << charr1 << endl;
    cout << charr2 << endl;
    */

    string str[20];             //字符串数组    
    string str1 = "america";       //字符串
    string str2 = "chinese";    //字符串

    /*
    strcpy(charr1,charr2); // 将charr2复制到charr1中
    str1 = str2;           // 将str2复制到str1中

    strcat(charr1,charr2); // 将charr2加到charr1后
    str1 += str2;          // 将str2加到str1中

    cin.getline(charr1,20); // 输入字符串
    getline(cin,str1);      // 输入字符串

    cout << charr1 << endl; 
    cout << str1 << endl; 

    cout << strlen(charr1) << endl; // 字符串中字符数
    cout << str1.size() << endl;    // 字符串中字符数

    */
    for (int i = str1.size()-1; i >= 0; i--) // 倒序输出str1,str1总长度为str1.size(),但实际存储中位置-1
    {
        cout << str1[i] << endl;
    }
    

    system("pause");
    return 0;
}
