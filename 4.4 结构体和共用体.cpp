#include<iostream>
#include<cstring>

using namespace std;

struct people   // 结构体 外部声明，也可以放在main()中，是内部声明。
{
    string name;
    int age;
    char sex[20];
    float length;
    float weight;
}people1,people2;

// 共用体   只能存储 int char float等 同时用其中之一，为了节约存储空间。
union QQid
{
    int id;
    char name; 
};

int main(){

    // 初始化结构体
    people s1 = {
        "songjiahao",
        22,
        "man",
        172,
        73    
    };
    people s2 = {"shijingyi",22,"woman",168,50};

    // 结构体数组
    people student[2] = {
        {"zzz",22,"man",180,65},
        {"lyh",22,"woman",160,50}
    };
    cout << student[0].name << endl; 

    union QQid QQ1 = {10847};
    QQ1.name = 'a';
    cout << QQ1.name << endl;

    system("pause");
    return 0;
}

