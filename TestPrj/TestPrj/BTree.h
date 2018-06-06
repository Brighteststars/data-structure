#ifndef BTREE_H
#define BTREE_H
#include "BTNode.h"

template<typename T>
class BTree
{
protected:
	int _size;	//关键码总数
	int _order;	//B-树的阶次
	BTNodePosi(T) _root; //B-树的根
	BTNodePosi(T) _hot;	//BTree::search()最后查找的非空节点
	void solveOverflow(BTNodePosi(T));//因插入而上溢之后的分裂处理
	void solveUnderflow(BTNodePosi(T));//因删除而下溢之后的合并处理
public:
	BTree(int order = 3) : _size(0), _order(3)
	{
		_root = new BTNode<T>();
	}
	~BTree(){ if (_root) RELEASE(_root); }

	int size() const { return _size; }
	
	BTNodePosi(T) & root() { return _root; }
	int order() const { return _order; }
	bool empty() const { return !_root; }

	BTNodePosi(T) search(const T& e); //查找
	bool insert(const T& e); //插入
	bool remove(const T& e); //删除
};

#endif