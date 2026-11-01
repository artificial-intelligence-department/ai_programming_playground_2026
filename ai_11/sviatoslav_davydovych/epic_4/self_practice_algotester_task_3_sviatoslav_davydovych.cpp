/* 
Автор: Давидович Святослав
Група: ШІ-11
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/31
*/

#include <iostream>
#include <cmath>

using namespace std;

double maxSubSet(const double sub[], int n, double k){
    double max = sub[0]-k, min = sub[0]-k;
    double lastmax = max, lastmin = min;
    for (int i = 1; i<n; i++){
        double e = sub[i]-k;
        lastmax = fmax(lastmax+e, e);
        lastmin = fmin(lastmin+e, e);

        max = fmax(max, lastmax);
        min = fmin(min, lastmin);
    }

    return fmax(max, abs(min));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const double E = 0.0001;

    int n;
    cin >> n;

    double arr[n];
    cin >> arr[0];
    double min = arr[0];
    for (int i = 1; i<n; i++){
        cin >> arr[i];
        if (arr[i]<min) min = arr[i];
    }

    double range = 0;
    for (int i = 0; i<n; i++){
        arr[i]-=min;
        if (arr[i]>range) range = arr[i];
    }

    double l = 0;
    double r = range;
    double k, Fk, prev;
    int C = 0;
    do{
        prev = Fk;
        k = (r+l)/2;
        Fk = maxSubSet(arr,n, k);

        double Flk = maxSubSet(arr,n, k-E);
        double Frk = maxSubSet(arr,n, k+E);
        if (Flk<Frk) r = k;
        else l = k;
        C++;
    }
    while(abs(prev-Fk)>E);

    cout << Fk;
}