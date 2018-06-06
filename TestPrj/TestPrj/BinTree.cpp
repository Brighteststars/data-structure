#include "BinTree.h"

template<typename T>
int BinTree<T>::updataHeight(BinNodePosi(T) x)		//���½ڵ�x�߶�
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
void BinTree<T>::updataHeightAbove(BinNodePosi(T) x) //���½ڵ�x���丸�ڵ�߶�
{
	while (x){
		updataHeight(x);
		x = x->parent;
	}
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)		//��e�������ڵ����յĶ�����
{
	_size = 1;
	return _root = new BinNode(e);
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) //e������Ϊx����
{
	_size++;
	x->insertAsLChild(e);
	updataHeightAbove(x);
	return x->lc;
}


template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)//e������Ϊx�Һ���
{
	_size++;
	x->insertAsRChild(e);
	updataHeightAbove(x);
	return x->rc;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) //��T�ĸ��ڵ����x��ڵ�,������x
{
	if (x->lc = S->_root)	//����
		x->lc->parent = x;
	_size += S->size;		//����ȫ����ģ
	updataHeightAbove(x);	//����x�����������ȸ߶�

	S->_root = NULL;	
	S->size = 0;
	S->~BinTree();		//�ͷ�ԭ��
	S = NULL;
	return x;		//���ؽ���λ��
}

template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(x) = NULL;
	updataHeightAbove(x->parent);	//�������ȸ߶�
	int n = removeAt(x);	//ɾ������
	_size -= n;		//���¹�ģ
	return n;
}


template<typename T>
static int removeAt(BinNodePosi(T) x) //ɾ���������ڵ�x������,���ر�ɾ���Ĺ�ģ
{
	if (!x) //�п�,����
		return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);	//�ǿ���,��ģ��1,�ݹ��ͷ�����,����
	RELEASE(x->data); //ɾ���������ڵ��г�ԱT data
	delete x;	//ɾ���������ڵ�
	return n;
}

template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(x) = NULL;
	updataHeightAbove(x->parent);	//���½ڵ�x�游�ڵ�߶�
	BinTree<T>* S = new BinTree<T>;
	S->_root = x;		//����S��xΪ��
	x->parent = NULL;
	S->_size = x->size();
	_size -= S->_size; //����ԭ����ģ
	return S; //���ط������������
}