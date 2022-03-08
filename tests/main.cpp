#include "../containres/RBTree.hpp"
#include <iostream>
#include <vector>

int main() 
{
	std::vector<int> nums{10,40,30,60,90,70,20,50,80,100};
	RBTree<int> tree;
	for (auto num : nums)
		tree.insert(num);
	tree.inOrder();
	std::cout << std::endl;
	tree.print();
	return 0;
}