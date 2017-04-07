#include "Station.hpp"
#include "Date.hpp"
enum TicketLevel{
	SECOND_SEAT,//������
	FIRST_SEAT,//һ����
	BUSINESS_SEAT,//������
	SPECIAL_SEAT,//�ص���
	NO_SEAT,//����
	SOFT_SEAT,//����
	HARD_SEAT//Ӳ��
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
