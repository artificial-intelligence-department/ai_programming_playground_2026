// Без STL

#include <iostream>

using namespace std;

int in_res(int in_a, int in_b, int op) {
    switch (op) {
        case 1: return in_a > in_b ? in_a - in_b : 0;
        case 2: return in_b > in_a ? in_b - in_a : 0;
        case 3: return in_a < in_b ? in_a : in_b;
        case 4: return in_a > in_b ? in_a : in_b;
        case 5: return in_a > in_b ? in_a - in_b : in_b - in_a;
    }
    return false;
}

void print_res(const int a[], const int b[]) {
    int count = 0;
    for (int op {1}; op <= 5; op++) {
        for (int x{1}; x < 101; x++) count += in_res(a[x], b[x], op);
        
        cout << count << endl;
        int printed = 0;
        for (int x{1}; x < 101; x++) {
            int k = in_res(a[x], b[x], op);
            for (int j {0}; j < k; j++) {
                if (printed > 0) cout << ' ';
                cout << x;
                printed++;
            }
        }
        cout << (op < 5 ? "\n\n" : "\n");
        count = 0;
    }
}

int main() {
    int a[101] {0};
    int b[101] {0};
    int n, m, x;

    cin >> n;
    for (int i {0}; i < n; i++) {
        cin >> x;
        a[x]++;
    }

    cin >> m;
    for (int i {0}; i < m; i++) {
        cin >> x;
        b[x]++;
    }

    print_res(a, b);
}