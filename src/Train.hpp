#pragma once

#include "Station.hpp"
#include "Ticket.hpp"
#include "lib/vector.hpp"
#include "lib/Date.hpp"
#include "FileManager.hpp"
class Train{
private:
	string id;
    bool sale,isSold;
	vector<Station>way;
	vector<Date>date;
	vector<vector<double> >price;
	vector<vector<int> >restTicket;
public:
    Train(){}
    Train(string _id,vector<Station> _way,vector<Date>_date,vector<vector<double> >_price,vector<vector<int> >_restTicket):
        id(_id),way(_way),date(_date),price(_price),restTicket(_restTicket){sale=isSold=false;}
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
				x=price[int(level)][i];
			}
			if(way[i]==b){
				y=price[int(level)][i];
			}
		}
		return y-x;
    }
    Date getTime(Station station){
        for(int i=0;i<way.size();i++)
            if(way[i]==station)
                return date[i];
        throw "No such station!";
    }
    Date getStartTime(){
        return date.front();
    }
	int getRestTicket(Station a,Station b,TicketLevel level){
		int ans=int(2e9),start=0;
		for(int i=0;i<way.size();i++){
			if(way[i]==a)start=1;
			if(way[i]==b)break;
			if(start)
                ans=min(ans,restTicket[i][level]);
		}
		return ans;
	}
    Ticket buyTicket(Station a,Station b,TicketLevel level){
        isSold=true;
		int start=0;
		for(int i=0;i<way.size();i++){
			if(way[i]==a)start=1;
			if(way[i]==b)break;
			if(start)
                restTicket[i][level]--;
		}
        return Ticket(a,b,getCost(a,b,level),getTime(a),getTime(b),id,level);
	}
	void refundTicket(Station a,Station b,TicketLevel level,int num){
		int start=0;
		for(int i=0;i<way.size();i++){
			if(way[i]==a)start=1;
			if(way[i]==b)break;
			if(start)
                restTicket[i][level]+=num;
		}
	}
	void startSale(){
		sale=true;
	}
	void endSale(){
		sale=false;
	}
	bool canSell(){
		return sale;
	}
    bool hasSold(){
        return isSold;
    }
	string getID(){
		return id;
    }
    friend InputOfBinary& operator >> (InputOfBinary &cin,Train &train){
        cin>>train.id>>train.sale>>train.isSold>>train.way>>train.date>>train.price>>train.restTicket;
        return cin;
    }
    friend OutputOfBinary& operator << (OutputOfBinary &cout,const Train &train){
        cout<<train.id<<train.sale<<train.isSold<<train.way<<train.date<<train.price<<train.restTicket;
        return cout;
    }
};
