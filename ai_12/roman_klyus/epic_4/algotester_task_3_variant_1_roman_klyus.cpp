#include <iostream>
#include <string>

using namespace std;

int main() {
    string text;
    int N;
    cin >> N;
    cin.ignore();
    int count = 0;

    for (int i = 0; i < N; i++) {
        getline(cin, text);
        for (int i = 0; i < text.length(); i++) {
            if (i != 0) {
                if ((text[i] == '#') && (text[i-1] != '#')) {
                    count += 1;
                }
            } else if (text[0] == '#') count += 1;
        }
    }
    cout << count << endl;
}