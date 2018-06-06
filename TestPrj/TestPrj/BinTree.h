#ifndef BINTREE_H
#define BINTREE_H
#include "binNode.h"

template<typename T>
class BinTree{
protected:
	int _size;
	BinNodePosi(T) _root;	//根节点
	virtual int updataHeight(BinNodePosi(T) x); // 更新节点x高度
	void updataHeightAbove(BinNodePosi(T) x); //更新节点x及其祖先高度
public:
	BinTree() : _size(0), _root(NULL){}
	~BinTree() { if _size > 0; remove(_root); }
	bool empty() const { return !_root; } // 判空
	int size() const { return _size; }
	BinNodePosi(T) insertAsRoot(T const& e);	//插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); // e作为x左节点(原无)插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); // e作为x右节点(原无)插入
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T); // T作为x左子树接入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T); // T作为x右子树接入
	int remove(BinNodePosi(T) x); //删除以节点x为根的子树,返回该子树原先的规模
	BinTree<T>* secede(BinNodePosi(T) x); //将子树x从当前树中摘除,并将其转换为一颗独立子树

// 二叉树遍历
	template<typename VST> //操作器
	void traLevel(VST& visit) { if (_root) _root->traLevel(visit); } //层次遍历
	template<typename VST>
	void traPre(VST& visit) { if (_root) _root->traPre(visit); } //先序遍历
	template<typename VST>
	void traIn(VST& visit) { if (_root) _root->traIn(visit); } //中序遍历
	template<typename VST>
	void traPost(VST& visit){ if (_root) _root->traPost(visit); } //后序遍历

	bool operator==(BinTree<T> const& t)		//判断器
	{
		return _root && t._root && (_root == t._root);	//等于
	}
	bool operator<(BinNode<T> const& t)
	{
		return _root && t._root && It(_root, t._root); //小于
	}

};

#endif