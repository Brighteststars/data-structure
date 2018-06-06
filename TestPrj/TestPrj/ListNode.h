#ifndef LISTNODE_H
#define LISTNODE_H
#define Posi(T) ListNode<T>*
typedef int Rank;

template<typename T>
struct ListNode{
// 成员
	T data;
	Posi(T) pred;
	Posi(T) succ;
// 构造函数
	ListNode(){}
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
		: data(e), pred(p), succ(s){}

// 操作接口

	Posi(T) insertAsPred(T const& e);
	Posi(T) insertAsSucc(T const& e);
};


#endif