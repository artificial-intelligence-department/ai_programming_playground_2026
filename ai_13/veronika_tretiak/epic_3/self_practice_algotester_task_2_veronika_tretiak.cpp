#include <iostream> 
#include <string>

using namespace std;

int main(){
   int n, k;
   cin >> n >> k;

   char a[101];

   for(int i = 0; i < n * n; i++){
    cin >> a[i];
   }

   int answer = 0;

   for(int size = 1; size <= n; size++){
    for (int i = 0; i + size <= n; i++){
        for(int j = 0; j + size <= n; j++){
            int count = 0;
            for (int x = i; x < i + size; x++){
                for(int y = j; y < j + size; y++){
                    if (a[x * n + y] == '1'){
                        count++;
                    }
                }
            }
            if(count <= k){
                answer = size;
            }
        }
    }
   }
   cout << answer << '\n';
   return 0;

}