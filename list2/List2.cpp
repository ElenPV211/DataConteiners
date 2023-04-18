#include "List2.h"

//-----------------------Class definition - определение класса--------------------------
///////////////////////////////////////////////////////////////////////////
//////////////////////////------Element-----------////////////////////////
template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}
//////////////////////////------Element-----------////////////////////////
///////////////////////////////////////////////////////////////////////////

///----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
////////////////////////------ConstIterators-----------////////////////////////

template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()   //Prefix increment
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int) //Postfix increment
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

///---------------------------------------------------------------------------

template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator:: operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator  List<T>::ConstReverseIterator:: operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator:: operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator  List<T>::ConstReverseIterator:: operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

///---------------------------------------------------------------------------

template<typename T>bool List<T>::ConstBaseIterator::operator ==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator !=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

////////////////////////------ConstIterators-----------////////////////////////
///////////////////////////////////////////////////////////////////////////////

///--------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
////////////////////////------Iterators-----------////////////////////////
template <typename T> T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
template <typename T> T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
////////////////////////------Iterators-----------////////////////////////
///////////////////////////////////////////////////////////////////////

///--------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////
//////////////////////////------List-----------////////////////////////
template<typename T> const typename List<T>::ConstIterator List<T>::begin() const
{
	return Head;
}
template<typename T> const typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T> typename const  List<T>::ConstReverseIterator List<T>::rbegin() const
{
	return Tail;
}
template<typename T> typename const  List<T>::ConstReverseIterator List<T>::rend() const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>List<T>::List(const List<T>& other) : List()
{
	*this = other;
	cout << "LCopyConstractor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	while (Tail)pop_back();
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}
//-----------Operators-----
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}
//----------------Adding elements-----------------
template<typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}

	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{

		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	size++;
}

template<typename T>void List<T>::insert(T Data, int Index)
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
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}

	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}
//---------------Removing elements:---------------
template<typename T>void List<T>::pop_front()
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
template<typename T>void List<T>::pop_back()
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
template<typename T>void List<T>::erase(int Index)
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
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}
template<typename T> void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}
//////////////////////////------List-----------////////////////////////
/////////////////////////////////////////////////////////////////////////
template<typename T> List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat;
	for (typename List<T>::ConstIterator it = left.begin(); it != left.end(); ++it)cat.push_back(*it);
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)cat.push_back(*it);
	return cat;
}
//-----------------------Class definition - конец определения класса--------------
