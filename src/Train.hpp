﻿#pragma once

#ifndef TRAIN_HPP
#define TRAIN_HPP

#include "Station.hpp"
#include "Ticket.hpp"
#include "lib/vector.hpp"
#include "lib/Date.hpp"
#include "FileManager.hpp"

namespace sjtu{

class Train{
private:
    string id;
	vector<Station>way;
	vector<Date>date;
    vector<vector<double> >price;
    map<Date,vector<vector<int> > >restTicket;
    set<Date>onSale;
    set<Date>Sold;
public:
    Train(){}
    Train(string _id,vector<Station> _way,vector<Date>_date,vector<vector<double> >_price):
        id(_id),way(_way),date(_date),price(_price){}
	Station getStart(){
		return way.front();
	}
    Station getTarget(){
		return way.back();
	}
	vector<Station> getWay(){
		return way;
	}
	double getCost(Station a,Station b,TicketLevel level){
		double x,y;
		for(int i=0;i<way.size();i++){
			if(way[i]==a){
                x=price[i][int(level)];
			}
			if(way[i]==b){
                y=price[i][int(level)];
			}
		}
		return y-x;
    }
    Date getTime(Date dt,Station station){
        for(int i=0;i<way.size();i++)
            if(way[i]==station)
                return date[i]+(dt.to_day()-date[0].to_day());
        throw "No such station!";
    }
    Date getStartTime(){
        return date.front();
    }
    void init(Date date){
        if(!restTicket.count(date)){
            vector<vector<int> >&rT = restTicket[date];
            rT.resize(price.size());
            for(auto &x:rT){
                x.resize(price.front().size());
                for(auto &y:x)
                    y=2000;
            }
            onSale.insert(date);
        }
    }
    int getRestTicket(Station a,Station b,TicketLevel level,Date date){
        init(date);
		int ans=int(2e9),start=0;
		for(int i=0;i<way.size();i++){
			if(way[i]==a)start=1;
			if(way[i]==b)break;
			if(start)
                ans=min(ans,restTicket[date][i][level]);
		}
		return ans;
	}
    Ticket buyTicket(Station a,Station b,TicketLevel level,int num,Date date){
        Sold.insert(date);
		int start=0;
		for(int i=0;i<way.size();i++){
			if(way[i]==a)start=1;
			if(way[i]==b)break;
			if(start)
                restTicket[date][i][level]-=num;
		}
        return Ticket(a,b,getCost(a,b,level),getTime(date,a),getTime(date,b),id,level,num,getStartTime().to_day());
	}
    void refundTicket(Ticket ticket){
        init(ticket.getTrainDate());
		int start=0;
		for(int i=0;i<way.size();i++){
            if(way[i]==ticket.getStart())start=1;
            if(way[i]==ticket.getTarget())break;
			if(start)
                restTicket[ticket.getStartDate()][i][ticket.getLevel()]+=ticket.getNum();
		}
    }
    bool canBuy(Station a,Station b,TicketLevel level){
       return getCost(a,b,level)>1e-4;
    }
    void startSale(Date date){
        onSale.insert(date);
	}
    void endSale(Date date){
        if(onSale.count(date))
            onSale.erase(date);
	}
    bool canSell(Date date){
        return onSale.count(date);
	}
    bool hasSold(Date date){
        return Sold.count(date);
    }
	string getID(){
		return id;
    }
    friend InputOfBinary& operator >> (InputOfBinary &cin,Train &train){
        cin>>train.id>>train.way>>train.date>>train.price>>train.restTicket>>train.onSale>>train.Sold;
        return cin;
    }
    friend OutputOfBinary& operator << (OutputOfBinary &cout,const Train &train){
        cout<<train.id<<train.way<<train.date<<train.price<<train.restTicket<<train.onSale<<train.Sold;
        return cout;
    }
};

}
#endif
