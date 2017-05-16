#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

#include <functional>
#include <cstddef>
#include <iostream>
#include "set.hpp"
#include "utility.hpp"
#include "../FileManager.hpp"
#include "exceptions.hpp"
#include "vector.hpp"

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
		int index;
		int _index;
		
		
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

		void save(vector<T> &p, vector<int> &q, RBNode* o) const {
			if(!o) {
				q.push_back(2);	
				return;
			}
			p.push_back(*(o->v));
			q.push_back(o->color);
			save(p, q, o->ch[0]);
			save(p, q, o->ch[1]);
		}

		void build(int &s1, int &s2, const vector<T> &p, const vector<int> &q, RBNode* &o, RBNode* fa) {
			int c = q[s2];
			if(c == 2) return;
			++_size;
			o = new RBNode(p[s1++], fa, NULL, NULL, c);
			build(s1, ++s2, p, q, o->ch[0], o);
			build(s1, ++s2, p, q, o->ch[1], o);	
		}
		
		void print(vector<RBNode*> &A, RBNode* o) {
            if(!o) return;
            if(o->ch[0]) print(A, o->ch[0]);
			A.push_back(o);
			if(o->ch[1]) print(A, o->ch[1]);
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

			T* operator->() const noexcept {
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

			T* operator->() const noexcept {
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

		void save(int &s1, int &s2, vector<T> &p, vector<int> &q) const {
			save(p, q, root);
			s1 = p.size();
			s2 = q.size();
		}

		void build(const vector<T> &p, const vector<int> &q) {
			clear();
			index = 0;
			_index = 0;
			build(index, _index, p, q, root, NULL);
            /*vector<RBNode*> A(_size);
			print(A, root);
            if(_size) {
                fir = A.front();
                for(int i = 0; i < _size - 1; ++i) A[i]->nex = A[i + 1], A[i + 1]->pre = A[i];
                A[_size - 1]->nex = _end;
                _end->pre = A[_size - 1];
            }*/
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

        bool erase(const Key &e) {
            /*RBNode* x = search(value_type(e, T()));
            if (!x) return false;
            remove(x);
            return true;*/
            return _set::erase(value_type(e, T()));
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
