#ifndef STACK_H
#define STACK_H
#include "List.h"

template<typename T> 
class Stack : public List<T>
{
public:
	void push(T const& e) { insertAsLast(e); }
	T pop() { return remove(last()); }
	T& top() { return last()->data; }
};

#endif                                                            