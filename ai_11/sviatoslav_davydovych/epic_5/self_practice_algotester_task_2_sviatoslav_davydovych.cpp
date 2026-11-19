/* 
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/70963
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


int main(){
    const int LIMIT = 100000;

    int a,b,c,k;
    cin >> a >> b >> c >> k;

    bool isSwap = false;
    if (c>b){
        int temp = b;
        b = c;
        c = temp;
        isSwap = true;
    }

    bool isPossible = (b-c)%(k+3)==0;

    if (!isPossible || (a==0 && c==0) || (a==1 && b ==1)){
        cout << "NO";
        return 0;
    }
    string sequence[100000]{};
    int meetCount = 0;
    int centringCount = (b-c)/(k+3);
    
    while(meetCount<centringCount){
        if (a==0){
            a+=k+2;
            b--;
            c--;
            centringCount++;
            sequence[meetCount] = "B R";
        } else{
            a--;
            b--;
            c+=k+2;
            sequence[meetCount] = (isSwap) ? "O R" : "O B";
        }
        meetCount++;
    }
    if (meetCount+b>LIMIT){
        cout << "NO";
        return 0;
    }
    
    cout << "YES\n" << meetCount+b << "\n";
    for (int i = 0; i<meetCount; i++){
        cout << sequence[i] << "\n";
    }

    for (int i = 0; i<b; i++){
        cout << "B R" << "\n";
    }

    return 0;
}