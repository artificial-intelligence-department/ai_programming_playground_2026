#include <iostream>
#include <math.h>

int main(){
    
    //Виведення значень а та b
    std::cout << "a=100 b=0.001" << std::endl;
    
    //Оголощення змінних a i b типу даних double
    const double a = 100;
    const double b = 0.001;
    //Оголошення змінних для проміжних результатів типу даних double
    double result, num_1, num_2, num, den;

    //Обчислення першої частини чисельника типу даних double
    num_1 = pow(a + b, 4);
    //Обчислення другої частини чисельника типу даних double
    num_2 = pow(a, 4) + (4*b*(pow(a,3))) + (6*(pow(a,2))*(pow(b,2)));
    //Обчислення чисельника типу даних double
    num = num_1 - num_2;
    //Обчислення знаменника типу даних double
    den = (4*a*(pow(b, 3))) + pow(b, 4);
    //Обчислення результату виразу типу даних double
    result = num/den;
    //Виведення результату виразу типу даних double
    std::cout << "double: " << result << std::endl;


    //Оголощення змінних a i b типу даних float
    const float a_ = 100;
    const float b_ = 0.001;
    //Оголошення змінних для проміжних результатів типу даних float
    float result_, num_1_, num_2_, num_, den_;

    //Обчислення першої частини чисельника типу даних float
    num_1_ = pow(a_ + b_, 4);
    //Обчислення другої частини чисельника типу даних float
    num_2_ = pow(a_, 4) + (4*b_*(pow(a_,3))) + (6*(pow(a_,2))*(pow(b_,2)));
    //Обчислення чисельника типу даних float
    num_ = num_1_ - num_2_;
    //Обчислення знаменника типу даних float
    den_ = (4*a_*(pow(b_, 3))) + pow(b_, 4);
    //Обчислення результату виразу типу даних float
    result_ = num_/den_;
    //Виведення результату виразу типу даних float
    std::cout << "float: " << result_ << std::endl;

}