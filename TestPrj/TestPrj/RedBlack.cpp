#include "RedBlack.h"

template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x)
{
	x->height = max(stature(x->lc), stature(x->rc));
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e) //��e��������
{
	BinNodePosi(T) & x = search(e);
	if (x) //ȷ��Ŀ�겻����(�����_hot������)
		return x;
	x = new BinNode<T>(e, _hot, NULL, NULL, -1); //������ڵ�x,��_hotΪ��,�ڸ߶�Ϊ-1
	_size++;
	solveDoubleRed(x); //˫������
	return x ? x : _hot->parent;
}