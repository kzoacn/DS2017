#pragma once

#include "Station.hpp"
#include "lib/Date.hpp"
#include <QString>
#include <QDebug>
#include <string>
//#include "Ticket.hpp"
namespace sjtu{
//#define tr QString::fromLocal8Bit

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
#define ZKY(x,y) if(QString::fromStdString(s)==QString::fromLocal8Bit(x))return y;

        ZKY("二等座",SECOND_SEAT);
        ZKY("一等座",FIRST_SEAT);
        ZKY("商务座",BUSINESS_SEAT);
        ZKY("特等座",SPECIAL_SEAT);
        ZKY("无座",NO_SEAT);
        ZKY("软座",SOFT_SEAT);
        ZKY("硬座",HARD_SEAT);
        ZKY("高级软卧",AD_SOFT_BED);
        ZKY("软卧下",SOFT_BED);
        ZKY("硬卧下",HARD_BED);
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
    static QString to_Qstring(TicketLevel level){
        if(level==SECOND_SEAT)return QString::fromLocal8Bit("二等座");
        if(level==FIRST_SEAT)return QString::fromLocal8Bit("一等座");
        if(level==BUSINESS_SEAT)return QString::fromLocal8Bit("商务座");
        if(level==SPECIAL_SEAT)return QString::fromLocal8Bit("特等座");
        if(level==NO_SEAT)return QString::fromLocal8Bit("无座");
        if(level==SOFT_SEAT)return QString::fromLocal8Bit("软座");
        if(level==HARD_SEAT)return QString::fromLocal8Bit("硬座");
        if(level==AD_SOFT_BED)return QString::fromLocal8Bit("高级软卧");
        if(level==SOFT_BED)return QString::fromLocal8Bit("软卧");
        if(level==HARD_BED)return QString::fromLocal8Bit("硬卧");
        return QString::fromLocal8Bit("处女座");
    }
    /*static QString to_Qstring(TicketLevel level){
        if(level==SECOND_SEAT)return tr("二等座");
        if(level==FIRST_SEAT)return tr("一等座");
        if(level==BUSINESS_SEAT)return tr("商务座");
        if(level==SPECIAL_SEAT)return tr("特等座");
        if(level==NO_SEAT)return tr("无座");
        if(level==SOFT_SEAT)return tr("软座");
        if(level==HARD_SEAT)return tr("硬座");
        if(level==AD_SOFT_BED)return tr("高级软卧");
        if(level==SOFT_BED)return tr("软卧");
        if(level==HARD_BED)return tr("硬卧");
        return tr("处女座");
    }*/
    bool operator==(const Ticket &oth)const{

        qDebug()<<(start==oth.start)<<'\n';
        qDebug()<<(target==oth.target)<<'\n';
        qDebug()<<(trainDate==oth.trainDate)<<'\n';

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
