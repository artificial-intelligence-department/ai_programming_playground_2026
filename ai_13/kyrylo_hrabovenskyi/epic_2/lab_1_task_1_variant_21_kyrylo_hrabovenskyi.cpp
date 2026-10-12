/* 
Лабораторна робота 1 варіант 21 
Грабовенський Кирило ШІ-13 task 1
*/
#include <iostream> 

using namespace std;

int main()
{
	cout << "For double\n"; // Виведення текстового заголовка для блоку double

	double a_d = 100; // a_d значить а яке є в типі double 
	double b_d = 0.001;

	double first_task_d = pow(a_d - b_d, 4); // Обчислення (a - b) у 4-му степені
	double second_task_d = pow(a_d, 4) - 4 * pow(a_d, 3) * b_d; // Обчислення перших двох членів розкладу: a^4 - 4*(a^3)*b
	double third_task_d = second_task_d + 6 * pow(a_d, 2) * pow(b_d, 2); // Додавання третього члена розкладу: + 6*(a^2)*(b^2)
	double forth_task_d = first_task_d - third_task_d; // Фінальне значення чисельника: віднімання виразів
	//знаменника 
	double fifth_task_d = pow(b_d, 4) - 4 * a_d * pow(b_d, 3); // Обчислення знаменника виразу: b^4 - 4*a*(b^3)
	//результат для double 
	double result_d = forth_task_d / fifth_task_d; // Ділення чисельника на знаменник
	cout << result_d; // Виведення фінального результату для типу double

	cout << "\nfor float\n"; // Виведення текстового заголовка для блоку float
	float a_f = 100; // Змінна 'a' типу float
	float b_f = 0.001; //обчислення чисельника 
	float first_task_f = pow(a_f - b_f, 4); // Обчислення (a - b) у 4-му степені для типу float
	float second_task_f = pow(a_f, 4) - 4 * pow(a_f, 3) * b_f; // Обчислення a^4 - 4*(a^3)*b для типу float
	float third_task_f = second_task_f + 6 * pow(a_f, 2) * pow(b_f, 2); // Додавання третього члена розкладу для типу float
	float forth_task_f = first_task_f - third_task_f; // Фінальне значення чисельника для типу float
	//знаменника 
	float fifth_task_f = pow(b_f, 4) - 4 * a_f * pow(b_f, 3); // Обчислення знаменника виразу для типу float
	//результат для float 
	float result_f = forth_task_f / fifth_task_f; // Ділення чисельника на знаменник для типу float
	cout << result_f; // Виведення фінального результату для типу float
}