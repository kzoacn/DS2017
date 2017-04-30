#pragma once

#include <fstream>
#include <cstring>
#include <iostream>

#define string std::string
#define ifstream std::ifstream
#define ofstream std::ofstream
#define fstream std::fstream

const string inputfile = "input.txt";
const string outputfile = "output.txt";
const string logfile = "log.txt";

namespace sjtu {

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
			cout.fout << A;
			return cout;
		}

		~OutputOfAscll() {
			fout.flush();
			fout.close();
		}
	
	};

	bool isBlank(char c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\0';
	}

	class InputOfBinary {

		private:
			ifstream fin;
		
		public:
	
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
	
		friend InputOfBinary & operator >> (InputOfBinary & cin, string & A) {
			int m = 0;
			char t = ' ';
			while (isBlank(t)) cin >> t;
			while (!isBlank(t)) {
				std::cout << m << " " << t << std::endl;
				A[m++] = t;
				cin >> t;
			}
			A[m] = '\0';
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
	
		friend OutputOfBinary & operator << (OutputOfBinary & cout, const string & A) {
			cout << ' ';
			for (int i = 0; !isBlank(A[i]); i++) {
				cout << A[i];
			}
			cout << ' ';
			return cout;
		}
	
		~OutputOfBinary() {
			fout.flush();
			fout.close();
		}

	};

	void CopyFiles(string srcfile, string tarfile) {

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
	};
	
};
