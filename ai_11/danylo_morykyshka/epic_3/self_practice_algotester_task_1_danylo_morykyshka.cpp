//Складний екзамен

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;
    string text = to_string(n);
    bool hasfound = false;
    for(int i = 0; i < text.size();i++)
    {
        if(text[i] == '4' && text[i + 1] == '7'){
            cout << "YES";
            hasfound = true;
            break;
        }
    }
    if(!hasfound){
        cout << "NO";
    }

}