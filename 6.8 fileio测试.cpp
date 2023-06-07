#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main()
{
    /*
    // 文件输入
    ifstream inFile;
    inFile.open("fish.txt");
    if (!inFile.is_open())
    {
        exit (EXIT_FAILURE);
    }
    char wt[50];
    inFile >> wt;
    inFile.close();
    cout << wt << endl;

    // 指定文件名输入
    ifstream fin;
    string filename;
    // cin >> filename;
    getline(cin,filename);
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "fail" << endl;
        // exit (EXIT_FAILURE);
    }
    char line[81];
    fin.getline(line, 81);
    fin.close();
    cout << line << endl;
    */

    // 标准输入
    ifstream inFile;
    inFile.open("fish.txt");
    char value[50];
    while(inFile >> value)
    {
        cout << value << endl;
    }
    

    
    /*
    // 文件输出
    ofstream outFile;   // 指定文件
    outFile.open("fish.txt"); // 关联输出文件
    outFile << "Hellofile" << endl;
    outFile.close();        // 关闭文件6

    ofstream fout;      // 输入文件
    char filename[50];
    cin >> filename;
    fout.open(filename);
    fout.close();
    */

    system("pause");
    return 0;
    
}