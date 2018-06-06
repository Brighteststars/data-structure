#include "List.h"

template<typename T>
void List<T>::init()
{
	header = new ListNode<T>;	
	trailer = new ListNode<T>;
	header->succ = trailer; 
	header->pred = NULL;

	trailer->pred = header; 
	trailer->succ = NULL;
	_size = 0;
}

template<typename T>
T& List<T>::operator[](Rank r) const
{
	Posi(T) p = first();
	while (r-- > 0)
		p = p->succ;
	return p->data;
}

template<typename T>
Posi(T) List<T>::find(T const& e, int n, Posi(T)p) const
{
	while (n-- > 0){
		if (((p = p->pred)->data) == e)
			return p;
	}
	return NULL;
}

template<typename T>
Posi(T) List<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
Posi(T) List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template<typename T>
Posi(T) List<T>::insertA(Posi(T) p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
Posi(T) List<T>::insertB(Posi(T) p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
void List<T>::copyNodes(Posi(T) p, int n)
{
	init();
	while (n--){
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
List<T>::List(Posi(T) p, int n)
{
	copyNodes(p, n);
}

template<typename T>
List<T>::List(List<T> const& L)
{
	copyNodes(L.first(), L._size);
}

template<typename T>
List<T>::List(List<T> const& L, Rank r, int n)
{
	copyNodes(L[r], n);
}




template <typename T>
List<T>::~List()
{
	clear();
	delete header; 
	delete trailer;
}

template<typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (_size > 0)
		remove(header->succ);
	return oldSize;
}

template<typename T>
T List<T>::remove(Posi(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p; 
	_size--;
	return e;
}

template<typename T>
Posi(T) List<T>::search(T const& e, int n, Posi(T) p) const
{
	while (0 <= n--)
	{
		if ((p = p->pred)->data <= e)
			return p;
	}
}

template<typename T>
int List<T>::deduplicate()
{
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi(T) p = first(); Rank r = 1;
	while (trailer != (p = p->succ))
	{
		Posi(T) q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
	return oldSize - _size;
}

template<typename T>
int List<T>::uniquify()
{
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi(T) p = first(); Posi(T) q;
	while (trailer != (q = p->succ))
	{
		if (q->succ != p->succ)
			p = q;
		else
			remove(q);
	}
	return oldSize - _size;
}

template<typename T>
void List<T>::insertionSort(Posi(T) p, int n)
{
	for (int r = 0; r < n; r++)
	{
		insertA(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

template<typename T>
void List<T>::selectionSort(Posi(T) p, int n)
{
	Posi(T) head = p->pred;
	Posi(T) tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->succ;
	while (n > 1)
	{
		Posi(T) max = selectMax(p, n);
		insertB(tail, remove(max));
		tail = tail->pred;
		n--;
	}
}

template<typename T>
bool lt(T& a, T& b)
{
	return a < b;
}

template<typename T>
Posi(T) List<T>::selectMax(Posi(T) p, int n)
{
	Posi(T) max = p;
	for (Posi(T) cur = p; n > 1; n--)
	{
		cur = cur->succ;
		if (!lt(cur->data, max->data))
			return max = cur;
	}
	return max;
}




template<typename T>
void List<T>::deEquData(Posi(T) p)
{

	Posi(T) q = first();
	while (q != trailer){
		q = q->succ;
		if (q->pred->data == p->data)
			remove(q->pred);
	}
}