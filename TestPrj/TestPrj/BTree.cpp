#include "BTree.h"

template<typename T>
BTNodePosi(T)  BTree<T>::search(const T& e)
{
	BTNodePosi(T) v = _root; //�Ӹ��ڵ㿪ʼ����
	_hot = NULL;

	while (v)//������
	{
		Rank r = v->key.search(e); //�ڵ�ǰ�ڵ��в��Ҳ�����e�����ֵ
		if ((0 <= r) && (e == v->key[r]))
			return v;
		_hot = v;
		v = v->child[r + 1];
	}
	return NULL; //ʧ�ִܵ��ⲿ�ڵ�
}

template<typename T>
bool BTree<T>::insert(const T& e)
{
	BTNodePosi(T) v = search(e);
	if (v)
		return false;
	Rank r = _hot->key.search(e); //�ڽڵ�_hot����ؼ����в��Ҳ���λ��
	_hot->key.insert(r + 1, e);
	_hot->child.insert(r + 2, NULL); //����һ��������ָ��
	_size++; //����ȫ����ģ
	solveOverflow(_hot); //���б�Ҫ,��������
	return true;
}

template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)
{
	if (v->child.size() <= _order)
		return; //�ݹ��
	Rank s = _order; // _order = n,��λ��s
	BTNodePosi(T) u = new BTNode<T>(); //�����սڵ�u
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

	Rank r = 1 + p->key.search(v->key[0]);//p��key��ָ��u����
	p->key.insert(r, v->key.remove(s));
	p->child.insert(r + 1, u);
	u->parent = u;//�½ڵ�u�븸�ڵ�p����
	return solveOverflow(p);
}

template<typename T>
bool BTree<T>::remove(const T& e)
{
	BTNodePosi(T) v = search(e);
	if (!v)
		return false;

	Rank r = v->key.search(e);
	if (v->child[0]) //v��Ҷ�ڵ�,�����ҽڵ�
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
		return;		//�ݹ��
	BTNodePosi(T) p = v->parent;
	if (!p) //v�Ǹ��ڵ�
	{
		if (!v->key.size() && v->child[0]) //keyΪ�գ�child��һ���ڵ㲻Ϊ��
		{
			_root = v->child[0];
			_root->parent = NULL;
			v->child[0] = NULL;
			RELEASE(v);
		}
		return; //�ݹ��
	}

	Rank r = 0;
	while (p->child[r] != v) //�ڵ�v��p��child����Ϊr
		r++;

	if (0 < r) //�������ֵ�
	{
		BTNodePosi(T) lb = p->child[r - 1];//���ֵܱض�����
		if ((_order + 1) / 2 < lb->child.size()) //���ֵܹ���
		{
			v->key.insert(0, p->key[r - 1]);
			p->key[r - 1] = lb->key.remove(lb->key.size() - 1);
			v->child.insert(0, lb->child.remove(lb->child.size() - 1));
			if (v->child[0])
				v->child[0]->parent = v;
			return;
		}
	}

	if (r < p->child.size() - 1) //�ڵ�v�������ֵ�
	{
		BTNodePosi(T) rb = p->child[r + 1];
		if ((_order + 1) / 2 < rb->child.size()) //���ֵܹ���
		{
			v->key.insert(v->key.size(), p->key[r]);
			p->key[r] = rb->key.remove(0);
			v->child.insert(v->child.size(), rb->child.remove(0));
			if (v->child[v->child.size() - 1])
				v->child[v->child.size() - 1] = v;
			return;
		}
	}

	if (0 < r) //���ֵܹ���
	{
		BTNodePosi(T) lb = p->child[r - 1];
		lb->key.insert(lb->key.size(), p->key.remove(r - 1)); //�ѽڵ�p�йؼ���r-1,merge��lb��
		p->child.remove(r); //ɾ��p�ؼ��ȶ�Ӧ��child
		lb->child.insert(lb->child.size(), v->child.remove(0));
		if (lb->child[lb->child.size() - 1])
			lb->child[lb->child.size() - 1] = lb;
		while (!v->key.empty()) //ɾ���ڵ�v
		{
			lb->key.insert(lb->key.size(), v->key.remove(0));
			lb->child.insert(lb->child.size(), v->child.remove(0));
			if (lb->child[lb->child.size() - 1])
				lb->child[lb->child.size() - 1]->parent = lb;
		}
		RELEASE(v);
	}
	else //���ֵܹ���
	{
		BTNodePosi(T) rb = p->child[r + 1];
		rb->key.insert(0, p->key.remove(r));//��p����ΪrԪ��remove��rb��
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