#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    string s, t;
    cin >> s >> t;

    size_t l = s.length();
    cout << l << endl;

    for(size_t i = 0; i < l; i++)
    {
        int k = s.find(t[i]);
        cout << k + 1 << " ";

        s.erase(k, 1);
        s += t[i];
    }
    
    return 0;
}