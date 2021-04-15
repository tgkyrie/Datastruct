#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H
#endif
#include <iostream>
using namespace std;
template<typename Comparable>
class AVLTree {
public:
	typedef enum _order {PREORDER,INORDER,POSTORDER} ORDER;
public:
	AVLTree():m_root(nullptr) {}
	AVLTree(const AVLTree& rhs) 
	{
		m_root = clone(rhs.m_root);
	}
	~AVLTree() 
	{
		makeEmpty();
	}
	int getHeight()const 
	{
		return m_root.height;
	}
	const Comparable& findMin() const 
	{
		return findMin(m_root)->element;
	}
	const Comparable& findMax() const 
	{
		return findMax(m_root)->element;
	}
	bool contains(const Comparable& x)const 
	{
		return contains(x, m_root);
	}
	bool isEmpty()const 
	{
		return nullptr == m_root;
	}
	void printTree(ORDER ord = INORDER, ostream& out = cout) 
	{
		if (isEmpty()) {
			out << "Empty tree" << endl;
		}
		else {
			switch (ord)
			{
			case PREORDER:
				preOrder(m_root, cout);
				break;
			case INORDER:
				inOrder(m_root, cout);
				break;
			case POSTORDER:
				postOrder(m_root, cout);
				break;
			default:
				break;
			}
		}
	}
	void makeEmpty()
	{
		makeEmpty(m_root);//???
	}
	void insert(const Comparable& x) 
	{
		insert(x, m_root);
	}
	void remove(const Comparable& x) 
	{
		remove(x, m_root);

	}
	//深拷贝
	const AVLTree& operator=(const AVLTree& rhs)
	{
		if (this != &rhs) {
			AVLNode* tmp = clone(rhs.m_root);
			makeEmpty();
			m_root = tmp;
		}
		return *this;
	}
private:
	struct AVLNode
	{
		Comparable element;
		AVLNode* left;
		AVLNode* right;
		int height;
		AVLNode(const Comparable &theElement,AVLNode* lt,AVLNode* rt,int h=0):element(theElement),left(lt),right(rt),height(h){}

	};
	AVLNode* m_root;
	static const int ALLOW_IMBALANCE = 1;
	int max(int a, int b) {
		return a >= b ? a : b;
	}
	inline int height(AVLNode* t)const {
		return nullptr == t ? -1 : t->height;
	}
	void insert(const Comparable& x, AVLNode*& t);
	void remove(const Comparable& x, AVLNode*& t);
	AVLNode* findMin(AVLNode* t)const;
	AVLNode* findMax(AVLNode* t)const;
	bool contains(const Comparable& x, AVLNode* t);
	void makeEmpty(AVLNode*& t);
	void preOrder(AVLNode* t, ostream& out)const;
	void inOrder(AVLNode* t, ostream& out)const;
	void postOrder(AVLNode* t, ostream& out)const;
	AVLNode* clone(AVLNode* t)const;
	void balance(AVLNode* &t);
	void rotatewithRightChild(AVLNode*& k2);
	void rotatewithLeftChild(AVLNode*& k2);
	void doublewithLeftChild(AVLNode*& k3);
	void doublewithRightChild(AVLNode*& k3);
	inline void updateHeight(AVLNode*& t)
	{
		t->height = max(height(t->left), height(t->right));
	}
};
template<typename Comparable>
typename AVLTree<Comparable>::AVLNode*
AVLTree<Comparable>::clone(typename AVLTree<Comparable>::AVLNode* t)const
{
	if (t == nullptr)return nullptr;
	return new AVLNode(t->element, clone(t->left), clone(t->right));
}
template <typename Comparable>
void AVLTree<Comparable>::preOrder(typename AVLTree<Comparable>::AVLNode* t, ostream& out)const
{
	if (t != nullptr) {
		out << t->element << endl;
		preOrder(t->left,out);
		preOrder(t->right,out);
	}
}
template<typename Comparable>
void AVLTree<Comparable>::inOrder(
	typename AVLTree<Comparable>::AVLNode * t,
	ostream & out) const
	{
		if (nullptr != t)
		{
			inOrder(t->left, out);
			out << t->element << endl;
			inOrder(t->right, out);
		}
}
template<typename Comparable>
void AVLTree<Comparable>::postOrder(
	typename AVLTree<Comparable>::AVLNode* t,
	ostream& out) const
{

	if (nullptr != t)
	{
		postOrder(t->left, out);
		postOrder(t->right, out);
		out << t->element << endl;
	}
}
template<typename Comparable>
void AVLTree<Comparable>::makeEmpty(typename AVLTree<Comparable>::AVLNode* &t)
{
	if (t != nullptr) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}
