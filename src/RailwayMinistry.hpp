class RailwayMinistry{
private:

	map<string,string>pwdMap;
	map<string,string>nameMap;
	map<string,bool>adminMap;
	vector<Train>allTrain;
	
public:
	vector<Train>getTrainByST(Station a,Station b,Date date){
	
	}
	Train getTrainByID(string id){
	
	}
	void addTrain(Train train){
	
	}
	void updateTrain(Train train){
	
	}
	void removeTrain(string id){
	
	}
	void startSale(string id){
	
	}
	void endSale(string id){
	
	}
	vector<Ticket> queryTicket(string id){
	
	}
	string queryInfo(string id){
	
	}
	bool buyTicket(string id,string trainid,Station a,Station b,TicketLevel levle,int num){
	
	}
	bool refund(string id,Ticket ticket){
		
	}
	bool updateInfo(string id,string pwd,string name){
		pwdMap[id]=pwd;
		nameMap[id]=name;
	}	
	bool isAdmin(string id){
		return adminMap.count(id);
	}
};
