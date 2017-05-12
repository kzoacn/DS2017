//#include<list>
#include "exceptions.hpp"

//LIST!!!


#include <functional>
#include <cstddef>
#include "exceptions.hpp"
#include <iostream>

namespace sjtu{



    template<class T>
    class list{
    public:
        int siz;
    private:
        struct node{
            T* kv;
            node *pre,*nxt;
            node(){
                kv=0;pre=this;nxt=0;
            }
            node(const T &v){
                kv=new T(v);
                pre=this;nxt=0;
            }
            ~node(){
                if(kv)
                    delete kv;
            }
        }*head,*tail;

        __inline node* insert(node *t,const T & v){

            node *p=t->pre;
            node *np=new node(v);

            if(t==t->pre){
                t->pre=np;
                np->nxt=t;
                head=np;
            }else{
                p->nxt=np;
                t->pre=np;
                np->pre=p;
                np->nxt=t;
            }
            return np;
        }
        __inline node* del(node *t){
            node *tmp=t->nxt;
            if(t!=head){
                t->pre->nxt=t->nxt;
                t->nxt->pre=t->pre;
            }else{
                head=t->nxt;
                t->nxt->pre=t->nxt;
            }
            delete t;
            t=0;
            return tmp;
        }


    public:

        class const_iterator;
        class iterator {


        private:
            node *p;
        public:
            iterator() {
                p=0;
            }
            iterator(node *t) {
                p=t;
            }
            __inline node* ptr(){return p;}
            __inline bool is_end()const{
                return p->nxt==0;
            }
            __inline iterator& try_nxt(){
                if(p->nxt)
                    p=p->nxt;
                return *this;
            }
            __inline iterator& try_pre(){
                p=p->pre;
                return *this;
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
            __inline T & operator*() const {return *p->kv;}
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
            __inline T* operator->() const noexcept {
                return p->kv;
            }
            __inline T* getTptr() const noexcept {
                return p->kv;
            }
        };
        class const_iterator {
            public:
                node *p;
                node* ptr(){return p;}
                __inline bool is_end()const{
                    return p->nxt==0;
                }
                const_iterator& try_nxt(){
                    if(p->nxt)
                        p=p->nxt;
                    return *this;
                }
                const_iterator& try_pre(){
                    p=p->pre;
                    return *this;
                }
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
                __inline const T & operator*() const {return *p->kv;}
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
                __inline const T* operator->() const noexcept {
                    return p->kv;
                }
                __inline const T* getTptr() const noexcept {
                    return p->kv;
                }
        };



        list(){
            head=0;
            tail=new node();
            head=tail;
            siz=0;
        }
        ~list(){
            clear();
            if(tail){
                delete tail;
                tail=0;
            }
        }
        list(const list &other) {
            head=0;
            tail=new node();
            head=tail;
            for(const_iterator it=other.cbegin();it!=other.cend();it++){
                insert(end(),*it);
            }
            siz=other.siz;
        }
        list& operator=(const list &other){
            if(this==&other)
                return *this;
            clear();
            for(const_iterator it=other.cbegin();it!=other.cend();it++){
                insert(end(),*it);
            }
            siz=other.siz;
            return *this;
        }
        __inline void split_to(list &oth,int oth_siz){
            node *t=head;
            for(int i=0;i<siz-oth_siz;i++){

            }
        }

        __inline iterator begin() {return iterator(head);}
        __inline const_iterator cbegin() const {return const_iterator(head);}
        __inline iterator end() {return iterator(tail);}
        __inline const_iterator cend() const {return const_iterator(tail);}
        __inline bool empty() const {return siz==0;}
        __inline size_t size() const {return siz;}

        __inline void clear() {
            while(!empty())
                erase(begin());
            siz=0;
        }

        __inline iterator insert(iterator pos,const T &kv) {
            siz++;
            return iterator(insert(pos.ptr(),kv));
        }
        __inline iterator erase(iterator pos) {
            if(pos==end())throw invalid_iterator();
            else {
                siz--;
                return iterator(del(pos.ptr()));
            }
        }
        __inline void push_back(const T& v){insert(end(),v);}
        __inline void pop_back(){erase(--end());}
        __inline void push_front(const T& v){insert(begin(),v);}
        __inline void pop_front(){erase(begin());}
        __inline T& front(){return *begin();}
        __inline T& back(){return *--end();}

    };
}



//LIST END


//#define DEBUG

//#define MAGIC (sqrt(siz)+5)
#define MAGIC2 (siz+10)
//#define MAGIC2 1000000

namespace sjtu{
    const int TAT=4;

