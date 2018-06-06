#include "ListNode.h"


template<typename T>
Posi(T) ListNode<T>::insertAsPred(T const& e)
{
	Posi(T) x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T>
Posi(T) ListNode<T>::insertAsSucc(T const& e)
{
	Posi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}
