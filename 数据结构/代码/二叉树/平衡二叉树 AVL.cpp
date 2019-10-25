#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 105;
int n,data[maxn];
struct Node
{
	int data;
	int height;
	Node* lchild;
	Node* rchild;
};
Node* newNode(int x)
{
	Node* node = new Node;
	node->data = x;
	node->height = 1;
	node->lchild = node->rchild = NULL;
	return node;
}
int getHeight(Node* node)
{
	if(node == NULL) return 0;
	return node->height;
}
int getBalanceFactor(Node* root)
{
	return getHeight(root->lchild) - getHeight(root->rchild);
}
void updateHeight(Node* &root)
{
	root->height = max(getHeight(root->lchild),getHeight(root->rchild))+1;
}
void L(Node* &root)
{
	Node* tmp = root->rchild;
	root->rchild = tmp->lchild;
	tmp->lchild = root;
	updateHeight(root);
	updateHeight(tmp);
	root = tmp;
}
void R(Node* &root)
{
	Node* tmp = root->lchild;
	root->lchild = tmp->rchild;
	tmp->rchild = root;
	updateHeight(root);
	updateHeight(tmp);
	root = tmp;
}
void insert(Node* &root,int x)
{
	if(root == NULL) {
		root = newNode(x);
		return ;
	}
	if(root->data > x) {
		insert(root->lchild,x);
		updateHeight(root);
		if(getBalanceFactor(root) == 2) {
			if(getBalanceFactor(root->lchild) == 1) {
				R(root);
			}
			else if(getBalanceFactor(root->lchild) == -1) {
				L(root->lchild);
				R(root);
			}
		}
		
	}
	else {
		insert(root->rchild,x);
		updateHeight(root);
		if(getBalanceFactor(root) == -2) {
			if(getBalanceFactor(root->rchild) == 1) {
				R(root->rchild);
				L(root);
			}
			else if(getBalanceFactor(root->lchild) == -1) {
				L(root);
			}
		}
	}
}
Node* create()
{
	Node* root = NULL;
	for(int i=0;i<n;++i) {
		insert(root,data[i] );
	}
	return root;
}
int main()
{
	
	return 0;
}