    template<typename T>
    class deque{
    public:
        class iterator;
    private:
        list<list<T> >lst;
        int siz;
//		int optimes;
        typedef typename list<list<T> >::iterator l_iter;
        typedef typename list<T>::iterator v_iter;
        #define sqr(x) (x*x)
        //inline int sqr(const int &x){return x*x;}
        inline l_iter nxt(l_iter x){x++;return x;}
        __inline T& get(l_iter l,int x){
            v_iter it=l->begin();
            while(x--)
                it++;
            return *it;
        }
        __inline pair<l_iter,int> get_block(const int &x){
            if(x*2<=siz){
                int cur=x+1,presize=0;
                for(l_iter it=lst.begin();it!=lst.end();it++){
                    if(cur<=it->size())
                        return make_pair(it,presize);
                    presize+=it->size();
                    cur-=it->size();
                }
            }else{
                int cur=siz-x,lasize=0;
                for(l_iter it=--lst.end();;){
                    if(it->size()>=cur){
                        return make_pair(it,siz-lasize-it->size());
                    }
                    cur-=it->size();
                    lasize+=it->size();
                    if(it==lst.begin())
                        break;
                    it--;
                }
            }
            return make_pair(lst.end(),siz);
        }
        __inline int presize(l_iter it){

            l_iter i=lst.begin();
            int ans=0;
            while(i!=it){
                ans+=i->size();
                i++;
            }
            return ans;
        }
        __inline void merge(l_iter a,l_iter b){
            for(auto x:*b)
                a->push_back(x);
            lst.erase(b);
        }
        __inline void rebuild(){
            list<T>tmp;
            for(auto x:lst){
                for(auto y:x)
                    tmp.push_back(y);
            }
            lst.clear();
            lst.push_back(list<T>());
            while(!tmp.empty()){
                lst.back().push_back(tmp.front());
                tmp.pop_front();
                //if(lst.back().size()>MAGIC)
                //	lst.push_back(list<T>());
            }
        }
        __inline void mtlist(){
            /*if(lst.size()*MAGIC>2*siz){
                rebuild();
                return ;
            }*/
            l_iter it=lst.begin();
            while(it!=lst.end()){
                l_iter nit=nxt(it);
                while(nit!=lst.end()&&(TAT*sqr(it->size())<MAGIC2||TAT*sqr(nit->size())<MAGIC2)){
                    merge(it,nit);
                    nit=nxt(it);
                }
                if(sqr(it->size())>MAGIC2*TAT){
                    split(it,it->size()/2);
                }
                it++;
            }
        }


        __inline void mtlist(l_iter it){
            if(it!=lst.end()){
                l_iter nit=nxt(it);
                while(nit!=lst.end()&&(sqr(it->size()+nit->size())<=TAT*MAGIC2)){
                    merge(it,nit);
                    nit=nxt(it);
                }
                if(sqr(it->size())>MAGIC2*TAT){
                    split(it,it->size()/2);
                }
                it++;
            }
        }

