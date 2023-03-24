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
	cout << "������� ������ �������: "; cin >> n;
	int* arr = new int[n];
	FillRand(arr, n);
	Print(arr, n);
	int value;
	cout << "������� ����������� �������� "; cin >> value;

	//arr = push_back(arr, n, value);
	arr = push_front(arr, n, value);



	Print(arr, n);

	delete[]arr;
#endif // DYNAMIC_MEMORY_1
	int rows;
	int cols;
	cout << " ������� ���������� �����: "; cin >> rows;
	cout << " ������� ���������� ��������: "; cin >> cols;
	int** arr = new int* [rows];//1)
	//2) �������� ������ ��� ������, � ������ ����� ���������� � �������� ������� ����������
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
	//1)������ ����� ������ ������� �������
	int* buffer = new int[n + 1] {};
	//2)�������� �� ���������� ��������� ������� � ����� ������
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) ������� �������� ������
	delete[] arr;
	//4)��������� ����� ��������� ������� ������� ������ �������:
	arr = buffer;
	//5) ������ ���������� � ����� ������� 'arr' ����� �������� ��� ���� �������
	arr[n] = 123;
	//6) ����� ���������� �������� � ������, ���������� ��� ��������� ������������� 
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
