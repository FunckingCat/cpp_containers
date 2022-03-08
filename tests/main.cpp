#include "../containers/RBTree.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main() 
{
	RBTree<int> tree;

	srand(time(0));
	for (int i = 0; i < 101; i++)
		tree.insert(rand() % 1000);
	tree.inOrder();
	std::cout << std::endl;
	tree.print();
	for (int i = 0; i < 1000; i++)
		tree.remove(rand() % 1000);
	tree.inOrder();
	std::cout << std::endl;
	tree.print();
	return 0;
}