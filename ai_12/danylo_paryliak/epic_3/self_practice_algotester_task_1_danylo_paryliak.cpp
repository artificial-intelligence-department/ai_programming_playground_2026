#include <iostream>
#include <algorithm>  
#include <utility> 
using namespace std;

int main(){

    int n;
    cin >> n;

   pair <int,int> company[100000];
   

    for (int i = 0;i < n;i++) {
        cin >> company[i].first;
        company[i].second=i+1;
    }

    sort(company,company + n);

    for(int i = 0;i < n;i++){
        cout << company[i].second<<"  ";
    }

    return 0;
}