#include <iostream>
#include <string>
using namespace std;

int main()
{
    int i;
        cin >> i;
    string up, down;
    cin >> up;
    cin >> down;

    bool teeth = false;

    for(int b = 0; b < i; ++b)
        {
            if(up[b] == '1' && down[b] == '1')
            {
                teeth = true;
                break;
            }
        }
    if(teeth == true)
    {
            cout << "Yes";
    }
    else
    {
            cout << "No";
    }
}