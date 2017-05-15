

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QString>
#include "src/RailwayMinistry.hpp"
#include "src/Station.hpp"
#include <QMessageBox>
#include "minewindow.h"
#define tr QString::fromLocal8Bit
using namespace sjtu;
using std::to_string;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load(string _id, shared_ptr<RailwayMinistry> _rm){
    user=User(_id,_rm);
}

void MainWindow::on_search_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(16);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("车次"));
    model->setHeaderData(1,Qt::Horizontal,tr("起点"));
    model->setHeaderData(2,Qt::Horizontal,tr("终点"));
    model->setHeaderData(3,Qt::Horizontal,tr("出发时间"));
    model->setHeaderData(4,Qt::Horizontal,tr("到达时间"));
    model->setHeaderData(5,Qt::Horizontal,tr("经过时间"));
    model->setHeaderData(6,Qt::Horizontal,tr("二等座"));
    model->setHeaderData(7,Qt::Horizontal,tr("一等座"));
    model->setHeaderData(8,Qt::Horizontal,tr("商务座"));
    model->setHeaderData(9,Qt::Horizontal,tr("特等座"));
    model->setHeaderData(10,Qt::Horizontal,tr("无座"));
    model->setHeaderData(11,Qt::Horizontal,tr("软座"));
    model->setHeaderData(12,Qt::Horizontal,tr("硬座"));
    model->setHeaderData(13,Qt::Horizontal,tr("高级软卧"));
    model->setHeaderData(14,Qt::Horizontal,tr("软卧下"));
    model->setHeaderData(15,Qt::Horizontal,tr("硬卧下"));
    Station a,b;
    a=Station(ui->start->text().toStdString());
    b=Station(ui->target->text().toStdString());
    Date date(ui->dateEdit->date());
    //date=Date::fromDay(ui->date->text().toStdString());
    vector<Train>trains=user.getTrainByST(a,b,date);
    for(int i=0;i<trains.size();i++){
        model->setItem(i,0,new QStandardItem(QString::fromStdString(trains[i].getID())));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(a.getName())));
        model->setItem(i,2,new QStandardItem(QString::fromStdString(b.getName())));
        model->setItem(i,3,new QStandardItem(QString::fromStdString(trains[i].getTime(date,a).to_string())));
        model->setItem(i,4,new QStandardItem(QString::fromStdString(trains[i].getTime(date,b).to_string())));
        model->setItem(i,5,new QStandardItem(QString::fromStdString(to_string((trains[i].getTime(date,b)-trains[i].getTime(date,a))))));
        for(int l=0;l<10;l++){
            if(trains[i].getCost(a,b,Ticket::toLevel(l))==0)
                model->setItem(i,6+l,new QStandardItem("-"));
            else
                model->setItem(i,6+l,new QStandardItem(QString::fromStdString(to_string((trains[i].getCost(a,b,Ticket::toLevel(l)))))));
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}



void MainWindow::on_train_query_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(13);
    model->setHeaderData(0,Qt::Horizontal,tr("站点"));
    model->setHeaderData(1,Qt::Horizontal,tr("时间"));
    model->setHeaderData(2,Qt::Horizontal,tr("二等座"));
    model->setHeaderData(3,Qt::Horizontal,tr("一等座"));
    model->setHeaderData(4,Qt::Horizontal,tr("商务座"));
    model->setHeaderData(5,Qt::Horizontal,tr("特等座"));
    model->setHeaderData(6,Qt::Horizontal,tr("无座"));
    model->setHeaderData(7,Qt::Horizontal,tr("软座"));
    model->setHeaderData(8,Qt::Horizontal,tr("硬座"));
    model->setHeaderData(9,Qt::Horizontal,tr("高级软卧"));
    model->setHeaderData(10,Qt::Horizontal,tr("软卧下"));
    model->setHeaderData(11,Qt::Horizontal,tr("硬卧下"));
    Train train=user.getTrainByID(ui->train_number->text().toStdString());
    Date date(ui->dateEdit->date());
    //date=Date::fromDay(ui->date->text().toStdString());

    for(int i=0;i<train.getWay().size();i++){
        Station a=train.getWay()[i];
        model->setItem(i,0,new QStandardItem(QString::fromStdString(a.getName())));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(train.getTime(date,a).to_string())));
        for(int l=0;l<10;l++){
            if(train.getCost(train.getStart(),a,Ticket::toLevel(l))==0)
                model->setItem(i,2+l,new QStandardItem("-"));
            else
                model->setItem(i,2+l,new QStandardItem(QString::fromStdString(to_string((train.getCost(train.getStart(),a,Ticket::toLevel(l)))))));
        }
    }

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}

void MainWindow::on_buy_clicked()
{
    int row=ui->tableView->currentIndex().row();
    int col=ui->tableView->currentIndex().column();
    string trainid = (ui->tableView->model()->index(row,0,QModelIndex()).data())
                                .toString().toStdString();
    Station a,b;
    a=Station(ui->start->text().toStdString());
    b=Station(ui->target->text().toStdString());
    Date date(ui->dateEdit->date());
    //date=Date::fromDay(ui->date->text().toStdString());
    TicketLevel level=Ticket::toLevel(ui->tableView->model()->headerData(col,Qt::Horizontal).toString().toStdString());
    bool succ=user.buyTicket(trainid,a,b,level,1,date).second;
    if(succ)
        QMessageBox::information(NULL, tr("提示"), tr("购票成功"));
    else
        QMessageBox::information(NULL, tr("提示"), tr("购票失败..."));
}


void MainWindow::on_mine_clicked()
{
    MineWindow *mine=new MineWindow(this);
    mine->load(user.id,user.rw);
    mine->show();
}

void MainWindow::on_special_clicked()
{
/*
    int num;
    TicketLevel level;
    string train;
    double cost;
    Station start,target;
    Date startDate,targetDate;
    Date trainDate;
*/
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(8);
    model->setHeaderData(0,Qt::Horizontal,tr("车次"));
    model->setHeaderData(1,Qt::Horizontal,tr("起点"));
    model->setHeaderData(2,Qt::Horizontal,tr("终点"));
    model->setHeaderData(3,Qt::Horizontal,tr("出发时间"));
    model->setHeaderData(4,Qt::Horizontal,tr("到达时间"));
    model->setHeaderData(5,Qt::Horizontal,tr("经过时间"));
    model->setHeaderData(6,Qt::Horizontal,tr("座位类型"));
    model->setHeaderData(7,Qt::Horizontal,tr("费用"));
    Station a,b;
    a=Station(ui->start->text().toStdString());
    b=Station(ui->target->text().toStdString());
    Date date(ui->dateEdit->date());
    vector<Ticket>tickets=user.queryPath(a,b,date);
    for(int i=0;i<tickets.size();i++){
        Ticket tic=tickets[i];
        model->setItem(i,0,new QStandardItem(QString::fromStdString(tic.getTrain())));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(tic.getStart().getName())));
        model->setItem(i,2,new QStandardItem(QString::fromStdString(tic.getTarget().getName())));
        model->setItem(i,3,new QStandardItem(QString::fromStdString(tic.getStartDate().to_string())));
        model->setItem(i,4,new QStandardItem(QString::fromStdString(tic.getTargetDate().to_string())));
        model->setItem(i,5,new QStandardItem(QString::fromStdString(to_string((tic.getTargetDate()-tic.getStartDate())))));
        model->setItem(i,6,new QStandardItem((Ticket::to_Qstring(tic.getLevel()))));
        model->setItem(i,7,new QStandardItem(QString::fromStdString(to_string(tic.getCost()))));
    }
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
