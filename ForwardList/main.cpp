﻿//ForwardList
#include<iostream>
#include<ctime>
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
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;

#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;

#endif // DEBUG
	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	friend class ConstIterator;
	friend class Iterator;
};
int Element::count = 0;//статическую переменную можно проинициализировать толькза пределами класса

class ConstIterator
{
	Element* Temp;
public:
	ConstIterator(Element* Temp) :Temp(Temp)
	{
		cout << "ItConstractor:\t" << this << endl;

	}
	~ConstIterator()
	{
		cout << "ItDestractor:\t" << this << endl;
	}
	ConstIterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const ConstIterator& other) const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ConstIterator& other)const
	{
		return this->Temp != other.Temp;
	}
	const int& operator*()const //оператор разыменование
	{
		return Temp->Data;
	}
};

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "ItConstractor:\t" << this << endl;

	}
	~Iterator()
	{
		cout << "ItDestractor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const Iterator& other) const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int& operator*()	//оператор разыменование
	{
		return Temp->Data;
	}
};
class ForwardList
{
	Element* Head; //указатель на начальный элемент списка
	unsigned int size;
public:

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	const ConstIterator begin()const
	{
		return Head;
	}
	const ConstIterator end()const
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;//если список пуст то его голова указывает на ноль
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il) :ForwardList()
	{
		//begin() - возвращает итератор на начало контейнера
		//end() - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()//из конструктора копирования делегируем конструктор по умолчанию
		//для того чтобы конструктор копирования обнулял голову
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data); или*/
		*this = other; //в операторе присваивания написана процедура копирования, а конструктор копирования её просто вызывает 
	}
	//перенапишем конструктор переноса MOVE метод из за того чтобы пересоздать объект на месте вызова идля этого он обращается к конструктору
	ForwardList(ForwardList&& other) :ForwardList() 
	{
		*this = std::move(other);//тоже в конструкторе преноса повторно использует код оператора присваивания = 
		//move - это функция из пространства std
	}
	~ForwardList()
	{
		while (Head)pop_front();

		cout << "LDestructor:\t" << this << endl;
	}
	///------------------Operator-------------------
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this; //если тот список равен этому - тот оставить неизменным
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		return* this;
	}

	//---------------Move Metods------------------
	ForwardList& operator=(ForwardList&& other)//оператор присваивания принимает не константу и не ссылку
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		return *this;

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
		Head = new Element(Data, Head);


		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1)создаём новый элемент
		//Element* New = new Element(Data);
		//2)доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//По завершении этого цикла Temp указывает на последний элемент списка
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

	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		if (Index > size)return;
		//1)Доходим до элемента перед удаляемым
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//2)Запоминаем адрес удаляемого элемента
		Element* Erased = Temp->pNext;
		//3)исключаем удаляемый элемент из списка
		Temp->pNext = Temp->pNext->pNext;
		//4)
		delete Erased;
		size--;
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
	void reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		buffer.Head = nullptr;
	}
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
		cout << "Общее количество элементов:  " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat=left;
	//for (Element* Temp = left.Head; Temp; Temp = Temp->pNext)cat.push_back(Temp->Data);
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)cat.push_back(Temp->Data);
	
	return cat;
}


void print(int arr[])
{
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	/*for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;*/
}
void print(const ForwardList& list)
{
	for (const int& i : list)
	{
		//i *= 10;
		cout << i << tab;
	}
	cout << endl;
}

//#define BASE_CHACK
//#define OPERATOR_PLUS
//#define RANGE_BASED_FOR_ARRA
//#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHACK
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
	/*cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value,index);
	list.print();*/
	cout << "введите номер удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();

	/*ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();*/
#endif // BASE_CHACK

#ifdef OPERATOR_PLUS
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
	list1 = list1;
	cout << delimiter << endl;

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	cout << delimiter << endl;

	//ForwardList list3 = list1 + list2; //CopyConstractor
	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
#endif // OPERATOR_PLUS

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	//Range-based for
	for (int i : arr)     //синтаксис for который используется исключительно с диапазонами
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };

	/*for (int i : list)    //синтаксис for который используется исключительно с диапазонами
	{
		i *= 10;
		cout << i << tab;
	}*/
	cout << endl;
	print(list);
	list.print();
#endif // RANGE_BASED_FOR_LIST

	int n;
	cout << "Введите размер списка: "; cin >> n;

	clock_t start = clock();
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand()); //намного медленнее
		list.push_front(rand()%100);
	}

	clock_t end = clock();
	double delta = double(end - start) / CLOCKS_PER_SEC;

	cout << "список заполнен за :"<< delta <<"сек" << endl;
	//list.print();
	start = clock();
	ForwardList list2 = list;
	end = clock();
	delta = double(end - start) / CLOCKS_PER_SEC;
	cout << "список скопирован за "<< delta << endl;
	//list2.print();

}