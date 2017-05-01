#pragma once


#include "User.hpp"

class Admin : public User{
public:
    void addTrain(Train train){
        rw->addTrain(train);
    }
    void updateTrain(Train train){
        rw->updateTrain(train);
    }
    void removeTrain(string id){
        rw->removeTrain(id);
    }
    void startSale(string id){
        rw->startSale(id);
    }
    bool endSale(string id){
        return rw->endSale(id);
    }

};
