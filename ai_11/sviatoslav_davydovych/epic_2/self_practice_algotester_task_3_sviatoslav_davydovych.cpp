/* Algotester: "Менші зліва, більші справа" 
https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/71093
Автор: Давидович Святослав 
Група: ШІ-11 
*/ 
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        cout << (l + r) << " ";
    }

    return 0;
}