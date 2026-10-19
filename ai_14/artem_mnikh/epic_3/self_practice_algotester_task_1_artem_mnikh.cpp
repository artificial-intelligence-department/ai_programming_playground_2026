/*Ku+Kyu 1141*/

#include <iostream>
#include <string>

using namespace std;

int ku2num(string number)
{
    int ku = 0;
    int kyu = 0;
    for (char n : number)
    {
        if (n == 'k') continue;
        if (n == 'u')
            ++ku;
        else
        {
            ++kyu;
            --ku;
        }
    }
    return ku * 2 + kyu;
}

string num2ku(int number)
{
    string result = "";
    for (int i = 1; i <= number >> 1; ++i) result += "ku";
    return number & 1 ? result + "kyu" : result;
}

int main()
{
    string ku1, ku2;
    cin >> ku1 >> ku2;
    int num1 = ku2num(ku1);
    int num2 = ku2num(ku2);
    cout << num2ku(num1 + num2);
}
