#ifndef BST_H
#define BST_H
#include "BinTree.h"	//����BinTree


template<typename T>
class BST : public BinTree<T>
{
protected:
	BinNodePosi(T) _hot; //"����"�ڵ�ĸ���
	BinNodePosi(T) connect34(
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x); //��x���丸��,�游��ͳһ��ת
public:
	virtual BinNodePosi(T) & search(const T& e);//����
	virtual BinNodePosi(T) insert(const T& e);//����
	virtual bool remove(const T& e);//ɾ��
};

#endif