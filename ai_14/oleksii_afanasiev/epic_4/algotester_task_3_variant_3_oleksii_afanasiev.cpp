/*
Задача: Lab 3v3 (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    cin>>s;

    int count = 1;
    int N = s.length();

    for(int i = 1; i < N; i++)
    {
        if(s[i] == s[i-1]) count++;
        else if(count > 1) 
        {
            cout << s[i-1] << count;
            count = 1;
        }
        else cout << s[i-1];
    }

    if(count > 1) cout << s[N-1] << count;
    else cout << s[N-1];
}
