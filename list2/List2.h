#pragma once
#include <iostream>
using namespace std;
#define tab "\t"
//-----------------------Class declaration-Объявление класса--------------

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;//чтобы запись была короче иначе за классом вызывалось бы так:
	//Element* Head, Element* Tail
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator ==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
		//Element* Temp;
	public:
		ConstIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp) {}
		~ConstIterator() {}
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{

	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp) {}

		~ConstReverseIterator() {}

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};
	const ConstIterator begin() const;
	const ConstIterator end()const;
	const ConstReverseIterator rbegin() const;
	const ConstReverseIterator rend() const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//-----------Operators-----
	List<T>& operator=(const List<T>& other);
	//----------------Adding elements-----------------
	void push_front(T Data);
	void push_back(T Data);

	void insert(T Data, int Index);

	//---------------Removing elements:---------------
	void pop_front();
	void pop_back();
	void erase(int Index);

	//---------------Metods-----------
	void print()const;
	void reverse_print()const;
};
template<typename T> List<T> operator+(const List<T>& left, const List<T>& right);
//-----------------------Class declaration end - Конец объявления класса--------------
