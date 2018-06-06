#ifndef LISTNODE_H
#define LISTNODE_H
#define Posi(T) ListNode<T>*
typedef int Rank;

template<typename T>
struct ListNode{
// ��Ա
	T data;
	Posi(T) pred;
	Posi(T) succ;
// ���캯��
	ListNode(){}
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
		: data(e), pred(p), succ(s){}

// �����ӿ�

	Posi(T) insertAsPred(T const& e);
	Posi(T) insertAsSucc(T const& e);
};


#endif