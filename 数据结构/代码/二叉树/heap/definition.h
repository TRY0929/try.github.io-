#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

template <typename E>
class Heap
{
private:
    E* heap;
    int maxSize; //最大容量
    int n; //当前元素个数
public:
    Heap(E*h, int maxs,int n0):heap(h),maxSize(maxs),n(n0) {};
    void downAdjust(int pos);
    void buildHeap();
    void insert(E&val);
    E removeFirst();
    E remove(int pos);
};


#endif // DEFINITION_H_INCLUDED
