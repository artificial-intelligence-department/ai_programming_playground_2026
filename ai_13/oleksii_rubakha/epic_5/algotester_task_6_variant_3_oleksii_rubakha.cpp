#include <iostream>

int main(){
    int N; std::cin>>N;
    std::string s[100];
    for (int i = 0; i<N; i++){
        std::cin >> s[i];
    }

    int Q; std::cin>>Q;
    while(Q--){
        int x, y; std::cin>>x>>y;
        x--; y--;
        if(s[x][y] != '0') {
            std::cout<<"1"<<std::endl<<s[x][y]<<std::endl;
            continue;
        }

        bool digits[10] = {false};
        for (int i = 0; i<N; i++)
            if(s[i][y] != '0' && !digits[s[i][y]-'0'-1]) digits[s[i][y]-'0'-1] = true;
        for (int j = 0; j<N; j++)
            if(s[x][j] != '0' && !digits[s[x][j]-'0'-1]) digits[s[x][j]-'0'-1] = true;

        int count = 0;
        for (int i = 0; i<N; i++)
            if (!digits[i]) count++;
        
        std::cout<<count<<std::endl;
        bool first = true;
        for (int i = 0; i<N; i++)
            if (!digits[i]) {
                if(first) {
                    std::cout<<i+1;
                    first = false;
                }else std::cout<<" "<<i+1;
            }
        std::cout<<std::endl<<std::endl;
    }
    return 0;
}