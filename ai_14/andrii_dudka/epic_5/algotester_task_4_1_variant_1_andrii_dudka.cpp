#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> read_set() {
    int size = 0;
    cin >> size;

    vector<int> values(size);
    for (int& value : values) {
        cin >> value;
    }

    sort(values.begin(), values.end());
    return values;
}

void print_set(const vector<int>& values, int size) {
    cout << size << '\n';
    for (int i = 0; i < size; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << values[i];
    }
    cout << '\n';
}

int main() {
    const vector<int> n = read_set();
    const vector<int> m = read_set();
    vector<int> result(n.size() + m.size());

    auto end = set_difference(n.begin(), n.end(), m.begin(), m.end(), result.begin());
    print_set(result, end - result.begin());
    cout << '\n';

    end = set_difference(m.begin(), m.end(), n.begin(), n.end(), result.begin());
    print_set(result, end - result.begin());
    cout << '\n';

    end = set_intersection(n.begin(), n.end(), m.begin(), m.end(), result.begin());
    print_set(result, end - result.begin());
    cout << '\n';

    end = set_union(n.begin(), n.end(), m.begin(), m.end(), result.begin());
    print_set(result, end - result.begin());
    cout << '\n';

    end = set_symmetric_difference(n.begin(), n.end(), m.begin(), m.end(), result.begin());
    print_set(result, end - result.begin());
}

