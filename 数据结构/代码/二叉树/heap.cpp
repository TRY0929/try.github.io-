#include <iostream>

using namespace std;
void downAdjust(int heap[],int low,int high)
//��heap������[low,high]��Χ�������µ�����
//����lowΪ���������������±꣬highһ��Ϊ�ѵ����һ��Ԫ�ص������±ꣻ
{
    int i=low,i_child=i*2; //��������ȫ������������
    while(i_child<=high) {
        if(i_child+1 <= high && heap[i_child]<heap[i_child+1])
            //���Һ��Ӵ����Ҵ������ӣ���child��¼�ϴ�����
            ++i_child;
        if(heap[i] < heap[i_child]) {
            swap(heap[i],heap[i_child]);
            i = i_child; //����������������ӽڵ�
            i_child = i*2;
        }
        else break;
    }
}
void upAdjust(int heap[],int low,int high)
{//���ϵ������Ǵ�ʱhigh����Ҫ�����Ľ�㣬lowһ��Ϊ���ڵ�
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
{//valҪ���뵽��n������heap����
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
    for(int i=1;i<=n;++i) //ע���±��1��ʼ��
        cin >> heap[i];
//    createHeap(heap,n);
    heapSort(n,heap);
    for(int i=1;i<=n;++i)
        cout << heap[i] << ' ';
    return 0;
}
