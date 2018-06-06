#ifndef BTNODE_H
#define BTNODE_H

#include "Vector.h"
#define BTNodePosi(T) BTNode<T>*	//B-���ڵ�λ��

template<typename T>
struct BTNode
{
//	��Ա
	BTNodePosi(T) parent;	//���ڵ�
	Vector<T> key;	//�ؼ�������
	Vector<BTNodePosi(T)> child;	//��������
//	���캯��
	BTNode(){ parent = NULL; child.insert(0, NULL); }
	BTNode(T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL)
	{
		parent = NULL;
		key.insert(0, e);
		child.insert(0, NULL);
		child.insert(1, NULL);
		if (lc)
			lc->parent = this;
		if (rc)
			rc->parent = this;
	}
};

#endif