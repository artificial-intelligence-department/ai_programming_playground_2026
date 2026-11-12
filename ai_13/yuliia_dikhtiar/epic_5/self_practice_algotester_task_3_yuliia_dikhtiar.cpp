/*
Назва задачі: Найкращий акумулятор
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <string>

using namespace std;

string insertLetter(string name, char letter) {
    size_t position = 0;

    while (position < name.size() && name[position] <= letter) {
        position++;
    }

    name.insert(position, 1, letter);
    return name;
}

int main() {
    int n;
    char letter;
    cin >> n >> letter;

    string bestName;

    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;

        string newName = insertLetter(name, letter);

        if (i == 0 || newName < bestName) {
            bestName = newName;
        }
    }

    cout << bestName << '\n';

    return 0;
}