#include <iostream>
#include "implement.h"
using namespace std;

int main()
{
    cout << endl << "******************************������ֻ������������****************************" << endl << endl;
	cout << "ADT�嵥��" << endl;
	cout << "1.void insert(Node* r, int key, int ele); ����һ�����" << endl;
	cout << "2.void clear(Node* r); �����" << endl;
	cout << "3.Node* remove(int key); ���߽�㣬�ж��ʱɾ���ɸ���Ҷ�ĵ�һ���������ڷ���NULL" << endl;
	cout << "4.Node* deletemin(Node* r,int time = 0); ɾ�����е���Сֵ����������ڣ�����NULL" << endl;
	cout << "5.Node* findmin(Node* r); �ҵ����е���Сֵ����������ڣ�����NULL" << endl;
	cout << "6.bool intree(int key); �жϼ���ֵΪkey��Ԫ���Ƿ�������" << endl;
	cout << "7.void preorder(Node* r); �����������(���keyֵ���Կ������������������ͬ)" << endl;
	cout << "8.void indorder(Node* r); �����������" << endl;
	cout << "9.void postorder(Node* r); �����������" << endl;
	cout << "10.void levelorder(Node* r); �����������" << endl;
	cout << "0. Enter 0 to quit" << endl << endl ;
    return 0;
}
