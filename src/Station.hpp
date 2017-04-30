#pragma once


class Station{
private:
    string id;
public:
    Station(){}
    Station(const string &_id):id(_id){}
    const string& getName()const{
        return id;
    }
    bool operator==(const Station &oth)const{
        return getName()==oth.getName();
    }
    bool operator<(const Station &oth)const{
        return getName()<oth.getName();
    }
};

