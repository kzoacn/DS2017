#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {

    template<typename T>
    class vector {

    private:
        T* a;
        int siz;
        int maxsize;

        void doublespace() {
            T* t = a;
            maxsize *= 2;
            a = (T*):: operator new(maxsize * sizeof(T));
            for (int i = 0; i < siz; ++i) :: new (a + i) T(t[i]);
                //a[i] = t[i];
            ::operator delete(t);
        }

    public:

        class const_iterator;
        class iterator {

        public:

            vector* p;
            int index;

            iterator() : p(NULL), index(0) {}
            iterator(vector* p, int index) : p(p), index(index) {}
            iterator(const iterator &t) : p(t.p), index(t.index) {}

            iterator operator+(const int &n) const {
                iterator t(*this);
                t.index += n;
                return t;
            }

            iterator operator-(const int &n) const {
                iterator t(*this);
                t.index -= n;
                return t;
            }

            int operator-(const iterator &rhs) const {
                if (p != rhs.p) throw(invalid_iterator());
                return index - rhs.index;
            }

            iterator operator+=(const int &n) {
                index += n;
                return *this;
            }

            iterator operator-=(const int &n) {
                index -= n;
                return *this;
            }

            iterator operator++(int) {
                iterator t(*this);
                ++index;
                return t;
            }

            iterator& operator++() {
                ++index;
                return *this;
            }

            iterator operator--(int) {
                iterator t(*this);
                --index;
                return t;
            }

            iterator& operator--() {
                --index;
                return *this;
            }

            T& operator*() const {
                return p->a[index];
            }

            bool operator==(const iterator &rhs) const {
                return p == rhs.p && index == rhs.index;
            }

            bool operator==(const const_iterator &rhs) const {
                return p == rhs.p && index == rhs.index;
            }

            bool operator!=(const iterator &rhs) const {
                return !(p == rhs.p && index == rhs.index);
            }

            bool operator!=(const const_iterator &rhs) const {
                return !(p == rhs.p && index == rhs.index);
            }

        };

        class const_iterator {

        public:

            const vector* p;
            int index;

            const_iterator() : p(NULL), index(0) {}
            const_iterator(const vector* p, int index) : p(p), index(index) {}
            const_iterator(const const_iterator &t) : p(t.p), index(t.index) {}

            const_iterator operator+(const int &n) const {
                const_iterator t(*this);
                t.index += n;
                return t;
            }

            const_iterator operator-(const int &n) const {
                const_iterator t(*this);
                t.index -= n;
                return t;
            }

            int operator-(const iterator &rhs) const {
                if (p != rhs.p) throw(invalid_iterator());
                return index - rhs.index;
            }

            const_iterator operator+=(const int &n) {
                index += n;
                return *this;
            }

            const_iterator operator-=(const int &n) {
                index -= n;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator t(*this);
                ++index;
                return t;
            }

            const_iterator& operator++() {
                ++index;
                return *this;
            }

            const_iterator operator--(int) {
                iterator t(*this);
                --index;
                return t;
            }

            const_iterator& operator--() {
                --index;
                return *this;
            }

            T& operator*() const {
                return p->a[index];
            }

            bool operator==(const iterator &rhs) const {
                return p == rhs.p && index == rhs.index;
            }

            bool operator==(const const_iterator &rhs) const {
                return p == rhs.p && index == rhs.index;
            }

            bool operator!=(const iterator &rhs) const {
                return !(p == rhs.p && index == rhs.index);
            }

            bool operator!=(const const_iterator &rhs) const {
                return !(p == rhs.p && index == rhs.index);
            }
        };

        vector(int Maxsize = 10) : maxsize(Maxsize), siz(0) {
            a = (T*):: operator new(maxsize * sizeof(T));
        }

        vector(const vector &other) : maxsize(other.maxsize), siz(other.siz){
            a = (T*):: operator new(maxsize * sizeof(T));
            for (int i = 0; i < siz; ++i) :: new (a + i) T(other.a[i]);
                //a[i] = other.a[i];
        }

        ~vector() {
            for (int i = 0; i < siz; ++i) (a + i)->~T();
            ::operator delete(a);
        }

        vector &operator=(const vector &other) {
            if (a == other.a) return *this;
            for (int i = 0; i < siz; ++i) (a + i)->~T();
            ::operator delete(a);
            maxsize = other.maxsize;
            siz = other.siz;
            a = (T*):: operator new(maxsize * sizeof(T));
            for (int i = 0; i < siz; ++i) :: new (a + i) T(other.a[i]);
            //a[i] = other.a[i];
            return *this;
        }

        T & at(const size_t &pos) {
            if (pos < 0 || pos >= siz) throw(index_out_of_bound());
            return a[pos];
        }

        const T & at(const size_t &pos) const {
            if (pos < 0 || pos >= siz) throw(index_out_of_bound());
            return a[pos];
        }

        T & operator[](const size_t &pos) {
            if (pos < 0 || pos >= siz) throw(index_out_of_bound());
            return a[pos];
        }

        const T & operator[](const size_t &pos) const {
            if (pos < 0 || pos >= siz) throw(index_out_of_bound());
            return a[pos];
        }

        T & front() const {
            if (!siz) throw(container_is_empty());
            return a[0];
        }

        T & back() const {
            if (!siz) throw(container_is_empty());
            return a[siz - 1];
        }
        void resize(int n){
            n-=size();
            for(int i=0;i<n;i++)
                push_back(T());
        }
        iterator begin() {
            iterator t(this, 0);
            return t;
        }

        const_iterator cbegin() const {
            const_iterator t(this, 0);
            return t;
        }

        iterator end() {
            iterator t(this, siz);
            return t;
        }

        const_iterator cend() const {
            const_iterator t(this, siz);
            return t;
        }

        bool empty() const {
            return siz == 0;
        }

        size_t size() const {
            return siz;
        }

        size_t capacity() const {
            return maxsize;
        }

        void clear() {
            for (int i = 0; i < siz; ++i) (a + i)->~T();
            siz = 0;
        }

        iterator insert(iterator pos, const T &value) {
            int cur = pos.index;
            if (cur > siz) throw(index_out_of_bound());
            if (siz == maxsize) doublespace();
            :: new (a + siz) T(a[siz - 1]);
            for (int i = siz - 1; i > cur; --i) a[i] = a[i - 1];
            a[cur] = value;
            ++siz;
            return pos;
        }

        iterator insert(const size_t &ind, const T &value) {
            int cur = ind;
            if (cur > siz) throw(index_out_of_bound());
            if (siz == maxsize) doublespace();
            :: new (a + siz) T(a[siz - 1]);
            for (int i = siz - 1; i > cur; --i) a[i] = a[i - 1];
            a[cur] = value;
            iterator pos(this, cur);
            ++siz;
            return pos;
        }

        iterator erase(iterator pos) {
            int cur = pos.index;
            if (cur < 0 || cur >= siz) throw(index_out_of_bound());
            --siz;
            for (int i = cur; i < siz; ++i) a[i] = a[i + 1];
            (a + siz)->~T();
            return pos;
        }

        iterator erase(const size_t &ind) {
            int cur = ind;
            if (cur < 0 || cur >= siz) throw(index_out_of_bound());
            --siz;
            for (int i = cur; i < siz; ++i) a[i] = a[i + 1];
            (a + siz)->~T();
            iterator pos(this, cur);
            return pos;
        }

        void push_back(const T &value) {
            if (siz == maxsize) doublespace();
            :: new (a + siz) T(value);
            ++siz;
        }

        void pop_back() {
            siz--;
            (a + siz)->~T();
        }
    };
}

#endif
