#pragma once
#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <iostream>

namespace sjtu {

template<class T>
inline void swap(T& a, T& b) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

template<typename T>
struct single_deleter {
    void operator ()(T*& rhs) {
        delete rhs;
        rhs = nullptr;
    }
};

template<typename T>
struct array_deleter {
    void operator ()(T*& rhs) {
        delete [] rhs;
        rhs = nullptr;
    }
};

template<typename T, class deleter = single_deleter<T> >
class shared_ptr {
    T* ptr;
    size_t* cnt;
public:
    shared_ptr(): cnt(nullptr), ptr(nullptr) {
    }
    shared_ptr(T* rhs): ptr(rhs), cnt(nullptr) {
        if (ptr) {
            cnt = new size_t(1);
        }
        rhs = nullptr;
    }
    shared_ptr(shared_ptr& rhs) {
        ptr = rhs.ptr;
        if (ptr) {
            (*rhs.cnt)++;
        }
        cnt = rhs.cnt;
    }
    shared_ptr(shared_ptr&& rhs) {
        ptr = rhs.ptr;
        cnt = rhs.cnt;
        rhs.ptr = nullptr;
        rhs.cnt = nullptr;
    }
    ~shared_ptr() {
        deconstruct();
    }
    void deconstruct() {
        if(ptr == nullptr) {
            return;
        }
        -- (*cnt);
        if (*cnt == 0) {
            deleter()(ptr);
            ptr = nullptr;
            delete cnt;
            cnt = nullptr;
        }
    }
    shared_ptr& operator = (T* rhs) {
        deconstruct();
        ptr = rhs;
        cnt = nullptr;
        if (ptr) {
            cnt = new size_t (1u);
        }
        return *this;
    }
    shared_ptr& operator = (const shared_ptr& rhs) {
        deconstruct();
        cnt = rhs.cnt;
        ptr = rhs.ptr;
        if (ptr) {
            (*cnt)++;
        }
        return *this;
    }
    shared_ptr& operator = (shared_ptr&& rhs) {
        if (this == &rhs) {
            return *this;
        }
        deconstruct();
        ptr = rhs.ptr;
        cnt = rhs.cnt;
        rhs.ptr = nullptr;
        rhs.cnt = nullptr;
        return *this;
    }
    bool operator == (const shared_ptr& rhs) {
        return ptr == rhs.ptr;
    }
    bool operator != (const shared_ptr& rhs) {
        return ptr != rhs.ptr;
    }
    bool operator ! () const{
        return ptr == nullptr;
    }
    bool check_null() const{
        return ptr == nullptr;
    }
    T& operator * () const{
        return *ptr;
    }
    T* operator -> () const{
        return ptr;
    }
    T& operator [] (size_t index) {
        return *(ptr + index);
    }
    size_t use_count() {
        return *cnt;
    }
};

}

#endif
