//#include <algorithm>
#include "vector.hpp"
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
      void sort(vector<T>&vec,int l,int r){
          if(l==r)return ;
          if(l+1==r)return ;
          int mid=(l+r)>>1;
          sort(vec,l,mid);
          sort(vec,mid,r);
          vector<T>tmp;
          int cur1=l,cur2=mid;
          while (cur1!=mid&&cur2!=r) {
              if(vec[cur1]<vec[cur2]){
                  tmp.push_back(vec[cur1++]);
              }else{
                  tmp.push_back(vec[cur2++]);
              }
          }
          while(cur1!=mid)
              tmp.push_back(vec[cur1++]);
          while(cur2!=r)
              tmp.push_back(vec[cur2++]);
          for(int i=0;i<tmp.size();i++)
              vec[l+i]=tmp[i];
      }
      template<class T>
      void reverse(vector<T>&vec){
          vector<T>tmp;
          for(int i=(int)vec.size()-1;i>=0;i--)
              tmp.push_back(vec[i]);
          vec=tmp;
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


