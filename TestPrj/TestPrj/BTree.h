#ifndef BTREE_H
#define BTREE_H
#include "BTNode.h"

template<typename T>
class BTree
{
protected:
	int _size;	//�ؼ�������
	int _order;	//B-���Ľ״�
	BTNodePosi(T) _root; //B-���ĸ�
	BTNodePosi(T) _hot;	//BTree::search()�����ҵķǿսڵ�
	void solveOverflow(BTNodePosi(T));//����������֮��ķ��Ѵ���
	void solveUnderflow(BTNodePosi(T));//��ɾ��������֮��ĺϲ�����
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

	BTNodePosi(T) search(const T& e); //����
	bool insert(const T& e); //����
	bool remove(const T& e); //ɾ��
};

#endif