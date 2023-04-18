//BinaryTree
#include<iostream>
#include<ctime>
#define delimiter "\n---------------------------------\n"
using namespace std;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstractor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestractor:\t" << this << endl;
#endif // DEBUG

		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;//сразу же объявляем Root - указатель на корень дерева
public:
	Element* getRoot() const
	{
		return Root;
	}

	Tree()
	{
		Root = nullptr;
		cout << "TConstractor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}
	}
	~Tree()
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
	int Depth(Element* Root)
	{
		if (Root == nullptr)return 0;
		/*if (Depth(Root->pLeft) + 1 > Depth(Root->pRight) + 1)
			 return Depth(Root->pLeft) + 1;
		else return Depth(Root->pRight) + 1;*/
		//return Depth(Root->pLeft) > Depth(Root->pRight) ? Depth(Root->pLeft) + 1 : Depth(Root->pRight) + 1;
		return 1 + max(Depth(Root->pLeft), Depth(Root->pRight));
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
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int Count(Element* Root)
	{
		/*if (Root == nullptr)return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;*/
		return Root==nullptr?0:Count(Root->pLeft) + Count(Root->pRight) + 1;
		//return !Root ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
		//return Root ? Count(Root->pLeft) + Count(Root->pRight) + 1:0;
	}
	int Sum(Element* Root)const
	{
		/*static int n = 0;//мой вариант
		if (Root == nullptr)return 0;
		summ(Root->pLeft);
		n += Root->Data;
		summ(Root->pRight);
		return n;*/
		/*if (Root == nullptr)return 0;
		else return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;*/
		return Root == nullptr?0:Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	double Avg(Element* Root)
	{
		return(double)Sum(Root) / Count(Root);
	}
	void Clear(Element* Root)
	{
		if (Root == nullptr) return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}

	void Erase(int Data, Element* Root)
	{
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == Data)Root->pLeft = nullptr;
			else Erase(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == Data)Root->pRight = nullptr;
			else Erase(Data, Root->pRight);
		}
	}
};
class  UniqueTree : public Tree
{
public:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
};

#define BASE_CHECK
//#define DEPTH_CHECK
void main()
{
	setlocale(0, "");
#ifdef BASE_CHECK
	Tree tree;
	//cout << "Минимальное значение в древе: " << tree.minValue(tree.getRoot()) << endl;
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	clock_t c_start = clock();
	//time_t t_start = time(NULL);
	for (int i = 0; i < n; i++)
	{
		int num = rand() % 100;
		//cout << num << "\t";
		tree.insert(num, tree.getRoot());
	}
	//time_t t_end = time(NULL);
	clock_t c_end = clock();
	cout << "Дерево заполнено за " << double(c_end-c_start)/CLOCKS_PER_SEC<<" сек";
		/*t_end - t_start*/ 
	//tree.print(tree.getRoot());
	cout << endl;
	c_start = clock();
	cout << "Минимальное значение в древе: " << tree.minValue(tree.getRoot()) << endl;
	c_end = clock();
	cout << "Найдено за " << double(c_end - c_start) / CLOCKS_PER_SEC << "секунд.\n";
	cout << "Максимальное значение в древе: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Количество элементов дерева: " << tree.Count(tree.getRoot()) << endl;
	cout << "Сумма элементов дерева: " << tree.Sum(tree.getRoot()) << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg(tree.getRoot()) << endl;
	cout << "Глубина дерева: " << tree.Depth(tree.getRoot()) << endl;



	cout << delimiter;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100, u_tree.getRoot());
	}
	u_tree.print(u_tree.getRoot());
	cout << endl;

	cout << "Минимальное значение в древе: " << u_tree.minValue(u_tree.getRoot()) << endl;
	cout << "Максимальное значение в древе: " << u_tree.maxValue(u_tree.getRoot()) << endl;
	cout << "Количество элементов дерева: " << u_tree.Count(u_tree.getRoot()) << endl;
	cout << "Сумма элементов дерева: " << u_tree.Sum(u_tree.getRoot()) << endl;
	cout << "Среднее арифметическое элементов дерева: " << u_tree.Avg(u_tree.getRoot()) << endl;
	cout << "Глубина дерева: " << u_tree.Depth(u_tree.getRoot()) << endl;
#endif // BASE_CHECK
#ifdef DEPTH_CHECK
	Tree tree = { 50,25,75,16,32,64,90 };
	tree.print(tree.getRoot());
	cout << endl;
	cout << "Глубина дерева: " << tree.Depth(tree.getRoot()) << endl;
#endif // DEPTH_CHECK


}
