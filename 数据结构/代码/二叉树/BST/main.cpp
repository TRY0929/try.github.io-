#include <iostream>
#include "implement.h"
using namespace std;

int main()
{
    cout << endl << "******************************本程序只允许输入整数****************************" << endl << endl;
	cout << "ADT清单：" << endl;
	cout << "1.void insert(Node* r, int key, int ele); 插入一个结点" << endl;
	cout << "2.void clear(Node* r); 清空树" << endl;
	cout << "3.Node* remove(int key); 移走结点，有多个时删除由根到叶的第一个，不存在返回NULL" << endl;
	cout << "4.Node* deletemin(Node* r,int time = 0); 删除树中的最小值，如果不存在，返回NULL" << endl;
	cout << "5.Node* findmin(Node* r); 找到树中的最小值，如果不存在，返回NULL" << endl;
	cout << "6.bool intree(int key); 判断检索值为key的元素是否在树中" << endl;
	cout << "7.void preorder(Node* r); 先序遍历该树(输出key值，对空树仅输出遍历名，下同)" << endl;
	cout << "8.void indorder(Node* r); 中序遍历该树" << endl;
	cout << "9.void postorder(Node* r); 后序遍历该树" << endl;
	cout << "10.void levelorder(Node* r); 层序遍历该树" << endl;
	cout << "0. Enter 0 to quit" << endl << endl ;
    return 0;
}
