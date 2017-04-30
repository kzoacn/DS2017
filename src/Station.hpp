#pragma once

#include "FileManager.hpp"

using namespace sjtu;

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
    friend InputOfBinary & operator >> (InputOfBinary & cin, Station &station) {
        cin>>station.id;
        return cin;
    }
    friend OutputOfBinary & operator << (OutputOfBinary & cout, Station &station) {
        cout<<station.id;
        return cout;
    }
};


