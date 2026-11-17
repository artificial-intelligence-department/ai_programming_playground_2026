#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string words[100000];
string tmp[100000];     // тимчасовий масив для злиття

// сортує words[l..r) за зростанням
void merge_sort(int l, int r){

    if (r - l <= 1) return;           // 0 або 1 елемент вже відсортовані

    int mid = (l + r) / 2;
    merge_sort(l, mid);               // ліва половина
    merge_sort(mid, r);               // права половина

    int i = l, j = mid, k = l;        // злиття двох відсортованих половин
    while (i < mid && j < r){
        if (words[i] <= words[j]) tmp[k++] = words[i++];
        else tmp[k++] = words[j++];
    }
    while (i < mid) tmp[k++] = words[i++];
    while (j < r) tmp[k++] = words[j++];

    for (int p = l; p < r; p++){
        words[p] = tmp[p];            // повертаємо результат у words
    }
}

int main(){

    int N = 0, K = 0;
    cin >> N >> K;

    for (int i = 0; i < N; i++){
        cin >> words[i];
        for (int j = 0; j < words[i].size(); j++){
            words[i][j] = tolower(words[i][j]);
        }
    }

    merge_sort(0, N);                 // однакові слова стають поруч

    bool used[26] = {false};

    int i = 0;
    while (i < N){
        int j = i;
        while (j < N && words[j] == words[i]){
            j++;
        }
        if (j - i >= K){
            for (int p = 0; p < words[i].size(); p++){
                used[words[i][p] - 'a'] = true;
            }
        }
        i = j;
    }

    int M = 0;
    for (int c = 0; c < 26; c++){
        if (used[c]) M++;
    }

    if (M == 0){
        cout << "Empty!" << endl;
        return 0;
    }

    cout << M << endl;
    for (int c = 25; c >= 0; c--){
        if (used[c]) cout << char('a' + c) << " ";
    }
    cout << endl;

    return 0;
}