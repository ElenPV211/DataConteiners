//BinaryTree
#include<iostream>
using namespace std;

class BinaryTree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstractor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestractor:\t" << this << endl;
		}
		friend class BinaryTree;
	}*Root;//����� �� ��������� Root - ��������� �� ������ ������
public:
	Element* getRoot() const
	{
		return Root;
	}

	BinaryTree()
	{
		Root = nullptr;
		cout << "TConstractor:\t" << this << endl;
	}
	~BinaryTree()
	{
		cout << "TDestractor:\t" << this << endl;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	int minValue(Element* Root)
	{

		/*if (Root->pLeft == nullptr)return Root->Data;
		else return  minValue(Root->pLeft);*/
		if (Root == nullptr)return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return  maxValue(Root->pRight);*/
		if (Root == nullptr)return 0;
		return Root->pRight ?  maxValue(Root->pRight):Root->Data;
	}
};

void main()
{
	setlocale(0, "");
	BinaryTree tree;
	cout << "����������� �������� � �����: " << tree.minValue(tree.getRoot()) << endl;
	int n;
	cout << "������� ������ ������: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int num = rand() % 100;
		cout << num << "\t";
		tree.insert(num, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;
	cout << "����������� �������� � �����: " << tree.minValue(tree.getRoot()) << endl;
	cout << "������������ �������� � �����: " << tree.maxValue(tree.getRoot()) << endl;
}
