#include "Splay.h"
#include "BST.cpp"

template<typename BinNode>
inline void attachAsLChild(BinNode p, BinNode lc)
{
	p->lc = lc;
	if (lc)
		lc ->parent = p;
}

template<typename BinNode>
inline void attachAsRChild(BinNode p, BinNode rc)
{
	p->rc = rc;
	if (rc)
		rc->parent = p;
}

template<typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
{
	if (!v)
		return NULL;
	BinNodePosi(T) p;
	BinNodePosi(T) g;
	while ((p = v->parent) && (g = p->parent)) //双旋
	{
		BinNodePosi(T) gg = g->parent;
		if (IsLChild(*v))
		{
			if (IsLChild(*p))/* zig-zig */
			{
				attachAsRChild(g, p->rc);
				attachAsRChild(p, v->rc);
				attachAsRChild(p, g);
				attachAsRChild(v, p);
			}
			else/* zig-zag */
			{
				attachAsRChild(g, v->lc);
				attachAsLChild(p, v->rc);
				attachAsLChild(v, g);
				attachAsRChild(v, p);
			}
		}
		else if (IsRChild(*p))/* zag-zag */
		{
			attachAsRChild(g, p->lc);
			attachAsRChild(p, v->lc);
			attachAsLChild(p, v);
			attachAsLChild(v, p);
		}
		else/* zag-zig */
		{
			attachAsLChild(g, v->rc);
			attachAsRChild(p, v->lc);
			attachAsRChild(v, g);
			attachAsLChild(v, p);
		}
		if (!gg)
			v->parent = NULL;
		else
			(g == gg->lc) ? attachAsLChild(gg, v); attachAsRChild(gg, v);
		updataHeight(g);
		updataHeight(p);
		updataHeight(v);
	}
	if (p = v->parent) //单旋
	{
		if (IsRChild(*v))
		{
			attachAsRChild(p, v->lc);
			attachAsLChild(v, p);
		}
		else
		{
			attachAsLChild(p, v->rc);
			attachAsRChild(v, p);
		}
		v->parent = NULL;
		updataHeight(p);
		updataHeight(v);
	}

	return v;
}

template<typename T>
BinNodePosi(T) & Splay<T>::search(const T& e)
{
	BinNodePosi(T) p = searchIn(e);//在二叉树中查找节点e是否存在
	_root = splay(p ? p : _hot);
	return _root;
}

template<typename T>
BinNodePosi(T) Splay<T>::insert(const T& e)
{
	if (!_root)//空树
	{
		_size++;
		return _root = BinNode<T>(e);
	}
	if (e == search(e)) //查看节点e是否存在
		return _root;
	_size++;
	BinNodePosi(T) t = _root;
	if (_root->data < e)
	{
		t->parent = _root = BinNode<T>(e, NULL, t, t->rc);
		if (HasRChild(*t))
		{
			t->rc->parent = _root;
			t->rc = NULL;
		
		}
	}
	else
	{
		t->parent = _root = BinNode<T>(e, NULL, t->lc, t);
		if (HasLChild(*t))
		{
			t->lc->parent = _root;
			t->lc = NULL;
		}
	}

	updataHeightAbove(t);
	return _root;
}

template<typename T>
bool Splay<T>::remove(const T& e)
{
	if (!_root || e != search(e))//空树或者找不到节点e
		return false;
	BinNodePosi(T) w = _root;
	if (!HasLChild(*_root))
	{
		_root = _root->rc;
		if (_root)
			_root->parent = NULL;
	}
	else if (!HasRChild(*_root))
	{
		_root = _root->lc;
		if (_root)
			_root->parent = NULL;
	}
	else
	{
		BinNodePosi(T) lTree = _root->lc; //分开左树
		lTree->parent = NULL;
		_root->lc = NULL;

		_root = _root->rc;
		search(e);
		_root->lc = lTree;
		lTree->parent = _root;
	}

	RELEASE(w->data); //伪代码release(w->data)
	RELEASE(w);
	_size--;
	if (_root)
		updataHeight(_root);

	return true;
}