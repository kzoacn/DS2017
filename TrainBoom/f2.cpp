#include <locale>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
#include <bits/stdc++.h>
using namespace std;
struct csv_reader: std::ctype<char> {
    csv_reader(): std::ctype<char>(get_table()) {}
    static std::ctype_base::mask const* get_table() {
        static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());

        rc[','] = std::ctype_base::space;
        rc['\n'] = std::ctype_base::space;
        rc[' '] = std::ctype_base::space;
        return &rc[0];
    }
}; 


	string id;
	vector<string>way;
	vector<string>date;
	vector<string>dis;
	vector<string>seat;
	vector<vector<string> >price;

	void push(){
		if(id=="")return ;
		cout<<id<<endl;

		int n=way.size(),m=seat.size();
		cout<<n<<" "<<m<<endl;
		for(auto x:way)
			cout<<x<<" ";
		cout<<endl;
		for(auto x:date)
			cout<<x<<endl;
		cout<<endl;
		for(auto x:seat)
			cout<<x<<" ";
		cout<<endl;
		for(auto &x:price){
			for(auto y:x){
				cout<<y<<" ";
			}
			cout<<endl;
		}

		way.clear();
		date.clear();
		dis.clear();
		seat.clear();
		price.clear();
	}

int main() {
    std::cin.imbue(std::locale(std::locale(), new csv_reader()));
    string s;
	set<string>S;


	while(cin>>s){
		if(s.find("нт")!=-1)
			S.insert(s);
	}
	for(auto x:S)
		cout<<x<<endl;
    return 0;
}
