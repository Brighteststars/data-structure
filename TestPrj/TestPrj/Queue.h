#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"

template<typename T>
class Queue : public List<T>
{
public:
	void enqueue(T const& e) { insertAsLast(e); } //��ӣ�β������
	T dequeue() { return remove(first()); }	// ���ӣ��ײ�ɾ��
	T& front() { return first()->data; }	// ����
};


#endif