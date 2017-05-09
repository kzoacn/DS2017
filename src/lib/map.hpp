#pragma once

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"
#include "vector.hpp"
#include "../FileManager.hpp"

namespace sjtu{
    template<class T1,class T2>
    pair<T1,T2>make_pair(const T1 &a,const T2 &b){
        return pair<T1,T2>(a,b);
    }

    __inline int get_rand(){
        static int x=136484679;
        x=(x*31+152121);
        return x;
    }


    template<class Key,class T,class Compare = std::less<Key> >
    class map{
    public:
        typedef pair<const Key, T> value_type;
    private:
#define key kv->first
#define val kv->second
        struct node{
            value_type* kv;
            int rnd,siz;
            node *c[2],*pre,*nxt;
            node(){
                kv=0;pre=this;nxt=0;
                siz=0;rnd=0;c[0]=c[1]=0;
            }
            node(const Key &k,const T &v){
                kv=new value_type(k,v);
                rnd=get_rand();
                c[0]=c[1]=0;
                pre=nxt=0;
                siz=1;
            }
            ~node(){
                if(kv)
                    delete kv;
            }
            __inline void rz(){
                siz=1;
                if(c[0])siz+=c[0]->siz;
                if(c[1])siz+=c[1]->siz;
            }
        }*root,*head,*tail;
        Compare cmp;
        __inline bool equals(const Key &a,const Key &b)const{
            return !(cmp(a,b)||cmp(b,a));
        }
        __inline void rot(node *&t,const bool &d){
            if(!t->c[d])t=t->c[!d];
            else{
                node *p=t->c[d];t->c[d]=p->c[!d];
                p->c[!d]=t;t->rz();p->rz();t=p;
            }
        }
        __inline node* insert(node *&t,const Key &k,const T &v){
            if(!t){
                t=new node(k,v);
                return t;
            }
            if(equals(t->key,k))
                return t;
            bool d=!cmp(k,t->key);
            node *p=insert(t->c[d],k,v);
            if(t->rnd<t->c[d]->rnd)
                rot(t,d);
            else t->rz();
            return p;
        }
        __inline void del(node *&t,const Key &k){
            if(!t)return;
            if(equals(t->key,k)){
                if(!t->c[0]||!t->c[1]){
                    node *p=t;
                    if(!t->c[0])t=t->c[1];
                    else t=t->c[0];
                    delete p;
                    return;
                }
                int d=t->c[0]->rnd<t->c[1]->rnd;
                rot(t,d);
                del(t,k);
                return;
            }
            del(t->c[!cmp(k,t->key)],k);
            t->rz();
        }
        __inline node *_find(node *t,const Key &k)const{
            while(t){
                if(equals(t->key,k))
                    return t;
                if(cmp(t->key,k))
                    t=t->c[1];
                else t=t->c[0];
            }
            return 0;
        }
        __inline node* prev(node *t,const Key &k){
            if(!t)return 0;
            node *p=prev(t->c[cmp(t->key,k)],k);
            if(cmp(t->key,k)){
                if(!p||cmp(p->key,t->key))
                    p=t;
            }
            return p;
        }
        __inline node* succ(node *t,const Key & k){
            if(!t)return 0;
            node *p=succ(t->c[!cmp(k,t->key)],k);
            if(cmp(k,t->key)){
                if(!p||cmp(t->key,p->key))
                    p=t;
            }
            return p;
        }
        __inline node* build(int l,int r,vector<node*>&nodes){
            if(l>=r)return NULL;
            int mid=(l+r)>>1;
            node *x=nodes[mid];
            x->c[0]=build(l,mid-1,nodes);
            x->c[1]=build(mid+1,r,nodes);
            return x;
        }

        __inline node* insert(const Key & k,const T & v){
            if(count(k)){
                node *t=_find(root,k);
                t->val=v;
                return t;
            }
            node *p=prev(root,k);
            node *n=succ(root,k);
            node *t=insert(root,k,v);


            if(!n)n=tail;

            if(p)
                p->nxt=t;
            else{
                head=t;
                head->pre=head;
            }
            if(n)n->pre=t;
            t->pre=p;t->nxt=n;
            return t;
        }
        __inline void del(const Key & k){
            if(!count(k)){
                return ;
            }
            node *t=_find(root,k);
            if(t!=head){
                t->pre->nxt=t->nxt;
                t->nxt->pre=t->pre;
            }else{
                head=t->nxt;
                t->nxt->pre=t->nxt;
            }
            del(root,t->key);
        }


    public:

