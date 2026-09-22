#include <iostream>

int main(){
    double s_d, s_u, v;
    std::cin>> s_d>> s_u >> v;
    double v_u = v/2;
    double v_d = v*2;
    double t_u = s_u/v_u;
    double t_d = s_d/v_d;
    if (t_d<t_u){
        std::cout<< "Down";
    }else if (t_d>t_u){
        std::cout << "Up";
    }else {
        std::cout <<"Never mind";
    }
    return 0;
}