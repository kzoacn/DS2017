#pragma once
#ifndef LOG_HPP
#define LOG_HPP

#include "Ticket.hpp"
#include "lib/Date.hpp"
namespace sjtu {

class Log{
public:
   string id,name;
   bool ty;
   Ticket ticket;
   Log(){}
   Log(string _id,string _name,bool _ty,Ticket tic):
        id(_id),name(_name),ty(_ty),ticket(tic){}
   string to_string(){
        string ans;
        ans+=name+" ";
        ans+=id+" ";
        ans+=(ty==1?string("bought"):string("refund"))+" ";
        ans+=std::to_string(ticket.getNum())+" ";
        ans+=Ticket::to_string(ticket.getLevel())+" ";
        ans+="tickets of ";
        ans+=ticket.getTrain()+" ";
        ans+=string("from ")+ticket.getStart().getName()+" to "+ticket.getTarget().getName()+" ";
        ans+="in "+ticket.getStartDate().to_string();
        return ans;
   }
   friend OutputOfBinary & operator << (OutputOfBinary & cout, const Log &log) {
       cout<<log.id<<log.name<<log.ty<<log.ticket;
       return cout;
   }
   friend InputOfBinary & operator >> (InputOfBinary & cin, Log &log) {
       cin>>log.id>>log.name>>log.ty>>log.ticket;
       return cin;
   }
};

}

#endif LOG_HPP
