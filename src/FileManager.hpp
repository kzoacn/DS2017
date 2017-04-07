#include <fstream>
#include <cstring>
#include <iostream>
#define string std::string
#define ifstream std::ifstream
#define ofstream std::ofstream

const string inputfile = "input.txt";
const string outputfile = "output.txt";
const string logfile = "log.txt";

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
	friend OutputOfAscll & operator << (OutputOfAscll & cout, string A) {
		cout.fout << A;
		return cout;
	}
	~OutputOfAscll() {
		fout.flush();
		fout.close();
	}
};

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
	friend InputOfBinary & operator >> (InputOfBinary & cin, string & A) {
		cin.fin.read((char *) (& A), 256);
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
	friend OutputOfBinary & operator << (OutputOfBinary & cout, const string & A) {
		cout.fout.write((char *) (& A), 256);
		return cout;
	}
	~OutputOfBinary() {
		fout.flush();
		fout.close();
	}
};
