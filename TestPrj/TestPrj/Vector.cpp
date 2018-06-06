#include "Vector.h"
#include <stdlib.h>

template<typename T>
Vector<T>::Vector(int c /* = DEFAULT_CAPACITY */, int s /* = 0 */, T v /* = 0 */)
{
	_elem = new T[_capacity = c];
	for (_size = 0; _size < s; _elem[_size++] = v);
}

template<typename T>
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)//拷贝构造函数,重新创造一个对象
{
	_elem = new T[_capacity = (hi - lo) * 2];//分配空间
	_size = 0;//规模清零
	while (lo < hi)
		_elem[_size++] = A[lo++];//复制至_elem[0,hi-lo)
}

template<typename T>
void Vector<T>::shrink()//缩容
{
	if (_capacity < DEFAULT_CAPACITY << 1)//缩容容量不能低于标准一半
		return;
	if (_capacity < _size << 2)//以25%为界
		return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];//容量减半
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];//复制原向量内容
	delete [] oldElem;
}
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem)
		delete[] _elem;//释放原有内容
	copyFrom(V._elem, 0, V.size());//整体复制
	return *this;
}

template<typename T>
void Vector<T>::expand()//向量空间不足时扩容
{
	if (_size < _capacity)//规模,容量
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity * 2];//容量加倍
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;//释放原空间
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
	expand();//若有必要,扩容
	for (int i = _size; r < i; i--)//自后向前,后继元素向后移动一个单元
		_elem[i] = _elem[i - 1];
	_elem[r] = e;//置入新元素并更新容量
	_size++;

	return r;//返回秩
}


template<typename T>
static Rank BinSearch(T* A, const T& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		int mi = (hi + lo) / 2;
		(e < A[mi]) ? hi = mi : lo = mi + 1;
	}//退出时hi = lo,lo为大于e的最小秩
	return --lo;//找到的元素接近e
}

template<typename T>
Rank Vector<T>::search(const T& e, Rank lo, Rank hi) const
{
	return BinSearch(_elem, e, lo, hi);
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)
		return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;//更新规模
	shrink();//若有必要缩容
	return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}


template<typename T>
Rank Vector<T>::patition(Rank lo, Rank hi)
{
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);
	int mi = lo;
	T pivot = _elem[lo];
	for (int i = lo + 1; i <= hi; i++)
	{
		if (_elem[i] < pivot)
			swap(_elem[++mi], _elem[i]);
	}
	swap(_elem[lo], _elem[mi]);
	return mi;
}

template<typename T>
void Vector<T>::quickSort(Rank lo, Rank hi)
{
	if (hi - lo < 2)
		return;
	Rank mi = patition(lo, hi - 1);
	quickSort(lo, mi);
	quickSort(mi + 1, hi);
}