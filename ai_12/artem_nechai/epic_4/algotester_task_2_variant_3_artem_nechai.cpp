#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    int arr[1000];
    
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }
    
    int pos1 = 1;
    int pos2 = N;
    
    while (true) {
        if (pos1 == pos2) {
            cout << pos1 << " " << pos2 << endl << "Collision";
            break;
        } else if (pos1 + 1 == pos2) {
            cout << pos1 << " " << pos2 << endl << "Stopped";
            break;
        } else if (pos1 > pos2) {
            cout << pos1 << " " << pos2 << endl << "Miss";
            break;
        }
        
        pos1 += arr[pos1-1];
        pos2 -= arr[pos2-1];
    }
    
    return 0;
}