        __inline void split(l_iter blk,const int &pos){
            //blk -> [0,pos)+[pos,blk.size())
            if(pos==blk->size())return ;
            l_iter nblk=lst.insert(nxt(blk),list<T>());
            int lsiz=(int)blk->size()-pos;
            while(lsiz--){
                nblk->push_front(blk->back());
                blk->pop_back();
            }
        }
        __inline void __push_front(const T &x){
            lst.front().push_front(x);
            siz++;
            if(sqr(lst.front().size())>TAT*MAGIC2)
                mtlist();
        }
        __inline void __push_back(const T &x){
            lst.back().push_back(x);
            siz++;
            if(sqr(lst.back().size())>TAT*MAGIC2)
                mtlist();
        }
        __inline void __insert(int pos,const T &x){
            if(pos>siz+1||pos<0)
                throw "out of index!";
            if(pos==0){
                __push_front(x);
                return;
            }
            if(pos==siz){
                __push_back(x);
                return;
            }
            pair<l_iter,int> blk=get_block(pos);

            register int sz=blk.second;
            auto it=blk.first->begin();

            sz=pos-blk.second;

            /*while(sz>=TAT){
                it++;it++;it++;it++;
                sz-=TAT;
            }*/
            while(sz--){
                it++;
            }
            blk.first->insert(it,x);
            siz++;
            if(sqr(blk.first->size())>TAT*MAGIC2)
                mtlist();
            /*split(blk.first,pos-blk.second);
            blk.first->push_back(x);
            siz++;
            mtlist();*/
        }
        __inline void __insert(int pos,const T &x,const iterator &it){
            if(pos>siz+1||pos<0)
                throw "out of index!";
            /*if(pos==0){
                __push_front(x);
                return;
            }
            if(pos==siz){
                __push_back(x);
                return;
            }*/

            it.it2->insert(it.it1,x);
            siz++;
            if(sqr(it.it2->size())>TAT*MAGIC2)
                mtlist();
        }
        __inline void __pop_front(){
            lst.front().pop_front();
            siz--;
            if(lst.front().empty()&&lst.size()!=1){
                lst.pop_front();
            }
            if(TAT*sqr(lst.front().size())<MAGIC2)
                mtlist();
        }
        __inline void __pop_back(){
            lst.back().pop_back();
            siz--;
            if(lst.back().empty()&&lst.size()!=1){
                lst.pop_back();
            }
            if(TAT*sqr(lst.back().size())<MAGIC2)
                mtlist();
        }
        __inline void __erase(const int &pos){
            if(pos>=siz||pos<0)
                throw "out of index";
            if(pos==0){
                __pop_front();
                return;
            }
            if(pos==siz-1){
                __pop_back();
                return;
            }
            auto blk=get_block(pos);
            blk.second=pos-blk.second;
            auto it=blk.first->begin();

            while(blk.second>=8){
                it++;it++;it++;it++;
                it++;it++;it++;it++;
                blk.second-=8;
            }
            while(blk.second--){
                it++;
            }

            blk.first->erase(it);
            siz--;
            if(TAT*sqr(blk.first->size())<MAGIC2)
                mtlist();
        }
        __inline void __erase(const int &pos,const iterator &it){
            /*if(pos>=siz||pos<0)
                throw "out of index";
            if(pos==0){
                __pop_front();
                return;
            }
            if(pos==siz-1){
                __pop_back();
                return;
            }*/
            it.it2->erase(it.it1);
            siz--;
            if(TAT*sqr(it.it2->size())<MAGIC2)
                mtlist();
        }

    public:
        class iterator{
        public:
            typename list<list<T> >::iterator it2;
            typename list<T>::iterator it1;
            int siz;
            deque* belong;
            __inline void add(){
                if(it1.is_end())
                    throw sjtu::invalid_iterator();
                it1++;
                if(it1.is_end()){
                    it2++;
                    if(it2.is_end()){
                        it2--;
                        it1=it2->end();
                    }else
                        it1=it2->begin();
                }
                siz++;
            }
            __inline void dec(){
                if(it1==it2->begin()){
                    it2--;
                    it1=it2->end().try_pre();
                }else{
                    it1--;
                }
                siz--;
            }
        public:
            iterator(){siz=0;belong=0;}
            iterator(typename list<list<T> >::iterator i2,typename list<T>::iterator i1,int sz,deque *b){
                it2=i2;
                it1=i1;
                siz=sz;
                belong=b;
            }
            iterator(const iterator &oth){
                it1=oth.it1;
                it2=oth.it2;
                siz=oth.siz;
                belong=oth.belong;
            }
            __inline int size(){return siz;}
            __inline bool operator==(const iterator &oth)const{
                return it1==oth.it1&&it2==oth.it2;
            }
            __inline bool operator!=(const iterator &oth)const{
                return !(*this==oth);
            }
            __inline iterator& operator=(const iterator &oth){
                if(this==&oth)return *this;
                it1=oth.it1;
                it2=oth.it2;
                siz=oth.siz;
                belong=oth.belong;
            }
            __inline iterator operator++(int){
                iterator tmp(*this);
                add();
                return tmp;
            }
            __inline iterator& operator++(){
                add();
                return *this;
            }
            __inline iterator operator--(int){
                iterator tmp(*this);
                dec();
                return tmp;
            }
            __inline iterator& operator--(){
                dec();
                return *this;
            }
            __inline iterator& operator+=(const int &x){
                if(x<0)
                    return *this-=(-x);
                if(x==0)return *this;
                static int tar;
                tar=siz+x;
                *this=belong->begin();
                //TODO
                /*while(siz!=tar&&!it1.is_end()){
                    it1++;
                    siz++;
                }

                if(it1.is_end()){
                    it2++;
                    if(it2.is_end()){
                        it2--;
                        it1=it2->end();
                    }else
                        it1=it2->begin();
                }
                if(siz==tar)return *this;*/
                while(siz+it2->size()<tar){
                    siz+=it2->size();
                    it2++;
                    it1=it2->begin();
                }
                while(siz!=tar){
                    add();
                }
                return *this;
            }
            __inline iterator& operator-=(const int &x){
                if(x<0)
                    return *this+=(-x);
                if(x==0)return *this;
                int tar=siz-x;
                *this=belong->begin()+tar;
                /*while(siz!=tar&&it1!=it2->begin()){
                    siz--;
                    it1--;
                }
                if(siz==tar)return *this;
                while(1){
                    auto pre=it2;
                    pre--;
                    if(siz-pre->size()>tar){
                        siz-=pre->size();
                        it2--;
                        it1=it2->begin();
                    }else{
                        break;
                    }
                }
                while(siz!=tar){
                    dec();
                }*/
                return *this;
            }
            __inline iterator operator+(const int &x){
                iterator tmp(*this);
                tmp+=x;
                return tmp;
            }
            __inline iterator operator-(const int &x){
                iterator tmp(*this);
                tmp-=x;
                return tmp;
            }
            __inline int operator-(const iterator &oth)const{
                if(belong!=oth.belong)
                    throw invalid_iterator();
                return siz-oth.siz;
            }
            __inline deque* get_belong()const{return belong;}
            __inline T& operator*()const{
                if(it1.is_end())
                    throw invalid_iterator();
                return *it1;
            }
            __inline T* operator->()const{
                if(it1.is_end())
                    throw invalid_iterator();
                return it1.getTptr();
            }
        };

