#include "../containers/RBTree.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main() 
{
	// std::vector<int> nums;
	// for (int i = 0; i < 101; i += 10)
	// 	nums.push_back(i);
	// RBTree<int> tree;
	// for (std::vector<int>::iterator num = nums.begin(); num != nums.end(); num++)
	// 	tree.insert(*num);
	// tree.inOrder();
	// std::cout << std::endl;
	// tree.print();
	// return 0;

	RBTree<int> tree;
	for (int i = 0; i < 101; i += 10)
		tree.insert(i);
	tree.inOrder();
	cout << endl;
	cout << "Найти узел с ключом 30: \n";
	cout << endl<<tree.search(30)->key<<endl;
	cout << "Удалить узел с ключом 100 \n";
	for (int i = 0; i < 101; i += 10)
	{
		cout<< i << endl;
		tree.remove(i);
		tree.print();
	}
	tree.print();
	return 0;
}