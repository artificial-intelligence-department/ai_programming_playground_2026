//арифметика
#include <iostream>
using namespace std;

struct Stack {
    char* arr;
    int topIdx;

    Stack(int capacity) {
        arr = new char[capacity];
        topIdx = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(char c) {
        arr[++topIdx] = c;
    }

    void pop() {
        if (topIdx >= 0) topIdx--;
    }

    char top() const {
        return arr[topIdx];
    }

    bool empty() const {
        return topIdx == -1;
    }
};

int main() {
    long long x, n, k;
    cin >> x >> n >> k;

    Stack st(n + k + 25);
    long long carry = 0;

    for (long long p = 0; p <= n + k - 2; p++) {
        long long L = (p - n + 1 > 0LL) ? (p - n + 1) : 0LL;
        long long R = (k - 1 < p) ? (k - 1) : p;
        long long cnt = R - L + 1;

        long long sum = cnt * x + carry;
        st.push(char('0' + (sum % 10)));
        carry = sum / 10;
    }

    while (carry > 0) {
        st.push(char('0' + (carry % 10)));
        carry /= 10;
    }

    while (!st.empty()) {
        cout << st.top();
        st.pop();
    }
    cout << '\n';

    return 0;
}