#include <fstream>
#include <cstring>
#define string std::string
#define ifstream std::ifstream
#define ofstream std::ofstream

const string inputfile = "input.txt";
const string outputfile = "output.txt";
const string logfile = "log.txt";

class InputOfAscll {
	private:
		int Integer;
		double Double;
		string String;
		ifstream fin;
	public:
	InputOfAscll(string s = inputfile) {
		fin.open(s.c_str()); 
	}
	int nextInt() {
		fin >> Integer;
		return Integer;
	}
	double nextDouble() {
		fin >> Double;
		return Double;
	}
	string nextString() {
		fin >> String;
		return String;
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
		int Integer;
		double Double;
		string String;
		ofstream fout;
	public:
	OutputOfAscll(string s = outputfile) {
		fout.open(s.c_str()); 
	}
	int nextInt() {
		fout << Integer;
		return Integer;
	}
	double nextDouble() {
		fout << Double;
		return Double;
	}
	string nextString() {
		fout << String;
		return String;
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
