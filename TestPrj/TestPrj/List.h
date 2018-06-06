#ifndef LIST_H
#define LIST_H
#include "ListNode.h"


template<typename T>
class List{


private:
	int _size; 
	Posi(T) header;
	Posi(T) trailer;

protected:
	void init();
	int clear();
	void selectionSort(Posi(T) p, int n);
	void insertionSort(Posi(T) p, int n);
	void copyNodes(Posi(T) p, int n);

	
public:
// ���캯��
	List(){ init(); }
	List(Posi(T) p, int n);
	List(List<T> const& L);
	List(List<T> const& L, Rank r, int n);
// ��������
	~List();

// ֻ�����ʽӿ�
	T& operator[](Rank r) const;
	bool empty() const { return _size <= 0; } //�п�
	Posi(T) find(T const& e, int n, Posi(T) p) const;
	Posi(T) find(T const& e) const 
	{
		return find(e, _size, trailer);
	}

	Posi(T) search(T const& e, int n, Posi(T) p) const;
	Posi(T) search(T const& e) const  { return search(e, _size, trailer); }

	Posi(T) first() const { return header->succ; }
	Posi(T) last() const { return trailer->pred; }
	Posi(T) selectMax(Posi(T) p, int n);
	int size() const { return _size; }

// ��д���ʽӿ�
	Posi(T) insertAsFirst(T const& e);
	Posi(T) insertAsLast(T const& e);
	Posi(T) insertA(Posi(T) p, T const& e);
	Posi(T) insertB(Posi(T) p, T const& e);

	T remove(Posi(T) p);
	int deduplicate();	// �����ظ�
	int uniquify();		//  Ψһ��
	void deEquData(Posi(T) p);	// ������p->data��ͬ�Ľڵ�

	

// ����
	
};



#endif