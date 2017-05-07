#pragma once

#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "User.hpp"
#include <iostream>

namespace sjtu{

class Admin : public User{
public:
    Admin(){}
    Admin(string _id,shared_ptr<RailwayMinistry>_rm):
        User(_id,_rm){}
    void addTrain(Train train){
        rw->addTrain(train);
    }
    void addTrainFromCSV(string input){
        ifstream fin(input);
        if(fin)
            rw->addTrainFromCSV(fin);
    }
    void updateTrain(Train train){
        rw->updateTrain(train);
    }
    void removeTrain(string id){
        rw->removeTrain(id);
    }
    void startSale(string id,Date date){
        rw->startSale(id,date);
    }
    bool endSale(string id,Date date){
        return rw->endSale(id,date);
    }

};

}
#endif