        class const_iterator{
        private:
            typename list<list<T> >::const_iterator it2;
            typename list<T>::const_iterator it1;
            int siz;
            const deque* belong;
            __inline void add(){
                if(it1.is_end())
                    throw sjtu::invalid_iterator();
                it1++;
                if(it1.is_end()){
                    it2++;
                    if(it2.is_end()){
                        it2--;
                        it1=it2->cend();
                    }else
                        it1=it2->cbegin();
                }
                siz++;
            }
            __inline void dec(){
                if(it1==it2->cbegin()){
                    it2--;
                    it1=it2->cend().try_pre();
                }else{
                    it1--;
                }
                siz--;
            }
        public:
            const_iterator(){siz=0;belong=0;}
            const_iterator(typename list<list<T> >::const_iterator i2,typename list<T>::const_iterator i1,int sz,const deque *b):belong(b){
                it2=i2;
                it1=i1;
                siz=sz;
            }
            const_iterator(const const_iterator &oth){
                it1=oth.it1;
                it2=oth.it2;
                siz=oth.siz;
                belong=oth.belong;
            }
            __inline int size(){return siz;}
            __inline bool operator==(const const_iterator &oth)const{
                return it1==oth.it1&&it2==oth.it2;
            }
            __inline bool operator!=(const const_iterator &oth)const{
                return !(*this==oth);
            }
            __inline const_iterator& operator=(const const_iterator &oth){
                if(this==&oth)return *this;
                it1=oth.it1;
                it2=oth.it2;
                siz=oth.siz;
                belong=oth.belong;
            }
            __inline const_iterator operator++(int){
                const_iterator tmp(*this);
                add();
                return tmp;
            }
            __inline const_iterator& operator++(){
                add();
                return *this;
            }
            __inline const_iterator operator--(int){
                const_iterator tmp(*this);
                dec();
                return tmp;
            }
            __inline const_iterator& operator--(){
                dec();
                return *this;
            }
            __inline const_iterator& operator+=(const int &x){
                if(x<0)
                    return *this-=(-x);
                if(x==0)return *this;
                int tar=siz+x;
                while(siz!=tar&&!it1.is_end()){
                    it1++;
                    siz++;
                }

                if(it1.is_end()){
                    it2++;
                    if(it2.is_end()){
                        it2--;
                        it1=it2->cend();
                    }else
                        it1=it2->cbegin();
                }
                if(siz==tar)return *this;
                while(siz+it2->size()<tar){
                    siz+=it2->size();
                    it2++;
                    it1=it2->cbegin();
                }
                while(siz!=tar){
                    add();
                }
                return *this;
            }
            __inline const_iterator& operator-=(const int &x){
                if(x<0)
                    return *this+=(-x);
                if(x==0)return *this;
                int tar=siz-x;
                while(siz!=tar&&it1!=it2->cbegin()){
                    siz--;
                    it1--;
                }
                if(siz==tar)return *this;
                while(1){
                    auto pre=it2;
                    pre--;
                    if(siz-pre->size()>tar){
                        siz-=pre->size();
                        it2--;
                        it1=it2->cbegin();
                    }else{
                        break;
                    }
                }
                while(siz!=tar){
                    dec();
                }
                return *this;
            }
            __inline const_iterator operator+(const int &x){
                const_iterator tmp(*this);
                tmp+=x;
                return tmp;
            }
            __inline const_iterator operator-(const int &x){
                const_iterator tmp(*this);
                tmp-=x;
                return tmp;
            }
            __inline int operator-(const const_iterator &oth)const{
                if(belong!=oth.belong)
                    throw invalid_iterator();
                return siz-oth.siz;
            }
            __inline deque* get_belong()const{return belong;}
            __inline const T& operator*()const{
                if(it1.is_end())
                    throw invalid_iterator();
                return *it1;
            }
            __inline const T* operator->()const{
                if(it1.is_end())
                    throw invalid_iterator();
                return it1.getTptr();
            }
        };

