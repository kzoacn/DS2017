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


	while(getline(cin,s)){
		stringstream sin;
		sin<<s;
		sin.imbue(std::locale(std::locale(), new csv_reader()));
	
		string tmp;
		sin>>tmp;
		if(isalpha(tmp[0])){
			push();
			id=tmp;
		}else if(tmp=="վ��"){
			sin>>tmp>>tmp>>tmp>>tmp;
			while(sin>>tmp){
				seat.push_back(tmp);
			}
		}else{
			way.push_back(tmp);
			sin>>tmp;date.push_back(tmp);
			sin>>tmp;date.back()+="+"+tmp;
			sin>>tmp;date.back()+="+"+tmp;
			//sin>>tmp;date.back()+="+"+tmp;
			sin>>tmp;dis.push_back(tmp);
			price.push_back(vector<string>());
			for(int i=0;i<seat.size();i++){
				sin>>tmp;
				price.back().push_back(tmp);
			}
		}
	
	}
	push();
    return 0;
}
