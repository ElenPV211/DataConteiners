//ForwardList
#include<iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n---------------------------------------------\n"

class Element
{
	int Data;       //значение элемента
	Element* pNext; //адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;

	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0;//статическую переменную можно проинициализировать толькза пределами класса


class ForwardList
{
	Element* Head; //указатель на начальный элемент списка
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;//если список пуст то его голова указывает на ноль
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//---------Adding elements: (добавление элементов)

	void push_front(int Data)
	{
		/*//1)создаём новый элемент
		Element* New = new Element(Data);
		//2)новый элемент должен указывать на начало списка
		New->pNext = Head;
		//3) В голову списка нужно поместить адрес нового элемента
		Head = New;
		*/
		Head =new Element(Data,Head);
		
		
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1)создаём новый элемент
		//Element* New = new Element(Data);
		//2)доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext !=nullptr)
		{
			Temp = Temp->pNext;
		}
		//По завершении этого цикла указывает на последний элемент списка
		//3)Вставляем новый элемент в конец списка:
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;
		//1)Создаём новый элемент
		Element* New = new Element(Data);
		//2)Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//3)Поместить элемент в список на нужную позицию
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;

	}

	//----------------Removing elements:
	void pop_front()
	{
		//1))запоминем адрес удаляемого элемента
		Element* Erased = Head;
		//2)Переводим голову на следующий элемент и исключаем удаляемый элемент из списка
		Head = Head->pNext;
		//3) удаляем элемент из пмяти
		delete Erased;
		size--;
	}
	void pop_back()
	{
		//1)доходим до предпоследнего элемента списка
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
			
		}
		//2) Удаляем последний элемент из памяти

		delete Temp->pNext;
		//3)зануляем адрес последнего элемента
		Temp->pNext = nullptr;
		size--;
	}

	//----------------Metods:---------------
	void print()const
	{
	/*Element* Temp = Head; //Temp-итератор.
	//Итератор это указатель при помощи которого можно получить доступ к элементам структуры
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//переходим на новый элемент
		}*/	
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;

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
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;

	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value,index);
	
	list.print();
	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	ForwardList list3 = list + list2;
	list3.print();

}