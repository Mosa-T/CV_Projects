#ifndef BSTNODE_H
#define BSTNODE_H
#include "Player.h"
#include "CGPoints.h"
template<class T>
class BstNode
{
	BstNode *left, *right;
	T* pData;
	int id;
public:
	
	//insertion according to binary search tree rules, requires operator< from object class.
	void insert(BstNode<T> **tree, BstNode<T> *node) {
		if ((*tree) == NULL) {
			(*tree) = node;
			return;
		}
		else if ((node)->operator<((*tree))) {
			insert(&(((*tree)->left)), node);
		}
		else {
			insert(&((*tree)->right), node);
		}
	}

	//two search functions, one doesn't require an operator from T, other does
	BstNode<T>* search(BstNode<T> **node, T value) {
		if ((*node) == NULL) return NULL;
		if (value == *((*node)->pData))
			return (*node);
		else if (value < *((*node)->pData))
			return search(&(((*node)->left)), value);
		else
			return search(&((*node)->right), value);
	}

	//two search functions, one doesn't require an operator from T, other does
	BstNode<T>* search(BstNode<T> **node, int key) {
		if ((*node) == NULL) return NULL;
		if (key == *((*node)->id))
			return (*node);
		else if (key < *((*node)->id))
			return search(&(((*node)->left)), key);
		else
			return search(&((*node)->right), key);
	}

	void remove(BstNode<T> **nodePtr,T item)
	{
		if (item < *((*nodePtr)->pData))
			remove(&((*nodePtr)->left),item);
		else if (*((*nodePtr)->pData) < item)
			remove(&((*nodePtr)->right),item);
		else
			makeDeletion(&((*nodePtr)));
	}

	T* min(BstNode<T> *tree) {
		while (tree->left) {
			tree = tree->left;
		}
		return tree->pData;
	}

	T* max(BstNode<T> *tree) {
		while (tree->right) {
			tree = tree->right;
		}
		return tree->pData;
	}

	void makeDeletion(BstNode<T> **nodePtr){
		//Define a temporary pointer to use in reattaching the left subtree
		BstNode<T> *tempNodePtr;
		if ((*nodePtr) == NULL)
			cout << "Cannot delete empty node.\n";
		else if ((*nodePtr)->right == NULL){
			tempNodePtr = (*nodePtr);
			(*nodePtr) = (*nodePtr)->left;           //Reattach the left child
			delete tempNodePtr;
		}
		else if ((*nodePtr)->left == NULL){
			tempNodePtr = (*nodePtr);
			(*nodePtr) = (*nodePtr)->right;           //Reattach the right child
			delete tempNodePtr;
		}
		//If the node has two children
		else{
			//Move one node to the right
			tempNodePtr = (*nodePtr)->right;
			//Go to the end left node
			while (tempNodePtr->left)
				tempNodePtr = tempNodePtr->left;
			//Reattach the ledt subtree
			tempNodePtr->left = (*nodePtr)->left;
			tempNodePtr = (*nodePtr);
			//Reattach the right subtree
			(*nodePtr) = (*nodePtr)->right;
			delete tempNodePtr;
		}
	}

	BstNode(const T &a) :left(0), right(0), pData(a), id(0) { 
		*pData = a;; 
	}

	BstNode<T>&operator=(const BstNode<T>&a) { 
		(pData = a.pData); 
		id = a.id;
		return *this;
	}

	BstNode() :left(0), right(0), id(0), pData(new T) {};
	~BstNode() {
		delete pData;
		pData = NULL;
	}

	BstNode( T &pd,const int id) :left(0), right(0), id(id) {
		this->id = id;
		pData = new T(pd);
	}

	BstNode(const BstNode<T> &a) :left(a.left), right(a.right), pData(a.pData) { id = a.id; }

	BstNode<T> *getLeft() { return left; }

	BstNode<T> *getRight() { return right; }

	T& getData() { return *pData; }

	int getId() { return id; }

	void setID(int id) {
		this->id = id;
	}

	void setLeft(BstNode<T>* l) { left = l; }

	void setRight(BstNode<T>* r) { right = r; }

	void setData(const T& d) {
		*pData = d;
	}
	
	bool operator<(const T &other) {
		return (pData < other);
	}

	bool operator<(const BstNode *other) {
		return (this->id < other->id);
	}
	
	void walk(BstNode<T> **tree, int size) {
		if ((*tree) == NULL) return;
		size--;
		walk(&((*tree)->left), size);
		if (size == 0) {
			std::cout << *(*((*tree)->pData));
			return;
		}
		std::cout << *(*((*tree)->pData)) << "\n";
		walk(&((*tree)->right), size);
	}

	//friend std::ostream &operator<<(std::ostream &output,const BstNode<T> root) {
	//	if (!root) return;
	//	//walk(root);
	//	return output;
	//}
};

#endif 