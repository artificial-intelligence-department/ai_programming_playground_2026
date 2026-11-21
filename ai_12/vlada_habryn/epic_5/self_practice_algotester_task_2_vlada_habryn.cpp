#include <iostream>
#include <string>
using namespace std;
int main() {
    int n;
    cin >> n;
    int p[100001];
    int rank[100002];
    for (int i = 0;i<n;i++){
        cin >> p[i];
        rank[p[i]] = i + 1;
    }
    rank[n + 1] = 0;
    string result(n, 'a');
    int letter = 'a';
    for (int i = 1; i<n; i++) {
         if (rank[p[i - 1] + 1] > rank[p[i] + 1]){
            letter++;
        }
        result[p[i] - 1] = letter;
    }
    if (letter>'z'){
        cout<<"-1";
        return 0;
    }
    cout<<result;
    return 0;
}
