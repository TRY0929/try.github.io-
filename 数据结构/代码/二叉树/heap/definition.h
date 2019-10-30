#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

template <typename E>
class Heap
{
private:
    E* heap;
    int maxSize; //�������
    int n; //��ǰԪ�ظ���
public:
    Heap(E*h, int maxs,int n0):heap(h),maxSize(maxs),n(n0) {};
    int size() {return n;}
    void downAdjust(int start,int End);
    void buildHeap();
    void insert(E&val);
    E removeFirst();
    E remove(int pos);
    void heapSort();
    void levelOrder();
};


#endif // DEFINITION_H_INCLUDED
