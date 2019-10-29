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
{ //删除特定值的结点
    if(r==nullptr) return nullptr;
    if(r->data > key) return remove(r->lchild,key);
    else if(r->data < key) return remove(r->rchild,key);
    else { //找到结点了 开始删除
        if(r->lchild==nullptr && r->rchild==nullptr) {
                //左右节点均为空
            BSTnode<E>* tmp = r;
            if(r == root) root=nullptr; //若为根节点 则根节点置空 也就是树没了
            else { //判断该结点是在其父亲节点的哪棵子树上
                if(r->parent->lchild==r) r->parent->lchild = nullptr;
                else r->parent->rchild = nullptr;
            }
            return tmp;
        }
        else if(r->lchild==nullptr) { //右子树不为空
            if(r == root) { //若为根节点
                BSTnode<E>* tmp = r;
                root = root->rchild; //根节点置为其右结点
                root->parent = nullptr; //根节点的父节点置空
                return tmp;
            }
            else { //判断该结点是在其父亲节点的哪棵子树上
                if(r->parent->lchild == r) { //指针的操作 一定要好好理解一下
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
        else { //左右子树都不为空
            BSTnode<E>*tmp = new BSTnode<E>(r->data);
            BSTnode<E>* result = deleteMin(r->rchild);
            //将右子树中的最小值的位置删掉(后继)
            //并且将要删去的值赋为后继的值(相当于交换了位置)
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
        //第一次循环 因为是删右子树中的最小值 因此如果是第一次的话 那该节点就在其父亲节点的右子树中
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
