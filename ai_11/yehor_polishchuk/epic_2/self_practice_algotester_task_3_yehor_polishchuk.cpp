#include <iostream>
using namespace std;

int main() {
    const int MAX = 10001;
    bool john[MAX] = {false};
    bool bruce[MAX] = {false};

    int nj, nb;
    cin >> nj >> nb;

    for (int i = 0; i < nj; i++) {
        int a;
        cin >> a;
        john[a] = true;
    }
    for (int i = 0; i < nb; i++) {
        int a;
        cin >> a;
        bruce[a] = true;
    }

    int either = 0, both = 0;
    for (int i = 1; i < MAX; i++) {
        if (john[i] || bruce[i]) either++;
        if (john[i] && bruce[i]) both++;
    }

    cout << either << " " << both << endl;
    return 0;
}