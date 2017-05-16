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
#include "Log.hpp"
#include <QString>
#include <QDebug>

namespace sjtu{

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
        for(int i=0;i<s.length();i++)if(is_digit(s[i]))
            x=x*10+s[i]-'0';
        if(s.find('.')!=-1)
            x/=10;
        return x;
    }
    Train push(){
        if(id=="")return Train();

        vector<Station> _way;
        vector<Date>_date;
        vector<vector<double> >_price;
        //vector<vector<int> >_restTicket;
        //_restTicket.resize(way.size());
        for(auto x:way)
            _way.push_back(Station(x));

        for(auto x:date){

            if(!is_digit(x[1][0]))
                x[1]=x[2];

            if(!is_digit(x[2][0]))
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
        /*for(int i=0;i<_restTicket.size();i++){
            _restTicket[i].resize(10);
            for(auto x:mp){
                _restTicket[i][x]=2000;
            }
        }*/

        for(int i=0;i<price.size();i++){
            _price.push_back(vector<double>());
            _price.back().resize(10);
            for(int j=0;j<mp.size();j++){
                _price.back()[mp[j]]=to_double(price[i][j]);
                //if(_price.back()[mp[i]]==0)
                //    _price.back()[mp[i]]=_price.front()[mp[i]];
            }
        }

        way.clear();
        date.clear();
        dis.clear();
        seat.clear();
        price.clear();
        Train train(id,_way,_date,_price);
        return train;
    }

    bool is_alpha(char c){
        return 'a'<=c&&c<='z' || 'A'<=c&&c<='Z';
    }
    bool is_blank(char c){
        return c==' '||c=='\n'||c=='\t';
    }
    bool is_digit(char c){
        return '0'<=c&&c<='9';
    }

public:
    vector<Train> process(ifstream &cin){
        vector<Train>ans;
        string s;
        int second=0;
        while(getline(cin,s)){
            std::stringstream sin;
            sin<<s;
            sin.imbue(std::locale(std::locale(), new csv_reader()));
            string tmp;
            sin>>tmp;
            //qDebug()<<QString::fromStdString(tmp)<<" "<<is_alpha(tmp[0])<<" "<<second<<endl;
            if(is_alpha(tmp[0])){
                if(id!="")ans.push_back(push());
                id=tmp;
                second=1;
            }else if(second==1){
                second=2;
              //  qDebug()<<"here!"<<endl;
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


    vector<string>split(string s){
        vector<string>vec;
        string tmp;
        for(int i=0;i<s.length();i++){
            if(is_blank(s[i])){
                if(!tmp.empty())
                    vec.push_back(tmp);
                tmp="";
            }else{
                tmp+=s[i];
            }
        }
        if(!tmp.empty())
            vec.push_back(tmp);
        return vec;
    }
    vector<Log> processLog(ifstream &fin){
        vector<Log>Logs;
        string s;
        int T=0;
        while(getline(fin,s)){
            if(is_digit(s[0]))continue;
            vector<string>vec=split(s);
            Logs.push_back(Log());
            Log &lg=Logs.back();
            if(++T%10000==0)
                qDebug()<<T/10000<<'\n';
           // for(auto x:vec)
           //     qDebug()<<QString::fromStdString(x)<<'\n';
            Ticket tic=Ticket(Station(vec[9]),Station(vec[11]),Date::fromDay(vec[13]),vec[7],Ticket::toLevel(vec[4]),to_int(vec[3]));
            lg=Log(vec[1],vec[0],vec[2][0]=='b'?1:0,tic);
        }
        return Logs;
    }
};

}
