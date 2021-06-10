#pragma once
#include<iostream>
template <typename KEY>
int Hash(KEY key,int size) {
	return key % size;
}
template <typename KEY,typename WORD>
class HashTable
{
public:
	struct ListNode
	{
		KEY key;
		WORD word;
		ListNode* next;
		ListNode() :next(nullptr){}
	};
	typedef ListNode* Position;
	typedef Position List;
	int TableSize;
	List* theList;
	HashTable(int size);
	~HashTable();
	ListNode* find(KEY key);
	void insert(KEY key,WORD word);
	void remove(KEY key);
	WORD operator[](KEY key) {
		Position Pos = find(key);
		if (Pos == nullptr)return -1;
		else return Pos->word;
	}
};



template <typename KEY, typename WORD>
HashTable <typename KEY, typename WORD>::HashTable(int size)
{
	int i = 0;
/*	if (size < MinTableSize) {
		Error("Table size too small");
		return nullptr;
	}
	TableSize=nextprime(size);
	*/
	TableSize = size;
	theList = new List[TableSize];
	for (i = 0; i < TableSize; i++) {
		theList[i] = new ListNode;
		theList[i]->next = nullptr;
	}

}

template <typename KEY, typename WORD>
HashTable<typename KEY, typename WORD>::~HashTable()
{

}

template <typename KEY, typename WORD>
typename HashTable <typename KEY, typename WORD>::ListNode*
HashTable <typename KEY, typename WORD>::find(KEY key){
	Position P;
	List L;
	L = theList[Hash(key, TableSize)];
	P = L->next;
	while (P!=nullptr&&P->key!=key)
	{
		P = P->next;
	}
	return P;
}
template <typename KEY, typename WORD>
void HashTable <typename KEY, typename WORD>::insert(KEY key,WORD word) {
	Position Pos, NewCell;
	List L;
	Pos = find(key);
	if (Pos == nullptr) {
		NewCell = new ListNode;
		L = theList[Hash(key, TableSize)];
		NewCell->next =L->next;
		NewCell->key = key;
		NewCell->word = word;
		L->next = NewCell;
	}
}
template <typename KEY,typename WORD>
void HashTable <typename KEY, typename WORD>::remove(KEY key) {
	Position P,Tmp;
	List L;
	L = theList[Hash(key, TableSize)];
	P = L;
	while (P ->next!= nullptr && P->next->key != key)
	{
		P = P->next;
	}
	if (P->next== nullptr)return;
	Tmp = P->next;
	P->next = Tmp->next;
	delete Tmp;
}

void test() {
	HashTable<int, int> h(10007);
	h.insert(1, 3);
	h.insert(2, 4);
	h.insert(3, 5);
	h.remove(3);
	cout << h[3] << endl;
	cout << h[1] << endl;
	cout << h[2] << endl;
}
