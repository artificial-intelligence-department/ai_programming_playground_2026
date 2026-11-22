#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;

    string* lines = new string[n];
    
    string dummy;
    getline(cin, dummy);

    for(int i = 0; i < n; ++i)
    {
        getline(cin, lines[i]);
    }

    int total_rituals = 0;

    for(int i = 0; i < n; ++i)
    {
        bool in_damaged_block = false;

        for(char c : lines[i])
        {
            if(c == '#')
            {
                if(!in_damaged_block)
                {
                    total_rituals++;
                    in_damaged_block = true;
                }
            }
            else
            {
                in_damaged_block = false;
            }
        }
    }
    
    cout << total_rituals << "\n";
    
    delete[] lines;
    
    return 0;
}