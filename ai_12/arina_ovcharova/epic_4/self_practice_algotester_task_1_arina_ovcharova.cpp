// Ідея: опукла оболонка (алгоритм Ендрю), далі B = сума gcd(|dx|, |dy|) по сторонах.
// Векторний добуток рахуємо в __int128, різниці координат - у long long.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;

__int128 cross(const P&o,const P&a,const P&b){
    return (__int128)(a.first-o.first)*(b.second-o.second)
         - (__int128)(a.second-o.second)*(b.first-o.first);
}
ll edge(const P&a,const P&b){
    return __gcd(llabs(a.first-b.first), llabs(a.second-b.second));
}
int main(){
    int n; scanf("%d",&n);
    vector<P> p(n);
    for(auto&q:p) scanf("%lld %lld",&q.first,&q.second);
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    n=p.size();
    if(n==1){ puts("1"); return 0; }
    vector<P> h(2*n);
    int k=0;
    for(int i=0;i<n;i++){
        while(k>=2 && cross(h[k-2],h[k-1],p[i])<=0) k--;
        h[k++]=p[i];
    }
    for(int i=n-2,t=k+1;i>=0;i--){
        while(k>=t && cross(h[k-2],h[k-1],p[i])<=0) k--;
        h[k++]=p[i];
    }
    k--;
    if(k==2){ printf("%lld\n",edge(h[0],h[1])+1); return 0; }
    ll ans=0;
    for(int i=0;i<k;i++) ans+=edge(h[i],h[(i+1)%k]);
    printf("%lld\n",ans);
}