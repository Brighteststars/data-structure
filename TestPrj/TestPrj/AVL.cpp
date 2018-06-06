#include "AVL.h"


template<typename T>
BinNodePosi(T) AVL<T>::insert(const T& e)
{
	BinNodePosi(T) x = search(e);
	if (x) //如果x存在
		return x;
	BinNodePosi(T) xx = x = new BinNode<T>(e, _hot); //插入新元素
	_size++;

	for (BinNodePosi(T) g = _hot; g; g = g->parent)
	{
		if (!AvlBalanced(*g))
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(*g)));
			break;
		}
		else
		{
			updataHeight(g);
		}
	}
	return xx;
}

template<typename T>
bool AVL<T>::remove(const T& e）
{
	BinNodePosi(T) x = search(e);
	if (!x)//x不存在
		return false;
	
	removeAt(x, _hot);
	_size--;

	for (BinNodePosi(T) g = _hot; g; g = g->parent)
	{
		if (!AvlBalanced(*g))
		{
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(*g)));
		}
		else
			updataHeight(g);
	}

	return true;
}