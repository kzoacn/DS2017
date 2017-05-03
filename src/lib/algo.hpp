//#include <algorithm>
//using namespace std;

#pragma once

namespace sjtu {

    template<class InputIterator, class T>
      InputIterator find (InputIterator first, InputIterator last, const T& val){
      while (first!=last) {
        if (*first==val) return first;
        ++first;
      }
      return last;
    }


    template<class T>
    T min(const T &a,const T &b){
        return a<b?a:b;
    }
    template<class T>
    T max(const T &a,const T &b){
        return a<b?b:a;
    }
}


