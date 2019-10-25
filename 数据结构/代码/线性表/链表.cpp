#include <iostream>
#include <algorithm>
using namespace std;
template <typename Object>
class list
{
    private:
        struct Node
        {
            Node* pre;
            Node* next;
            Object data;
            Node():pre(nullptr),next(nullptr),data(0) {}
            Node* newNode(Node* p,Node* n,const Object & x)
            {
                Node* newnode = new Node(p,n,x);
                return newnode;
            }

        };
        class const_iterator
        {
            protected:
                const_iterator(Node* p=nullptr):current(p) {};
                Node* current;
            public:

                const Object & operator*  () {return current->data;}
                const_iterator & operator++ ()
                {
                    current = current->next;
                    return *this;
                }
                const_iterator & operator++ (int)
                {
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }
                bool operator== (const const_iterator & c) {return current==c.current;}
                bool operator!= (const const_iterator & c) {return current!=c.current;}

                friend class list;
        };
        class iterator:public const_iterator
        {
            protected:
                iterator(Node* p=nullptr):const_iterator(p) {}
            public:
                iterator() {}
                iterator & operator* () {return const_iterator::operator*();}
                const iterator & operator* () const {return const_iterator::operator*();}
                iterator & operator++ ()
                {
                    *this.current = *this.current->next;
                    return *this;
                }
                iterator & operator++ (int)
                {
                    iterator old = *this;
                    ++(*this);
                    return old;
                }
                friend class list;
        };
        void push_back(int x) {insert(end(),x);}
        void pop_back() {erase(--end());}
        iterator & insert(iterator & it,const Object & x)
        {
            Node* p = it.current;
            ++Size;
            Node* n = newNode(it->pre,it,x);
            it->pre->next = p;
            it->pre = p;
            return p;
        }
        iterator & erase(iterator & it)
        {
            Node* p = it.current;
            Node* p1 = p->next;
            p->pre->next = p->next;
            p->next->pre = p->pre;
            delete p;
            --Size;
            return iterator(p1);
        }
        iterator erase(iterator & b,iterator & e)
        {
            for(iterator it = b;it!=e;++it)
                it = erase(it);
            return e;
        }
        bool empty() {return size==0;}
        int size() {return Size;}
        iterator & begin() {return iterator(head->next);}
        const const_iterator & begin() const {return const_iterator(head->next);}
        iterator & end() {return iterator(tail);}
        const const_iterator & end() const {return const_iterator(tail);}
        Object & front() {return *begin();}
        list(int initsize=0):Size(initsize)
        {
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->pre = head;
        }

    private:
        int Size;
        Node* head;
        Node* tail;

};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
