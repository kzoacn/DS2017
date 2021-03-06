//#pragma once

#ifndef SJTU_FILEMANAGER_HPP
#define SJTU_FILEMANAGER_HPP


#include <fstream>
#include <cstring>
#include <iostream>
//#include "Station.hpp"
#include "lib/vector.hpp"
//#include "lib/set.hpp"
#include "lib/map.hpp"
#include "lib/algo.hpp"

#define string std::string
#define ifstream std::ifstream
#define ofstream std::ofstream
#define fstream std::fstream

//using sjtu::map;
const string inputfile = "input.txt";
const string outputfile = "output.txt";
const string logfile = "log.txt";

namespace sjtu {

	class InputOfBinary {

		private:
			ifstream fin;
		
		public:

        operator bool(){
            return bool(fin);
        }

		InputOfBinary(string s = logfile) {
            fin.open(s.c_str(), std::ios::binary);
		}
	
		friend InputOfBinary & operator >> (InputOfBinary & cin, int & A) {
			cin.fin.read((char *) (& A), sizeof A);
			return cin;
		}
	
		friend InputOfBinary & operator >> (InputOfBinary & cin, double & A) {
			cin.fin.read((char *) (& A), sizeof A);
			return cin;
		}

        friend InputOfBinary & operator >> (InputOfBinary & cin, char & A) {
            cin.fin.read((char *) (& A), sizeof A);
            return cin;
        }
        friend InputOfBinary & operator >> (InputOfBinary & cin, bool & A) {
            cin.fin.read((char *) (& A), sizeof A);
            return cin;
        }
	
        friend InputOfBinary & operator >> (InputOfBinary & cin, string & A) {
            int len;
            cin>>len;
            A="";
            for(int i=0;i<len;i++){
                char c;cin>>c;
                A+=c;
            }
            return cin;
        }

        template<class T1,class T2>
        friend InputOfBinary & operator >> (InputOfBinary & cin, pair<T1,T2> & A) {
            cin>>A.first>>A.second;
            return cin;
        }

        template<class T>
        friend InputOfBinary & operator >> (InputOfBinary & cin, vector<T> & A) {
            int len;
            cin>>len;
            A.clear();
            for(int i=0;i<len;i++){
                T c;cin>>c;
                A.push_back(c);
            }
            return cin;
        }
		
        template<class T>
        friend InputOfBinary & operator >> (InputOfBinary & cin, set<T> & A) {
			int len1, len2;
			cin >> len1 >> len2;
			vector<T> p(len1);
			vector<int> q(len2);
			while(len1--) {
				T v;
				cin >> v;
				p.push_back(v);
			}
			while(len2--) {
				int type;
				cin >> type;
				q.push_back(type);
			}
			A.build(p, q);
			return cin;
        }
		
        template<class T1,class T2>
        friend InputOfBinary & operator >> (InputOfBinary & cin, map<T1,T2> & A) {
			int len1, len2;
			cin >> len1 >> len2;
			vector<pair<T1, T2>> p(len1);
			vector<int> q(len2);
			while(len1--) {
				pair<T1, T2> v;
				cin >> v;
				p.push_back(v);
			}
			while(len2--) {
				int type;
				cin >> type;
				q.push_back(type);
			}
			A.build(p, q);
			return cin;
        }


		~InputOfBinary() {
			fin.close();
        }
	
    };

	class OutputOfBinary {

		private:
			ofstream fout;
		
		public:
	
		OutputOfBinary(string s = outputfile) {
            fout.open(s.c_str(), std::ios::binary);
		}
	
		friend OutputOfBinary & operator << (OutputOfBinary & cout, const int & A) {
			cout.fout.write((char *) (& A), sizeof A);
			return cout;
		}
	
		friend OutputOfBinary & operator << (OutputOfBinary & cout, const double & A) {
			cout.fout.write((char *) (& A), sizeof A);
			return cout;
		}

        friend OutputOfBinary & operator << (OutputOfBinary & cout, const char & A) {
            cout.fout.write((char *) (& A), sizeof A);
            return cout;
        }
        friend OutputOfBinary & operator << (OutputOfBinary & cout, const bool & A) {
            cout.fout.write((char *) (& A), sizeof A);
            return cout;
        }
	
        friend OutputOfBinary & operator << (OutputOfBinary & cout, const string & A) {
            cout<<(int)A.length();
            for(int i=0;i<A.length();i++)
                cout<<A[i];
            return cout;
        }

        template<class T>
        friend OutputOfBinary & operator << (OutputOfBinary & cout, const vector<T> & A) {
            cout<<(int)A.size();
            for(int i=0;i<A.size();i++)
                cout<<(T)A.at(i);
            return cout;
        }
        template<class T>
        friend OutputOfBinary & operator << (OutputOfBinary & cout, const set<T> & A) {
			int s1, s2;
			vector<T> p;
			vector<int> q;
			A.save(s1, s2, p, q);
			cout << s1;
			cout << s2;
			for(int i = 0; i < s1; ++i) cout << (T)p[i];
			for(int i = 0; i < s2; ++i) cout << q[i];
			return cout;
        }
        template<class T1,class T2>
        friend OutputOfBinary & operator << (OutputOfBinary & cout, const map<T1,T2> & A) {
			int s1, s2;
			vector<pair<T1, T2> > p;
			vector<int> q;
			A.save(s1, s2, p, q);
			cout << s1;
			cout << s2;
			for(int i = 0; i < s1; ++i) cout << (pair<T1, T2>)p[i];
			for(int i = 0; i < s2; ++i) cout << q[i];
			return cout;
        } 

        template<class T1,class T2>
        friend OutputOfBinary & operator << (OutputOfBinary & cout, const pair<T1,T2> & A) {
            cout<<(T1)A.first<<(T2)A.second;
            return cout;
        }
	
		~OutputOfBinary() {
			fout.flush();
			fout.close();
        }

	};

    /*void CopyFiles(string srcfile, string tarfile) {

		ifstream cin(srcfile.c_str(), fstream::in|fstream::binary);
		ofstream cout(tarfile.c_str(), fstream::out|fstream::binary);

		char buffer[1024];
	
		for (;!cin.eof();) {
			size_t len = cin.read(buffer, 1024).gcount();
			cout.write(buffer, len);
		}

		cin.close();
		cin.clear();
		cout.close();
		cout.clear();
    };*/
	
};
#undef string

#endif
