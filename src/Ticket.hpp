#pragma once

#include "Station.hpp"
#include "lib/Date.hpp"
//#include "Ticket.hpp"
using namespace sjtu;
enum TicketLevel{
	SECOND_SEAT,//二等座
	FIRST_SEAT,//一等座
	BUSINESS_SEAT,//商务座
	SPECIAL_SEAT,//特等座
	NO_SEAT,//无座
	SOFT_SEAT,//软座
	HARD_SEAT//硬座
};

class Ticket{
private:
    TicketLevel level;
	string train;
	double cost;
	Station start,target;
    Date startDate,targetDate;
public:
	Ticket(){}
	Ticket(const Station &s,const Station &t,const double &c,const Date &sd,const Date &td,const string &tn,const TicketLevel &l):
        start(s),target(t),cost(c),startDate(sd),targetDate(td),train(tn),level(l){}
    bool operator==(const Ticket &oth)const{
        return level==oth.level&&train==oth.train
                &&cost==oth.cost&&start==oth.start
                &&target==oth.target
                &&startDate==oth.startDate
                &&targetDate==oth.targetDate;
    }
    const double& getCost()const{
		return cost;
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
};
