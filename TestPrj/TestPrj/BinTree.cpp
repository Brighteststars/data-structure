#include "BinTree.h"

template<typename T>
int BinTree<T>::updataHeight(BinNodePosi(T) x)		//更新节点x高度
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc)); 
}

template<typename T>
T max(T& a, T& b)
{
	if (a >= b)
		return a;
	else
		return b;
}

template<typename T>
void BinTree<T>::updataHeightAbove(BinNodePosi(T) x) //更新节点x及其父节点高度
{
	while (x){
		updataHeight(x);
		x = x->parent;
	}
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)		//将e当做根节点插入空的二叉树
{
	_size = 1;
	return _root = new BinNode(e);
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) //e插入作为x左孩子
{
	_size++;
	x->insertAsLChild(e);
	updataHeightAbove(x);
	return x->lc;
}


template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)//e插入作为x右孩子
{
	_size++;
	x->insertAsRChild(e);
	updataHeightAbove(x);
	return x->rc;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) //将T的根节点接入x左节点,并返回x
{
	if (x->lc = S->_root)	//接入
		x->lc->parent = x;
	_size += S->size;		//更新全树规模
	updataHeightAbove(x);	//更新x及其所有祖先高度

	S->_root = NULL;	
	S->size = 0;
	S->~BinTree();		//释放原树
	S = NULL;
	return x;		//返回接入位置
}

template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(x) = NULL;
	updataHeightAbove(x->parent);	//更新祖先高度
	int n = removeAt(x);	//删除子树
	_size -= n;		//更新规模
	return n;
}


template<typename T>
static int removeAt(BinNodePosi(T) x) //删除二叉树节点x及其后代,返回被删除的规模
{
	if (!x) //判空,空树
		return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);	//非空树,规模加1,递归释放左树,右树
	RELEASE(x->data); //删除二叉树节点中成员T data
	delete x;	//删除二叉树节点
	return n;
}

template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(x) = NULL;
	updataHeightAbove(x->parent);	//更新节点x祖父节点高度
	BinTree<T>* S = new BinTree<T>;
	S->_root = x;		//新树S以x为根
	x->parent = NULL;
	S->_size = x->size();
	_size -= S->_size; //更新原树规模
	return S; //返回分离出来的子树
}