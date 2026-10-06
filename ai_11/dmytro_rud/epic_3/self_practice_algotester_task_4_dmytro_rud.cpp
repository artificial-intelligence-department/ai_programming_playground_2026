#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Оптимізація введення-виведення
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    const int TOTAL_SECONDS = 12 * 3600;
    vector<int> timeline(TOTAL_SECONDS + 1, 0);
    
    for (int i = 0; i < n; ++i) {
        int h1, m1, s1, h2, m2, s2;
        cin >> h1 >> m1 >> s1 >> h2 >> m2 >> s2;
        
        int start_sec = (h1 - 8) * 3600 + m1 * 60 + s1;
        int end_sec = (h2 - 8) * 3600 + m2 * 60 + s2;
        
        timeline[start_sec]++;
        timeline[end_sec]--;
    }
    
    int empty_seconds = 0;
    int current_voters = 0;
    
    for (int sec = 0; sec < TOTAL_SECONDS; ++sec) {
        current_voters += timeline[sec];
        if (current_voters == 0) {
            empty_seconds++;
        }
    }
    
    cout << empty_seconds << "\n";
    
    return 0;
}
