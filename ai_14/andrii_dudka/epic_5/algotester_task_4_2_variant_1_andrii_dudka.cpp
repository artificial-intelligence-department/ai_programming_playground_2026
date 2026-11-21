#include <iostream>

using namespace std;

long long* read_set(int& size) {
    cin >> size;

    long long* values = new long long[size];
    for (int i = 0; i < size; ++i) {
        cin >> values[i];
    }

    for (int end = size - 1; end > 0; --end) {
        bool swapped = false;
        for (int i = 0; i < end; ++i) {
            if (values[i] > values[i + 1]) {
                long long temp = values[i];
                values[i] = values[i + 1];
                values[i + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return values;
}

void print_set(const long long values[], int size) {
    cout << size << '\n';
    for (int i = 0; i < size; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << values[i];
    }
    cout << '\n';
}

int difference(const long long a[], int n, const long long b[], int m,
               long long result[]) {
    int count = 0;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < m && b[j] < a[i]) {
            ++j;
        }
        if (j == m || a[i] != b[j]) {
            result[count++] = a[i];
        } else {
            ++j;
        }
    }
    return count;
}

int intersection(const long long a[], int n, const long long b[], int m,
                 long long result[]) {
    int i = 0;
    int j = 0;
    int count = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            ++i;
        } else if (b[j] < a[i]) {
            ++j;
        } else {
            result[count++] = a[i++];
            ++j;
        }
    }
    return count;
}

int unite(const long long a[], int n, const long long b[], int m,
          long long result[]) {
    int i = 0;
    int j = 0;
    int count = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            result[count++] = a[i++];
        } else if (b[j] < a[i]) {
            result[count++] = b[j++];
        } else {
            result[count++] = a[i++];
            ++j;
        }
    }
    while (i < n) {
        result[count++] = a[i++];
    }
    while (j < m) {
        result[count++] = b[j++];
    }
    return count;
}

int main() {
    int n_size = 0;
    int m_size = 0;
    long long* n = read_set(n_size);
    long long* m = read_set(m_size);
    long long* only_n = new long long[n_size];
    long long* only_m = new long long[m_size];
    long long* result = new long long[n_size + m_size];

    int only_n_size = difference(n, n_size, m, m_size, only_n);
    print_set(only_n, only_n_size);
    cout << '\n';

    int only_m_size = difference(m, m_size, n, n_size, only_m);
    print_set(only_m, only_m_size);
    cout << '\n';

    int size = intersection(n, n_size, m, m_size, result);
    print_set(result, size);
    cout << '\n';

    size = unite(n, n_size, m, m_size, result);
    print_set(result, size);
    cout << '\n';

    size = unite(only_n, only_n_size, only_m, only_m_size, result);
    print_set(result, size);

    delete[] result;
    delete[] only_m;
    delete[] only_n;
    delete[] m;
    delete[] n;
}

