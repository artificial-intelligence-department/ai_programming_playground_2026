#include <iostream>
#include <string>
using namespace std;
int main()
{
    long long N;
    cin >> N;
    cin.ignore(100000, '\n');
    long long counter = 0;
    string s;
    for (long long i = 0; i < N; i++) {
        getline(cin, s);
        
        for (long long j = 0; j < s.length(); j++) {
            if (s[j] == '#' &&  s[j - 1] != '#') {
                counter++;
            }
        }
    }
    

    cout << counter;

    return 0;
}