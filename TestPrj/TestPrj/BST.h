#ifndef BST_H
#define BST_H
#include "BinTree.h"	//引入BinTree


template<typename T>
class BST : public BinTree<T>
{
protected:
	BinNodePosi(T) _hot; //"命中"节点的父亲
	BinNodePosi(T) connect34(
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x); //对x及其父亲,祖父做统一旋转
public:
	virtual BinNodePosi(T) & search(const T& e);//查找
	virtual BinNodePosi(T) insert(const T& e);//插入
	virtual bool remove(const T& e);//删除
};

#endif