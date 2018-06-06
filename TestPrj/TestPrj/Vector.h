#ifndef VECTOR_H
#define VECTOR_H

typedef int Rank;//秩
#define DEFAULT_CAPACITY  3

template<typename T>
class Vector{//向量模板类
protected:
	Rank _size;//规模
	int _capacity;//容量
	T* _elem;//数据区

	void expand(); //空间不足时扩容
	void shrink();//填装因子过小时压缩
	void copyFrom(const T* A, Rank lo, Rank hi);//复制数组区间A[lo,hi)

	Rank patition(Rank lo, Rank hi); //轴点构造算法
	void quickSort(Rank lo, Rank hi); //快排
public:
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0);//容量为c,规模为s,所有元素初始化为v
	Vector(Vector<T> const& V){ copyFrom(V._elem, 0, V._size); }

	~Vector(){ delete[] _elem; }
//	只读访问接口
	Rank size() const { return _size; } //规模
	bool empty() const { return !_size; } //判空
	Rank search(const T& e, Rank lo, Rank hi) const; //有序向量区间查找
	Rank search(const T& e) const { return (_size <= 0) ? -1 : search(e, 0, _size); }//有序向量整体查找

//	只写访问接口
	T& operator[](Rank i) const { return _elem[i]; }
	Vector<T> & operator=(Vector<T> const& V);
	Rank insert(Rank r, const T& e);//插入元素
	Rank insert(const T& e) { insert(_size, e); }//默认作为末元素插入
	int remove(Rank lo, Rank hi);//删除区间[lo,hi)中元素
	T remove(Rank r); //删除秩为r的元素
};

#endif