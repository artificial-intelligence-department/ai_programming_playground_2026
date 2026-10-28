/*
Назва задачі: Lab 3v1
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <string>

using namespace std;

int main() {

int n = 0;
cin >> n;

cin.ignore(10000, '\n');

char ch;
char previous = ' ';
int count = 0;

for (int i = 0; i < n; i++) {

    previous = ' ';

    while (cin.get(ch) && ch != '\n') {

        if (ch == '#' && previous != '#') {
        count++;
        }
    
    previous = ch;

    }
}

cout << count << endl;

return 0;

}