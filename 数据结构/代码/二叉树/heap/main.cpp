#include <iostream>
#include "implement.h"
using namespace std;

int main()
{

    int a[] = {5,1,3,6,7,2,9,0,10};
    Heap<int> h(a,20,9);
    h.buildHeap();
    //���Ѻ�Ĳ������
    h.levelOrder(); cout << endl;
    h.heapSort();
    h.levelOrder();
    return 0;
}
