#pragma once

#ifndef USER_HPP
#define USER_HPP

#include "RailwayMinistry.hpp"
#include "lib/shared_ptr.hpp"
#include "lib/vector.hpp"

namespace sjtu{

class User{
public:
    string id;
    shared_ptr<RailwayMinistry>rw;
    User(){}
    User(string _id,shared_ptr<RailwayMinistry> _rw):id(_id),rw(_rw){}

    bool login(string _id,string pwd){
        if(rw->isUser(id,pwd)){
            id=_id;
            return true;
        }else{
            return false;
        }
    }
    vector<Train>getTrainByST(Station a,Station b,Date date){
        return rw->getTrainByST(a,b,date);
    }
    vector<Ticket> queryTicket(){
        return rw->queryTicket(id);
    }
    Train getTrainByID(string id){
        return rw->getTrainByID(id);
    }
    bool existTrain(string id){
        return rw->existTrain(id);
    }
    pair<Ticket,bool> buyTicket(string trainid,Station a,Station b,TicketLevel level,int num,Date date){
        return rw->buyTicket(id,trainid,a,b,level,num,date);
    }
    bool refund(Ticket ticket){
        return rw->refund(id,ticket);
    }
    bool updateInfo(string pwd,string name){
        rw->updateInfo(id,pwd,name);
    }
    vector<Ticket> queryPath(Station a,Station b,Date date){
        return rw->queryPath(a,b,date);
    }
};

}
#endif