        deque(){
            siz=0;
            lst.push_back(list<T>());
        }
        deque(const deque &oth){
            siz=oth.siz;
            lst=oth.lst;
        }
        deque& operator=(const deque &oth){
            siz=oth.siz;
            lst=oth.lst;
            return *this;
        }
        ~deque(){
            clear();
        }
        __inline int size()const{return siz;}
        __inline bool empty()const{return siz==0;}
        __inline void clear(){
            siz=0;
            lst.clear();
            lst.push_back(list<T>());
        }
        __inline void push_back(const T &x){
            insert(end(),x);
        }
        __inline void pop_back(){
            erase(--end());
        }
        __inline void push_front(const T &x){
            insert(begin(),x);
        }
        __inline void pop_front(){
            erase(begin());
        }
        __inline void insert(const int &x,const T &y){__insert(x,y);}
        __inline void erase(const int &x){__erase(x);}

        __inline iterator insert(iterator pos,const T &y){
            if(pos.get_belong()!=this)
                throw invalid_iterator();
            int ps=pos.size();
            __insert(pos.size(),y,pos);
            if(ps+1==siz)
                return --end();
            return begin()+ps;
        }
        __inline iterator erase(iterator pos){

            if(pos.get_belong()!=this || pos==end())
                throw invalid_iterator();

            int ps=pos.size();
            __erase(ps,pos);
            if(ps==siz)
                return end();
            else
                return begin()+ps;
        }

        __inline T& at(const int &x){
            if(x<0||x>=siz)
                throw index_out_of_bound();
            return *(begin()+x);
        }
        __inline const T& at(const int &x)const{
            if(x<0||x>=siz)
                throw index_out_of_bound();
            return *(cbegin()+x);
        }
        __inline T& front(){
            if(empty())
                throw container_is_empty();
            return lst.front().front();
        }
        __inline T& back(){
            if(empty())
                throw container_is_empty();
            return lst.back().back();
        }

        __inline T& operator[](const int &x){
            if(x<0||x>=siz)
                throw index_out_of_bound();
            if(x==siz-1)return back();
            return *(begin()+x);
        }
        __inline const T& operator[](const int &x)const{
            if(x<0||x>=siz)
                throw index_out_of_bound();
            return *(cbegin()+x);
        }

        __inline iterator begin(){
            iterator iter(lst.begin(),lst.begin()->begin(),0,this);
            return iter;
        }
        __inline iterator end(){
            iterator iter(lst.end().try_pre(),(lst.end().try_pre())->end(),siz,this);
            return iter;
        }


        __inline const_iterator cbegin()const{
            const_iterator iter(lst.cbegin(),lst.cbegin()->cbegin(),0,this);
            return iter;
        }
        __inline const_iterator cend()const{
            const_iterator iter(lst.cend().try_pre(),(lst.cend().try_pre())->cend(),siz,this);
            return iter;
        }
    };
}
