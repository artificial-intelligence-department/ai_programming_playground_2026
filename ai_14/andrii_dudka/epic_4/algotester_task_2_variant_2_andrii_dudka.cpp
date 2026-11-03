#include <iostream>

using namespace std;

int main() {
    int a, b, c, n, new_count = 0;
    cin >> n;
    
    int* turple = new int[n];
    for (int i = 0; i < n; ++i) cin >> turple[i];
    
    cin >> a >> b >> c;
    
    for (int i = 0; i < n; ++i) {
        if (turple[i] != a && turple[i] != b && turple[i] != c) {
            new_count++;
        }
    }
    
    if (new_count < 2) {
        cout << 0 << endl;
        delete[] turple;
        return 0;
    }
    
    int* new_turple = new int[new_count];
    for (int i = 0, j = 0; i < n; ++i) {
        if (turple[i] != a && turple[i] != b && turple[i] != c) {
            new_turple[j] = turple[i];
            j++;
        }
    }
    
    delete[] turple;

    int* final_turple = new int[new_count - 1];
    for (int i = 0; i < new_count - 1; ++i) final_turple[i] = new_turple[i] + new_turple[i + 1];
    delete[] new_turple;
    
    
    cout << new_count - 1 << endl;
    for (int i = 0; i < new_count - 1; ++i) cout << final_turple[i] << " ";
    
    cout << endl;

    delete[] final_turple;
    return 0;
}