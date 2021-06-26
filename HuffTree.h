#pragma once
#include<iostream>
#include<string>
#include"HashSep.h"
#include"List.h"

using namespace std;
class HuffmanTree
{
public:
	HuffmanTree(char* str,int* fre);
	~HuffmanTree();
	string encode(char* str);
	string encode(char c);
private:
	struct HuffNode
	{
		int weight;
		char c;
		HuffNode* left;
		HuffNode* right;
		int leaf_fre;
		bool isleaf;
		HuffNode(int w, char p_c, HuffNode* l, HuffNode* r,bool leaf=false):weight(w),c(p_c),left(l),right(r),isleaf(leaf){}
		HuffNode operator=(int a) { HuffNode n(a, '0', nullptr, nullptr); return n; }
	};
	struct PointToNode
	{	
		HuffNode* ptr;
		PointToNode(HuffNode* n) :ptr(n){}
		PointToNode():ptr(nullptr){}
		PointToNode operator=(HuffNode* n) { PointToNode p(n); return p; }
		HuffNode operator*(PointToNode p) { return *(p.ptr); }
		HuffNode* operator->() { return ptr; }
		bool operator>(PointToNode& n) { return(ptr->isleaf ? ptr->leaf_fre : ptr->weight) > (n->isleaf ? n->leaf_fre : n->weight); }
		bool operator<(PointToNode& n) { return(ptr->isleaf ? ptr->leaf_fre : ptr->weight) < (n->isleaf ? n->leaf_fre : n->weight); }
		bool operator>=(PointToNode& n) { return(ptr->isleaf ? ptr->leaf_fre : ptr->weight) >= (n->isleaf ? n->leaf_fre : n->weight); }
		bool operator<=(PointToNode& n) { return(ptr->isleaf ? ptr->leaf_fre : ptr->weight) <= (n->isleaf ? n->leaf_fre : n->weight); }
		bool operator==(PointToNode& n) { return(ptr->isleaf ? ptr->leaf_fre : ptr->weight) == (n->isleaf ? n->leaf_fre : n->weight); }
	};
	HuffNode* m_root;
	HashTable<char, string > *CodeTable;
	void Update_Table(HuffNode* &n,string code);
};

HuffmanTree::HuffmanTree(char* str,int* fre)
{	
	CodeTable = new HashTable<char, string>(256);

	List<PointToNode > NodeList;
	for (int i = 0; str[i] != '\0'; i++) {
		PointToNode newcell = new HuffNode(fre[i], str[i], nullptr, nullptr,true);
		newcell->leaf_fre = fre[i];
		NodeList.insert(newcell);
	}
	while (NodeList.len() > 2) {
		PointToNode n1 = NodeList.top();
		NodeList.pop();
		PointToNode n2 = NodeList.top();
		NodeList.pop();
		PointToNode newcell = new HuffNode(n1->weight+n2->weight+n1->leaf_fre+n2->leaf_fre, '\0', n1.ptr, n2.ptr);
		newcell->leaf_fre = n1->leaf_fre + n2->leaf_fre;
		NodeList.insert(newcell);
	}
	PointToNode n1 = NodeList.top();
	NodeList.pop();
	PointToNode n2 = NodeList.top();
	NodeList.pop();
	m_root = new HuffNode(n1->weight + n2->weight + n1->leaf_fre + n2->leaf_fre, '\0', n1.ptr, n2.ptr);
	m_root->leaf_fre = n1->leaf_fre + n2->leaf_fre;
	Update_Table(m_root, "");
}

HuffmanTree::~HuffmanTree()
{
}
void HuffmanTree::Update_Table(HuffmanTree::HuffNode* &n,string code) {
	if (n->left == nullptr && n->right == nullptr) {
		CodeTable->insert(n->c, code);
	}
	else {
		Update_Table(n->left, code + "0");
		Update_Table(n->right, code + "1");
	}
}


string HuffmanTree::encode(char* str) {
	string ret_code = "";
	for (int i = 0; str[i] != '\0'; i++) {
		ret_code += (*CodeTable)[str[i]];
	}
	return ret_code;
}

string HuffmanTree::encode(char c) {
	return (*CodeTable)[c];
}

void test_for_encode() {
	char str[8] = "abcdefg";
	int p[7] = { 1,2,3,4,5,6,7 };
	HuffmanTree t1(str, p);
	for (int i = 0; str[i] != '\0'; i++) {
		cout <<str[i]<<":"<< t1.encode(str[i])<<endl;
	}
	char words[5] = "ddee";
	cout << t1.encode(words) << endl;
}
