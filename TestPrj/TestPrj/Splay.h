#ifndef SPLAY_H
#define SPLAY_H

#include "BST.h"

template<typename T>
class Splay : public BST<T>
{
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v);//从节点v出自下而上伸展
public:
	BinNodePosi(T) & search(const T& e);//查找(重写)
	BinNodePosi(T) insert(const T& e);//插入
	bool remove(const T& e);//删除
};

#endif