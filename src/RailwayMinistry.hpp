#pragma once
#include "FileManager.hpp"
#include "lib/map.hpp"
#include "lib/set.hpp"
#include "lib/vector.hpp"
#include "lib/algo.hpp"
#include "lib/Date.hpp"
#include "Train.hpp"
#include "Station.hpp"
using namespace sjtu;
class RailwayMinistry{
private:

	map<string,string>pwdMap;
	map<string,string>nameMap;
    map<string,int>adminMap;
    vector<Train>allTrain;
    map<string,Train>trainMap;
    map<pair<Station,Station>,set<string> >stTrain;
    map<string,vector<Ticket> >ticketMap;
public:
    vector<Train>getTrainByST(Station a,Station b,Date date){
        if(stTrain.count(make_pair(a,b))){
            set<string>tmp=stTrain[make_pair(a,b)];
            vector<Train>ans;
            for(auto id:tmp){
                Train train=getTrainByID(id);
                if(train.getStartTime()<=date)
                    ans.push_back(train);
            }
            return ans;
        }
        return vector<Train>();
	}
	Train getTrainByID(string id){
        return trainMap[id];
	}
	void addTrain(Train train){
        vector<Station>way=train.getWay();
        trainMap[train.getID()]=train;
        for(int i=0;i<way.size();i++){
            for(int j=i+1;j<way.size();j++){
                stTrain[make_pair(way[i],way[j])].insert(train.getID());
            }
        }
	}
	void updateTrain(Train train){
        removeTrain(train.getID());
        addTrain(train);
	}
	void removeTrain(string id){
        Train train=trainMap[id];
        vector<Station>way=train.getWay();
        trainMap.erase(id);
        for(int i=0;i<way.size();i++){
            for(int j=i+1;j<way.size();j++){
                stTrain[make_pair(way[i],way[j])].erase(train.getID());
            }
        }
	}
    void startSale(string id){
        trainMap[id].startSale();
	}
    bool endSale(string id){
        if(trainMap[id].hasSold()){
            return false;
        }
        trainMap[id].endSale();
        return true;
	}


    Ticket buyTicket(string id,string trainid,Station a,Station b,TicketLevel level){
        Ticket ticket=trainMap[trainid].buyTicket(a,b,level);
        ticketMap[id].push_back(ticket);
	}
	bool refund(string id,Ticket ticket){
        vector<Ticket>&tickets=ticketMap[id];
        if(find(tickets.begin(),tickets.end(),ticket)!=tickets.end()){
            tickets.erase(find(tickets.begin(),tickets.end(),ticket));
            return true;
        }
        return false;
	}
	bool updateInfo(string id,string pwd,string name){
		pwdMap[id]=pwd;
		nameMap[id]=name;
	}	
	bool isAdmin(string id){
		return adminMap.count(id);
	}
    bool isUser(string id,string pwd){
        if(pwdMap.count(id)&&pwd==pwdMap[id])
            return true;
        return false;
    }
    bool regiser(string id,string pwd,string name){
        if(pwdMap.count(id))
            return false;
        pwdMap[id]=pwd;
        nameMap[id]=name;
        return true;
    }

    void readFromFile(string input="data.bin"){
       InputOfBinary fin(input);
       fin>>pwdMap>>nameMap>>adminMap>>allTrain>>trainMap>>stTrain>>ticketMap;
    }
    void writeToFile(string output="data.bin"){
       OutputOfBinary fout(output);
       fout<<pwdMap<<nameMap<<adminMap<<allTrain<<trainMap<<stTrain<<ticketMap;
    }
};
