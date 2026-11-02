#include <iostream>


using namespace std;

int main() {


    int n;
    cin >> n;


    char* upper = new char[n];
    for (int i = 0; i < n; ++i) {
        cin >> upper[i];
    }

    bool canChew = false;
    for (int i = 0; i < n; ++i) {
        char lower_teeth;
        cin >> lower_teeth;

        if (upper[i] == '1' && lower_teeth == '1') {
            canChew = true;
        }
    }

    if (canChew) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    delete[] upper;
    return 0;
}