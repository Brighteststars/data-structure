#ifndef BINNODE_H
#define BINNODE_H
#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(x) ( (x) ? (x).height : -1)	//节点高度
typedef enum{ RB_RED, RB_BLACK } RB_Color; //节点颜色

//当前节点状态及其性质判断
#define  IsRoot(x) (!(x).parent) //非空
#define  IsLChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->lc))
#define  IsRChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->rc) )
#define  HasParent(x) (!IsRoot(x))
#define  HasLChild(x) ((x).lc)
#define  HasRChild(x) ((x).rc)
#define  HasChild(x) ( HasRChild(x) || HasLChild(x))
#define  HasBothChild(x) ( HasLChild(x) && HasRChild(x))
#define  IsLeaf(x) (!HasChild(x))
//与BinNode具有特定关系的节点及指针
#define  sibling(p) /*兄弟*/ \
	( IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define  uncle(p) /*叔叔*/ \
	( IsLChild(* ( (p)->parent ) ) ?  (p)->parent->parent->rc : (p)->parent->parent->lc)
#define FromParentTo(x) /*来自父亲的引用*/ \
	( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc) )

template<typename T>
struct BinNode{
// 成员
	T data; //数值
	BinNodePosi(T) parent;	//父节点
	BinNodePosi(T) lc; //左孩子节点
	BinNodePosi(T) rc;
	int height;
	int npl; // Null Path Length(左式堆）
	RB_Color c; //红黑树
// 构造函数
	BinNode()
		: parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), c(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0,
		int l = 1, RB_Color c = RB_RED)
		: data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), c(c){}
// 操作接口
	int size(); // 统计当前节点后代总数
	BinNodePosi(T) insertAsLChild(T const& e); // 作为当前节点左孩子插入
	BinNodePosi(T) insertAsRChild(T const& e);
	BinNodePosi(T) succ(); //取当前节点的直接后继
	template<typename VST> void traLevel(VST&); // 子树层次遍历
	template<typename VST> void traPre(VST&); // 子树先序遍历
	template<typename VST> void traIn(VST&); // 子树中序遍历
	template<typename VST> void traPost(VST&); // 子树后序遍历
// 比较器、判断器
	bool operator<(BinNode const& bn) { return data < bn.data; } //小于
	bool operator==(BinNode const& bn) { return data == bn.data; } //等于
};

#endif	