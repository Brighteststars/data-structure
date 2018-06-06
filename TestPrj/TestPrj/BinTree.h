#ifndef BINTREE_H
#define BINTREE_H
#include "binNode.h"

template<typename T>
class BinTree{
protected:
	int _size;
	BinNodePosi(T) _root;	//���ڵ�
	virtual int updataHeight(BinNodePosi(T) x); // ���½ڵ�x�߶�
	void updataHeightAbove(BinNodePosi(T) x); //���½ڵ�x�������ȸ߶�
public:
	BinTree() : _size(0), _root(NULL){}
	~BinTree() { if _size > 0; remove(_root); }
	bool empty() const { return !_root; } // �п�
	int size() const { return _size; }
	BinNodePosi(T) insertAsRoot(T const& e);	//������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); // e��Ϊx��ڵ�(ԭ��)����
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); // e��Ϊx�ҽڵ�(ԭ��)����
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T); // T��Ϊx����������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T); // T��Ϊx����������
	int remove(BinNodePosi(T) x); //ɾ���Խڵ�xΪ��������,���ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T) x); //������x�ӵ�ǰ����ժ��,������ת��Ϊһ�Ŷ�������

// ����������
	template<typename VST> //������
	void traLevel(VST& visit) { if (_root) _root->traLevel(visit); } //��α���
	template<typename VST>
	void traPre(VST& visit) { if (_root) _root->traPre(visit); } //�������
	template<typename VST>
	void traIn(VST& visit) { if (_root) _root->traIn(visit); } //�������
	template<typename VST>
	void traPost(VST& visit){ if (_root) _root->traPost(visit); } //�������

	bool operator==(BinTree<T> const& t)		//�ж���
	{
		return _root && t._root && (_root == t._root);	//����
	}
	bool operator<(BinNode<T> const& t)
	{
		return _root && t._root && It(_root, t._root); //С��
	}

};

#endif