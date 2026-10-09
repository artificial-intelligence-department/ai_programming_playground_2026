/* Algotester: "Юний художник"
https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/40857
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin >> n >> m;

    int list[n+1][2];
    for (int i = 0; i < n; i++){
        list[i][0] = 0;
        list[i][1] = i+1;
    }

    int revert[m][3];
    for (int i = m-1; i>=0; i--){
        int l,r,c;
        cin >> l >> r >> c;

        revert[i][0] = l-1;
        revert[i][1] = r-1;
        revert[i][2] = c;
    }

    int c = 0;
    for (int i = 0; i<m && c!=n; i++){
        int j = revert[i][0];
        while(j<=revert[i][1]){
            int temp = j;
            j = list[j][1];

            if (list[temp][0]==0){
                list[temp][0]=revert[i][2];
                c++;
            }
            list[temp][1]=revert[i][1]+1;
        }
    }

    for (int i = 0; i<n; i++){
        cout << list[i][0] << " ";
    }

    return 0;
}