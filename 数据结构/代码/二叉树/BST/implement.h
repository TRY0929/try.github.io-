#ifndef IMPLEMENT_H_INCLUDED
#define IMPLEMENT_H_INCLUDED
#include <iostream>
#include <queue>
#include "definition.h"
using namespace std;
template <typename E>
void BSTtree<E>::clear(BSTnode<E>* root)
{
    if(root==nullptr) return ;
    clear(root->lchild);
    clear(root->rchild);
}
template <typename E>
void BSTtree<E>::clear()
{
    clear(root);
    delete root;
    root = nullptr;
}
template <typename E>
BSTnode<E>* BSTtree<E>::insert(BSTnode<E>* r,E& val)
{
    if(r == nullptr) {
        r = new BSTnode<E> (val);
        return r;
    }
    if(val > r->data) insert(r->rchild,val);
    else insert(r->lchild,val);
}
template <typename E>
BSTnode<E>* BSTtree<E>::insert(E& val)
{
    return insert(root,val);
}
template <typename E>
bool BSTtree<E>::inTree(BSTnode<E>* r,E& val)
{
    if(r==nullptr) return false;
    if(r->data>val) return inTree(r->lchild,val);
    else if(r->data<val) return inTree(r->rchild,val);
    return true;
}
template <typename E>
bool BSTtree<E>::inTree(E& val)
{
    return inTree(root,val);
}
template <typename E>
BSTnode<E>* BSTtree<E>::findMin(BSTnode<E>*r)
{
    if(r==nullptr) return nullptr;
    if(r->lchild==nullptr) return r;
    return findMin(r->lchild);
}
template <typename E>
BSTnode<E>* BSTtree<E>::remove(BSTnode<E>*r, E& key)
{ //ɾ���ض�ֵ�Ľ��
    if(r==nullptr) return nullptr;
    if(r->data > key) return remove(r->lchild,key);
    else if(r->data < key) return remove(r->rchild,key);
    else { //�ҵ������ ��ʼɾ��
        if(r->lchild==nullptr && r->rchild==nullptr) {
                //���ҽڵ��Ϊ��
            BSTnode<E>* tmp = r;
            if(r == root) root=nullptr; //��Ϊ���ڵ� ����ڵ��ÿ� Ҳ������û��
            else { //�жϸý�������丸�׽ڵ���Ŀ�������
                if(r->parent->lchild==r) r->parent->lchild = nullptr;
                else r->parent->rchild = nullptr;
            }
            return tmp;
        }
        else if(r->lchild==nullptr) { //��������Ϊ��
            if(r == root) { //��Ϊ���ڵ�
                BSTnode<E>* tmp = r;
                root = root->rchild; //���ڵ���Ϊ���ҽ��
                root->parent = nullptr; //���ڵ�ĸ��ڵ��ÿ�
                return tmp;
            }
            else { //�жϸý�������丸�׽ڵ���Ŀ�������
                if(r->parent->lchild == r) { //ָ��Ĳ��� һ��Ҫ�ú����һ��
                    r->rchild->parent = r->parent;
                    r->parent->lchild = r->rchild;
                }
                else {
                    r->rchild->parent = r->parent;
                    r->parent->rchild = r->rchild;
                }
                return r;
            }

        }
        else if(r->rchild==nullptr) {
            if(r == root) {
                root = root->lchild;
                root->parent = nullptr;
            }
            else {
                if(r->parent->lchild == r) {
                    r->lchild->parent = r->parent;
                    r->parent->lchild = r->lchild;
                }
                else {
                    r->lchild->parent = r->parent;
                    r->parent->rchild = r->lchild;
                }
            }
        }
        else { //������������Ϊ��
            BSTnode<E>*tmp = new BSTnode<E>(r->data);
            BSTnode<E>* result = deleteMin(r->rchild);
            //���������е���Сֵ��λ��ɾ��(���)
            //���ҽ�Ҫɾȥ��ֵ��Ϊ��̵�ֵ(�൱�ڽ�����λ��)
            r->data = result->data;
            delete result;
            return tmp;
        }
    }
}
template <typename E>
BSTnode<E>* BSTtree<E>::remove(E& key)
{
    remove(root,key);
}
template <typename E>
BSTnode<E>* BSTtree<E>::deleteMin(BSTnode<E>*r,int times)
{
    times++;
    if(r == nullptr) return nullptr;
    if(r->lchild!=nullptr) return deleteMin(r->lchild,times);

    if(r->rchild!=nullptr) {
        if(r == root) {
            BSTnode<E>* tmp = r;
            root = root->rchild;
            root->parent = nullptr;
            return tmp;
        }
        r->rchild->parent = r->parent;
        if(times == 1) r->parent->rchild = r->rchild;
        //��һ��ѭ�� ��Ϊ��ɾ�������е���Сֵ �������ǵ�һ�εĻ� �Ǹýڵ�����丸�׽ڵ����������
        else r->parent->lchild = r->rchild;
    }
    else {
        if(r == root) {
            root = nullptr;
            return r;
        }
        BSTnode<E>* tmp = r;
        if(times == 1) r->parent->rchild = nullptr;
        else r->parent->lchild = nullptr;
        return r;
    }
}
template <typename E>
void BSTtree<E>::preOrder(BSTnode<E>* r)
{
    if(r == nullptr) return ;
    cout << r->data;
    preOrder(r->lchild);
    preOrder(r->rchild);
}
template <typename E>
void BSTtree<E>::preOrder()
{
    preOrder(root);
}
template <typename E>
void BSTtree<E>::layerOrder(BSTnode<E>* r)
{
    queue<BSTnode<E>*> q;
    if(r!=nullptr) q.push(r);
    BSTnode<E>* top;
    while(!q.empty()) {
        top = q.front();
        q.pop();
        cout << top->data;
        if(top->lchild!=nullptr) q.push(top->lchild);
        if(top->rchild!=nullptr) q.push(top->rchild);
        if(!q.empty()) cout << " ";
    }
}
template <typename E>
void BSTtree<E>::layerOrder()
{
    layerOrder(root);
}
template <typename E>
int BSTtree<E>::getTreeHeight(BSTnode<E>* r)
{
    if(r == nullptr) return 0;
    return max(getTreeHeight(r->lchild),getTreeHeight(r->rchild))+1;
}
template <typename E>
int BSTtree<E>::getTreeHeight()
{
    return getTreeHeight(root);
}
#endif // IMPLEMENT_H_INCLUDED
