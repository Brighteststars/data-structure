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
// 构造函数
	List(){ init(); }
	List(Posi(T) p, int n);
	List(List<T> const& L);
	List(List<T> const& L, Rank r, int n);
// 析构函数
	~List();

// 只读访问接口
	T& operator[](Rank r) const;
	bool empty() const { return _size <= 0; } //判空
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

// 可写访问接口
	Posi(T) insertAsFirst(T const& e);
	Posi(T) insertAsLast(T const& e);
	Posi(T) insertA(Posi(T) p, T const& e);
	Posi(T) insertB(Posi(T) p, T const& e);

	T remove(Posi(T) p);
	int deduplicate();	// 消除重复
	int uniquify();		//  唯一化
	void deEquData(Posi(T) p);	// 消除与p->data相同的节点

	

// 遍历
	
};



#endif