#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED
template <typename E>
class BSTtree; //记得这里要提前引用说明，不然BSTnode中无法把BSTtree作为友元类
template <typename E>
class BSTnode
{
private:
    E data;
    BSTnode* lchild;
    BSTnode* rchild;
    BSTnode* parent; //三叉链表 第三叉就是父节点
public:
    BSTnode(E e=E{},BSTnode* lc=nullptr, BSTnode* rc=nullptr,BSTnode*par=nullptr):
        data(e),lchild(lc),rchild(rc),parent(par) {}
    BSTnode* getLeft() {return lchild;}
    BSTnode* getRight() {return rchild;}
    BSTnode* getParent() {return parent;}
    friend class BSTtree<E>;
};
template <typename E>
class BSTtree
{
    //有没有发现 每个都有两个同名的函数 一个是封装起来的，另一个是公共调用的
    //好好理解一下面向对象与封装以及树的遍历所需要用到的问题
private:
    BSTnode<E>* root;
    void clear(BSTnode<E>*r);
    BSTnode<E>* insert(BSTnode<E>*r, E&val);
    BSTnode<E>* remove(BSTnode<E>*r, E& key);
    BSTnode<E>* deleteMin(BSTnode<E>*r,int times);
    BSTnode<E>* findMin(BSTnode<E>*r);
    bool inTree(BSTnode<E>*r,E&val);
    void preOrder(BSTnode<E>* r);
    void inOrder(BSTnode<E>* r);
    void postOrder(BSTnode<E>* r);
    void layerOrder(BSTnode<E>* r);
    int getTreeHeight(BSTnode<E>* r);
public:
    BSTtree(BSTnode<E>* b=nullptr):root(b) {};
    void clear();
    BSTnode<E>* insert(E&val);
    BSTnode<E>* remove(E& key);
    BSTnode<E>* deleteMin();
//    BSTnode<E>* findMin();
    bool inTree(E&val);
    void preOrder();
    void inOrder();
    void postOrder();
    void layerOrder();
    int getTreeHeight();
};

#endif // DEFINITION_H_INCLUDED
