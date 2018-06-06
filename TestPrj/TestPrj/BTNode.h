#ifndef BTNODE_H
#define BTNODE_H

#include "Vector.h"
#define BTNodePosi(T) BTNode<T>*	//B-树节点位置

template<typename T>
struct BTNode
{
//	成员
	BTNodePosi(T) parent;	//父节点
	Vector<T> key;	//关键码向量
	Vector<BTNodePosi(T)> child;	//孩子向量
//	构造函数
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