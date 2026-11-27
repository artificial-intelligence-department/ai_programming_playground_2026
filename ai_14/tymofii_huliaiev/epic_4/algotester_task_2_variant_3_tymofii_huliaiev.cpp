#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int a[1001];
    for (int i = 1; i <= n; ++i)
        {
        cin >> a[i];
        }

    int left = 1;
    int right = n;
    string result = "";
    
    while (true)
    {
        if (left == right)
        {
            result = "Collision";
            break;
        }
        if (left > right)
        {
            result = "Miss";
            break;
        }
        if (left + 1 == right)
        {
            result = "Stopped";
            break;
        }
        int move_left = a[left];
        int move_right = a[right];

        left += move_left;
        right -= move_right;
    }
    cout << left << " " << right << "\n";
    cout << result << "\n";
}