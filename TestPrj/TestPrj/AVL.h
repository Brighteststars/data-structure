#ifndef AVL_H
#define AVL_H
#include "BST.h"


#define Balanced(x) (stature( (x).lc) == stature( (x).rc) )//理想平衡条件
#define BalFac(x) ( stature( (x).lc) - stature( (x).rc) ) //平衡因子
#define AvlBalanced(x) ( (-2 < BalFac(x)) && ( BalFac(x) < 2) ) //AVL平衡条件

#define tallerChild(x) (\
	stature( (x).lc )  > stature( (x).rc) ? (x).lc : (/*左高*/\
	stature( (x).lc) < stature( (x).rc) ? (x).rc : (/*右高*/)\
	IsLChild( *(x) ) ? (x).lc : (x).rc /*等高: 与父亲x同侧者优先*/\
)\
)\
)

template< typename T>
class AVL : public BST<T>
{
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};

#endif