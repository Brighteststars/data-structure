#include "binNode.h"
#include "Stack.h"
#include "Queue.h"


template<typename T>
int BinNode<T>::size() //统计当前节点及其子树总数
{
	int s = 1;	// 当前节点总数
	if (lc)
		s += lc->size();
	if (rc)
		s += rc->size();
	return s;

}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLChild(T const& e) // 插入左孩子节点到当前节点
{
	return lc = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRChild(T const& e)
{
	return rc = new BinNode(e, this);
}

// 二叉树先序迭代遍历
//从当前节点出发，沿着左分支不断深入，直至没有节点
template<typename T,typename VST> //元素类型，操作器
static void vistAlongLeftBrach(BinNodePosi(T) x, VST& visit,Stack<BinNodePosi(T)>& s)
{
	while (x)
	{
		visit(x->data); // 访问当前元素
		if (HasRChild(x))
		{
			s.push(x->data); //右孩子入栈暂存
		
		}
		x = x->lc; // 沿左分支深入一层
	}
}

template<typename T,typename VST>
void traPreModel(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> s; //辅助栈
	while (true)
	{
		vistAlongLeftBrach(x, visit);
		if (s.empty()) //直到空栈
			break;
		x = s.pop(); // 弹出下一批起点
	}
}

template<typename T> template<typename VST>
void BinNode<T>::traPre(VST& visit)
{
	traPreModel(this, visit);
}


// 二叉树中序遍历迭代

template<typename T>
static void goAlongLeftBrach(BinNodePosi(T) x, Stack<BinNodePosi(T)>& s)
{
	while (x) // 反复入栈，沿左分支深入
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
		x = x->rc;	// 从右子树继续迭代
	}
}

template<typename T> template<typename VST>
void BinNode<T>::traIn(VST& visit)	// 中序迭代
{
	inorderTra(this, visit);
}


template<typename T> template<typename VST>
void BinNode<T>::traLevel(VST& visit)		//二叉树层次遍历
{
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);	//根节点入队
	while (!Q.empty())
	{
		BinNodePosi(T) x = Q.dequeue();
		visit(x->data);
		if (HasLChild(*x))
			Q.enqueue(x->lc);	//左孩子入队
		if (HasRChild(*x))
			Q.enqueue(x->rc);	//右孩子入队
	}
}

template<typename T,typename VST>
void traPostModel(BinNodePosi(T) x, VST& visit)	//二叉树后序遍历
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
BinNodePosi(T) BinNode<T>::succ() //定位节点V直接后继
{
	BinNodePosi(T) s = this;//记录后继的临时变量
	if (rc)
	{
		s = rc;
		while (HasLChild(*s))
			s = s->lc; //最靠左(最小)节点

	}
	else
	{
		while (IsRChild(*s))
			s = s->parent;
		s = s->parent;
	}
	return s;
}