#pragma once

#include "Station.hpp"
#include "lib/Date.hpp"
#include <QString>
//#include "Ticket.hpp"
namespace sjtu{


enum TicketLevel{
    SECOND_SEAT=0,//二等座
	FIRST_SEAT,//一等座
	BUSINESS_SEAT,//商务座
	SPECIAL_SEAT,//特等座
	NO_SEAT,//无座
    SOFT_SEAT,//软座
    HARD_SEAT,//硬座
    AD_SOFT_BED,//高级软卧
    SOFT_BED,//软卧下
    HARD_BED//硬卧下
};

class Ticket{
private:
    int num;
    TicketLevel level;
	string train;
	double cost;
	Station start,target;
    Date startDate,targetDate;
    Date trainDate;
public:
    Ticket(){}
    Ticket(const Station &s,const Station &t,const Date &sd,const string &tn,const TicketLevel &l,const int &_num):
        start(s),target(t),trainDate(sd),train(tn),level(l),num(_num){}
    Ticket(const Station &s,const Station &t,const double &c,const Date &sd,const Date &td,const string &tn,const TicketLevel &l,const int &_num,const Date &_tD):
        start(s),target(t),cost(c),startDate(sd),targetDate(td),train(tn),level(l),num(_num),trainDate(_tD){}
    static TicketLevel toLevel(string s){
        if(QString::fromStdString(s)==QString::fromLocal8Bit("二等座"))return SECOND_SEAT;
        if(s=="一等座")return FIRST_SEAT;
        if(s=="商务座")return BUSINESS_SEAT;
        if(s=="特等座")return SPECIAL_SEAT;
        if(s=="无座")return NO_SEAT;
        if(s=="软座")return SOFT_SEAT;
        if(s=="硬座")return HARD_SEAT;
        if(s=="高级软卧")return AD_SOFT_BED;
        if(s=="软卧下")return SOFT_BED;
        if(s=="硬卧下")return HARD_BED;
        return NO_SEAT;
    }
    static TicketLevel toLevel(int x){
        if(x==0)return SECOND_SEAT;
        if(x==1)return FIRST_SEAT;
        if(x==2)return BUSINESS_SEAT;
        if(x==3)return SPECIAL_SEAT;
        if(x==4)return NO_SEAT;
        if(x==5)return SOFT_SEAT;
        if(x==6)return HARD_SEAT;
        if(x==7)return AD_SOFT_BED;
        if(x==8)return SOFT_BED;
        if(x==9)return HARD_BED;
        return NO_SEAT;
    }
    static string to_string(TicketLevel level){
        if(level==SECOND_SEAT)return "二等座";
        if(level==FIRST_SEAT)return "一等座";
        if(level==BUSINESS_SEAT)return "商务座";
        if(level==SPECIAL_SEAT)return "特等座";
        if(level==NO_SEAT)return "无座";
        if(level==SOFT_SEAT)return "软座";
        if(level==HARD_SEAT)return "硬座";
        if(level==AD_SOFT_BED)return "高级软卧";
        if(level==SOFT_BED)return "软卧";
        if(level==HARD_BED)return "硬卧";
        return "处女座";
    }
    bool operator==(const Ticket &oth)const{
        return level==oth.level&&train==oth.train
                &&start==oth.start
                &&target==oth.target
                &&trainDate==oth.trainDate;
    }
    Date getTrainDate()const{
        return trainDate;
    }
    const double& getCost()const{
        return cost;
    }
    const int& getNum()const{
        return num;
    }
	const string& getTrain()const{
		return train;
	}
	const Station& getStart()const{
		return start;
	}
	const Station& getTarget()const{
		return target;
	}
	TicketLevel getLevel()const{
		return level;
	}
	const Date& getStartDate()const{
		return startDate;
	}
	const Date& getTargetDate()const{
		return targetDate;
    }
    friend InputOfBinary& operator >> (InputOfBinary &cin,Ticket &ticket){
        int l;
        cin>>l>>ticket.train>>ticket.cost>>ticket.start>>ticket.target>>ticket.startDate>>ticket.targetDate>>ticket.num;
        ticket.level=(TicketLevel)l;
        return cin;
    }
    friend OutputOfBinary& operator << (OutputOfBinary &cout,const Ticket &ticket){
        cout<<int(ticket.level)<<ticket.train<<ticket.cost<<ticket.start<<ticket.target<<ticket.startDate<<ticket.targetDate<<ticket.num;
        return cout;
    }
};


}
