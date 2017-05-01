#pragma once

#ifndef SJTU_FILEMANAGER_HPP
#define SJTU_FILEMANAGER_HPP


#include <fstream>
#include <cstring>
#include <iostream>
//#include "Station.hpp"
#include "lib/vector.hpp"
#include "lib/set.hpp"
#include "lib/map.hpp"
#include "lib/algo.hpp"

//#define string std::string
#define ifstream std::ifstream
#define ofstream std::ofstream
#define fstream std::fstream

const string inputfile = "input.txt";
const string outputfile = "output.txt";
const string logfile = "log.txt";

namespace sjtu {
/*
	class InputOfAscll {

		private:
			ifstream fin;
		
		public:
	
		InputOfAscll(string s = inputfile) {
			fin.open(s.c_str()); 
		}
	
		friend InputOfAscll & operator >> (InputOfAscll & cin, int & A) {
			cin.fin >> A;
			return cin;
		}
	
		friend InputOfAscll & operator >> (InputOfAscll & cin, double & A) {
			cin.fin >> A;
			return cin;
		}
		
		friend InputOfAscll & operator >> (InputOfAscll & cin, char & A) {
			cin.fin >> A;
			return cin;
		}
	
		friend InputOfAscll & operator >> (InputOfAscll & cin, string & A) {
            cin.fin >> A;
			return cin;
		}

		~InputOfAscll() {
			fin.close();
		}
	
	};


	class OutputOfAscll {

		private:
			ofstream fout;
		
		public:
	
		OutputOfAscll(string s = outputfile) {
			fout.open(s.c_str()); 
		}
	
		friend OutputOfAscll & operator << (OutputOfAscll & cout, int A) {
			cout.fout << A;
			return cout;
		}
	
		friend OutputOfAscll & operator << (OutputOfAscll & cout, double A) {
			cout.fout << A;
			return cout;
		}
	
		friend OutputOfAscll & operator << (OutputOfAscll & cout, char A) {
			cout.fout << A;
			return cout;
		}
	
		friend OutputOfAscll & operator << (OutputOfAscll & cout, string A) {
//			cout.fout << A;
			return cout;
		}

		~OutputOfAscll() {
			fout.flush();
			fout.close();
		}
	
	};
*/

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
            int len;//TODO
            cin>>len;
            A.clear();
            for(int i=0;i<len;i++){
                T c;cin>>c;
                A.insert(c);
            }
            return cin;
        }
        template<class T1,class T2>
        friend InputOfBinary & operator >> (InputOfBinary & cin, map<T1,T2> & A) {
            int len;//TODO
            cin>>len;
            A.clear();
            for(int i=0;i<len;i++){
                T1 a;T2 b;
                cin>>a>>b;
                A[a]=b;
            }
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
            cout<<(int)A.size();//TODO
            for(auto x:A)
                cout<<(T)x;
            return cout;
        }
        template<class T1,class T2>
        friend OutputOfBinary & operator << (OutputOfBinary & cout, const map<T1,T2> & A) {
            cout<<(int)A.size();//TODO
            for(auto x:A)
                cout<<(T1)x.first<<(T2)x.second;
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
#endif
