#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 105;
struct Node
{
	int data;
	Node* lchild;
	Node* rchild;
}node[maxn];
void Search(Node* root,int x)
{
	if(root == NULL) {
		printf("Search failed!\n");
		return ;
	}
	if(root->data == x) {
		printf("%d",root->data);
		return ;
	}
	else if(root->data > x) {
		Search(root->lchild,x); 
	} else Search(root->rchild,x);
}
Node* newNode(int x)
{
	Node* root = new Node;
	root->data = x;
	root->lchild = root->rchild = NULL;
	return root;
}
void insert(Node* &root,int x)
{
	if(root == NULL) {
		root = newNode(x);
		return ;
	}
	if(root->data == x) return ;
	else if(root->data > x) insert(root->lchild,x);
	else insert(root->rchild,x);
}
Node* FindMax(Node* root)
{
	while(root->rchild != NULL)
		root = root->rchild;
	return root;
}
Node* FindMin(Node* root)
{
	while(root->lchild != NULL)
		root = root->rchild;
	return root;
}
Node* Create(int data[],int n)
{
	Node* root = new Node;
	root = NULL;
	for(int i=0;i<n;++i) {
		insert(root,data[i]);
	}
	return root;
}
void deleteNode(Node* &root,int x)
{
	Node* pre,*next;
	if(root == NULL) return ;
	if(root->data == x) {
		if(root->lchild == NULL && root->rchild == NULL) root = NULL;
		else if(root->lchild != NULL) {
			pre = FindMax(root->lchild);
			root->data = pre->data;
			deleteNode(root->lchild,pre->data);
		}
		else {
			next = FindMin(root->rchild);
			root->data = next->data;
			deleteNode(root->rchild,next->data);
		}
	}
	else if(root->data > x) {
		deleteNode(root->lchild,x);
	} else deleteNode(root->rchild,x);
}
int main()
{
	
	return 0;
}
