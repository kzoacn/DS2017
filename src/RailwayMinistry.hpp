#pragma once
#include "FileManager.hpp"
#include "lib/map.hpp"
#include "lib/set.hpp"
#include "lib/vector.hpp"
#include "lib/algo.hpp"
#include "lib/Date.hpp"
#include "lib/shared_ptr.hpp"
#include "Train.hpp"
#include "Station.hpp"
#include "CSVParser.hpp"
#include <iostream>
#include "Log.hpp"
namespace sjtu{

class RailwayMinistry{
private:

	map<string,string>pwdMap;
	map<string,string>nameMap;
    map<string,int>adminMap;
    vector<Train>allTrain;
    map<string,Train>trainMap;
    map<pair<Station,Station>,set<string> >stTrain;
    map<string,vector<Ticket> >ticketMap;
    vector<Log>Logs;
public:
    vector<Train>getTrainByST(Station a,Station b,Date date){
        if(stTrain.count(make_pair(a,b))){
            set<string>tmp=stTrain[make_pair(a,b)];
            vector<Train>ans;
            for(auto id:tmp){
                Train train=getTrainByID(id);
                if(train.canSell(date))
                    ans.push_back(train);
            }
            return ans;
        }
        return vector<Train>();
    }
    vector<Train>getTrainBySTForAdmin(Station a,Station b,Date date){
        if(stTrain.count(make_pair(a,b))){
            set<string>tmp=stTrain[make_pair(a,b)];
            vector<Train>ans;
            for(auto id:tmp){
                Train train=getTrainByID(id);
                ans.push_back(train);
            }
            return ans;
        }
        return vector<Train>();
    }
    Train getTrainByID(string id){
        return trainMap[id];
    }
    bool existTrain(string id){
        return trainMap.count(id);
    }
    string getName(string id){
        return nameMap[id];
    }
	void addTrain(Train train){
        if(trainMap.count(train.getID()))
            return ;
        vector<Station>way=train.getWay();
        trainMap[train.getID()]=train;
        for(int i=0;i<way.size();i++){
            for(int j=i+1;j<way.size();j++){
                stTrain[make_pair(way[i],way[j])].insert(train.getID());
            }
        }
    }
    void addTrainFromCSV(ifstream &fin){
        shared_ptr<CSVParser> csv(new CSVParser());
        vector<Train>trains=csv->process(fin);
        for(auto &x:trains)
            addTrain(x);
    }
    void exportLog(ofstream &fout){
        for(auto x:Logs){
            fout<<x.to_string()<<'\n';
            qDebug()<<QString::fromStdString(x.to_string())<<'\n';
        }
        fout.close();
    }
    void addLogFromFile(ifstream &fin){
        shared_ptr<CSVParser> csv(new CSVParser());
        vector<Log>newLogs=csv->processLog(fin);
        int T=0;
        for(auto &x:newLogs){
            if(!nameMap.count(x.id)){
                nameMap[x.id]=x.name;
                pwdMap[x.id]="000000";
            }
            T++;
            if(T%10000==0)
                qDebug()<<T/10000<<'\n';
            if(x.ty==1){
                buyTicket(x.id,x.ticket.getTrain(),x.ticket.getStart(),x.ticket.getTarget(),x.ticket.getLevel(),x.ticket.getNum(),x.ticket.getTrainDate());
            }else{
                refund(x.id,x.ticket);
            }
        }
    }

	void updateTrain(Train train){
        removeTrain(train.getID());
        addTrain(train);
	}
    bool removeTrain(string id){
        if(!trainMap.count(id)||trainMap[id].hasSold())
            return false;
        Train train=trainMap[id];
        vector<Station>way=train.getWay();
        trainMap.erase(id);
        for(int i=0;i<way.size();i++){
            for(int j=i+1;j<way.size();j++){
                stTrain[make_pair(way[i],way[j])].erase(train.getID());
            }
        }
        return true;
	}
    void startSale(string id,Date date){
        trainMap[id].startSale(date);
	}
    bool hasSold(string id,Date date){
        return trainMap[id].hasSold(date);
    }

    bool endSale(string id,Date date){
        if(trainMap[id].hasSold(date)){
            return false;
        }
        trainMap[id].endSale(date);
        return true;
	}
    bool canSell(string id,Date date){
        trainMap[id].init(date);
        if(trainMap[id].canSell(date))
            return true;
        return false;
    }


    pair<Ticket,bool> buyTicket(string id,string trainid,Station a,Station b,TicketLevel level,int num,Date date){
        if(!trainMap.count(trainid))
            return make_pair(Ticket(),false);
        Train &train=trainMap[trainid];
        train.init(date);
        if(!train.canBuy(a,b,level)||!train.canSell(date)||train.getRestTicket(a,b,level,date)==0)
            return make_pair(Ticket(),false);
        Ticket ticket=train.buyTicket(a,b,level,num,date);
        ticketMap[id].push_back(ticket);
        Logs.push_back(Log(id,nameMap[id],1,ticket));
        return make_pair(ticket,true);
	}
	bool refund(string id,Ticket ticket){
        vector<Ticket>&tickets=ticketMap[id];

        if(find(tickets.begin(),tickets.end(),ticket)!=tickets.end()){
            tickets.erase(find(tickets.begin(),tickets.end(),ticket));
            Logs.push_back(Log(id,nameMap[id],0,ticket));
            return true;
        }
        return false;
	}
    vector<Ticket> queryTicket(string id){
        return ticketMap[id];
    }
	bool updateInfo(string id,string pwd,string name){
		pwdMap[id]=pwd;
		nameMap[id]=name;
	}	
    bool isAdmin(string id){
        if(adminMap.count(id))
            return true;
        return false;
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
       if(fin){
           fin>>pwdMap>>nameMap>>adminMap>>allTrain>>trainMap>>stTrain>>ticketMap>>Logs;
       }else{
           writeToFile(input);
       }

       //for test
       pwdMap["admin"]="admin";
       nameMap["admin"]="admin";
       adminMap["admin"]=1;
       pwdMap["user"]="user";
       nameMap["user"]="user";

    }
    void writeToFile(string output="data.bin"){
       OutputOfBinary fout(output);
       fout<<pwdMap<<nameMap<<adminMap<<allTrain<<trainMap<<stTrain<<ticketMap<<Logs;
    }
    ~RailwayMinistry(){
        writeToFile();
    }
};

}
