#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char buffer[105];
    cin >> buffer;

    int len = strlen(buffer);

    // Динамічне виділення пам'яті
    char* str = new char[len + 1];
    strcpy(str, buffer);

    char* unique = new char[26];
    int count = 0;


    for (int i = 0; i < len; i++) {
        bool exists = false;

        for (int j = 0; j < count; j++) {
            if (unique[j] == str[i]) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            unique[count] = str[i];
            count++;
        }
    }

    cout << count << endl;

    // Звільнення динамічної пам'яті
    delete[] str;
    delete[] unique;

    return 0;
}
