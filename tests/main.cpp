#include "../containres/RBTree.hpp"
#include <iostream>
#include <vector>

int main() 
{
	std::vector<int> nums{10,40,30,60,90,70,20,50,80,100};
	RBTree<int> tree;
	for (auto num : nums)
		tree.insert(num);
	tree.preOrder();
	std::cout << std::endl;
	tree.inOrder();
	std::cout << std::endl;
	tree.postOrder();
	std::cout << std::endl;
	std::cout << "\nFIND 30: ";
	std::cout << tree.search(30)->key<<std::endl;
	std::cout << "\nDEL 100 --> ";
	tree.remove(100);
	tree.preOrder();
	std::cout << std::endl;
	std::cout << "\nDETAILS: \n";
	tree.print();
	return 0;
}