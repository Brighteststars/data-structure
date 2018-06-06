#include "BTree.h"

template<typename T>
BTNodePosi(T)  BTree<T>::search(const T& e)
{
	BTNodePosi(T) v = _root; //从根节点开始查找
	_hot = NULL;

	while (v)//逐层查找
	{
		Rank r = v->key.search(e); //在当前节点中查找不大于e的最大值
		if ((0 <= r) && (e == v->key[r]))
			return v;
		_hot = v;
		v = v->child[r + 1];
	}
	return NULL; //失败抵达外部节点
}

template<typename T>
bool BTree<T>::insert(const T& e)
{
	BTNodePosi(T) v = search(e);
	if (v)
		return false;
	Rank r = _hot->key.search(e); //在节点_hot有序关键码中查找插入位置
	_hot->key.insert(r + 1, e);
	_hot->child.insert(r + 2, NULL); //创建一个空子树指针
	_size++; //更新全树规模
	solveOverflow(_hot); //如有必要,需做分裂
	return true;
}

template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)
{
	if (v->child.size() <= _order)
		return; //递归基
	Rank s = _order; // _order = n,中位数s
	BTNodePosi(T) u = new BTNode<T>(); //创建空节点u
	for (Rank j = 0; i < _order - s - 1; j++)
	{
		u->key.insert(j, v->key.remove(s + 1));
		u->child.insert(j, v->child.remove(s + 1));
	}
	u->child[_order - s - 1] = v->child.remove(s + 1);
	if (u->child[0])
	{
		for (Rank j = 0; j < _order - s; j++)
			u->child[j].parent = u;
	}
	BTNodePosi(T) p = v->parent;
	if (!p)
	{
		p = _root = new BTNode<T>();
		p->child[0] = v;
		v->parent = p;
	}

	Rank r = 1 + p->key.search(v->key[0]);//p的key中指向u的秩
	p->key.insert(r, v->key.remove(s));
	p->child.insert(r + 1, u);
	u->parent = u;//新节点u与父节点p相联
	return solveOverflow(p);
}

template<typename T>
bool BTree<T>::remove(const T& e)
{
	BTNodePosi(T) v = search(e);
	if (!v)
		return false;

	Rank r = v->key.search(e);
	if (v->child[0]) //v非叶节点,深入右节点
	{
		BTNodePosi(T) u = v->child[r + 1];
		while (u->child[0])
			u = u->child[0];
		v->key[r] = u->key[0];
		v = u;
		r = 0;
	}

	v->key.remove(r);
	v->child.remove(r + 1);
	_size--;
	return true;
}


template<typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) v)
{
	if ((_order + 1) / 2 <= v->child.size())
		return;		//递归基
	BTNodePosi(T) p = v->parent;
	if (!p) //v是根节点
	{
		if (!v->key.size() && v->child[0]) //key为空，child第一个节点不为空
		{
			_root = v->child[0];
			_root->parent = NULL;
			v->child[0] = NULL;
			RELEASE(v);
		}
		return; //递归基
	}

	Rank r = 0;
	while (p->child[r] != v) //节点v在p的child中秩为r
		r++;

	if (0 < r) //存在左兄弟
	{
		BTNodePosi(T) lb = p->child[r - 1];//左兄弟必定存在
		if ((_order + 1) / 2 < lb->child.size()) //左兄弟够胖
		{
			v->key.insert(0, p->key[r - 1]);
			p->key[r - 1] = lb->key.remove(lb->key.size() - 1);
			v->child.insert(0, lb->child.remove(lb->child.size() - 1));
			if (v->child[0])
				v->child[0]->parent = v;
			return;
		}
	}

	if (r < p->child.size() - 1) //节点v存在右兄弟
	{
		BTNodePosi(T) rb = p->child[r + 1];
		if ((_order + 1) / 2 < rb->child.size()) //右兄弟够胖
		{
			v->key.insert(v->key.size(), p->key[r]);
			p->key[r] = rb->key.remove(0);
			v->child.insert(v->child.size(), rb->child.remove(0));
			if (v->child[v->child.size() - 1])
				v->child[v->child.size() - 1] = v;
			return;
		}
	}

	if (0 < r) //左兄弟够瘦
	{
		BTNodePosi(T) lb = p->child[r - 1];
		lb->key.insert(lb->key.size(), p->key.remove(r - 1)); //把节点p中关键码r-1,merge到lb中
		p->child.remove(r); //删除p关键秩对应的child
		lb->child.insert(lb->child.size(), v->child.remove(0));
		if (lb->child[lb->child.size() - 1])
			lb->child[lb->child.size() - 1] = lb;
		while (!v->key.empty()) //删除节点v
		{
			lb->key.insert(lb->key.size(), v->key.remove(0));
			lb->child.insert(lb->child.size(), v->child.remove(0));
			if (lb->child[lb->child.size() - 1])
				lb->child[lb->child.size() - 1]->parent = lb;
		}
		RELEASE(v);
	}
	else //右兄弟够胖
	{
		BTNodePosi(T) rb = p->child[r + 1];
		rb->key.insert(0, p->key.remove(r));//把p中秩为r元素remove到rb中
		p->child.remove(r);
		rb->child.insert(0, v->child.remove(v->child.size() - 1));
		while (!v->key.empty())
		{
			rb->key.insert(0, v->key.remove(v->key.size() - 1));
			rb->child.insert(0, v->child.remove(v->child.size() - 1));
			if (rb->child[0])
				rb->child[0]->parent = rb;
		}
		RELEASE(v);
	}

	return solveUnderflow(p);
}