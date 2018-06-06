#include "RedBlack.h"

template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x)
{
	x->height = max(stature(x->lc), stature(x->rc));
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e) //将e插入红黑树
{
	BinNodePosi(T) & x = search(e);
	if (x) //确认目标不存在(留意对_hot的设置)
		return x;
	x = new BinNode<T>(e, _hot, NULL, NULL, -1); //创建红节点x,以_hot为父,黑高度为-1
	_size++;
	solveDoubleRed(x); //双红修正
	return x ? x : _hot->parent;
}