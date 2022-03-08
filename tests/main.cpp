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
	std::cout << "FIND 30: \n";
	std::cout << std::endl<<tree.search(30)->key<<std::endl;
	std::cout << "DEL 100 \n";
	tree.remove(100);
	tree.preOrder();
	std::cout << std::endl;
	std::cout << "\nDETAILS: \n";
	tree.print();
	return 0;
}