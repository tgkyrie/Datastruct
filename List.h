#pragma once
template <typename Comparable>
class List
{
public:
	List();
	~List();
	void insert(Comparable x);
	int len();
	Comparable top();
	void pop();
private:
	int length;
	struct ListNode
	{
		Comparable elm;
		ListNode* next;
		ListNode():next(nullptr){}
		ListNode(Comparable x,ListNode* ptr):elm(x),next(ptr){}
	};
	ListNode* head;
};
template <typename Comparable>
List<Comparable>::List()
{
	head = new ListNode();
	length = 0;
}

template <typename Comparable>
List<Comparable>::~List()
{
}

template <typename Comparable>
int List<Comparable>::len() {
	return length;
}

template <typename Comparable>
void List<Comparable>::insert(Comparable x) {
	ListNode* pos = head;
	while (pos->next!=nullptr&&x > pos->next->elm)pos = pos->next;
	ListNode* newcell = new ListNode(x, pos->next);
	pos->next = newcell;
	length++;
}

template<typename Comparable>
Comparable List<Comparable>::top() {
	return head->next->elm;
}

template<typename Comparable>
void List<Comparable>::pop() {
	if (length == 0)return;
	ListNode* p = head->next;
	head->next = p->next;
	delete p;
	length--;
}
