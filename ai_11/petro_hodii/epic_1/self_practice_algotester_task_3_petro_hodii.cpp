#include <iostream>

using namespace std;

int main()
{
    int count;
    cin >> count;

    long long sum = 0;

    for(int i = 0; i < count; ++i){
        int current_number;
        cin >> current_number;
        sum += current_number - 1;
    }   

    cout << sum << endl;

    return 0;
}