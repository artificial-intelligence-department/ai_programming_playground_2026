
/*
    Найкращий акумулятор
    Рубаха Олексій
    ШІ-13
*/

#include <iostream>

int main(){
    int n; std::cin>>n;
    char fav; std::cin>>fav;
    std::string best = "";

    for (int i = 0; i<n; i++){
        std::string str; std::cin>>str;
        bool found = false;
        for (int i = 0; i<str.length(); i++)
            if (str[i] > fav){
                str.insert(str.begin()+i, fav);
                found = true;
                break;
            }
        if(!found) str+=fav;

        if (best.empty()) best = str;
        else if (str<best) best = str;
    }

    std::cout<<best;

    return 0;
}