/*#include <locale>
#include <vector>
#include <algorithm>
#include <iterator>
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


int main() {
    std::cin.imbue(std::locale(std::locale(), new csv_reader()));
    string s;
	set<string>S;
	while(cin>>s){
		if(s.find("��")!=-1){
			S.insert(s);
		}
	}
	for(auto x:S)
		cout<<x<<endl;
    return 0;
}*/
