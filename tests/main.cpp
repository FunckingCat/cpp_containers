#include "../containers/RBTree.hpp"
#include <iostream>
#include <vector>

int main() 
{
	std::vector<int> nums;
	for (int i = 0; i < 101; i += 10)
		nums.push_back(i);
	RBTree<int> tree;
	for (std::vector<int>::iterator num = nums.begin(); num != nums.end(); num++)
		tree.insert(*num);
	tree.inOrder();
	std::cout << std::endl;
	tree.print();
	return 0;
}