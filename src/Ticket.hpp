#include "Station.hpp"
#include "Date.hpp"
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
	TickketLevel level;
	string train;
	double cost;
	Station start,target;
	Date stateDate,targetDate;
public:
	Ticket(){}
	Ticket(const Station &s,const Station &t,const double &c,const Date &sd,const Date &td,const string &tn,const TicketLevel &l):
		start(s),target(t),cost(c),sd(startDate),td(targetDate),tn(train),level(l){}
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
