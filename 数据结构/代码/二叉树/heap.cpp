#include <iostream>

using namespace std;
void downAdjust(int heap[],int low,int high)
//对heap数组在[low,high]范围进行向下调整；
//其中low为欲调整结点的数组下标，high一般为堆的最后一个元素的数组下标；
{
    int i=low,i_child=i*2; //利用了完全二叉树的性质
    while(i_child<=high) {
        if(i_child+1 <= high && heap[i_child]<heap[i_child+1])
            //若右孩子存在且大于左孩子，则child记录较大的这个
            ++i_child;
        if(heap[i] < heap[i_child]) {
            swap(heap[i],heap[i_child]);
            i = i_child; //调整完继续向下找子节点
            i_child = i*2;
        }
        else break;
    }
}
void upAdjust(int heap[],int low,int high)
{//向上调整，那此时high就是要调整的结点，low一般为根节点
    int i=high,i_parent=high/2;
    while(i_parent >= low) {
        if(heap[i] > heap[i_parent]) {
            swap(heap[i],heap[i_parent]);
            i = i_parent;
            i_parent = i/2;
        }
        else break;
    }
}
void insert(int val,int n,int heap[])
{//val要插入到有n个结点的heap堆中
    heap[++n] = val;
    upAdjust(heap,1,n);
}
void createHeap(int a[],int n)
{
    for(int i=n/2;i>0;--i)
        downAdjust(a,i,n);
}
void heapSort(int n,int heap[])
{
    createHeap(heap,n);
    for(int i=n;i>1;--i) {
        swap(heap[1],heap[i]);
        downAdjust(heap,1,i-1);
    }
}
void deleteTop(int heap[],int n)
{
    swap(heap[1],heap[n--]);
    downAdjust(heap,1,n);
}
int main()
{
    int n; cin >> n;
    int heap[n+1];
    for(int i=1;i<=n;++i) //注意下标从1开始的
        cin >> heap[i];
//    createHeap(heap,n);
    heapSort(n,heap);
    for(int i=1;i<=n;++i)
        cout << heap[i] << ' ';
    return 0;
}
