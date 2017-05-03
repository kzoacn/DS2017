#pragma once

#ifndef STATION_HPP
#define STATION_HPP

#include "FileManager.hpp"

namespace sjtu{

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
    friend OutputOfBinary & operator << (OutputOfBinary & cout, const Station &station) {
        cout<<station.id;
        return cout;
    }
    friend InputOfBinary & operator >> (InputOfBinary & cin, Station &station) {
        cin>>station.id;
        return cin;
    }
};

}
#endif

