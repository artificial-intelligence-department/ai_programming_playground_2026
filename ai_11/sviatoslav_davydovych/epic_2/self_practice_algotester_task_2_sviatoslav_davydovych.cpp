/* Algotester: "Вправи"
https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/40857
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n,k,m,p;

    cin >> n >> k >> m >> p;

    long long min = 0;
    for (int i = 0; i<k; i++){
        int l;
        cin >> l;
        min+=l;
    }
    long long max = min + (n-k)*m;

    if (((min-1)% p - min + max + 1)>=p) cout << "Yes";
    else cout << "No";

    return 0;
}