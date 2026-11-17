#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

    int n, m;

    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++){
        cin >> A[i];
    }

    cin >> m;
    vector<int> B(m);
    for (int i = 0; i < m; ++i) {
        cin >> B[i];
    }

    //Сортування для роботи з STL функціями
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    vector<int> res; //поожній вектор для запису результатів пунктів

    //Різниця N - M
    set_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(res));
    cout << res.size() << endl;
    for (int i : res) cout << i << " ";
    cout << endl << endl;
    res.clear();

    //Різниця M - N
    set_difference(B.begin(), B.end(), A.begin(), A.end(), back_inserter(res));
    cout << res.size() << endl;
    for (int i : res) cout << i << " ";
    cout << endl << endl;
    res.clear();

    //Перетин
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(res));
    cout << res.size() << endl;
    for (int i : res) cout << i << " ";
    cout << endl << endl;
    res.clear();

    //Об'єднання 
    set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(res));
    cout << res.size() << endl;
    for (int i : res) cout << i << " ";
    cout << endl << endl;
    res.clear();

    //Симетрична різниця 
    set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(res));
    cout << res.size() << endl;
    for (int i : res) cout << i << " ";
    cout << endl;

    return 0;
}
