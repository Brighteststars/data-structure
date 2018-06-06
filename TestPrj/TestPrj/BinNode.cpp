#include "binNode.h"
#include "Stack.h"
#include "Queue.h"


template<typename T>
int BinNode<T>::size() //ͳ�Ƶ�ǰ�ڵ㼰����������
{
	int s = 1;	// ��ǰ�ڵ�����
	if (lc)
		s += lc->size();
	if (rc)
		s += rc->size();
	return s;

}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLChild(T const& e) // �������ӽڵ㵽��ǰ�ڵ�
{
	return lc = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRChild(T const& e)
{
	return rc = new BinNode(e, this);
}

// �����������������
//�ӵ�ǰ�ڵ�������������֧�������룬ֱ��û�нڵ�
template<typename T,typename VST> //Ԫ�����ͣ�������
static void vistAlongLeftBrach(BinNodePosi(T) x, VST& visit,Stack<BinNodePosi(T)>& s)
{
	while (x)
	{
		visit(x->data); // ���ʵ�ǰԪ��
		if (HasRChild(x))
		{
			s.push(x->data); //�Һ�����ջ�ݴ�
		
		}
		x = x->lc; // �����֧����һ��
	}
}

template<typename T,typename VST>
void traPreModel(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> s; //����ջ
	while (true)
	{
		vistAlongLeftBrach(x, visit);
		if (s.empty()) //ֱ����ջ
			break;
		x = s.pop(); // ������һ�����
	}
}

template<typename T> template<typename VST>
void BinNode<T>::traPre(VST& visit)
{
	traPreModel(this, visit);
}


// �����������������

template<typename T>
static void goAlongLeftBrach(BinNodePosi(T) x, Stack<BinNodePosi(T)>& s)
{
	while (x) // ������ջ�������֧����
	{
		s.push(x);
		x = x->lc;
	}
}

template<typename T,typename VST>
void inorderTra(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> s;
	while (true)
	{
		goAlongLeftBrach(x, s);
		if (s.empty())
			break;
		x = s.pop();
		visit(x->data);
		x = x->rc;	// ����������������
	}
}

template<typename T> template<typename VST>
void BinNode<T>::traIn(VST& visit)	// �������
{
	inorderTra(this, visit);
}


template<typename T> template<typename VST>
void BinNode<T>::traLevel(VST& visit)		//��������α���
{
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);	//���ڵ����
	while (!Q.empty())
	{
		BinNodePosi(T) x = Q.dequeue();
		visit(x->data);
		if (HasLChild(*x))
			Q.enqueue(x->lc);	//�������
		if (HasRChild(*x))
			Q.enqueue(x->rc);	//�Һ������
	}
}

template<typename T,typename VST>
void traPostModel(BinNodePosi(T) x, VST& visit)	//�������������
{
	if (!x)
		return;
	traPostModel(x->lc);
	traPostModel(x->rc);
	visit(x->data);
}

template<typename T> template<typename VST>
void BinNode<T>::traPost(VST& visit)
{
	traPostModel(this, visit);
}

template<typename T>
BinNodePosi(T) BinNode<T>::succ() //��λ�ڵ�Vֱ�Ӻ��
{
	BinNodePosi(T) s = this;//��¼��̵���ʱ����
	if (rc)
	{
		s = rc;
		while (HasLChild(*s))
			s = s->lc; //���(��С)�ڵ�

	}
	else
	{
		while (IsRChild(*s))
			s = s->parent;
		s = s->parent;
	}
	return s;
}