#ifndef REDBLACK_H
#define REDBLACK_H
#include "BST.h"

#define IsBlack(p) ( !(p) || RB_BLACK == (p)->color)
#define IsRed(p) (! IsBlack(p))
#define BlackHeightUpdated(x) ( /*RedBlack高度更新条件*/\
	( stature((x).lc) == stature( (x).rc ) ) && \
	( (x).height == ( IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1))\
)

template<typename T>
class RedBlack : public BST<T>
{
protected:
	void solveDoubleRed(BinNodePosi(T) x); //双红修正
	void sovleDoubleBlack(BinNodePosi(T) x); //双黑修正
	int updateHeight(BinNodePosi(T) x); //更新节点x高度
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
}

#endif