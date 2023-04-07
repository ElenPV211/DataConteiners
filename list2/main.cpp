#include <iostream>
using namespace std;
#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;//чтобы запись была короче иначе за классом вызывалось бы так:
	//Element* Head, Element* Tail
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		while (Head)pop_front();
		cout<< "LDestructor:\t" << this << endl;
	}
	//----------------Adding elements-----------------
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//1) создаём новый элемент
			Element* New = new Element(Data);
			//2) пристыковываем новый элемент к списку
			New->pNext = Head;
			//3) пристыковываем список к новому элементу
			Head->pPrev = New;
			//4) переводим голову на новый элемент
			Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//1) создаём новый элемент
			Element* New = new Element(Data);
			//2) пристыковываем новый элемент к списку
			New->pPrev = Tail;
			//3) пристыковываем список к новому элементу
			Tail->pNext = New;
			//4) переводим голову на новый элемент
			Tail = New;
		}
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index == size) { push_back(Data); return; }
		if (Index == 0) { push_front(Data); return; }
		if (Index > size)return;
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size- Index - 1; i++)Temp = Temp->pPrev;
		}
		//1)создаём новый элемент
		Element* New = new Element(Data);
		//2)пристыковываем новый элемент к списку
		New->pNext = Temp;//справа
		New->pPrev = Temp->pPrev;//слева
		//3)пристыковываем список к элементу
		Temp->pPrev->pNext = New;

		Temp->pPrev = New; 
		size++;
	}


	//---------------Removing elements:---------------
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		//1)Исключаем элемент из списка
		Head = Head->pNext;
		//2)удаляем элемент из памяти
		delete Head->pPrev;
		//3)Забываем про удаленный элемент
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
			return;
		}
		//1)Исключаем элемент из списка
		Tail = Tail->pPrev;
		//2)удаляем элемент из памяти
		delete Tail->pNext;
		//3)Забываем про удаленный элемент
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == size) { pop_back(); return; }
		if (Index == 0) { pop_front(); return; }
		if (Head == Tail)return pop_front();
		if (Index > size)return;
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		if (Temp == Tail)return pop_back();
		Temp->pPrev->pNext = Temp->pNext;
		delete Temp;
		Temp = nullptr;
		size--;

	}
	
	//---------------Metods-----------
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab  <<Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		    cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
        for (Element* Temp = Tail; Temp; Temp =Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

void main()
{
	setlocale(0, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "Введите индекс добавляемогоэлемента: "; cin >> index;
	cout << "Введите значение добавляемогоэлемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();

	int index2;
	cout << "Введите индекс удаляемого элемента: "; cin >> index2;
	list.erase(index2);
	list.print();
	list.reverse_print();

}