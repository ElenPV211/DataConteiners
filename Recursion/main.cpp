#include<iostream>
using namespace std;

void elevator(int floor)
{
	if (floor <= 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "вы на  " << floor << " этаже" << endl;
	elevator(floor - 1); //гуляет по функции вычитая 1 пока не дойдёт до return
	cout << "вы на  " << floor << " этаже" << endl;
}
int factorial(int n)
{
	if (n < 0)return 0;
	/*if (n == 0)return 1;
	else return n * factorial(n - 1);*/
	return n == 0 ? 1 : n * factorial(n - 1);
}
double power(double a, int n)
{
	//a - основание степени
	//n - показатель степени
	/*if (n == 0)return 1;
	else if (n > 0)return a * power(a, n - 1);
	//else return 1 / a * power(a, n + 1);
	else return 1 / power(a, -n);*/
	return n == 0 ? 1 : n > 0 ? a * power(a, n - 1) : 1 / power(a, -n);
}
int f(int n)
{
	if (n == 0)return 0;
	if (n == 1 || n == 2)return 1;
	if (n>2)return f(n - 1) + f(n - 2);
	else return f(n + 2) - f(n + 1);
}
void main()
{
	setlocale(0, "");
	//cout << "Hello Recursion!";
	/*int n;
	cout << "Введите номер этажа: "; cin >> n;
	elevator(n);*/
	//main();
	/*int n;
    cout << "Введите число: "; cin >> n;
    cout << factorial(n) << endl;*/
	/*int a = 0, n = 0;
	cout << "Введите число: "; cin >> a;
	cout << "Введите степень: "; cin >> n;
	cout << a << " ^ " << n << " = " << power(a, n) << endl;*/
	
	int n = 0;
	cout << "Введите число: "; cin >> n;
	cout << f(n);
}