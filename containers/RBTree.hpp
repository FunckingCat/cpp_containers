#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>

enum Color { Black, Red };

template<class T>
struct  Node
{
	T key;
	Color color;
	Node<T> * left;
	Node<T> * right;
	Node<T> * parent;
	Node(T k, Color c, Node* p, Node*l, Node*r) :
		key(k), color(c), left(l), right(r), parent(p) { };
};

template<class T>
class  RBTree
{
private:
	Node<T>*root;

	void leftRotate(Node<T>* &root, Node<T>* x);
	void rightRotate(Node<T>* &root, Node<T>* y);
	void insert(Node<T>* &root, Node<T>* node);
	void InsertFixUp(Node<T>* &root, Node<T>* node);
	void destory(Node<T>* &node);
	void remove(Node<T>*& root, Node<T>*node);
	void removeFixUp(Node<T>* &root, Node<T>* node, Node<T>*parent);
	Node<T>* search(Node<T>*node, T key) const;
	void print(const std::string& prefix, const Node<T>* node, bool isLeft) const;
	void inOrder(Node<T>* tree)const;

public:
	RBTree();
	~RBTree();

	void insert(T key);
	void remove(T key);
	Node<T>* search(T key);
	void print();
	void inOrder();
};

template<class T>
RBTree<T>::RBTree() :root(NULL) {
	root = NULL;
}

template<class T>
RBTree<T>::~RBTree() {
	destory(root);
}

template<class T>
void RBTree<T>::destory(Node<T>* &node) 
{
	if (node == NULL)
		return;
	destory(node->left);
	destory(node->right);
	delete node;
	node = NULL;
};

template<class T>
void RBTree<T>::leftRotate(Node<T>* &root, Node<T>* x) {
	Node<T>*y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};

template<class T>
void RBTree<T>::rightRotate(Node<T>*&root, Node<T>*y) {
	Node<T>*x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else {
		if  (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
};

template<class T>
void RBTree<T>::insert(T key)
{
	Node<T>*z = new Node<T>(key, Red, NULL, NULL, NULL);
	insert(root, z);
};

template<class T>
void RBTree<T>::insert(Node<T>* &root, Node<T>* node)
{
	Node<T> *x = root;
	Node<T> *y = NULL;
	while (x != NULL)
	{
		y = x;
		if (node->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if(y!=NULL)
	{
		if (node->key > y->key)
			y->right = node;
		else
			y->left = node;
	}
	else 
		root = node;
	node->color = Red;
	InsertFixUp(root, node);
};

template<class T>
void RBTree<T>::InsertFixUp(Node<T>* &root, Node<T>* node)
{
	Node<T>*parent;
	parent = node->parent;
	while (node != RBTree::root  && parent->color == Red)
	{
		Node<T>*gparent = parent->parent;
		if (gparent->left == parent)
		{
			Node<T>*uncle = gparent->right;
			if (uncle != NULL && uncle->color == Red)
			{
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					leftRotate(root, parent);
					std::swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else
		{
			Node<T>*uncle = gparent->left;
			if (uncle != NULL && uncle->color == Red)
			{
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rightRotate(root, parent);
					std::swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	root->color = Black;
};

template<class T>
void RBTree<T>::remove(T key) 
{
	Node<T>*deletenode = search(root,key);
	if (deletenode != NULL)
		remove(root, deletenode);
};

template<class T>
void RBTree<T>::remove(Node<T>*&root, Node<T>*node)
{
	Node<T> *child, *parent;
	Color color;
	// Левый и правый узлы удаленного узла не пусты (не конечные узлы)
	if (node->left != NULL && node->right != NULL)
	{
		Node<T> *replace = node;
		// Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
		replace = node->right;
		while (replace->left != NULL)
			replace = replace->left;
		// Случай, когда удаленный узел не является корневым узлом
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		// Ситуация с корневым узлом
		else
			root = replace;
		// child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
		// Поскольку замена является преемником, он не может иметь левого дочернего узла
		// Аналогично, у узла-предшественника не может быть правого дочернего узла
		child = replace->right;
		parent = replace->parent;
		color = replace->color;
		// Удаленный узел является родительским узлом замещающего узла (repalce)
		if (parent == node)
			parent = replace;
		else
		{
			// Существование дочернего узла
			if (child != NULL)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}
	// Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child) 
	{
		child->parent = parent;
	}
	// Удаленный узел не является корневым узлом
	if (parent)
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	// Удаленный узел является корневым узлом
	else
		RBTree::root = child;
	if (color == Black)
	{
		removeFixUp(root, child, parent);
	}
	delete node;

};

template<class T>
void RBTree<T>::removeFixUp(Node<T>* &root, Node<T>* node,Node<T>*parent)
{
	Node<T>*othernode;
	while ((!node) || (node->color == Black && node != RBTree::root))
	{
		if (!parent)
			return ; //Sega
		if (parent->left == node)
		{
			othernode = parent->right;
			if (!othernode)
				return ; //Sega
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				leftRotate(root, parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == Black)
				{
					if (!othernode->left)
						return ; // Sega
					othernode->left->color=Black;
					othernode->color = Red;
					rightRotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->right->color = Black;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->left;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				rightRotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black))
			{
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->color == Black)
				{
					othernode->right->color = Black;
					othernode->color = Red;
					leftRotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->left->color = Black;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = Black;
};

template<class T>
Node<T>* RBTree<T>::search(T key) 
{
	return search(root, key);
};

template<class T>
Node<T>* RBTree<T>::search(Node<T>*node, T key) const
{
	if (node == NULL || node->key == key)
		return node;
	else
		if (key > node->key)
			return search(node->right, key);
		else
			return search(node->left, key);
};

template<class T>
void RBTree<T>::print() {
	if (root == NULL)
		return ;
	else
		print("", root, false);
};

template<class T>
void RBTree<T>::print(const std::string& prefix, const Node<T>* node, bool isLeft) const {
	if (node == NULL)
		return;
	std::cout << prefix;
	std::cout << (isLeft ? "├──" : "└──" );
	std::cout << node->key << std::endl;
	print( prefix + (isLeft ? "│   " : "    "), node->left, true);
	print( prefix + (isLeft ? "│   " : "    "), node->right, false);
};

template<class T>
void RBTree<T>::inOrder() {
	if (root == NULL)
		return ;
	else
		inOrder(root);
};

template<class T>		 
void RBTree<T>::inOrder(Node<T>* tree)const {
	if (tree != NULL) {
		inOrder(tree->left);
		std::cout << tree->key << " ";
		inOrder(tree->right);
	}
};

#endif