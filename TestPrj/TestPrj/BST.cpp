#include "BST.h"

template<typename T>
static BinNodePosi(T) & searchIn(BinNodePosi(T) v, const T& e, BinNodePosi(T) &hot)
{
	if (!v || v->data == e)
		return v; //递归基
	hot = v;//记录当前节点

	return searchIn( ( (e < v->data) ? v->lc : v->rc), e, hot); //深入一层,递归查找
}

template<typename T>
BinNodePosi(T) & BST<T>::search(const T& e)//在BST中查找关键码e
{
	return searchIn(_root, e, _hot = NULL);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e)
{
	BinNodePosi(T) x = search(e);
	if (x) //如果存在,直接返回
		return x;
	x = new BinNode<T>(e, _hot);
	++_size;
	updataHeightAbove(x);//更新x及其父亲,祖父高度
	return x;//新插入节点必为叶节点
}

template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) x, BinNodePosi(T) & hot)
{
	BinNodePosi(T) w = x;//实际被摘除节点,初值同x
	BinNodePosi(T) succ = NULL;//实际被删除节点继承者
	if (!HasLChild(*x))
	{
		succ = x = x->rc;
	}
	else if (!HasRChild(*x))
	{
		succ = x = x->lc;
	}
	else
	{
		w = w->succ();//(在右子树)找到*x直接后继*w
		swap(x->data, w->data);
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc;
	}

	hot = w->parent;
	if (succ)
		succ->parent = hot;
	RELEASE(w->data);
	return succ;

}

template<typename T>
bool BST<T>::remove(const T& e)
{
	BinNodePosi(T) x = search(e);
	if (!x)
		return false;
	removeAt(x, _hot);
	--_size;
	updataHeightAbove(_hot);
	return true;
}

template<typename T>
BinNodePosi(T) BST<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
	a->lc = T0;
	if (T0)
		T0->parent = a;
	a->rc = T1;
	if (T1)
		T1->parent = a;
	updataHeight(a);

	c->lc = T2;
	if (T2)
		T2->parent = c;
	c->rc = T3;
	if (T3)
		T3->parent = c;
	updataHeight(c);

	b->lc = a;
	a->parent = b;
	b->rc = c;
	c->parent = b;
	updataHeight(b);

	return b;//该子树新的根节点
}

template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) x)
{
	BinNodePosi(T) p = x->parent;
	BinNodePosi(T) g = p->parent;
	if (IsLChild(*p)) /* zig */
	{
		if (IsLChild(*x)) /* zig-zig */
		{
			p->parent = g->parent;
			return connect34(x, p, g, x->lc, x->rc, p->rc, g->rc);
		
		}
		else /* zig-zag */
		{
			x->parent = g->parent;
			return connect34(p, x, g, p->lc, x->lc, x->rc, g->rc);
		}
	}
	else if (IsRChild(*x))/* zag */
	{
		p->parent = g->parent;
		return connect34(g, p, x, g->lc, p->lc, x->lc, x->rc);
	}
	else /* zag-zig */
	{
		x->parent = g->parent;
		return connect34(g, v, p, g->lc, x->lc, x->rc, p->rc);
	}
}