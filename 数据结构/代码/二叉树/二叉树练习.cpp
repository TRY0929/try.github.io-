//中序遍历分别和前、中、后、层序遍历来还原二叉树 

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 105;
int pre[maxn],in[maxn],post[maxn],lay[maxn],post0[maxn];
struct Node
{
	int data;
	Node* lchild;
	Node* rchild;
	Node* layer;
};
void preorder(Node* root)
{
	if(root == NULL) return ;
	
	printf("%d ",root->data);
	preorder(root->lchild);
	preorder(root->rchild);
}
void inorder(Node* root)
{
	if(root == NULL) return ;
	
	inorder(root->lchild);
	printf("%d ",root->data);
	inorder(root->rchild);
}
void postorder(Node* root)
{
	if(root == NULL) return ;
	
	postorder(root->lchild);
	postorder(root->rchild);
	printf("%d ",root->data);
}
void LayerOrder(Node* root)
{
	queue<Node*> q;
	if(root != NULL) q.push(root);
	while(!q.empty()) {
		root = q.front();
		q.pop();
		printf("%d",root->data);
		if(root->lchild != NULL) q.push(root->lchild);
		if(root->rchild != NULL) q.push(root->rchild);
		if(!q.empty()) printf(" ");
	}
}
Node* create1(int preL,int preR,int inL,int inR) //前+中
{
	if(preL > preR) return NULL;
	int k = 0,numLeft;
	Node* root = new Node;
	root->data = pre[preL];
	
	for(k=inL;k<=inR;++k)
		if(in[k] == pre[preL]) break;
	numLeft = k-inL;
	
	root->lchild = create1(preL+1,preL+numLeft,inL,k-1);
	root->rchild = create1(preL+numLeft+1,preR,k+1,inR);
	return root; 
}
Node* create2(int postL,int postR,int inL,int inR) //后+中 
{
	if(postL > postR) return NULL;
	int k,numLeft;
	Node* root = new Node;
	root->data = post[postR];
	
	for(k=inL;k<=inR;++k)
		if(in[k] == post[postR]) break;
	numLeft = k-inL;
	
	root->lchild = create2(postL,postL+numLeft-1,inL,k-1);
	root->rchild = create2(postL+numLeft,postR-1,k+1,inR);
	
	return root;
}
Node* create3(int inL,int inR,int post[],int n) //层+中 
{
	if(n <= 0 || inL > inR) return NULL;
	int indexL = 0,indexR = 0,k,numLeft,postL[maxn],postR[maxn];
	Node* root = new Node;
	root->data = post[0];
	
	for(k=inL;k<=inR;++k)
		if(in[k] == post[0]) break;
		
	for(int j=0;j<n;++j) {
		for(int i=inL;i<k;++i) {
			if(in[i] == post[j]) postL[indexL++] = post[j];
		}
	}
	for(int j=0;j<n;++j) {
		for(int i=k+1;i<=inR;++i) {
			if(in[i] == post[j]) postR[indexR++] = post[j];
		}
	}
	
	root->lchild = create3(inL,k-1,postL,indexL);
	root->rchild = create3(k+1,inR,postR,indexR);
	
	return root;
}
int main()
{
	int n;
//	while((scanf("%d",&n))!=EOF) {
//		if(n==0) break;
		scanf("%d",&n);
		for(int i=0;i<n;++i)
			scanf("%d",&lay[i]);
//		for(int i=0;i<n;++i)
//			scanf("%d",&pre[i]);
		for(int i=0;i<n;++i)
			scanf("%d",&in[i]);
//		Node* root = create1(0,n-1,0,n-1);
//		LayerOrder(root);
		Node* root = create3(0,n-1,lay,n);
		preorder(root);
//		printf("\n");a
//	}
	
	return 0;
}
