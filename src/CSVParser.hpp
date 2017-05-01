#include <locale>
#include <iterator>
#include <iostream>
#include <sstream>
#include <cctype>
#include "lib/vector.hpp"
#include "lib/algo.hpp"
#include "lib/Date.hpp"
#include "lib/shared_ptr.hpp"
#include "Train.hpp"
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


class CSVParser{
private:
    string id;
    vector<string>way;
    vector<vector<string> >date;
    vector<string>dis;
    vector<string>seat;
    vector<vector<string> >price;
    int to_int(string s){
        int x=0;
        for(int i=0;i<s.length();i++)
            x=x*10+s[i]-'0';
        return x;
    }
    double to_double(string s){
        int x=0;
        for(int i=0;i<s.length();i++)if(isdigit(s[i]))
            x=x*10+s[i]-'0';
        if(s.find('.')!=-1)
            x/=10;
        return x;
    }
    Train push(){
        if(id=="")return Train();
        vector<Station> _way;
        vector<Date>_date;
        vector<vector<double> >_price(way.size());
        vector<vector<int> >_restTicket(way.size());

        for(auto x:way)
            _way.push_back(Station(x));

        for(auto x:date){
            if(!isdigit(x[1][0]))
                x[1]=x[2];
            if(!isdigit(x[2][0]))
                x[2]=x[1];
            int y,m,d,h,min;
            y=to_int(x[0].substr(0,4));
            m=to_int(x[0].substr(5,2));
            d=to_int(x[0].substr(8,2));
            h=to_int(x[1].substr(0,2));
            min=to_int(x[1].substr(3,2));
            _date.push_back(Date(y,m,d,h,min));
        }
        vector<int>mp;
        for(auto x:seat){
            mp.push_back(Ticket::toLevel(x));
        }
        for(int i=0;i<_restTicket.size();i++){
            _restTicket[i].resize(10);
            for(auto x:mp){
                _restTicket[i][x]=2000;
            }
        }
        for(auto &x:price){
            _price.push_back(vector<double>());
            _price.back().resize(10);
            for(int i=0;i<x.size();i++){
                _price.back()[mp[i]]=to_double(x[i]);
            }
        }

        way.clear();
        date.clear();
        dis.clear();
        seat.clear();
        price.clear();
        Train train(id,_way,_date,_price,_restTicket);
        return train;
    }

public:
    vector<Train> process(ifstream &cin){
        vector<Train>ans;
        string s;
        while(getline(cin,s)){
            stringstream sin;
            sin<<s;
            sin.imbue(std::locale(std::locale(), new csv_reader()));
            string tmp;
            sin>>tmp;
            if(isalpha(tmp[0])){
                if(id!="")ans.push_back(push());
                id=tmp;
            }else if(tmp=="站名"){
                sin>>tmp>>tmp>>tmp>>tmp;
                while(sin>>tmp){
                    seat.push_back(tmp);
                }
            }else{
                way.push_back(tmp);
                date.push_back(vector<string>());
                sin>>tmp;date.back().push_back(tmp);
                sin>>tmp;date.back().push_back(tmp);
                sin>>tmp;date.back().push_back(tmp);
                sin>>tmp;dis.push_back(tmp);
                price.push_back(vector<string>());
                for(int i=0;i<seat.size();i++){
                    sin>>tmp;
                    price.back().push_back(tmp);
                }
            }

        }
        if(id!="")ans.push_back(push());
        return ans;
    }

};
