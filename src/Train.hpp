#include "Staion.hpp"
#include "Ticket.hpp"
#include "lib/vector"

class Train{
private:
	string id;
	vector<Station>way;
	vector<Date>date;
	vector<vector<double> >price;
	vector<vector<int> >restTicket;
public:
	Station getStart(){
		return way.front();
	}
	Statoin getTarget(){
		return way.back();
	}
	vector<Station> getWay(){
		return way;
	}
	double getCost(Station a,Station b,TicketLevel level){
		//TODO
	}
	Date getTime(Station station){
		for(int i=0;i<way.size();i++)
			if(way[i]==staion)
				return date[i];
		throw "No such station!";
	}
	int getRestTicket(Station a,Station b,TicketLevel level){
	
	}
	void buyTicket(Station a,Station b,TicketLevel level,int num){
	
	}
	void refundTicket(Station a,Station b,TicketLevel level,int num){
	
	}
	void startSale(){
	
	}
	void endSale(){
	
	}
	bool canSell(){
	
	}
	string getID(){
		return id;
	}
};
