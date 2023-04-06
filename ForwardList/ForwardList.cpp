#include"ForwardList.h"
///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////------------Element---------/////////////////////////////////////////////
template<typename T>Element<T>::Element(T Data, Element<T>* pNext) : Data(Data), pNext(pNext)
{
	count++;
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;

#endif // DEBUG

}
template<typename T>Element<T>::~Element()
{
	count--;
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;

#endif // DEBUG
}
//////////////////////------------Element---------/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///----------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////---------ConstIterator---------/////////////////////////////////////////////

template<typename T>ConstIterator<T>::ConstIterator(Element<T>* Temp) :Temp(Temp)
{
	cout << "ItConstractor:\t" << this << endl;

}
template<typename T>ConstIterator<T>::~ConstIterator()
{
	cout << "ItDestractor:\t" << this << endl;
}
template<typename T>ConstIterator<T>& ConstIterator<T> ::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T>bool ConstIterator<T>::operator==(const ConstIterator& other) const
{
	return this->Temp == other.Temp;
}
template<typename T>bool ConstIterator<T>::operator!=(const ConstIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>const T& ConstIterator<T>::operator*()const //оператор разыменование
{
	return Temp->Data;
}
//////////////////////---------ConstIterator---------/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///--------------------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////---------Iterator---------/////////////////////////////////////////////
template<typename T> Iterator<T>::Iterator(Element<T>* Temp) :Temp(Temp)
{
	cout << "ItConstractor:\t" << this << endl;

}
template<typename T> Iterator<T>::~Iterator()
{
	cout << "ItDestractor:\t" << this << endl;
}
template<typename T> Iterator<T>& Iterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T> bool Iterator<T>:: operator==(const Iterator& other) const
{
	return this->Temp == other.Temp;
}
template<typename T> bool Iterator<T>::operator!=(const Iterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> T& Iterator<T>::operator*()	//оператор разыменование
{
	return Temp->Data;
}
////////////////////-----------Iterator---------/////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

///-----------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////----ForwardList---------/////////////////////////////////////////////
template<typename T>Iterator<T> ForwardList<T>::begin()
{
	return Head;
}
template<typename T>Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}
template<typename T>const ConstIterator<T> ForwardList<T>::begin()const
{
	return Head;
}
template<typename T>const ConstIterator<T> ForwardList<T>::end()const
{
	return nullptr;
}

template<typename T>ForwardList<T>::ForwardList()
{
	Head = nullptr;//если список пуст то его голова указывает на ноль
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(initializer_list<T> il) :ForwardList()
{
	//begin() - возвращает итератор на начало контейнера
	//end() - возвращает итератор на конец контейнера
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>ForwardList<T>::ForwardList(const ForwardList<T>& other) :ForwardList()//из конструктора копирования делегируем конструктор по умолчанию
//для того чтобы конструктор копирования обнулял голову
{
	/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data); или*/
	*this = other; //в операторе присваивания написана процедура копирования, а конструктор копирования её просто вызывает 
}
template<typename T>ForwardList<T>::ForwardList(ForwardList<T>&& other) :ForwardList()
{
	*this = std::move(other);//тоже в конструкторе преноса повторно использует код оператора присваивания = 
	//move - это функция из пространства std
}
template<typename T>ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();

	cout << "LDestructor:\t" << this << endl;
}
///------------------Operator-------------------
template<typename T>ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this == &other)return *this; //если тот список равен этому - тот оставить неизменным
	while (Head)pop_front();
	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);
	reverse();
	return*this;
}
template<typename T>ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other)//оператор присваивания принимает не константу и не ссылку
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
template<typename T>void ForwardList<T>::push_front(T Data)
{
	/*//1)создаём новый элемент
	Element* New = new Element(Data);
	//2)новый элемент должен указывать на начало списка
	New->pNext = Head;
	//3) В голову списка нужно поместить адрес нового элемента
	Head = New;
	*/
	Head = new Element<T>(Data, Head);


	size++;
}
template<typename T>void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr)return push_front(Data);
	//1)создаём новый элемент
	//Element* New = new Element(Data);
	//2)доходим до конца списка
	Element<T>* Temp = Head;
	while (Temp->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	//По завершении этого цикла Temp указывает на последний элемент списка
	//3)Вставляем новый элемент в конец списка:
	Temp->pNext = new Element<T>(Data);
	size++;
}
template<typename T>void ForwardList<T>::insert(T Data, int Index)
{
	if (Index == 0)return push_front(Data);
	if (Index > size)return;
	//1)Создаём новый элемент
	Element<T>* New = new Element<T>(Data);
	//2)Доходим до нужного элемента
	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
	//3)Поместить элемент в список на нужную позицию
	New->pNext = Temp->pNext;
	Temp->pNext = New;
	size++;
}
//----------------Removing elements:
template<typename T>void ForwardList<T>::pop_front()
{
	//1))запоминем адрес удаляемого элемента
	Element<T>* Erased = Head;
	//2)Переводим голову на следующий элемент и исключаем удаляемый элемент из списка
	Head = Head->pNext;
	//3) удаляем элемент из пмяти
	delete Erased;
	size--;
}
template<typename T>void ForwardList<T>::pop_back()
{
	//1)доходим до предпоследнего элемента списка
	Element<T>* Temp = Head;
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
template<typename T>void ForwardList<T>::erase(int Index)
{
	if (Index == 0)return pop_front();
	if (Index > size)return;
	//1)Доходим до элемента перед удаляемым
	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
	//2)Запоминаем адрес удаляемого элемента
	Element<T>* Erased = Temp->pNext;
	//3)исключаем удаляемый элемент из списка
	Temp->pNext = Temp->pNext->pNext;
	//4)
	delete Erased;
	size--;
}
//----------------Metods:---------------
template<typename T>void ForwardList<T>::reverse()
{
	ForwardList<T> buffer;//<T>это шаблонный список
	while (Head)
	{
		buffer.push_front(Head->Data);
		pop_front();
	}
	this->Head = buffer.Head;
	buffer.Head = nullptr;
}
template<typename T>void ForwardList<T>::print()const
{
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << "Общее количество элементов:  " << Element<T>::count << endl;
}
template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;
	//for (Element* Temp = left.Head; Temp; Temp = Temp->pNext)cat.push_back(Temp->Data);
	for (Element<T>* Temp = right.Head; Temp; Temp = Temp->pNext)cat.push_back(Temp->Data);

	return cat;
}
template<typename T>void print(T arr[])
{
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	/*for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;*/
}
template<typename T> void print(const ForwardList<T>& list)
{
	for (const T& i : list)
	{
		//i *= 10;
		cout << i << tab;
	}
	cout << endl;
}
/////////////////////------ForwardList----------///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
