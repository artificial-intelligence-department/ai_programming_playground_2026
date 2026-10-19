/*
Задача: Курфюрста жахів (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    int count_in = 0;
    int count_out = 0;
    string word;

    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> word;
        if(word == "In") count_in++;
        else count_out ++;

        if(count_out > count_in)
        {
            cout << "Error";
            return 0;
        }
    }

    if(count_in > count_out) cout << "Cunning elector";
    else cout << "Just a fantasy";


    return 0;
}
