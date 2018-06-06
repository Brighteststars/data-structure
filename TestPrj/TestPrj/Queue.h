#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"

template<typename T>
class Queue : public List<T>
{
public:
	void enqueue(T const& e) { insertAsLast(e); } //入队：尾部插入
	T dequeue() { return remove(first()); }	// 出队：首部删除
	T& front() { return first()->data; }	// 队首
};


#endif