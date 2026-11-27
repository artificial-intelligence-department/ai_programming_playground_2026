
#include <iostream>
using namespace std;

struct Stem {
    int id;
    int space;
    bool used;
};

int main() {
    int n;
    cin >> n;

    Stem stems[100];
    for (int i = 0; i < n; i++) {
        stems[i].id = i + 1;
        cin >> stems[i].space;
        stems[i].used = false;
    }

    int last = 0;
    bool rising = false;

    for (int step = 0; step < n; step++) {
        int minSpace = 1000;
        for (int i = 0; i < n; i++)
            if (!stems[i].used && stems[i].space < minSpace)
                minSpace = stems[i].space;

        int best = -1;
        for (int i = 0; i < n; i++) {
            if (stems[i].used)
                continue;

            bool ok;
            if (rising)
                ok = (stems[i].space == minSpace);
            else if (step == 0)
                ok = true;
            else if (minSpace <= last)
                ok = (stems[i].space <= last);
            else
                ok = (stems[i].space == minSpace);

            if (ok) {
                best = i;
                break;
            }
        }

        stems[best].used = true;
        if (step > 0 && stems[best].space > last)
            rising = true;
        last = stems[best].space;

        if (step > 0)
            cout << " ";
        cout << stems[best].id;
    }
    cout << endl;
    return 0;
}
