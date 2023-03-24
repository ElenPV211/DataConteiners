#include<iostream>
using namespace std;
#define tab "\t"

void FillRand(int arr[], const int n);
void FillRand(int** arr, const int rows, const int cols);
void Print(int arr[], const int n);
void Print(int** arr, const int rows, const int cols);

int* push_back(int arr[], int& n, int value);
int* push_front(int arr[], int& n, int value);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(0, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "¬ведите размер массива: "; cin >> n;
	int* arr = new int[n];
	FillRand(arr, n);
	Print(arr, n);
	int value;
	cout << "¬ведите добавл€емое значение "; cin >> value;

	//arr = push_back(arr, n, value);
	arr = push_front(arr, n, value);



	Print(arr, n);

	delete[]arr;
#endif // DYNAMIC_MEMORY_1
	int rows;
	int cols;
	cout << " ¬ведите количество строк: "; cin >> rows;
	cout << " ¬ведите количество столбцов: "; cin >> cols;
	int** arr = new int* [rows];//1)
	//2) выдел€ем пам€ть под строки, и адреса строк записываем в элементы массива указателей
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}



	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	//1)
	for (int i = 0; i < rows; i++)
	{
		delete[]arr[i];
	}
	//2)
	delete[]arr;

}
void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
	}
}
void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}
}

void Print(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}
void Print(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;

		}
		cout << endl;
	}
}

int* push_back(int arr[], int& n, int value)
{
	//1)—оздаЄм новый массив нужного размера
	int* buffer = new int[n + 1] {};
	//2)копируем всЄ содержимое исходного массива в новый массив
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) удал€ем исходный массив
	delete[] arr;
	//4)подмен€ем адрес исходного массива адресом нового массива:
	arr = buffer;
	//5) только послеэтого в конец массива 'arr' можно дописать ещЄ один элемент
	arr[n] = 123;
	//6) после добавлени€ элемента в массив, количество его элементов увеличиваетс€ 
	n++;
	return buffer;
}
int* push_front(int arr[], int& n, int value)
{
	int* buffer = new int[n + 1] {};

	for (int i = 0; i < n; i++)
	{

		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	arr = buffer;
	arr[0] = value;
	n++;
	return buffer;
}
