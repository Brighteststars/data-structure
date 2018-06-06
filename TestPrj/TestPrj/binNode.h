#ifndef BINNODE_H
#define BINNODE_H
#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(x) ( (x) ? (x).height : -1)	//�ڵ�߶�
typedef enum{ RB_RED, RB_BLACK } RB_Color; //�ڵ���ɫ

//��ǰ�ڵ�״̬���������ж�
#define  IsRoot(x) (!(x).parent) //�ǿ�
#define  IsLChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->lc))
#define  IsRChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->rc) )
#define  HasParent(x) (!IsRoot(x))
#define  HasLChild(x) ((x).lc)
#define  HasRChild(x) ((x).rc)
#define  HasChild(x) ( HasRChild(x) || HasLChild(x))
#define  HasBothChild(x) ( HasLChild(x) && HasRChild(x))
#define  IsLeaf(x) (!HasChild(x))
//��BinNode�����ض���ϵ�Ľڵ㼰ָ��
#define  sibling(p) /*�ֵ�*/ \
	( IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define  uncle(p) /*����*/ \
	( IsLChild(* ( (p)->parent ) ) ?  (p)->parent->parent->rc : (p)->parent->parent->lc)
#define FromParentTo(x) /*���Ը��׵�����*/ \
	( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc) )

template<typename T>
struct BinNode{
// ��Ա
	T data; //��ֵ
	BinNodePosi(T) parent;	//���ڵ�
	BinNodePosi(T) lc; //���ӽڵ�
	BinNodePosi(T) rc;
	int height;
	int npl; // Null Path Length(��ʽ�ѣ�
	RB_Color c; //�����
// ���캯��
	BinNode()
		: parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), c(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0,
		int l = 1, RB_Color c = RB_RED)
		: data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), c(c){}
// �����ӿ�
	int size(); // ͳ�Ƶ�ǰ�ڵ�������
	BinNodePosi(T) insertAsLChild(T const& e); // ��Ϊ��ǰ�ڵ����Ӳ���
	BinNodePosi(T) insertAsRChild(T const& e);
	BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
	template<typename VST> void traLevel(VST&); // ������α���
	template<typename VST> void traPre(VST&); // �����������
	template<typename VST> void traIn(VST&); // �����������
	template<typename VST> void traPost(VST&); // �����������
// �Ƚ������ж���
	bool operator<(BinNode const& bn) { return data < bn.data; } //С��
	bool operator==(BinNode const& bn) { return data == bn.data; } //����
};

#endif	