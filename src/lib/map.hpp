#include <map>

using namespace std;
/*
#pragma once

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"


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
        map(const map &other) {
            root=head=0;
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
*/

/*
#pragma once
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

#define IsBlack(p) (!p || p->color == 1)
#define IsRed(p) (!IsBlack(p))

namespace sjtu {

	template<typename T, class Compare = std::less<T> >
	class set {

	protected:

		struct RBNode {
			RBNode* ch[2];
			RBNode* parent;
			RBNode* pre;
			RBNode* nex;
			T* v;
			int color;


			RBNode() : parent(NULL), color(0), pre(NULL), nex(NULL), v(NULL) {
				ch[0] = NULL;
				ch[1] = NULL;
			}

			RBNode(const T &e, RBNode* p = NULL, RBNode* lc = NULL, RBNode* rc = NULL, int color = 0) : v(new T(e)), parent(p), color(color), pre(NULL), nex(NULL) {
				ch[0] = lc;
				ch[1] = rc;
			}

		};

	public:
		RBNode* root;
		RBNode* f;
		RBNode* _end;
		RBNode* fir;
		int _size;

		Compare cmp;

		bool equal(const T &a, const T &b) const {
			return !cmp(a, b) && !cmp(b, a);
		}

		void removetree(RBNode* &x) {
			if (x == NULL) return;
			if (x->ch[0] != NULL) removetree(x->ch[0]);
			if (x->ch[1] != NULL) removetree(x->ch[1]);
			delete x->v;
			delete x;
			x = NULL;
		}

		RBNode* search(const T &e) {
			RBNode* o = root;
			while (o && !equal(e, *(o->v))) o = o->ch[cmp(*(o->v), e)];
			if (o) f = o->parent;
			return o;
		}

		RBNode* _search(const T &e) const {
			RBNode* o = root;
			while (o && !equal(e, *(o->v))) o = o->ch[cmp(*(o->v), e)];
			return o ? o : _end;
		}

		RBNode* succ(RBNode* o) {
			if (o->ch[1]) {
				o = o->ch[1];
				while (o->ch[0] != NULL) o = o->ch[0];
			}
			else {
				RBNode* x = o;
				if (o == root) return o;
				while (o->parent->ch[1] == o) {
					o = o->parent;
					if (o == root) return x;
				}
				o = o->parent;
			}
			return o;
		}

		RBNode* connect(RBNode* a, RBNode* b, RBNode* c, RBNode* T0, RBNode* T1, RBNode* T2, RBNode* T3) {
			a->ch[0] = T0;
			if (T0) T0->parent = a;
			a->ch[1] = T1;
			if (T1) T1->parent = a;
			c->ch[0] = T2;
			if (T2) T2->parent = c;
			c->ch[1] = T3;
			if (T3) T3->parent = c;
			b->ch[0] = a;
			a->parent = b;
			b->ch[1] = c;
			c->parent = b;
			return b;
		}

		RBNode* rotate(RBNode* o) {
			RBNode* p = o->parent;
			RBNode* g = p->parent;
			if (g->ch[0] == p) {
				if (p->ch[0] == o) {
					p->parent = g->parent;
					return connect(o, p, g, o->ch[0], o->ch[1], p->ch[1], g->ch[1]);
				}
				else {
					o->parent = g->parent;
					return connect(p, o, g, p->ch[0], o->ch[0], o->ch[1], g->ch[1]);
				}
			}
			else {
				if (p->ch[1] == o) {
					p->parent = g->parent;
					return connect(g, p, o, g->ch[0], p->ch[0], o->ch[0], o->ch[1]);
				}
				else {
					o->parent = g->parent;
					return connect(g, o, p, g->ch[0], o->ch[0], o->ch[1], p->ch[1]);
				}
			}
		}

		void solveDoubleRed(RBNode* x) {
			if (!x->parent) {
				root->color = 1;
				return;
			}
			RBNode* p = x->parent; if (IsBlack(p)) return;
			RBNode* g = p->parent;
			RBNode* u = g->ch[g->ch[0] == p];
			if (IsBlack(u)) {
				RBNode* gp = g->parent;
				RBNode* r = rotate(x);
				r->color = 1;
				r->ch[0]->color = 0;
				r->ch[1]->color = 0;
				if (!gp) root = r;
				else gp->ch[gp->ch[1] == g] = r;
				r->parent = gp;
			}
			else {
				p->color = 1;
				u->color = 1;
				if (g->parent) g->color = 0;
				solveDoubleRed(g);
			}
		}

		void solveDoubleBlack(RBNode* r) {
			RBNode* p = r ? r->parent : f;
			if (!p) return;
			RBNode* s = p->ch[r == p->ch[0]];
			if (IsBlack(s)) {
				RBNode* t = NULL;
				if (IsRed(s->ch[0])) t = s->ch[0];
				else if (IsRed(s->ch[1])) t = s->ch[1];
				if (t) {
					int pc = p->color;
					RBNode* g = p->parent;
					RBNode* b = rotate(t);
					b->parent = g;
					if (!g) root = b;
					else g->ch[g->ch[1] == p] = b;
					if (b->ch[0]) b->ch[0]->color = 1;
					if (b->ch[1]) b->ch[1]->color = 1;
					b->color = pc;
				}
				else {
					s->color = 0;
					if (IsRed(p)) p->color = 1;
					else solveDoubleBlack(p);
				}
			}
			else {
				s->color = 1;
				p->color = 0;
				RBNode* t = s->ch[s->parent->ch[1] == s];
				f = p;
				RBNode* g = p->parent;
				RBNode* b = rotate(t);
				if (!g) root = b;
				else g->ch[g->ch[1] == p] = b;
				b->parent = g;
				solveDoubleBlack(r);
			}
		}

		RBNode* insert(const T &e, int flag) {
			RBNode* x = new RBNode(e);
			_size++;
			if (!root) {
				x->pre = NULL;
				x->nex = _end;
				_end->pre = x;
				fir = root = x;
			}
			else {
				RBNode* y = root;
				RBNode* fa = NULL;
				while (y) {
					fa = y;
					if (equal(e, *(y->v))) return y;
					else y = y->ch[cmp(*(y->v), e)];
				}
				x->parent = fa;
				fa->ch[cmp(*(fa->v), e)] = x;
				f = fa;
				RBNode* o = succ(x);
				RBNode* p = o->pre;
				if (x == o) {
					x->nex = _end;
					x->pre = _end->pre;
					_end->pre = x;
					x->pre->nex = x;
				}
				else {
					if (!p) x->nex = o, o->pre = x, fir = x;
					else {
						x->nex = o;
						x->pre = o->pre;
						o->pre = x;
						x->pre->nex = x;
					}
				}
			}
			solveDoubleRed(x);
			return x;
		}

		void remove(RBNode* x) {
			if (_size == 1) fir = _end;
			else {
				RBNode* o = x->nex;
				RBNode* p = x->pre;
				if (!p) o->pre = NULL, fir = o;
				else p->nex = o, o->pre = p;
			}
			--_size;
			RBNode* w = x;
			if (x->ch[0] != NULL && x->ch[1] != NULL) w = succ(x);
			RBNode* r = w->ch[0] != NULL ? w->ch[0] : w->ch[1];
			if (r) r->parent = w->parent;
			f = w->parent;
			if (w->parent == NULL) root = r;
			else w->parent->ch[w->parent->ch[1] == w] = r;
			int pc = w->color;
			if (w != x) {
				if (f == x) f = w;
				w->parent = x->parent, w->ch[0] = x->ch[0], w->ch[1] = x->ch[1], w->color = x->color;
				if (x->parent) x->parent->ch[x->parent->ch[1] == x] = w;
				else root = w;
				if (x->ch[0]) x->ch[0]->parent = w;
				if (x->ch[1]) x->ch[1]->parent = w;
			}
			if (pc == 1) {
				if (IsRed(r)) r->color = 1;
				else solveDoubleBlack(r);
			}
			delete x->v;
			delete x;
			return;
		}

	public:

		class const_iterator;
		class iterator {

			set* p;
			RBNode* r;

		public:

			friend const_iterator;

			iterator() : p(NULL), r(NULL) {
			}

			iterator(const set* p, RBNode* r) : p((set*)p), r(r) {
			}

			iterator(const iterator &other) : p(other.p), r(other.r) {
			}

			iterator operator++(int) {
				if (!r || !r->nex) throw (invalid_iterator());
				iterator t(*this);
				r = r->nex;
				return t;
			}

			iterator & operator++() {
				if (!r || !r->nex) throw (invalid_iterator());
				r = r->nex;
				return *this;
			}

			iterator operator--(int) {
				if (!r || !r->pre) throw (invalid_iterator());
				iterator t(*this);
				r = r->pre;
				return t;
			}

			iterator & operator--() {
				if (!r || !r->pre) throw (invalid_iterator());
				r = r->pre;
				return *this;
			}

			T & operator*() const {
				return *(r->v);
			}

			set* point() const {
				return p;
			}

			RBNode* Node() const {
				return r;
			}

			iterator & operator = (const iterator &rhs) {
				p = rhs.p, r = rhs.r;
				return *this;
			}

			iterator & operator = (const const_iterator &rhs) {
				p = rhs.p, r = rhs.r;
				return *this;
			}

			bool operator==(const iterator &rhs) const {
				return p == rhs.p && r == rhs.r;
			}

			bool operator==(const const_iterator &rhs) const {
				return p == rhs.p && r == rhs.r;
			}

			bool operator!=(const iterator &rhs) const {
				return p != rhs.p || r != rhs.r;
			}

			bool operator!=(const const_iterator &rhs) const {
				return p != rhs.p || r != rhs.r;
			}

            T* operator->() {
				return r->v;
			}

		};

		class const_iterator {

			set* p;
			RBNode* r;

		public:

			friend iterator;

			const_iterator(): p(NULL), r(NULL) {
			}

			const_iterator(const set* p, RBNode* r) : p((set*)p), r(r) {
			}

			const_iterator(const iterator &other) : p(other.p), r(other.r) {
			}

			const_iterator(const const_iterator &other) : p(other.p), r(other.r) {
			}

			const_iterator operator++(int) {
				if (!r || !r->nex) throw (invalid_iterator());
				const_iterator t(*this);
				r = r->nex;
				return t;
			}

			const_iterator & operator++() {
				if (!r || !r->nex) throw (invalid_iterator());
				r = r->nex;
				return *this;
			}

			const_iterator operator--(int) {
				if (!r || !r->pre) throw (invalid_iterator());
				const_iterator t(*this);
				r = r->pre;
				return t;
			}

			const_iterator & operator--() {
				if (!r || !r->pre) throw (invalid_iterator());
				r = r->pre;
				return *this;
			}

			T  operator*() const {
				return *(r->v);
			}

			set* point() const {
				return p;
			}

			RBNode* Node() const {
				return r;
			}

			const_iterator & operator = (const iterator &rhs) {
				p = rhs.p, r = rhs.r;
				return *this;
			}

			const_iterator & operator = (const const_iterator &rhs) {
				p = rhs.p, r = rhs.r;
				return *this;
			}

			bool operator==(const iterator &rhs) const {
				return p == rhs.p && r == rhs.r;
			}

			bool operator==(const const_iterator &rhs) const {
				return p == rhs.p && r == rhs.r;
			}

			bool operator!=(const iterator &rhs) const {
				return p != rhs.p || r != rhs.r;
			}

			bool operator!=(const const_iterator &rhs) const {
				return p != rhs.p || r != rhs.r;
			}

            T* operator->() {
				return r->v;
			}

		};

		set() : _size(0), root(NULL), f(NULL) {
			_end = new RBNode();
			fir = _end;
		}

		set(const set &other) : _size(0), root(NULL), f(NULL) {
			_end = new RBNode();
			fir = _end;
			for (const_iterator it = other.cbegin(); it != other.cend(); ++it) insert(*it, 0);
		}

		~set() {
			clear();
			delete _end;
		}

		set & operator = (const set &other) {
			if (root == other.root) return *this;
			clear();
			for (const_iterator it = other.cbegin(); it != other.cend(); ++it) insert(*it, 0);
		}

		iterator begin() {
			return iterator(this, fir);
		}

		const_iterator cbegin() const {
			return const_iterator(this, fir);
		}

		iterator end() {
			return iterator(this, _end);
		}

		const_iterator cend() const {
			return const_iterator(this, _end);
		}

		bool empty() const {
			return _size == 0;
		}

		size_t size() const {
			return _size;
		}

		pair<iterator, bool> insert(const T &e) {
			RBNode* x = search(e);
			if (x) return pair<iterator, bool>(iterator(this, x), 0);
			x = insert(e, 0);
			return pair<iterator, bool>(iterator(this, x), 1);
		}

		void clear() {
			removetree(root);
			_size = 0;
			fir = _end;
		}

		bool erase(const T &e) {
			RBNode* x = search(e);
			if (!x) return false;
			remove(x);
			return true;
		}

		void erase(iterator pos) {
			if (pos.point() != this || pos.Node() == _end) throw(invalid_iterator());
			remove(pos.Node());
		}

		bool count(const T &e) const {
			return find(e) != cend();
		}

		iterator find(const T &e) {
			return iterator(this, _search(e));
		}

		const_iterator find(const T &e) const {
			return const_iterator(this, _search(e));
		}

	};

	template<class Key, class T, class Compare = std::less<Key> >
	struct Cmp {

		bool operator() (const pair<Key, T> &a, const pair<Key, T> &b) const {
			return Compare() (a.first, b.first);
		}

	};

	template< class Key, class T, class Compare = std::less<Key> >
	class map : public set<pair<Key, T>, Cmp<Key, T, Compare> > {

	public:

		typedef pair<Key, T> value_type;

		typedef set<pair<Key, T>, Cmp<Key, T, Compare> > _set;

		typedef typename _set::iterator iterator;

		typedef typename _set::const_iterator const_iterator;

		iterator find(const Key &key) {
			return _set::find(value_type(key, T()));
		}

		const_iterator find(const Key &key) const {
			return _set::find(value_type(key, T()));
		}

		size_t count(const Key &key) const {
			return _set::count(value_type(key, T()));
		}

		T & at(const Key &key) {
			iterator it = find(key);
			if (it == _set::end()) throw(index_out_of_bound());
			return it->second;
		}

		const T & at(const Key &key) const {
			const_iterator it = find(key);
			if (it == _set::cend()) throw(index_out_of_bound());
			return it->second;
		}

		T & operator[](const Key &key) {
			return _set::insert(value_type(key, T())).first->second;
		}

		const T & operator[](const Key &key) const {
			return at(key);
		}

	};
}

#endif
*/
