#include <iostream>
#include <algorithm>
using namespace std;
template <typename Object>
class Vector
{
    private:
        Object* obs;
        int size;
        int capacity;
        static const int SPARE=16;
    public:
        Vector(const Vector & v):size(v.size),capacity(v.capacity)
        {
            obs = new Object[capacity];
            for(int i=0;i<size;++i)
                obs[i] = v[i];
        }
        Vector(int initsize=0):size(initsize),capacity(initsize+SPARE) {}
        Vector & operator= (const Vector& v) const
        {
            Vector copy = v;
            swap(v,*this);
            return *this;
        }
        Vector & operator= (Vector&& v)
        {
            swap(size,v.size);
            swap(capacity,v.capacity);
            swap(obs,v.obs);
            return *this;
        }
        Object & operator[] (int index) {return obs[index];}
        void Resize(int newsize)
        {
            if(newsize > capacity) Reserve(newsize*2);
            size = newsize;
        }
        void Reserve(int newc)
        {
            if(newc > capacity)
            {
                Object* newArray = new Object[newc];
                for(int i=0;i<size;++i)
                    newArray[i] = move(obs[i]);
                swap(obs,newArray);
                capacity = newc;
                delete []newArray;
            }
        }
        void push_back(int x)
        {
            if(size == capacity) Resize(2*capacity+1);
            obs[size++] = x;
        }
        void pop_back() {--size;}
        bool insert(int pos,const Object & x)
        {
            if(pos >= size) return false;
            if(size == capacity) Resize(2*capacity+1);
            for(int i=pos;i<size-1;++i)
                *(obs+i+1) = *(obs+i);
            *(obs+pos) = x;
            ++size;
            return true;
        }
        ~Vector() {delete []obs;}
        bool empty() {return size==0;}
        int length() {return size;}
        void clear(){size=0;}
        typedef Object* iterator;
        typedef Object* const_iterator;
        iterator begin() {return &obs[0];};
        const_iterator begin() const {return &obs[0];}
        iterator end() {return &obs[size-1];}
        const_iterator end() const {return &obs[size-1];}
        iterator find(const Object & x)
        {
            for(iterator it=begin();it!=end();++it)
                if(*it==x) return it;
            return nullptr;
        }
        iterator erase(const_iterator & it)
        {
            if(it==nullptr) return nullptr;
            for(iterator p = it;p!=end()-1;++p)
                *(p+1)=*p;
            return it;
        }
};
template <typename Object>
Vector<Object> MergeVector(const Vector<Object> v1,const Vector<Object> v2)
{
    int len1=v1.size(),len2=v2.size();
    Vector<Object> v3 (len1+len2);
    int i=0,j=0,k=0;
    while(i<len1 && j<len2)
    {
        if(v1[i] < v2[j]) v3[k++]=v1[i++];
        else v3[k++]=v2[j++];
    }
    while(i<len1) v3[k++]=v1[i++];
    while(j<len2) v3[k++]=v2[j++];
    return v3;
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
