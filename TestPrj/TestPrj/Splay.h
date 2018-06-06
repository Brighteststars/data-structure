#ifndef SPLAY_H
#define SPLAY_H

#include "BST.h"

template<typename T>
class Splay : public BST<T>
{
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v);//�ӽڵ�v�����¶�����չ
public:
	BinNodePosi(T) & search(const T& e);//����(��д)
	BinNodePosi(T) insert(const T& e);//����
	bool remove(const T& e);//ɾ��
};

#endif