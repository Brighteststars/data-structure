#ifndef AVL_H
#define AVL_H
#include "BST.h"


#define Balanced(x) (stature( (x).lc) == stature( (x).rc) )//����ƽ������
#define BalFac(x) ( stature( (x).lc) - stature( (x).rc) ) //ƽ������
#define AvlBalanced(x) ( (-2 < BalFac(x)) && ( BalFac(x) < 2) ) //AVLƽ������

#define tallerChild(x) (\
	stature( (x).lc )  > stature( (x).rc) ? (x).lc : (/*���*/\
	stature( (x).lc) < stature( (x).rc) ? (x).rc : (/*�Ҹ�*/)\
	IsLChild( *(x) ) ? (x).lc : (x).rc /*�ȸ�: �븸��xͬ��������*/\
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