template<typename Comparable>
typename AVLTree<Comparable>::AVLNode*
AVLTree<Comparable>::findMin(
	typename AVLTree<Comparable>::AVLNode* t) const
{
	if (t == nullptr)
		return nullptr;
	if (t->left == nullptr)
		return t;
	return findMin(t->left);
}

template<typename Comparable>
typename AVLTree<Comparable>::AVLNode*
AVLTree<Comparable>::findMax(
	typename AVLTree<Comparable>::AVLNode* t) const
{
	if (t != nullptr)
		while (t->right != nullptr)
			t = t->right;
	return t;
}
template<typename Comparable>
void AVLTree<Comparable>::remove(const Comparable& x, AVLTree<Comparable>::AVLNode*& t)
{
	if (t == nullptr)
	{
		return;
	}
	else if (x > t->element) {
		remove(x, t->right);
	}
	else if (x < t->element) {
		remove(x, t->left);
	}
	else if (t->left && t->right) {
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else {
		AVLNode* oldNode=t;
		t = (t->left == nullptr) ? t->right : t->left;
		delete oldNode;
		oldNode = NULL;
	}
	balance(t);
}
template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable& x, AVLTree<Comparable>::AVLNode*& t) {
	if (t == nullptr) {
		t = new AVLNode(x, nullptr, nullptr);
	}
	else if (x < t->element) {
		insert(x, t->left);
	}
	else if (x > t->element) {
		insert(x, t->right);
	}
	else;
	balance(t);
}
template <typename Comparable>
void AVLTree<Comparable>::balance(typename AVLTree<Comparable>::AVLNode*& t) {
	if (t == nullptr)return;
	else if (height(t->left) - height(t->right) > AVLTree<Comparable>::ALLOW_IMBALANCE) {
		if (height(t->left->left) >= height(t->left->right)) {
			rotatewithLeftChild(t);
		}
		else {
			doublewithLeftChild(t);
		}
	}
	else if (height(t->right) - height(t->left) > AVLTree<Comparable>::ALLOW_IMBALANCE) {
		if (height(t->right->right) >= height(t->right->left)) {
			rotatewithRightChild(t);
		}
		else {
			doublewithRightChild(t);
		}
	}
	else;
	updateHeight(t);
}
template <typename Comparable>
void typename AVLTree<Comparable>::rotatewithLeftChild(typename AVLTree<Comparable>::AVLNode*& k2) {
	if (k2== nullptr)return;
	auto k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right));
	k1->height = max(height(k1->left), height(k1->right));
	k2 = k1;
}
template <typename Comparable>
void typename AVLTree<Comparable>::rotatewithRightChild(typename AVLTree<Comparable>::AVLNode*& k2) {
	if (k2 == nullptr)return;
	auto k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	updateHeight(k2);
	updateHeight(k1);
	k2 = k1;
}
template <typename Comparable>
void typename AVLTree<Comparable>::doublewithLeftChild(typename AVLTree<Comparable>::AVLNode*& k3) {
	rotatewithRightChild(k3->left);
	rotatewithLeftChild(k3);
}
template <typename Comparable>
void typename AVLTree<Comparable>::doublewithRightChild(typename AVLTree<Comparable>::AVLNode*& k3) {
	rotatewithLeftChild(k3->right);
	rotatewithRightChild(k3);
}
