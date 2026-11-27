#include <iostream>

using namespace std;
const int MAXN = 1000001;

long long findNSD(long long a, long long b) {
    while (b != 0) {
         long long t = a % b;
         a = b;
        b = t;
    }
    return a;
}
struct NSDStack {
    int size=0;
    long long val[MAXN];
    long long nsd_at[MAXN];

    bool empty() const {
        return size == 0;
    }
    void push(long long x) {
        size++;
        val[size] = x;
        if (size == 1) {
            nsd_at[size] = x;
        } else {
            nsd_at[size] = findNSD(nsd_at[size - 1], x);
        }
    }
    void pop() {
        if (size > 0) {
            size--;
        }
    }
    long long top() const {
        return val[size];
    }
    long long nsd() const {
        return nsd_at[size];
    }
};

int main() {
    NSDStack st;
    int n;
    cin>>n;
    for (int i = 0; i < n; i++) {
        char action;
        cin >> action;

        if (action == '+') {
            long long x;
            cin >> x;
            st.push(x);
        } else if (action == '-') {
            st.pop();
        } else if (action == '?') {
            cout << st.nsd() << '\n';
        }
    }
    return 0;
}