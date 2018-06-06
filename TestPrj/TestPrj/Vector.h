#ifndef VECTOR_H
#define VECTOR_H

typedef int Rank;//��
#define DEFAULT_CAPACITY  3

template<typename T>
class Vector{//����ģ����
protected:
	Rank _size;//��ģ
	int _capacity;//����
	T* _elem;//������

	void expand(); //�ռ䲻��ʱ����
	void shrink();//��װ���ӹ�Сʱѹ��
	void copyFrom(const T* A, Rank lo, Rank hi);//������������A[lo,hi)

	Rank patition(Rank lo, Rank hi); //��㹹���㷨
	void quickSort(Rank lo, Rank hi); //����
public:
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0);//����Ϊc,��ģΪs,����Ԫ�س�ʼ��Ϊv
	Vector(Vector<T> const& V){ copyFrom(V._elem, 0, V._size); }

	~Vector(){ delete[] _elem; }
//	ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	bool empty() const { return !_size; } //�п�
	Rank search(const T& e, Rank lo, Rank hi) const; //���������������
	Rank search(const T& e) const { return (_size <= 0) ? -1 : search(e, 0, _size); }//���������������

//	ֻд���ʽӿ�
	T& operator[](Rank i) const { return _elem[i]; }
	Vector<T> & operator=(Vector<T> const& V);
	Rank insert(Rank r, const T& e);//����Ԫ��
	Rank insert(const T& e) { insert(_size, e); }//Ĭ����ΪĩԪ�ز���
	int remove(Rank lo, Rank hi);//ɾ������[lo,hi)��Ԫ��
	T remove(Rank r); //ɾ����Ϊr��Ԫ��
};

#endif