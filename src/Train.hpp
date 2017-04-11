#include "Staion.hpp"
#include "Ticket.hpp"
#include "lib/vector"
#include "lib/Date"
class Train{
private:
	string id;
	bool sale;
	vector<Station>way;
	vector<Date>date;
	vector<vector<double> >price;
	vector<vector<int> >restTicket;
public:
	Train(string _id,vector<Staion> _way,vector<Date>_date,vector<vector<double> >_price,vector<vector<int> >_restTicket):
		id(_id),way(_way),date(_date),price(_price),restTicket(_restTicket){sale=false;}
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
			if(way[i]==staion)
				return date[i];
		throw "No such station!";
	}
	int getRestTicket(Station a,Station b,TicketLevel level){
		int ans=int(2e9),start=0;
		for(int i=0;i<way.size();i++){
			if(way[i]==a)start=1;
			if(way[i]==b)break;
			if(start)
				ans=min(ans,restTicket[i]);
		}
		return ans;
	}
	void buyTicket(Station a,Station b,TicketLevel level,int num){
		int start=0;
		for(int i=0;i<way.size();i++){
			if(way[i]==a)start=1;
			if(way[i]==b)break;
			if(start)
				restTicket[i]-=num;
		}
	}
	void refundTicket(Station a,Station b,TicketLevel level,int num){
		int start=0;
		for(int i=0;i<way.size();i++){
			if(way[i]==a)start=1;
			if(way[i]==b)break;
			if(start)
				restTicket[i]+=num;
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
	string getID(){
		return id;
	}
};