        class const_iterator;
        class iterator {
        public:
            node *p;
            iterator() {
                p=0;
            }
            iterator(node *t) {
                p=t;
            }
            iterator(const iterator &other):p(other.p){}
            __inline iterator operator++(int) {
                if(!p->nxt){
                    throw invalid_iterator();
                }else{
                    iterator tmp(*this);
                    p=p->nxt;
                    return tmp;
                }
            }
            __inline iterator & operator++() {
                if(!p->nxt){
                    throw invalid_iterator();
                }else{
                    p=p->nxt;
                    return *this;
                }
            }
            __inline iterator operator--(int) {
                if(p->pre==p){
                    throw invalid_iterator();
                }else{
                    iterator tmp(*this);
                    p=p->pre;
                    return tmp;
                }
            }
            __inline iterator & operator--() {
                if(p->pre==p){
                    throw invalid_iterator();
                }else{
                    p=p->pre;
                    return *this;
                }
            }
            __inline value_type & operator*() const {return *p->kv;}
            __inline bool operator==(const iterator &rhs) const {
                return p==rhs.p;
            }
            __inline bool operator==(const const_iterator &rhs) const {
                return p==rhs.p;
            }
            __inline bool operator!=(const iterator &rhs) const {
                return p!=rhs.p;
            }
            __inline bool operator!=(const const_iterator &rhs) const {
                return p!=rhs.p;
            }
            __inline value_type* operator->() const {
                return p->kv;
            }
        };
        class const_iterator {
            public:
                node *p;
                const_iterator() {
                    p=0;
                }
                const_iterator(node *t) {
                    p=t;
                }
                const_iterator(const const_iterator &other):p(other.p) {}
                const_iterator(const iterator &other):p(other.p) {}
                __inline const_iterator operator++(int) {
                    if(!p->nxt){
                        throw invalid_iterator();
                    }else{
                        const_iterator tmp(*this);
                        p=p->nxt;
                        return tmp;
                    }
                }
                __inline const_iterator & operator++() {
                    if(!p->nxt){
                        throw invalid_iterator();
                    }else{
                        p=p->nxt;
                        return *this;
                    }
                }
                __inline const_iterator operator--(int) {
                    if(p->pre==p){
                        throw invalid_iterator();
                    }else{
                        const_iterator tmp(*this);
                        p=p->pre;
                        return tmp;
                    }
                }
                __inline const_iterator & operator--() {
                    if(p->pre==p){
                        throw invalid_iterator();
                    }else{
                        p=p->pre;
                        return *this;
                    }
                }
                __inline const value_type & operator*() const {return *p->kv;}
                __inline bool operator==(const iterator &rhs) const {
                    return p==rhs.p;
                }
                __inline bool operator==(const const_iterator &rhs) const {
                    return p==rhs.p;
                }
                __inline bool operator!=(const iterator &rhs) const {
                    return p!=rhs.p;
                }
                __inline bool operator!=(const const_iterator &rhs) const {
                    return p!=rhs.p;
                }
                __inline const value_type* operator->() const {
                    return p->kv;
                }
        };




        __inline size_t count(const Key &k) const {
            return int(_find(root,k)!=0);
        }



        map(){
            root=0;head=0;
            tail=new node();
            head=tail;
        }
        ~map(){
            clear();
            if(tail){
                delete tail;
                tail=0;
            }
        }
        map(const vector<pair<Key,T> > &other){
            if(other.empty()){
                root=0;head=0;
                tail=new node();
                head=tail;
                return ;
            }
            vector<node*>nodes;
            for(int i=0;i<other.size();i++)
                nodes.push_back(new node(other[i].first,other[i].second));
            root=head=0;
            tail=new node();
            nodes[0]->pre=nodes[0];
            for(int i=1;i<nodes.size();i++)
                nodes[i]->pre=nodes[i-1];
            for(int i=0;i+1<nodes.size();i++)
                nodes[i]->nxt=nodes[i+1];
            root=build(0,nodes.size(),nodes);
        }
        map(const map &other) {
            root=0;head=0;
            tail=new node();
            head=tail;
            for(const_iterator it=other.cbegin();it!=other.cend();it++){
                insert(*it);
            }
        }
        map& operator=(const map &other){
            if(this==&other)
                return *this;
            clear();
            for(const_iterator it=other.cbegin();it!=other.cend();it++){
                insert(*it);
            }
            return *this;
        }
        map& operator=(map &&other){
            if(this==&other)
                return *this;
            root=other.root;other.root=0;
            head=other.head;other.head=0;
            tail=other.tail;other.tail=0;
            return *this;
        }
        __inline T & at(const Key &k) {
            if(!count(k)){
                throw index_out_of_bound();
            }else{
                node *p=_find(root,k);
                return p->val;
            }
        }
        __inline T & get(const Key &k) {
            if(!count(k)){
                insert(k,T());
            }
            node *p=_find(root,k);
            return p->val;
        }
        __inline T & operator[](const Key &k) {
            return get(k);
        }


        __inline const T & at(const Key &k) const {
            if(!count(k)){
                throw index_out_of_bound();
            }else{
                node *p=_find(root,k);
                return p->val;
            }
        }
        __inline const T & operator[](const Key &k) const {return at(k);}


        __inline iterator begin() {return iterator(head);}
        __inline const_iterator cbegin() const {return const_iterator(head);}
        __inline iterator end() {return iterator(tail);}
        __inline const_iterator cend() const {return const_iterator(tail);}
        __inline bool empty() const {return root==0;}
        __inline size_t size() const {if(empty())return 0;return root->siz;}

        __inline void clear() {
            while(!empty())
                erase(begin());
        }

        __inline iterator find(const Key &k) {
            node *p=_find(root,k);
            if(!p)p=tail;
            return iterator(p);
        }
        __inline pair<iterator, bool> insert(const value_type &kv) {
            bool res=count(kv.first)?false:true;
            if(res)
                return make_pair(insert(kv.first,kv.second),res);
            else return make_pair(find(kv.first),res);
        }
        __inline void erase(iterator pos) {
            if(pos==end()||pos!=find(pos->first))throw invalid_iterator();
            else if(!count(pos->first))throw index_out_of_bound();
            else del(pos->first);
        }
        __inline void erase(const Key &k) {
            iterator pos=find(k);
            if(pos==end()||pos!=find(pos->first))throw invalid_iterator();
            else if(!count(pos->first))throw index_out_of_bound();
            else del(pos->first);
        }
        __inline const_iterator find(const Key &k) const {
            node *p=_find(root,k);
            if(!p)p=tail;
            return const_iterator(p);
        }
#undef key
#undef val
    };
}
#endif

