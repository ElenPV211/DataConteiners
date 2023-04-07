﻿#include <iostream>
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
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) : Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		Iterator& operator++()   //Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}

		Iterator operator++(int) //Postfix increment
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		bool operator ==(const Iterator& other)const
		{
			return this->Temp == other.Temp;

		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp) :Temp(Temp)
		{
			cout << "RItConstructor:\t"<< this << endl;
		}
		~ReverseIterator()
		{
		    cout << "RItDestructor:\t"<< this << endl;
		}

		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator == (const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;

		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}


	};
	
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
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
			size++;
			return;
		}
			/*//1) создаём новый элемент
			Element* New = new Element(Data);
			//2) пристыковываем новый элемент к списку
			New->pNext = Head;
			//3) пристыковываем список к новому элементу
			Head->pPrev = New;
			//4) переводим голову на новый элемент
			Head = New;*/
			Head = Head->pPrev =  new Element(Data, Head);
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
			/*//1) создаём новый элемент
			Element* New = new Element(Data);
			//2) пристыковываем новый элемент к списку
			New->pPrev = Tail;
			//3) пристыковываем список к новому элементу
			Tail->pNext = New;
			//4) переводим голову на новый элемент
			Tail = New;*/
			
			/*Element* New = new Element(Data);
			
			New->pPrev = Tail;
			//3) пристыковываем список к новому элементу
			Tail->pNext = New;
			//4) переводим голову на новый элемент
			Tail = New;*/
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
			size++;
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
		/*//1)создаём новый элемент
		Element* New = new Element(Data);
		//2)пристыковываем новый элемент к списку
		New->pNext = Temp;//справа
		New->pPrev = Temp->pPrev;//слева
		//3)пристыковываем список к элементу
		Temp->pPrev->pNext = New;

		Temp->pPrev = New; */
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
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
		Temp->pNext->pPrev = Temp->pPrev;
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
//#define BASE_CHECK

void main()
{
	setlocale(0, "");

#ifdef BASE_CHECK
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
#endif // BASE_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	//list.reverse_print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend();++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}