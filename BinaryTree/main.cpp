//BinaryTree
#include<iostream>
#include<ctime>
#define delimiter "\n---------------------------------\n"
using namespace std;
#define DEBUG
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
		clear(Root);
		cout << "TDestractor:\t" << this << endl;
	}


	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
		Root == nullptr;
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return minValue(Root);
	}
	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	int Avg()const
	{
		return Avg(Root);
	}

	int Depth()const
	{
		return Depth(Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}

private:
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
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr) return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);

		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft));
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight),Root->pRight);
				}
			}
		}
	}
	int Depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Depth(Root->pLeft) + 1 > Depth(Root->pRight) + 1)
			 return Depth(Root->pLeft) + 1;
		else return Depth(Root->pRight) + 1;*/
		//return Depth(Root->pLeft) > Depth(Root->pRight) ? Depth(Root->pLeft) + 1 : Depth(Root->pRight) + 1;

		/*int l_depth = Depth(Root->pLeft) + 1;
		int r_depth = Depth(Root->pRight) + 1;
		return l_depth > r_depth ? l_depth : r_depth;*/

		return 1 + max(Depth(Root->pLeft), Depth(Root->pRight));
	}
	void clear(Element* Root)
	{
		if (Root == nullptr) return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		//Root = nullptr;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	int minValue(Element* Root)const
	{

		/*if (Root->pLeft == nullptr)return Root->Data;
		else return  minValue(Root->pLeft);*/
		if (Root == nullptr)return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return  maxValue(Root->pRight);*/
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int Count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;*/
		return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
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
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	double Avg(Element* Root)const
	{
		return(double)Sum(Root) / Count(Root);
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

//#define BASE_CHECK
#define DEPTH_CHECK
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
		tree.insert(num);
	}

	//time_t t_end = time(NULL);
	clock_t c_end = clock();
	cout << "Дерево заполнено за " << double(c_end - c_start) / CLOCKS_PER_SEC << " сек";
	tree.clear();
	/*t_end - t_start*/
//tree.print(tree.getRoot());
	cout << endl;
	c_start = clock();
	cout << "Минимальное значение в древе: " << tree.minValue() << endl;
	c_end = clock();
	cout << "Найдено за " << double(c_end - c_start) / CLOCKS_PER_SEC << "секунд.\n";
	c_start = clock();
	cout << "Максимальное значение в древе: " << tree.maxValue() << endl;
	c_end = clock();
	cout << "Найдено за " << double(c_end - c_start) / CLOCKS_PER_SEC << "секунд.\n";

	c_start = clock();
	cout << "Количество элементов дерева: " << tree.Count() << endl;
	c_end = clock();
	cout << "Найдено за " << double(c_end - c_start) / CLOCKS_PER_SEC << "секунд.\n";

	c_start = clock();
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	c_end = clock();
	cout << "Найдено за " << double(c_end - c_start) / CLOCKS_PER_SEC << "секунд.\n";

	c_start = clock();
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg() << endl;
	c_end = clock();
	cout << "Найдено за " << double(c_end - c_start) / CLOCKS_PER_SEC << "секунд.\n";
	c_start = clock();
	cout << "Глубина дерева: " << tree.Depth() << endl;
	c_end = clock();
	cout << "Найдено за " << double(c_end - c_start) / CLOCKS_PER_SEC << "секунд.\n";


	cout << delimiter;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100, u_tree.getRoot());
	}
	u_tree.print();
	cout << endl;

	cout << "Минимальное значение в древе: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в древе: " << u_tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << u_tree.Count() << endl;
	cout << "Сумма элементов дерева: " << u_tree.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << u_tree.Avg() << endl;
	cout << "Глубина дерева: " << u_tree.Depth() << endl;
#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50,25,75,16,32,64,90 };
	tree.print();
	cout << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;
int value;
	cout << "Введите удаляемое значение:" ; cin >> value;
	tree.erase(value);
	tree.print();


#endif // DEPTH_CHECK

}
