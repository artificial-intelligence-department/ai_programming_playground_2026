/*
Lab 6v1
Кузовніков В'ячеслав Євгенійович
Ші - 13
Варіант 1
*/


#include <iostream>
#include <string>

using namespace std;


void my_sort(string* w, int left, int right) {
    if (left >= right) return;
    
    string pivot = w[(left + right) / 2];
    int i = left;
    int j = right;
    
    while (i <= j) {
        while (w[i] < pivot) i++;
        while (w[j] > pivot) j--;
        
        if (i <= j) {
            string temp = w[i];
            w[i] = w[j];
            w[j] = temp;
            i++;
            j--;
        }
    }
    
    my_sort(w, left, j);
    my_sort(w, i, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0; 
    int k = 0;
    if (!(cin >> n >> k)) return 0;

    string* w = new string[n];

    for (int i = 0; i < n; i++) {
        cin >> w[i];
        for (char &c : w[i]) {
            c = tolower(c);
        }
    }


    my_sort(w, 0, n - 1);

    string ans = "";

    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && w[j] == w[i]) {
            j++;
        }
        
        int count = j - i;

        if (count >= k) {
            for (char c : w[i]) {
                bool exists = false;
                for (char a : ans) {
                    if (a == c) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    ans += c;
                }
            }
        }

        i = j;
    }


    int len = ans.length();
    for (int x = 0; x < len; x++) {
        for (int y = x + 1; y < len; y++) {
            if (ans[x] < ans[y]) {
                char temp = ans[x];
                ans[x] = ans[y];
                ans[y] = temp;
            }
        }
    }

    if (ans.length() == 0) {
        cout << "Empty!\n";
    } else {
        cout << ans.length() << "\n";
        for (int x = 0; x < ans.length(); x++) {
            cout << ans[x];
            if (x < ans.length() - 1) {
                cout << " ";
            }
        }
        cout << "\n";
    }

    delete[] w;
    return 0;
}