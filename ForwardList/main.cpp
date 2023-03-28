//ForwardList
#include<iostream>
using namespace std;
#define tab "\t"

class Element
{
	int Data;       //значение элемента
	Element* pNext; //адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head; //указатель на начальный элемент списка
public:
	ForwardList()
	{
		Head = nullptr;//если список пуст то его голова указывает на ноль
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//---------Adding elements: (добавление элементов)

	void push_front(int Data)
	{
		//1)создаём новый элемент
		Element* New = new Element(Data);
		//2)новый элемент должен указывать на начало списка
		New->pNext = Head;
		//3) В голову списка нужно поместить адрес нового элемента
		Head = New;
	}
	//Metods:
	void print()const
	{
		Element* Temp = Head; //Temp-итератор.
	//Итератор это указатель при помощи которого можно получить доступ к элементам структуры
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//переходим на новый элемент
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
}