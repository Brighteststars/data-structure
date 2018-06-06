#include "Vector.h"
#include <stdlib.h>

template<typename T>
Vector<T>::Vector(int c /* = DEFAULT_CAPACITY */, int s /* = 0 */, T v /* = 0 */)
{
	_elem = new T[_capacity = c];
	for (_size = 0; _size < s; _elem[_size++] = v);
}

template<typename T>
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)//�������캯��,���´���һ������
{
	_elem = new T[_capacity = (hi - lo) * 2];//����ռ�
	_size = 0;//��ģ����
	while (lo < hi)
		_elem[_size++] = A[lo++];//������_elem[0,hi-lo)
}

template<typename T>
void Vector<T>::shrink()//����
{
	if (_capacity < DEFAULT_CAPACITY << 1)//�����������ܵ��ڱ�׼һ��
		return;
	if (_capacity < _size << 2)//��25%Ϊ��
		return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];//��������
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];//����ԭ��������
	delete [] oldElem;
}
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem)
		delete[] _elem;//�ͷ�ԭ������
	copyFrom(V._elem, 0, V.size());//���帴��
	return *this;
}

template<typename T>
void Vector<T>::expand()//�����ռ䲻��ʱ����
{
	if (_size < _capacity)//��ģ,����
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity * 2];//�����ӱ�
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;//�ͷ�ԭ�ռ�
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
	expand();//���б�Ҫ,����
	for (int i = _size; r < i; i--)//�Ժ���ǰ,���Ԫ������ƶ�һ����Ԫ
		_elem[i] = _elem[i - 1];
	_elem[r] = e;//������Ԫ�ز���������
	_size++;

	return r;//������
}


template<typename T>
static Rank BinSearch(T* A, const T& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		int mi = (hi + lo) / 2;
		(e < A[mi]) ? hi = mi : lo = mi + 1;
	}//�˳�ʱhi = lo,loΪ����e����С��
	return --lo;//�ҵ���Ԫ�ؽӽ�e
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
	_size = lo;//���¹�ģ
	shrink();//���б�Ҫ����
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