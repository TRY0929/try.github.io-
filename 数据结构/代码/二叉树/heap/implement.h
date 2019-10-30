#ifndef IMPLEMENT_H_INCLUDED
#define IMPLEMENT_H_INCLUDED
#include <iostream>
#include <queue>
#include "definition.h"
using namespace std;
template <typename E>
void Heap<E>::downAdjust(int pos,int End)
{
    int child=pos*2+1; //左孩子
    while(pos*2+1<n && child<=End) { //不是叶节点
        if(child+1 <= End) {
            if(heap[child+1]>heap[child]) ++child;
        }
        if(heap[child]>heap[pos]) {
            swap(heap[child],heap[pos]);
            pos = child;
            child = pos*2+1;
        }
        else break;
    }
}
template <typename E>
void Heap<E>::buildHeap()
{
    for(int i=n/2;i>=0;--i)
        downAdjust(i,n-1);
}
template <typename E>
void Heap<E>::insert(E&val)
{
    if(n+1>maxSize) {
        cout << "insert failed";
        return ;
    }
    heap[n] = val;
    int cur = n;
    while(cur!=0 && heap[cur]>heap[(cur-1)/2]) {
        swap(heap[cur],heap[(cur-1)/2]);
        cur = (cur-1)/2;
    }
}
template <typename E>
E Heap<E>::removeFirst()
{
    swap(heap[0],heap[--n]);
    downAdjust(0);
    return heap[n];
}
template <typename E>
E Heap<E>::remove(int pos)
{
    if(pos<0 || pos>=n) {
        cout << "illegal position";
        return -1;
    }
    if(pos==n) return heap[--n];
    else {
        swap(heap[pos],heap[--n]);
        while(pos>0 && heap[pos]>heap[(pos-1)/2]) { //先上拉
            swap(heap[pos],heap[(pos-1)/2]);
            pos = (pos-1)/2;
        }
        if(n!=0) downAdjust(pos); //再下拉
    }
    return heap[n];
}
template <typename E>
void Heap<E>::heapSort()
{
    for(int i=n-1;i>=0;--i) {
        swap(heap[0],heap[i]);
        downAdjust(0,i-1);
    }
}
template <typename E>
void Heap<E>::levelOrder()
{
    for(int i=0;i<n;++i) //数组中存放的顺序就是层序遍历
        cout << heap[i] << ' ';
}
#endif // IMPLEMENT_H_INCLUDED
