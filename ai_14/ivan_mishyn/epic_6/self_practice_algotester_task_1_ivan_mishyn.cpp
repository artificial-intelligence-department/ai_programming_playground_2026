#include <iostream>
using namespace std;


struct CityNode{
    CityNode* parent=nullptr;
    int size=1;
};
CityNode* findRoot(CityNode* node){
    if(node->parent==nullptr){
        return node;
    }
    else{
        return findRoot(node->parent);
    }
}
bool unite(CityNode* a, CityNode* b){
    CityNode* rootA = findRoot(a);
    CityNode* rootB = findRoot(b);
    if (rootA == rootB) return false;
    rootB->parent = rootA; 
    return true;
}
int main(){
    int n,m;
    cin>>n>>m;
    CityNode* cities = new CityNode[n];
    int components=n;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        if(unite(&cities[a-1], &cities[b-1])){
            components--;
        }
        cout<<components<<"\n";
    }
    delete[] cities;
    return 0;
}