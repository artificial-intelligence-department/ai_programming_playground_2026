// Ідея: для палиці a і цілі T: k розламувань (a>>k), потім додаємо одиниці.
// Вартість g(T) = n*T + сума h_a(T), мінімум лише в точках T = a>>k.
// Події (T, зміна суми h) сортуємо і проходимо за зростанням T.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    int n; scanf("%d",&n);
    vector<pair<int,int>> ev;
    ev.reserve((size_t)n*31);
    for(int i=0;i<n;i++){
        int a; scanf("%d",&a);
        int K=31-__builtin_clz(a);
        int m=INT_MAX;
        for(int k=K;k>=0;k--){
            int v=a>>k;
            int val=k-v;
            if(val<m){
                ev.push_back({v, m==INT_MAX ? val : val-m});
                m=val;
            }
        }
    }
    sort(ev.begin(),ev.end());
    ll H=0, best=LLONG_MAX;
    for(size_t i=0;i<ev.size();){
        int T=ev[i].first;
        while(i<ev.size() && ev[i].first==T){ H+=ev[i].second; i++; }
        best=min(best,(ll)n*T+H);
    }
    printf("%lld\n",best);
}
