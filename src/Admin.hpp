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
    vector<Train>getTrainByST(Station a,Station b,Date date){
        return rw->getTrainBySTForAdmin(a,b,date);
    }

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
    bool removeTrain(string id){
        return rw->removeTrain(id);
    }
    void startSale(string id,Date date){
        rw->startSale(id,date);
    }
    bool endSale(string id,Date date){
        return rw->endSale(id,date);
    }
    bool hasSold(string id,Date date){
        return rw->hasSold(id,date);
    }

    bool canSell(string id,Date date){
        return rw->canSell(id,date);
    }

    void addLogFromFile(string path){
        ifstream fin(path);
        if(fin)
            rw->addLogFromFile(fin);
    }
    void exportLog(string output){
        ofstream fout(output);
        if(fout)
            rw->exportLog(fout);
    }

};

}
#endif
